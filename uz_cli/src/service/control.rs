//! Bounded connection workers and a serialized command queue.
//!
//! Only complete, validated requests reach the service owner. Stop cancels the
//! queue under the same lock used to select the next command for execution.
use super::{Operation, Reply, Request, State, read_request, serve_data_query};
use anyhow::{Context, Result, anyhow};
use serde_json::json;
use std::{
    collections::VecDeque,
    io::Write,
    net::{TcpListener, TcpStream},
    sync::{
        Arc, Mutex,
        atomic::{AtomicBool, AtomicUsize, Ordering},
        mpsc,
    },
    thread,
    time::Duration,
};

const MAX_CLIENTS: usize = 64;
const MAX_DATA_QUERIES: usize = 4;

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
struct RequestQueue(Mutex<QueueState>);

impl RequestQueue {
    fn submit(&self, request: Request) -> mpsc::Receiver<Result<Reply>> {
        let (reply, receiver) = mpsc::channel();
        let mut state = self.0.lock().unwrap();
        if state.closed {
            let _ = reply.send(Err(anyhow!("service is shutting down")));
        } else {
            if matches!(request.command, Operation::Stop) {
                for pending in state.pending.drain(..) {
                    let _ = pending
                        .reply
                        .send(Err(anyhow!("request canceled by Stop before execution")));
                }
            }
            state.pending.push_back(Pending { request, reply });
        }
        receiver
    }

    fn next(&self) -> Option<Pending> {
        self.0.lock().unwrap().pending.pop_front()
    }

    fn close(&self) {
        let mut state = self.0.lock().unwrap();
        state.closed = true;
        for pending in state.pending.drain(..) {
            let _ = pending.reply.send(Err(anyhow!("service is shutting down")));
        }
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
                anyhow!("too many concurrent data queries; retry after a current query finishes")
            })?;
        Ok(Self(count.clone()))
    }
}
impl Drop for QuerySlot {
    fn drop(&mut self) {
        self.0.fetch_sub(1, Ordering::SeqCst);
    }
}

fn respond(mut socket: TcpStream, queue: &RequestQueue, queries: &Arc<AtomicUsize>) {
    let mut query_slot = None;
    let result = (|| -> Result<Reply> {
        let request = read_request(&mut socket)?;
        if matches!(request.command, Operation::ReadData { .. }) {
            query_slot = Some(QuerySlot::acquire(queries)?);
        }
        queue
            .submit(request)
            .recv()
            .context("service ended before replying")?
    })();
    let response = match result {
        Ok(Reply::Data(view, query)) => {
            serve_data_query(socket, *view, query);
            return;
        }
        Ok(Reply::Json(value)) => value,
        Err(error) => json!({"api_version":1,"ok":false,"error":format!("{error:#}")}),
    };
    if serde_json::to_writer(&mut socket, &response).is_ok() {
        let _ = socket.write_all(b"\n");
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
                                clients.push(
                                    thread::Builder::new()
                                        .name("uz-client".into())
                                        .spawn(move || respond(socket, &queue, &queries))?,
                                );
                            }
                            // Reject overload without blocking the acceptor on a reply.
                            Ok(_) => {}
                            Err(error) if error.kind() == std::io::ErrorKind::WouldBlock => {
                                thread::sleep(Duration::from_millis(5));
                            }
                            Err(error) => return Err(error.into()),
                        }
                    }
                    Ok(())
                })();
                if let Err(error) = &result {
                    health.lock().unwrap().error = Some(format!("control transport: {error:#}"));
                }
                stopped.store(true, Ordering::SeqCst);
                requests.close();
                drop(listener);
                for client in clients {
                    let _ = client.join();
                }
                result
            })?;
        Ok(Self {
            queue,
            shutdown,
            worker: Some(worker),
        })
    }

    pub fn next(&self) -> Option<Pending> {
        self.queue.next()
    }

    pub fn finish(mut self) -> Result<()> {
        self.shutdown.store(true, Ordering::SeqCst);
        self.queue.close();
        self.worker
            .take()
            .unwrap()
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

    fn request(command: Operation) -> Request {
        Request {
            api_version: 1,
            command,
        }
    }

    #[test]
    fn stop_cancels_pending_requests_but_preserves_in_flight_and_later_commands() {
        let queue = RequestQueue::default();
        let running = queue.submit(request(Operation::Status));
        let in_flight = queue.next().unwrap();
        let enable = queue.submit(request(Operation::EnableSystem));
        let control = queue.submit(request(Operation::EnableControl));
        let stop = queue.submit(request(Operation::Stop));
        let later = queue.submit(request(Operation::Status));
        for canceled in [enable, control] {
            let error = canceled.recv().unwrap().err().unwrap().to_string();
            assert_eq!(error, "request canceled by Stop before execution");
        }
        assert!(in_flight.reply.send(Ok(Reply::Json(json!({})))).is_ok());
        assert!(running.recv().unwrap().is_ok());
        let next = queue.next().unwrap();
        assert!(matches!(next.request.command, Operation::Stop));
        assert!(next.reply.send(Ok(Reply::Json(json!({})))).is_ok());
        assert!(stop.recv().unwrap().is_ok());
        let next = queue.next().unwrap();
        assert!(matches!(next.request.command, Operation::Status));
        assert!(next.reply.send(Ok(Reply::Json(json!({})))).is_ok());
        assert!(later.recv().unwrap().is_ok());
        assert!(queue.next().is_none());
    }

    #[test]
    fn repeated_stop_and_shutdown_notify_every_waiting_caller() {
        let queue = RequestQueue::default();
        let first = queue.submit(request(Operation::Stop));
        let second = queue.submit(request(Operation::Stop));
        assert!(first.recv().unwrap().is_err());
        assert!(matches!(
            queue.0.lock().unwrap().pending[0].request.command,
            Operation::Stop
        ));
        queue.close();
        assert!(second.recv().unwrap().is_err());
        assert!(
            queue
                .submit(request(Operation::EnableControl))
                .recv()
                .unwrap()
                .is_err()
        );
        assert!(queue.next().is_none());
    }
}
