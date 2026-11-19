"""The combined download includes the same native CLI as the CLI-only ZIP."""
from pathlib import Path
import sys
import tempfile
import unittest
import zipfile

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
from package_windows import package


class WindowsArchivesTest(unittest.TestCase):
    def test_contents_and_cli_identity(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            cli = root / 'cli.exe'
            cli.write_bytes(b'native CLI')
            viewer = root / 'viewer'
            viewer.mkdir()
            (viewer / 'ultrazohm-dataviewer.exe').write_bytes(b'GUI')
            (viewer / 'ultrazohm-dataviewer.ps1').write_text('wrapper')
            (viewer / '_internal').mkdir()
            (viewer / '_internal' / 'runtime.dll').write_bytes(b'runtime')
            output = root / 'out'
            package('0.1.88.dev0', cli, viewer, output)
            self.assertEqual(len(list(output.glob('*'))), 2)
            for name in ('ultrazohm-cli', 'ultrazohm-dataviewer'):
                with zipfile.ZipFile(output / f'{name}-0.1.88.dev0-windows-x86_64.zip') as archive:
                    self.assertEqual(archive.read(f'{name}/ultrazohm-cli.exe'), cli.read_bytes())
                    if name.endswith('dataviewer'):
                        self.assertIn(f'{name}/ultrazohm-dataviewer.ps1', archive.namelist())
                        self.assertIn(f'{name}/_internal/runtime.dll', archive.namelist())
                        self.assertEqual(len([n for n in archive.namelist() if n.endswith('.exe')]), 2)

    def test_incomplete_bundle_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            with self.assertRaises(FileNotFoundError):
                package('0.1.0', root / 'missing.exe', root, root / 'out')
            self.assertFalse((root / 'out').exists())
