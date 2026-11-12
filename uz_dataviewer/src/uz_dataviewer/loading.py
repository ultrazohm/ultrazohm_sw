"""Cancellable native conversion processes, owned by the loading worker."""
from .sources import check


def _convert_worker(source, destination, backend, connection):
    try:
        from .loader import _write_csv_to_parquet
        result = _write_csv_to_parquet(source, destination, backend=backend)
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
        # Drain the pipe while the worker is alive: a large result/error can
        # fill its buffer and prevent the worker from exiting.
        while not receive.poll(.05):
            check(cancel)
            if not process.is_alive():
                break
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
