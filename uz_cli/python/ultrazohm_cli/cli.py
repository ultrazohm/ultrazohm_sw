"""Console entry point; all parsing, control and acquisition run in Rust."""
import sys

from ._native import cli_main


def main():
    return cli_main(sys.argv)
