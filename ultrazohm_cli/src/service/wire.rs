//! Local control API v4: newline-delimited JSON envelopes over loopback TCP.
//!
//! Request: `{"version":4,"id":N,"op":"name","args":{...}}`.
//! Reply: `{"version":4,"id":N,"ok":true,"result":{...}}` or
//! `{"version":4,"id":N,"ok":false,"error":{"code":"...","message":"..."}}`.
//! A successful `read_data` reply is followed by `result.arrow_bytes` bytes of
//! Arrow IPC stream data on the same connection. The DataViewer control API
//! uses the same envelope with its own version and an additional token.
use super::Operation;
use crate::live::MAX_SNAPSHOT_BYTES;
use anyhow::{Context, Result, bail, ensure};
use serde::{Deserialize, Serialize};
use serde_json::{Map, Value, json};
use std::{
    io::{BufRead, BufReader, Read, Write},
    net::{Shutdown, SocketAddr, TcpStream},
    sync::atomic::{AtomicBool, Ordering},
    time::{Duration, Instant},
};

/// API v4: unified request/reply envelope, typed replies.
pub const VERSION: u32 = 4;
pub(crate) const MAX_MESSAGE: usize = 65536;
// Requests are small commands; catalogs and recording metadata can be larger.
pub(crate) const MAX_REPLY: usize = 8 * 1024 * 1024;
/// Error code of failures that carry no more specific code.
pub const FAILED: &str = "operation_failed";

/// An error with a stable machine-readable `code`, carried in JSON error replies.
#[derive(Debug)]
pub struct ApiError {
    pub code: String,
    pub message: String,
}
impl std::fmt::Display for ApiError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_str(&self.message)
    }
}
impl std::error::Error for ApiError {}

pub(crate) fn coded(code: &str, message: impl Into<String>) -> anyhow::Error {
    ApiError {
        code: code.into(),
        message: message.into(),
    }
    .into()
}

/// The error code of the first coded error in an error chain, if any.
pub fn error_code(error: &anyhow::Error) -> Option<&str> {
    error
        .chain()
        .find_map(|e| e.downcast_ref::<ApiError>())
        .map(|e| e.code.as_str())
}

/// A request that got no complete reply in time. Never sent to clients as a
/// reply code; clients map it to `timeout` (see [`client_error_code`]).
#[derive(Debug)]
pub(crate) struct Timeout(pub &'static str);
impl std::fmt::Display for Timeout {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_str(self.0)
    }
}
impl std::error::Error for Timeout {}

/// Error code of a failed client request: the service's code, or one of
/// `connection_refused` (no service at the endpoint), `timeout` and `transport`
/// for failures that never produced a reply. None for local validation errors.
pub fn client_error_code(error: &anyhow::Error) -> Option<&str> {
    if let Some(code) = error_code(error) {
        return Some(code);
    }
    if error.chain().any(|e| e.downcast_ref::<Timeout>().is_some()) {
        return Some("timeout");
    }
    let io = error
        .chain()
        .find_map(|e| e.downcast_ref::<std::io::Error>())?;
    Some(match io.kind() {
        std::io::ErrorKind::ConnectionRefused => "connection_refused",
        std::io::ErrorKind::TimedOut | std::io::ErrorKind::WouldBlock => "timeout",
        _ => "transport",
    })
}

/// A validated request: envelope identity plus the typed operation.
#[derive(Debug)]
pub struct Request {
    pub id: u64,
    pub command: Operation,
}

#[derive(Deserialize, Serialize)]
#[serde(deny_unknown_fields)]
struct Envelope {
    version: u32,
    id: u64,
    op: String,
    #[serde(default)]
    args: Map<String, Value>,
}

impl Operation {
    /// Split into the envelope's `op` name and `args` object.
    pub fn to_wire(&self) -> Result<(String, Map<String, Value>)> {
        let Value::Object(mut fields) = serde_json::to_value(self)? else {
            bail!("operation is not an object");
        };
        let Some(Value::String(op)) = fields.remove("op") else {
            bail!("operation has no name");
        };
        Ok((op, fields))
    }

    /// Build an operation from the envelope's `op` name and `args` object.
    pub fn from_wire(op: &str, mut args: Map<String, Value>) -> Result<Self> {
        ensure!(!args.contains_key("op"), "args must not contain op");
        args.insert("op".into(), Value::String(op.into()));
        Ok(serde_json::from_value(Value::Object(args))?)
    }
}

