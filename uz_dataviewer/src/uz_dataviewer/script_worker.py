"""Windows process-containment bootstrap with ordinary script/argv semantics."""
import runpy
import sys
from pathlib import Path


def main():
    from .script_job import contain_children
    job = contain_children()
    path = Path(sys.argv[1]).resolve()
    sys.argv = [str(path), *sys.argv[2:]]
    sys.path[0] = str(path.parent)
    runpy.run_path(str(path), run_name='__main__')
    del job  # Windows closes the handle on process exit, including SystemExit.


if __name__ == '__main__':
    main()
