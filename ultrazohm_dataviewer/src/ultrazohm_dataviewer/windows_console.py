"""Restore standard streams for the windowed Windows executable's CLI mode."""

import os
import sys


def initialize():
    if os.name != "nt":
        return
    import ctypes
    import msvcrt
    from ctypes import wintypes

    kernel = ctypes.WinDLL("kernel32", use_last_error=True)
    kernel.GetStdHandle.argtypes = [wintypes.DWORD]
    kernel.GetStdHandle.restype = wintypes.HANDLE
    kernel.GetCurrentProcess.restype = wintypes.HANDLE
    kernel.DuplicateHandle.argtypes = [
        wintypes.HANDLE,
        wintypes.HANDLE,
        wintypes.HANDLE,
        ctypes.POINTER(wintypes.HANDLE),
        wintypes.DWORD,
        wintypes.BOOL,
        wintypes.DWORD,
    ]
    kernel.DuplicateHandle.restype = wintypes.BOOL
    kernel.AttachConsole.argtypes = [wintypes.DWORD]
    kernel.AttachConsole.restype = wintypes.BOOL
    process = kernel.GetCurrentProcess()

    def duplicate(number):
        handle = kernel.GetStdHandle(wintypes.DWORD(number))
        copy = wintypes.HANDLE()
        if kernel.DuplicateHandle(
            process, handle, process, ctypes.byref(copy), 0, False, 2
        ):
            return copy.value
        return None

    specs = [("stdin", -10, "r"), ("stdout", -11, "w"), ("stderr", -12, "w")]
    # Preserve redirected pipe/file handles before attaching to a console.
    handles = [duplicate(number) for _, number, _ in specs]
    # Attach even with valid pipes so interactive Ctrl-C reaches this process.
    kernel.AttachConsole(wintypes.DWORD(-1))
    for (name, number, mode), handle in zip(specs, handles, strict=False):
        if handle is None:
            handle = duplicate(number)
        if handle is None:
            stream = open(os.devnull, mode, encoding="utf-8")
        else:
            flags = os.O_RDONLY if mode == "r" else os.O_WRONLY
            fd = msvcrt.open_osfhandle(handle, flags | os.O_BINARY)
            stream = os.fdopen(
                fd, mode, encoding="utf-8", errors="replace", buffering=1
            )
        setattr(sys, name, stream)
        setattr(sys, "__" + name + "__", stream)
