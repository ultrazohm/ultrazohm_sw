"""Console entry point; all parsing, control and acquisition run in Rust."""

import sys

from ._native import cli_main


def main():
    if sys.platform == "win32":
        import ctypes

        kernel = ctypes.WinDLL("kernel32", use_last_error=True)
        # Windows launchers may pass down the inheritable ignore-Ctrl-C flag.
        # Registering the Rust handler alone does not clear that flag.
        if kernel.GetConsoleCP() and not kernel.SetConsoleCtrlHandler(None, False):
            raise ctypes.WinError(ctypes.get_last_error())
    return cli_main(sys.argv)