pub(crate) fn encode_request(id: u64, command: &Operation) -> Result<Vec<u8>> {
    let (op, args) = command.to_wire()?;
    let mut line = serde_json::to_vec(&Envelope {
        version: VERSION,
        id,
        op,
        args,
    })?;
    line.push(b'\n');
    Ok(line)
}

/// Parse one request line. The id is returned even if the operation is invalid,
/// so the error reply can still be correlated.
pub(crate) fn decode_request(
    line: &[u8],
) -> std::result::Result<Request, (Option<u64>, anyhow::Error)> {
    let value: Value = serde_json::from_slice(line).map_err(|e| (None, e.into()))?;
    let id = value.get("id").and_then(Value::as_u64);
    let envelope: Envelope = serde_json::from_value(value).map_err(|e| (id, e.into()))?;
    if envelope.version != VERSION {
        return Err((
            id,
            coded(
                "unsupported_version",
                format!(
                    "unsupported API version {}; this service speaks {VERSION}",
                    envelope.version
                ),
            ),
        ));
    }
    let command = Operation::from_wire(&envelope.op, envelope.args).map_err(|e| (id, e))?;
    Ok(Request {
        id: envelope.id,
        command,
    })
}

pub(crate) fn ok_reply(id: Option<u64>, result: Value) -> Value {
    json!({"version":VERSION,"id":id,"ok":true,"result":result})
}

pub(crate) fn error_reply(id: Option<u64>, error: &anyhow::Error) -> Value {
    json!({"version":VERSION,"id":id,"ok":false,"error":{
        "code":error_code(error).unwrap_or(FAILED),"message":format!("{error:#}")}})
}

pub(crate) fn encode_reply(reply: &Value) -> Result<Vec<u8>> {
    let mut line = serde_json::to_vec(reply)?;
    if line.len() > MAX_REPLY {
        return Err(coded(
            "response_too_large",
            "Control response exceeds 8 MiB; request a smaller page",
        ));
    }
    line.push(b'\n');
    Ok(line)
}

/// Write a reply; an oversized reply becomes a bounded error reply instead.
pub(crate) fn write_reply(socket: &mut impl Write, reply: &Value) -> std::io::Result<()> {
    let line = encode_reply(reply).unwrap_or_else(|error| {
        encode_reply(&error_reply(reply["id"].as_u64(), &error)).expect("bounded transport error")
    });
    socket.write_all(&line)
}

/// End a connection after its final reply without losing that reply.
/// Closing a socket that still holds unread input sends a reset, and Windows
/// clients then discard the reply they already received. Send end of output
/// first, then discard input until the client closes or `limit` elapses; the
/// caller drops the socket afterwards.
pub(crate) fn finish_after_reply(socket: &TcpStream, limit: Duration) {
    let _ = socket.shutdown(Shutdown::Write);
    let deadline = Instant::now() + limit;
    let mut input = socket;
    let mut discard = [0u8; 4096];
    loop {
        let remaining = deadline.saturating_duration_since(Instant::now());
        if remaining.is_zero() || socket.set_read_timeout(Some(remaining)).is_err() {
            return;
        }
        if !matches!(input.read(&mut discard), Ok(read) if read > 0) {
            return;
        }
    }
}

pub(crate) fn local_address(s: &str) -> Result<SocketAddr> {
    let addr: SocketAddr = s
        .parse()
        .context("control endpoint must be a numeric loopback address:port")?;
    ensure!(addr.ip().is_loopback(), "control endpoint must be loopback");
    Ok(addr)
}

/// Read one newline-terminated message through a buffer; the binary body of a
/// data reply stays in the same reader. `Ok(None)` is EOF before a message, or
/// `idle_stop` becoming set, including during a partial request.
pub(crate) fn read_message(
    reader: &mut impl BufRead,
    deadline: Duration,
    idle_stop: Option<&AtomicBool>,
) -> Result<Option<Vec<u8>>> {
    read_bounded_message(reader, deadline, idle_stop, MAX_MESSAGE)
}

