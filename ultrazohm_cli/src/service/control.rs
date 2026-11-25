//! Persistent client connections and a serialized command queue.
//!
//! Each client connection is served by one thread that reads requests in order
//! and writes each reply before reading the next. Only complete, validated
//! requests reach the service owner. A Stop request cancels queued device
//! commands under the same lock used to select the next command for execution.
use super::{
    Operation,
    session::{Reply, State, serve_data_query},
    wire::{
        Request, coded, decode_request, error_reply, finish_after_reply, ok_reply, read_message,
        write_reply,
    },
};
use anyhow::{Result, anyhow};
use std::{
    collections::VecDeque,
    io::{BufRead, BufReader},
    net::{TcpListener, TcpStream},
    sync::{
        Arc, Condvar, Mutex,
        atomic::{AtomicBool, AtomicUsize, Ordering},
        mpsc,
    },
    thread,
    time::Duration,
};

const MAX_CLIENTS: usize = 64;
const MAX_DATA_QUERIES: usize = 4;
// How long a final reply may wait for the client to read it before its socket
// closes; bounds the acceptor thread for rejected clients.
const FINAL_REPLY_LINGER: Duration = Duration::from_millis(100);

pub(super) struct Pending {
    pub request: Request,
    pub reply: mpsc::Sender<Result<Reply>>,
}

#[derive(Default)]
struct QueueState {
    pending: VecDeque<Pending>,
    closed: bool,
}

#[derive(Default)]
struct RequestQueue {
    state: Mutex<QueueState>,
    ready: Condvar,
}

impl RequestQueue {
    fn submit(&self, request: Request) -> mpsc::Receiver<Result<Reply>> {
        let (reply, receiver) = mpsc::channel();
        let mut state = self.state.lock().unwrap();
        if state.closed {
            let _ = reply.send(Err(coded("shutting_down", "service is shutting down")));
        } else {
            let stop = matches!(request.command, Operation::Stop);
            if stop {
                // Stop supersedes queued device commands and executes next;
                // queued reads, logging control and shutdown keep their order after it.
                let (canceled, kept) = state
                    .pending
                    .drain(..)
                    .partition::<Vec<_>, _>(|p| p.request.command.superseded_by_stop());
                state.pending = kept.into();
                for pending in canceled {
                    // A caller that already disconnected needs no notification.
                    let _ = pending.reply.send(Err(coded(
                        "canceled_by_stop",
                        "request canceled by Stop before execution",
                    )));
                }
            }
            let pending = Pending { request, reply };
            if stop {
                state.pending.push_front(pending);
            } else {
                state.pending.push_back(pending);
            }
            self.ready.notify_one();
        }
        receiver
    }

    fn next(&self, timeout: Duration) -> Option<Pending> {
        let state = self.state.lock().unwrap();
        let (mut state, _) = self
            .ready
            .wait_timeout_while(state, timeout, |s| s.pending.is_empty() && !s.closed)
            .unwrap();
        state.pending.pop_front()
    }

    fn close(&self) {
        let mut state = self.state.lock().unwrap();
        state.closed = true;
        for pending in state.pending.drain(..) {
            let _ = pending
                .reply
                .send(Err(coded("shutting_down", "service is shutting down")));
        }
        self.ready.notify_all();
    }
}

/// Read the next request line. Idle connections wait until `stop` is set; a
/// started request must complete within two seconds. `Err` carries the request
/// id when it could be read, for the error reply.
#[allow(clippy::type_complexity)]
fn read_request(
    reader: &mut impl BufRead,
    stop: &AtomicBool,
) -> std::result::Result<Option<Request>, (Option<u64>, anyhow::Error)> {
    match read_message(reader, Duration::from_secs(2), Some(stop)) {
        Ok(None) => Ok(None),
        Ok(Some(line)) => decode_request(&line).map(Some),
        Err(error) => Err((None, error)),
    }
}

// Hold a slot from request admission until the complete data response is sent.
struct QuerySlot(Arc<AtomicUsize>);
impl QuerySlot {
    fn acquire(count: &Arc<AtomicUsize>) -> Result<Self> {
        count
            .fetch_update(Ordering::SeqCst, Ordering::SeqCst, |n| {
                (n < MAX_DATA_QUERIES).then_some(n + 1)
            })
            .map_err(|_| {
                coded(
                    "busy",
                    "too many concurrent data queries; retry after a current query finishes",
                )
            })?;
        Ok(Self(count.clone()))
    }
}
impl Drop for QuerySlot {
    fn drop(&mut self) {
        self.0.fetch_sub(1, Ordering::SeqCst);
    }
}

