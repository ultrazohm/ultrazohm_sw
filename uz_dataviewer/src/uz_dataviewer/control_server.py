"""Local transport and bounded application-thread dispatch, independent of ImGui.

The application calls poll(handler). A handler returns a result envelope with
session/result fields, or a Future completing with that envelope. Socket threads
only exchange messages; they never inspect application state.
"""
from concurrent.futures import Future
from queue import Queue, Empty, Full
import socket
import threading
import time
import select
import secrets

from . import control_protocol as wire
from .client import ViewerError


class ControlServer:
    def __init__(self, endpoint=wire.DEFAULT_ENDPOINT, *, capacity=128, max_clients=32):
        host, port = wire.address(endpoint, bind=True)
        self._listener = socket.socket(socket.AF_INET6 if ':' in host else socket.AF_INET,
                                       socket.SOCK_STREAM)
        try:
            self._listener.bind((host, port))
            self._listener.listen(max_clients)
        except BaseException:
            self._listener.close()
            raise
        port = self._listener.getsockname()[1]
        self.endpoint = f'[{host}]:{port}' if ':' in host else f'{host}:{port}'
        from .control_credentials import publish
        self.token = secrets.token_urlsafe(32)
        try:
            self._credential_path = publish(self.endpoint, self.token)
        except BaseException:
            self._listener.close()
            raise
        self._queue = Queue(maxsize=capacity)
        self._lock = threading.RLock()
        self._pending = set()
        self._clients = set()
        self._closed = False
        self._slots = threading.BoundedSemaphore(max_clients)
        self._owner = threading.get_ident()
        self._listener.settimeout(.2)
        self._thread = threading.Thread(target=self._accept, daemon=True, name='uz-viewer-api')
        self._thread.start()

    @property
    def pending(self):
        with self._lock:
            return bool(self._pending)

    def _submit(self, request):
        token = request.get('token')
        if not isinstance(token, str) or not secrets.compare_digest(token.encode(), self.token.encode()):
            raise ViewerError('unauthorized', 'Viewer credential is missing or invalid; reconnect with a new client')
        if (type(request.get('id')) is not int or
                not isinstance(request.get('operation'), str) or
                not isinstance(request.get('arguments'), dict) or
                request.get('session') is not None and not isinstance(request['session'], str)):
            raise ViewerError('invalid_request', 'Invalid request fields')
        future = Future()
        with self._lock:
            if self._closed:
                raise ViewerError('closed', 'Viewer is closing')
            try:
                self._queue.put_nowait((request, future))
            except Full as exc:
                raise ViewerError('busy', 'Viewer request queue is full') from exc
            self._pending.add(future)
        return future

    def _complete(self, target, *, result=None, error=None):
        with self._lock:
            if not target.done():
                if error is None:
                    target.set_result(result)
                else:
                    target.set_exception(error)
            self._pending.discard(target)

    def poll(self, handler, *, budget=.005, limit=32):
        """Start a bounded amount of work on the owning application thread."""
        if threading.get_ident() != self._owner:
            raise RuntimeError('Control requests must be dispatched on the application thread')
        deadline = time.monotonic() + budget
        for _ in range(limit):
            if self._closed or time.monotonic() >= deadline:
                break
            try:
                request, target = self._queue.get_nowait()
            except Empty:
                break
            if target.done():
                continue
            try:
                result = handler(request['operation'], request['arguments'], request.get('session'))
                if isinstance(result, Future):
                    target.add_done_callback(lambda completed, source=result:
                                             source.cancel() if completed.cancelled() or self._closed else None)
                    def completed(source, destination=target):
                        try:
                            value = source.result()
                        except BaseException as exc:
                            self._complete(destination, error=exc)
                        else:
                            self._complete(destination, result=value)
                    result.add_done_callback(completed)
                else:
                    self._complete(target, result=result)
            except Exception as exc:
                self._complete(target, error=exc)

    def _accept(self):
        while not self._closed:
            try:
                connection, _ = self._listener.accept()
            except socket.timeout:
                continue
            except OSError:
                break
            with self._lock:
                if self._closed or not self._slots.acquire(blocking=False):
                    connection.close()
                    continue
                self._clients.add(connection)
            threading.Thread(target=self._serve, args=(connection,), daemon=True,
                             name='uz-viewer-client').start()

    def _serve(self, connection):
        future = None
        try:
            with connection.makefile('rb') as stream:
                while not self._closed:
                    request = wire.read(stream)
                    reply = dict(version=wire.VERSION, id=request.get('id'))
                    try:
                        future = self._submit(request)
                        completed = threading.Event()
                        future.add_done_callback(lambda _, event=completed: event.set())
                        while not completed.wait(.05):
                            # Pipelined bytes also make a socket readable. Wait on
                            # completion first so those bytes cannot cause a busy loop.
                            readable, _, _ = select.select([connection], [], [], 0)
                            if readable and not connection.recv(1, socket.MSG_PEEK):
                                future.cancel()
                                with self._lock:
                                    self._pending.discard(future)
                                return
                        result = future.result()
                        reply.update(result)
                    except Exception as exc:
                        reply['error'] = dict(code=getattr(exc, 'code', 'operation_failed'),
                                              message=str(exc))
                    try:
                        data = wire.encode(reply)
                    except (ValueError, TypeError):
                        data = wire.encode(dict(version=wire.VERSION, id=request.get('id'),
                                                error=dict(code='invalid_result',
                                                           message='Operation result cannot be transmitted')))
                    connection.sendall(data)
        except (OSError, EOFError, ValueError):
            pass
        finally:
            if future is not None and not future.done():
                future.cancel()
                with self._lock:
                    self._pending.discard(future)
            connection.close()
            with self._lock:
                self._clients.discard(connection)
            self._slots.release()

    def close(self):
        with self._lock:
            self._closed = True
            for future in list(self._pending):
                self._complete(future, error=ViewerError('closed', 'Viewer is closing'))
            clients = list(self._clients)
            while True:
                try:
                    self._queue.get_nowait()
                except Empty:
                    break
        self._listener.close()
        for connection in clients:
            try:
                connection.shutdown(socket.SHUT_RDWR)
            except OSError:
                pass
            connection.close()
        self._thread.join(timeout=.5)
        from .control_credentials import remove
        remove(self._credential_path, self.token)
