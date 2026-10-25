"""Single cancellable loading worker; native IO never holds process shutdown open."""
from concurrent.futures import Future
from queue import Queue, Empty
import threading

from .sources import Cancelled, check


class LoadExecutor:
    def __init__(self):
        self.queue = Queue()
        self.cancel = threading.Event()
        self.thread = None

    def submit(self, function, *args):
        future = Future()
        if self.cancel.is_set():
            future.cancel()
            return future
        self.queue.put((future, function, args))
        if self.thread is None:
            self.thread = threading.Thread(target=self._work, daemon=True, name='uz-loader')
            self.thread.start()
        return future

    def _work(self):
        while not self.cancel.is_set():
            item = self.queue.get()
            if item is None:
                return
            future, function, args = item
            if not future.set_running_or_notify_cancel():
                continue
            result = None
            try:
                check(self.cancel)
                result = function(*args, cancel=self.cancel)
                check(self.cancel)
                future.set_result(result)
            except BaseException as exc:
                future.set_exception(exc)
            finally:
                item = future = function = args = result = None

    def shutdown(self):
        self.cancel.set()
        while True:
            try:
                item = self.queue.get_nowait()
            except Empty:
                break
            if item is not None:
                item[0].cancel()
        self.queue.put(None)
        if self.thread is not None:
            self.thread.join(timeout=.2)


def _convert_worker(source, destination, backend, connection):
    try:
        from .loader import convert_csv_to_parquet
        result = convert_csv_to_parquet(source, destination, backend=backend)
        connection.send((True, result))
    except Exception as exc:
        connection.send((False, str(exc)))
    finally:
        connection.close()


def convert_cancellable(source, destination, backend, cancel):
    """Isolate native streaming sinks so cancellation can stop their IO promptly."""
    import multiprocessing
    context = multiprocessing.get_context('spawn')
    receive, send = context.Pipe(duplex=False)
    process = context.Process(target=_convert_worker, args=(source, destination, backend, send), daemon=True)
    try:
        check(cancel)
        process.start()
        send.close()
        while process.is_alive():
            check(cancel)
            process.join(timeout=.05)
        check(cancel)
        if not receive.poll():
            raise RuntimeError(f'Conversion worker exited without a result (exit {process.exitcode})')
        try:
            ok, result = receive.recv()
        except EOFError as exc:
            raise RuntimeError('Conversion worker exited without a result') from exc
        if not ok:
            raise ValueError(result)
        return result
    finally:
        if process.pid is not None:
            if process.is_alive():
                process.terminate()
            process.join()
            process.close()
        receive.close()
        send.close()
