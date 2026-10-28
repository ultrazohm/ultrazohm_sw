"""Generated data belongs to the selected workspace's artifacts directory."""
from pathlib import Path


def data_directory(repo=None):
    if repo is not None:
        root = Path(repo).expanduser().resolve()
    else:
        # Source startup from a repository subdirectory, or standalone analysis.
        root = Path.cwd()
        for candidate in (root, *root.parents):
            if (candidate / 'vitis/software/Baremetal/src/include/javascope.h').is_file():
                root = candidate
                break
    path = root / 'artifacts'
    path.mkdir(parents=True, exist_ok=True)
    return path
