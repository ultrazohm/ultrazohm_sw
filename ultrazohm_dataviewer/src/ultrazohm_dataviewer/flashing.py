"""Viewer adapters for CLI-owned vendor tool preferences."""


def xsct_available(repo=None):
    from ultrazohm_cli.configuration import resolve_xsct

    try:
        resolve_xsct(repo=repo)
        return True
    except (OSError, ValueError):
        return False


def select_xsct(path, repo=None):
    from ultrazohm_cli.configuration import save_xsct

    return save_xsct(path, repo)


def restore_xsct(repo=None):
    from ultrazohm_cli.configuration import saved_xsct

    return saved_xsct(repo)


def connection_refused(error):
    """Whether a request failed because no service listens at the endpoint."""
    code = getattr(error, "code", None)
    if code is not None:
        return code == "connection_refused"
    if isinstance(error, ConnectionRefusedError):
        return True
    # CLI wheels without transport error codes report refusal only as text.
    text = str(error).lower()
    return (
        "connection refused" in text
        or "os error 10061" in text
        or "actively refused" in text
    )
