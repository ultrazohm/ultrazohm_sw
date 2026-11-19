"""Run the frozen self-test, including Windows executables without a console."""

import json
import subprocess
import sys
from pathlib import Path
from tempfile import TemporaryDirectory


def main():
    executable = Path(sys.argv[1]).resolve(strict=True)
    with TemporaryDirectory() as directory:
        report = Path(directory) / "result.json"
        result = subprocess.run(
            [str(executable), "--self-test", str(report)],
            cwd=directory,
            check=False,
            timeout=120,
        )
        if report.exists():
            details = json.loads(report.read_text(encoding="utf-8"))
            if not details.get("ok"):
                raise RuntimeError(details.get("error", str(details)))
            assert details == {"ok": True}
        else:
            raise RuntimeError(
                f"Frozen self-test exited {result.returncode} without a report"
            )
        result.check_returncode()
    print(
        "Frozen executable: native imports, Parquet reads, Python control, session restoration, downsampling and linked-axis input passed."
    )


if __name__ == "__main__":
    main()
