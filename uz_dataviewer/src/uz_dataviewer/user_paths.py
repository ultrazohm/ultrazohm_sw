"""Writable application data, independent of install directory and working directory."""
import os
from pathlib import Path


def data_directory():
    if os.name == 'nt':
        root = Path(os.environ.get('LOCALAPPDATA', str(Path.home()/'AppData/Local')))
    else:
        root = Path(os.environ.get('XDG_DATA_HOME', str(Path.home()/'.local/share')))
    path = root/'uz_dataviewer'
    path.mkdir(parents=True, exist_ok=True)
    return path