pub(crate) fn read_bounded_message(
    reader: &mut impl BufRead,
    deadline: Duration,
    idle_stop: Option<&AtomicBool>,
    limit: usize,
) -> Result<Option<Vec<u8>>> {
    let mut data = Vec::new();
    let mut started: Option<Instant> = None;
    loop {
        if idle_stop.is_some_and(|stop| stop.load(Ordering::SeqCst)) {
            return Ok(None);
        }
        if let Some(started) = started
            && started.elapsed() >= deadline
        {
            return Err(Timeout("control message deadline exceeded").into());
        }
        let available = match reader.fill_buf() {
            Ok(bytes) => bytes,
            Err(e) if e.kind() == std::io::ErrorKind::Interrupted => continue,
            Err(e)
                if matches!(
                    e.kind(),
                    std::io::ErrorKind::WouldBlock | std::io::ErrorKind::TimedOut
                ) =>
            {
                match (started, idle_stop) {
                    (Some(t), _) if t.elapsed() >= deadline => {
                        return Err(Timeout("control message deadline exceeded").into());
                    }
                    (Some(_), _) => {}
                    (None, Some(stop)) if stop.load(Ordering::SeqCst) => return Ok(None),
                    (None, Some(_)) => {}
                    (None, None) => return Err(Timeout("timed out waiting for a reply").into()),
                }
                continue;
            }
            Err(e) => return Err(e.into()),
        };
        // Check successful reads too: a peer can otherwise evade the deadline
        // by continuously sending fragments faster than the socket timeout.
        if let Some(started) = started
            && started.elapsed() >= deadline
        {
            return Err(Timeout("control message deadline exceeded").into());
        }
        if idle_stop.is_some_and(|stop| stop.load(Ordering::SeqCst)) {
            return Ok(None);
        }
        if available.is_empty() {
            ensure!(data.is_empty(), "connection closed before newline");
            return Ok(None);
        }
        started.get_or_insert_with(Instant::now);
        let newline = available.iter().position(|&b| b == b'\n');
        let take = newline.unwrap_or(available.len());
        data.extend_from_slice(&available[..take]);
        reader.consume(take + usize::from(newline.is_some()));
        ensure!(data.len() <= limit, "control message exceeds {limit} bytes");
        if newline.is_some() {
            return Ok(Some(data));
        }
    }
}

/// One request on a fresh connection, for short-lived CLI invocations. Returns
/// the reply's `result`.
pub fn request(endpoint: &str, command: Operation) -> Result<Value> {
    ensure!(
        !matches!(command, Operation::ReadData { .. }),
        "use exchange for binary sample responses"
    );
    let (result, _) = Connection::new(endpoint).exchange(command, false)?;
    Ok(result)
}

pub(crate) fn exchange(
    endpoint: &str,
    command: Operation,
    binary: bool,
) -> Result<(Value, Vec<u8>)> {
    Connection::new(endpoint).exchange(command, binary)
}

/// A persistent client connection. Requests are sent sequentially on one socket;
/// a broken socket is dropped and reopened. Only read-only operations are
/// retried automatically, because a device command must never be replayed.
pub struct Connection {
    endpoint: String,
    next_id: u64,
    socket: Option<(BufReader<TcpStream>, TcpStream)>,
}
impl Connection {
    pub fn new(endpoint: &str) -> Self {
        Self {
            endpoint: endpoint.into(),
            next_id: 1,
            socket: None,
        }
    }

    /// Drop the socket; the next exchange reconnects.
    pub fn reset(&mut self) {
        self.socket = None;
    }

    fn open(&mut self) -> Result<&mut (BufReader<TcpStream>, TcpStream)> {
        // A service that closed an idle connection (restart, shutdown) leaves a
        // readable EOF; detect it before sending rather than after.
        if let Some((reader, _)) = &mut self.socket {
            let stale = reader.buffer().is_empty() && {
                let socket = reader.get_ref();
                socket.set_nonblocking(true)?;
                let mut probe = [0u8];
                let state = socket.peek(&mut probe);
                socket.set_nonblocking(false)?;
                !matches!(&state, Err(e) if e.kind() == std::io::ErrorKind::WouldBlock)
            };
            if stale {
                self.socket = None;
            }
        }
        if self.socket.is_none() {
            // Windows retries refused loopback connections for about two seconds.
            // A two-second deadline can mask ConnectionRefused as TimedOut, preventing
            // callers from recognizing a stopped service during managed flashing.
            let connect_timeout = Duration::from_secs(if cfg!(windows) { 5 } else { 2 });
            let socket =
                TcpStream::connect_timeout(&local_address(&self.endpoint)?, connect_timeout)?;
            socket.set_nodelay(true)?;
            socket.set_write_timeout(Some(Duration::from_secs(2)))?;
            self.socket = Some((BufReader::new(socket.try_clone()?), socket));
        }
        Ok(self.socket.as_mut().expect("socket opened above"))
    }

