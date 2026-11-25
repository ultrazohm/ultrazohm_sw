"""Small, bounded JSON wire contract shared by viewer and control clients.

The envelope matches the acquisition service API (ultrazohm-cli protocol v4):

- request: ``{"version", "id", "op", "args", "token", "session"}``
- reply: ``{"version", "id", "ok": true, "result", "session"}`` or
  ``{"version", "id", "ok": false, "error": {"code", "message"}}``
"""

import ipaddress
import json

VERSION = 2
DEFAULT_ENDPOINT = "127.0.0.1:19741"
MAX_MESSAGE = 1024 * 1024
FAILED = "operation_failed"


def request(id, op, args, **fields):
    return {"version": VERSION, "id": id, "op": op, "args": args, **fields}


def success(id, result, **fields):
    return {"version": VERSION, "id": id, "ok": True, "result": result, **fields}


def failure(id, code, message):
    return {
        "version": VERSION,
        "id": id,
        "ok": False,
        "error": {"code": code, "message": message},
    }


def address(endpoint, *, bind=False):
    host, separator, port = endpoint.rpartition(":")
    host = host.strip("[]")
    if not separator or not ipaddress.ip_address(host).is_loopback:
        raise ValueError("Viewer endpoints must use a numeric loopback address")
    host = str(ipaddress.ip_address(host))
    port = int(port)
    if not (0 if bind else 1) <= port <= 65535:
        raise ValueError("Endpoint port must be between 1 and 65535")
    return host, port


def encode(message):
    data = (
        json.dumps(message, allow_nan=False, separators=(",", ":")).encode("utf-8")
        + b"\n"
    )
    if len(data) > MAX_MESSAGE:
        raise ValueError("Control message exceeds size limit")
    return data


def read(stream):
    line = stream.readline(MAX_MESSAGE + 1)
    if not line:
        raise EOFError("Viewer connection closed")
    if len(line) > MAX_MESSAGE or not line.endswith(b"\n"):
        raise ValueError("Invalid or oversized control message")

    def invalid_constant(value):
        raise ValueError(f"Nonfinite JSON value: {value}")

    message = json.loads(line, parse_constant=invalid_constant)
    if (
        not isinstance(message, dict)
        or type(message.get("version")) is not int
        or message.get("version") != VERSION
    ):
        raise ValueError("Unsupported viewer control protocol")
    return message