/// Serve one client until it disconnects, sends an invalid request, or the
/// service stops. Replies are written in request order.
fn serve_client(
    socket: TcpStream,
    queue: &RequestQueue,
    queries: &Arc<AtomicUsize>,
    stop: &AtomicBool,
) -> Result<()> {
    // Windows accepted sockets inherit the nonblocking listener mode. Short read
    // timeouts let idle connections notice shutdown.
    socket.set_nonblocking(false)?;
    socket.set_nodelay(true)?;
    socket.set_read_timeout(Some(Duration::from_millis(200)))?;
    socket.set_write_timeout(Some(Duration::from_secs(5)))?;
    let mut writer = socket.try_clone()?;
    let mut reader = BufReader::new(socket);
    loop {
        let request = match read_request(&mut reader, stop) {
            Ok(Some(request)) => request,
            Ok(None) => return Ok(()),
            Err((id, error)) => {
                // Framing is lost after an invalid message: report it and close.
                write_reply(&mut writer, &error_reply(id, &error))?;
                finish_after_reply(&writer, FINAL_REPLY_LINGER);
                return Ok(());
            }
        };
        let id = request.id;
        let result = (|| -> Result<(Reply, Option<QuerySlot>)> {
            let slot = matches!(request.command, Operation::ReadData { .. })
                .then(|| QuerySlot::acquire(queries))
                .transpose()?;
            let reply = queue
                .submit(request)
                .recv()
                .map_err(|_| anyhow!("service ended before replying"))??;
            Ok((reply, slot))
        })();
        match result {
            Ok((Reply::Data(view, query), _slot)) => {
                serve_data_query(&mut writer, id, *view, query)?
            }
            Ok((Reply::Json(value), _)) => write_reply(&mut writer, &ok_reply(Some(id), value))?,
            Err(error) => write_reply(&mut writer, &error_reply(Some(id), &error))?,
        }
        // A busy client never idles long enough to observe shutdown in
        // read_request; close after its current reply so the service can exit.
        if stop.load(Ordering::SeqCst) {
            return Ok(());
        }
    }
}

fn reject(mut socket: TcpStream) {
    // Best effort and bounded: never block the acceptor on an overloaded client.
    let _ = socket.set_nonblocking(false);
    let _ = socket.set_write_timeout(Some(FINAL_REPLY_LINGER));
    let busy = coded("busy", format!("too many clients (limit {MAX_CLIENTS})"));
    if write_reply(&mut socket, &error_reply(None, &busy)).is_ok() {
        finish_after_reply(&socket, FINAL_REPLY_LINGER);
    }
}

pub(super) struct ControlServer {
    queue: Arc<RequestQueue>,
    shutdown: Arc<AtomicBool>,
    worker: Option<thread::JoinHandle<Result<()>>>,
}

impl ControlServer {
    pub fn new(
        listener: TcpListener,
        shutdown: Arc<AtomicBool>,
        health: Arc<Mutex<State>>,
    ) -> Result<Self> {
        let queue = Arc::new(RequestQueue::default());
        let requests = queue.clone();
        let stopped = shutdown.clone();
        let worker = thread::Builder::new()
            .name("uz-control".into())
            .spawn(move || {
                let queries = Arc::new(AtomicUsize::new(0));
                let mut clients: Vec<thread::JoinHandle<()>> = Vec::new();
                let result = (|| -> Result<()> {
                    while !stopped.load(Ordering::SeqCst) {
                        clients.retain(|client| !client.is_finished());
                        match listener.accept() {
                            Ok((socket, _)) if clients.len() < MAX_CLIENTS => {
                                let queue = requests.clone();
                                let queries = queries.clone();
                                let stop = stopped.clone();
                                clients.push(
                                    thread::Builder::new().name("uz-client".into()).spawn(
                                        move || {
                                            if let Err(error) =
                                                serve_client(socket, &queue, &queries, &stop)
                                            {
                                                eprintln!("Control client: {error:#}");
                                            }
                                        },
                                    )?,
                                );
                            }
                            Ok((socket, _)) => reject(socket),
                            // Connections are persistent, so accept latency is paid once per client.
                            Err(error) if error.kind() == std::io::ErrorKind::WouldBlock => {
                                thread::sleep(Duration::from_millis(5));
                            }
                            Err(error) => return Err(error.into()),
                        }
                    }
                    Ok(())
                })();
                if let Err(error) = &result {
                    health
                        .lock()
                        .unwrap()
                        .error
                        .get_or_insert_with(|| format!("control transport: {error:#}"));
                }
                stopped.store(true, Ordering::SeqCst);
                requests.close();
                drop(listener);
                for client in clients {
                    if client.join().is_err() {
                        eprintln!("Control client thread panicked");
                    }
                }
                result
            })?;
        Ok(Self {
            queue,
            shutdown,
            worker: Some(worker),
        })
    }