    /// Send one operation; return the reply's `result` and any binary body.
    pub fn exchange(&mut self, command: Operation, binary: bool) -> Result<(Value, Vec<u8>)> {
        ensure!(
            binary == matches!(command, Operation::ReadData { .. }),
            "only read_data has a binary response"
        );
        let retry = command.read_only();
        let timeout =
            Duration::from_secs(if binary || matches!(command, Operation::Connect { .. }) {
                30
            } else {
                5
            });
        let id = self.next_id;
        self.next_id += 1;
        let request = encode_request(id, &command)?;
        let result = self.send(id, &request, binary, timeout);
        if let Err(error) = &result
            && retry
            && error.downcast_ref::<std::io::Error>().is_some()
        {
            self.socket = None;
            return self.send(id, &request, binary, timeout);
        }
        result
    }

    fn send(
        &mut self,
        id: u64,
        request: &[u8],
        binary: bool,
        timeout: Duration,
    ) -> Result<(Value, Vec<u8>)> {
        // An error reply without an id answers no particular request (client
        // limit, unreadable request); the service closes that connection.
        let mut unmatched = false;
        let result = (|| -> Result<(Value, Vec<u8>)> {
            let (reader, socket) = self.open()?;
            socket.set_read_timeout(Some(timeout))?;
            socket.write_all(request)?;
            let line =
                read_bounded_message(reader, timeout, None, MAX_REPLY)?.ok_or_else(|| {
                    std::io::Error::new(
                        std::io::ErrorKind::UnexpectedEof,
                        "service closed the connection",
                    )
                })?;
            let mut reply: Value = serde_json::from_slice(&line)?;
            ensure!(
                reply["version"] == VERSION,
                "unsupported response API version {}; client and service versions differ",
                reply["version"]
            );
            unmatched = reply["id"].is_null();
            ensure!(
                reply["id"] == id || (unmatched && reply["ok"] != true),
                "reply does not match request {id}"
            );
            if reply["ok"] != true {
                let error = &reply["error"];
                return Err(ApiError {
                    code: error["code"].as_str().unwrap_or(FAILED).into(),
                    message: error["message"].as_str().unwrap_or("request failed").into(),
                }
                .into());
            }
            let result = reply["result"].take();
            let mut bytes = Vec::new();
            if binary {
                let len = result["arrow_bytes"]
                    .as_u64()
                    .context("missing Arrow response length")?;
                ensure!(
                    len <= MAX_SNAPSHOT_BYTES as u64,
                    "snapshot exceeds response limit"
                );
                bytes.resize(len as usize, 0);
                reader.read_exact(&mut bytes)?;
            }
            Ok((result, bytes))
        })();
        // A reply error leaves the stream in sync; any other failure may not.
        if let Err(error) = &result
            && (unmatched || error.downcast_ref::<ApiError>().is_none())
        {
            self.socket = None;
        }
        result
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::net::TcpListener;

    #[test]
    fn envelope_round_trips_operations() {
        let command = Operation::SetVariable {
            name: "send_field_1".into(),
            value: 2.5,
        };
        let line = encode_request(7, &command).unwrap();
        let value: Value = serde_json::from_slice(&line).unwrap();
        assert_eq!(
            value,
            json!({"version":VERSION,"id":7,"op":"set_variable","args":{"name":"send_field_1","value":2.5}})
        );
        let request = decode_request(&line[..line.len() - 1]).unwrap();
        assert_eq!(request.id, 7);
        assert!(matches!(request.command, Operation::SetVariable { .. }));
        let unit = decode_request(br#"{"version":4,"id":1,"op":"status"}"#).unwrap();
        assert!(matches!(unit.command, Operation::Status));
        let (id, error) =
            decode_request(br#"{"version":3,"id":9,"op":"status","args":{}}"#).unwrap_err();
        assert_eq!(
            (id, error_code(&error)),
            (Some(9), Some("unsupported_version"))
        );
        assert!(
            decode_request(br#"{"version":4,"id":1,"op":"status","args":{"op":"stop"}}"#).is_err()
        );
    }

    #[test]
    fn large_catalog_replies_fit_without_increasing_request_limit() {
        let reply = ok_reply(
            Some(1),
            json!({"profile":{"name":"x".repeat(MAX_MESSAGE * 2)}}),
        );
        let mut wire = Vec::new();
        write_reply(&mut wire, &reply).unwrap();
        let received = read_bounded_message(
            &mut std::io::Cursor::new(&wire),
            Duration::from_secs(1),
            None,
            MAX_REPLY,
        )
        .unwrap()
        .unwrap();
        assert_eq!(serde_json::from_slice::<Value>(&received).unwrap(), reply);
        assert!(
            read_message(
                &mut std::io::Cursor::new(wire),
                Duration::from_secs(1),
                None
            )
            .is_err()
        );
    }

    #[test]
    fn oversized_reply_is_a_readable_error_and_preserves_next_message() {
        let mut wire = Vec::new();
        write_reply(
            &mut wire,
            &ok_reply(Some(1), json!({"value":"x".repeat(MAX_REPLY)})),
        )
        .unwrap();
        write_reply(&mut wire, &ok_reply(Some(2), json!({"next":true}))).unwrap();
        let mut reader = std::io::Cursor::new(wire);
        let first = read_message(&mut reader, Duration::from_secs(1), None)
            .unwrap()
            .unwrap();
        let first = serde_json::from_slice::<Value>(&first).unwrap();
        assert_eq!(first["error"]["code"], "response_too_large");
        assert_eq!(first["id"], 1);
        let second = read_message(&mut reader, Duration::from_secs(1), None)
            .unwrap()
            .unwrap();
        assert_eq!(
            serde_json::from_slice::<Value>(&second).unwrap()["result"]["next"],
            true
        );
    }

    #[test]
    fn message_deadline_includes_successful_fragment_reads() {
        struct Fragments(usize);
        impl Read for Fragments {
            fn read(&mut self, buffer: &mut [u8]) -> std::io::Result<usize> {
                if self.0 != 0 {
                    std::thread::sleep(Duration::from_millis(20));
                }
                buffer[0] = if self.0 == 0 { b'x' } else { b'\n' };
                self.0 += 1;
                Ok(1)
            }
        }
        let mut reader = BufReader::with_capacity(1, Fragments(0));
        let error = read_message(&mut reader, Duration::from_millis(10), None).unwrap_err();
        assert!(error.to_string().contains("deadline exceeded"));
    }

    #[test]
    fn shutdown_does_not_admit_buffered_requests() {
        let mut reader = std::io::Cursor::new(b"request\n");
        assert!(
            read_message(
                &mut reader,
                Duration::from_secs(2),
                Some(&AtomicBool::new(true)),
            )
            .unwrap()
            .is_none()
        );
    }

    #[test]
    fn stopped_service_reports_connection_refused() {
        let listener = TcpListener::bind("127.0.0.1:0").unwrap();
        let endpoint = listener.local_addr().unwrap().to_string();
        drop(listener);

        let error = request(&endpoint, Operation::Status).unwrap_err();
        assert_eq!(
            error.downcast_ref::<std::io::Error>().map(|e| e.kind()),
            Some(std::io::ErrorKind::ConnectionRefused),
            "a stopped service must report refusal, not a timeout: {error:#}"
        );
        assert_eq!(client_error_code(&error), Some("connection_refused"));
    }

    #[test]
    fn client_error_codes_distinguish_transport_failures() {
        let refused =
            anyhow::Error::from(std::io::Error::from(std::io::ErrorKind::ConnectionRefused));
        assert_eq!(client_error_code(&refused), Some("connection_refused"));
        let closed = anyhow::Error::from(std::io::Error::from(std::io::ErrorKind::UnexpectedEof));
        assert_eq!(client_error_code(&closed), Some("transport"));
        let mut silent = BufReader::new(std::io::Cursor::new(Vec::new()));
        // An empty reader is EOF, not a timeout; a WouldBlock reader times out.
        assert!(
            read_message(&mut silent, Duration::from_secs(1), None)
                .unwrap()
                .is_none()
        );
        struct Blocked;
        impl Read for Blocked {
            fn read(&mut self, _: &mut [u8]) -> std::io::Result<usize> {
                Err(std::io::Error::from(std::io::ErrorKind::WouldBlock))
            }
        }
        let timeout =
            read_message(&mut BufReader::new(Blocked), Duration::from_secs(1), None).unwrap_err();
        assert_eq!(client_error_code(&timeout), Some("timeout"));
        assert_eq!(
            client_error_code(&coded("busy", "too many clients")),
            Some("busy")
        );
        assert_eq!(client_error_code(&anyhow::anyhow!("invalid value")), None);
    }
}
