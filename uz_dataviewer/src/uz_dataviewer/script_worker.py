"""Execute one measurement script in a disposable Python process."""
import runpy
import sys
from pathlib import Path


def main():
    from .script_job import contain_children
    job = contain_children()
    from ultrazohm import Client
    path = Path(sys.argv[1]).resolve()
    sys.path.insert(0, str(path.parent))
    namespace = runpy.run_path(str(path), init_globals={'uz': Client(sys.argv[2])}, run_name='uz_measurement')
    entry = namespace.get('run')
    if not callable(entry):
        raise ValueError('Measurement scripts must define run(uz)')
    entry(namespace['uz'])
    del job  # The OS owns handle closure on process exit.


if __name__ == '__main__':
    main()