    pub fn invalidate_session(&self) {
        let mut state = self.queue.state.lock().unwrap();
        let (cancel, keep) = state
            .pending
            .drain(..)
            .partition::<Vec<_>, _>(|p| !p.request.command.survives_session_replacement());
        state.pending = keep.into();
        for p in cancel {
            let _ = p.reply.send(Err(coded(
                "session_replaced",
                "acquisition session changed before execution",
            )));
        }
    }

    pub fn next(&self, timeout: Duration) -> Option<Pending> {
        self.queue.next(timeout)
    }

    pub fn finish(mut self) -> Result<()> {
        self.shutdown.store(true, Ordering::SeqCst);
        self.queue.close();
        self.worker
            .take()
            .expect("control worker joined once")
            .join()
            .map_err(|_| anyhow!("control connection worker panicked"))?
    }
}

impl Drop for ControlServer {
    fn drop(&mut self) {
        self.shutdown.store(true, Ordering::SeqCst);
        self.queue.close();
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use serde_json::json;
    use std::io::{Read, Write};

    fn request(command: Operation) -> Request {
        Request { id: 1, command }
    }

    const WAIT: Duration = Duration::from_millis(10);

    #[test]
    fn rejected_client_receives_busy() {
        let listener = TcpListener::bind("127.0.0.1:0").unwrap();
        let endpoint = listener.local_addr().unwrap().to_string();
        let server = thread::spawn(move || reject(listener.accept().unwrap().0));
        let error = crate::service::request(&endpoint, Operation::Status).unwrap_err();
        server.join().unwrap();
        assert_eq!(crate::service::client_error_code(&error), Some("busy"));
        assert!(error.to_string().contains("too many clients"));
    }

    #[test]
    fn rejection_ends_with_a_clean_close() {
        // The rejected request is never read. Closing a socket with unread
        // input sends a reset, and Windows clients then discard the reply
        // they already received; Linux shows the reset on the next read.
        let listener = TcpListener::bind("127.0.0.1:0").unwrap();
        let mut client = TcpStream::connect(listener.local_addr().unwrap()).unwrap();
        client
            .write_all(b"{\"version\":4,\"id\":1,\"op\":\"status\"}\n")
            .unwrap();
        reject(listener.accept().unwrap().0);
        let mut reader = BufReader::new(client);
        let mut line = String::new();
        reader.read_line(&mut line).unwrap();
        let reply: serde_json::Value = serde_json::from_str(&line).unwrap();
        assert_eq!(reply["error"]["code"], "busy");
        let end = reader.read(&mut [0u8; 1]);
        assert!(
            matches!(end, Ok(0)),
            "expected end of stream, not a reset: {end:?}"
        );
    }

    #[test]
    fn concurrent_stops_are_all_executed() {
        let queue = RequestQueue::default();
        let running = queue.submit(request(Operation::Status));
        let in_flight = queue.next(WAIT).unwrap();
        let first = queue.submit(request(Operation::Stop));
        let second = queue.submit(request(Operation::Stop));
        assert!(in_flight.reply.send(Ok(Reply::Json(json!({})))).is_ok());
        assert!(running.recv().unwrap().is_ok());
        for _ in 0..2 {
            let next = queue.next(WAIT).unwrap();
            assert!(matches!(next.request.command, Operation::Stop));
            assert!(next.reply.send(Ok(Reply::Json(json!({})))).is_ok());
        }
        assert!(first.recv().unwrap().is_ok());
        assert!(second.recv().unwrap().is_ok());
        assert!(queue.next(WAIT).is_none());
    }

    #[test]
    fn stop_jumps_ahead_cancels_device_commands_and_preserves_reads() {
        let queue = RequestQueue::default();
        let running = queue.submit(request(Operation::Status));
        let in_flight = queue.next(WAIT).unwrap();
        let enable = queue.submit(request(Operation::EnableSystem));
        let read = queue.submit(request(Operation::Jobs));
        let logging = queue.submit(request(Operation::StopLogging {
            stream: crate::data::Stream::Fast,
        }));
        let shutdown = queue.submit(request(Operation::Shutdown));
        let control = queue.submit(request(Operation::EnableControl));
        let stop = queue.submit(request(Operation::Stop));
        let later = queue.submit(request(Operation::Status));
        for canceled in [enable, control] {
            let error = canceled.recv().unwrap().err().unwrap();
            assert_eq!(
                error.to_string(),
                "request canceled by Stop before execution"
            );
            assert_eq!(super::super::error_code(&error), Some("canceled_by_stop"));
        }
        assert!(in_flight.reply.send(Ok(Reply::Json(json!({})))).is_ok());
        assert!(running.recv().unwrap().is_ok());
        // Stop runs next, ahead of the read that was queued before it.
        let next = queue.next(WAIT).unwrap();
        assert!(matches!(next.request.command, Operation::Stop));
        assert!(next.reply.send(Ok(Reply::Json(json!({})))).is_ok());
        assert!(stop.recv().unwrap().is_ok());
        let next = queue.next(WAIT).unwrap();
        assert!(matches!(next.request.command, Operation::Jobs));
        assert!(next.reply.send(Ok(Reply::Json(json!({})))).is_ok());
        assert!(read.recv().unwrap().is_ok());
        let next = queue.next(WAIT).unwrap();
        assert!(matches!(
            next.request.command,
            Operation::StopLogging { .. }
        ));
        assert!(next.reply.send(Ok(Reply::Json(json!({})))).is_ok());
        assert!(logging.recv().unwrap().is_ok());
        let next = queue.next(WAIT).unwrap();
        assert!(matches!(next.request.command, Operation::Shutdown));
        assert!(next.reply.send(Ok(Reply::Json(json!({})))).is_ok());
        assert!(shutdown.recv().unwrap().is_ok());
        let next = queue.next(WAIT).unwrap();
        assert!(matches!(next.request.command, Operation::Status));
        assert!(next.reply.send(Ok(Reply::Json(json!({})))).is_ok());
        assert!(later.recv().unwrap().is_ok());
        assert!(queue.next(WAIT).is_none());
    }

    #[test]
    fn repeated_stop_and_shutdown_notify_every_waiting_caller() {
        let queue = RequestQueue::default();
        let first = queue.submit(request(Operation::Stop));
        let second = queue.submit(request(Operation::Stop));
        assert_eq!(queue.state.lock().unwrap().pending.len(), 2);
        queue.close();
        assert!(first.recv().unwrap().is_err());
        assert!(second.recv().unwrap().is_err());
        assert!(
            queue
                .submit(request(Operation::EnableControl))
                .recv()
                .unwrap()
                .is_err()
        );
        assert!(queue.next(WAIT).is_none());
    }
}

#[cfg(test)]
mod lifecycle_regressions {
    use super::*;
    #[test]
    fn guarded_shutdown_survives_session_replacement() {
        let queue = Arc::new(RequestQueue::default());
        let server = ControlServer {
            queue: queue.clone(),
            shutdown: Arc::new(AtomicBool::new(false)),
            worker: None,
        };
        let guarded = queue.submit(Request {
            id: 1,
            command: Operation::OwnedShutdown {
                service_id: "owned".into(),
            },
        });
        server.invalidate_session();
        assert!(matches!(guarded.try_recv(), Err(mpsc::TryRecvError::Empty)));
        assert!(matches!(
            queue.next(Duration::ZERO).unwrap().request.command,
            Operation::OwnedShutdown { .. }
        ));
    }
}
