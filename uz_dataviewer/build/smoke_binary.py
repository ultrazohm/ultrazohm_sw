"""Run the frozen self-test, including Windows executables without a console."""
import json
from pathlib import Path
import subprocess
import sys
from tempfile import TemporaryDirectory


def main():
    executable = Path(sys.argv[1]).resolve(strict=True)
    with TemporaryDirectory() as directory:
        report = Path(directory) / "result.json"
        subprocess.run(
            [str(executable), "--self-test", str(report)],
            cwd=directory, check=True, timeout=120,
        )
        assert json.loads(report.read_text(encoding="utf-8")) == {"ok": True}
    print("Frozen executable: native imports, Parquet reads and downsampling passed.")


if __name__ == "__main__":
    main()
