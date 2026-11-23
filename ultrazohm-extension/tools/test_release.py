"""Release gates must reject incomplete or altered platform artifacts."""
import hashlib
import json
import os
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import bundle
import release


class ReleaseTest(unittest.TestCase):
    def test_tag_must_match_version(self):
        with patch.dict(os.environ, {'GITHUB_REF': 'refs/tags/ultrazohm-extension-v999.0.0'}):
            with self.assertRaisesRegex(ValueError, 'Tag must match'):
                release.metadata()

    def fixture(self, directory):
        version = release.metadata()['version']
        for target in release.TARGETS:
            file = directory / f'ultrazohm-extension-{target}-{version}.vsix'
            file.write_bytes(target.encode())
            file.with_suffix('.json').write_text(json.dumps(dict(
                version=version, target=target, file=file.name,
                sha256=release.digest(file), commit='same-commit',
                tested_channel='prerelease', tested_packages={'example': '1.0'})))

    def test_manifest_requires_both_unchanged_platforms_from_same_commit(self):
        with tempfile.TemporaryDirectory() as temp, patch.dict(os.environ, {'GITHUB_REF': ''}):
            directory = Path(temp)
            self.fixture(directory)
            release.aggregate(directory)
            self.assertEqual(len((directory / 'SHA256SUMS').read_text().splitlines()), 2)
            receipt = next(directory.glob('*.vsix')).with_suffix('.json')
            data = json.loads(receipt.read_text())
            data['commit'] = 'different'
            receipt.write_text(json.dumps(data))
            with self.assertRaisesRegex(ValueError, 'same commit'):
                release.aggregate(directory)
            self.fixture(directory)
            receipt.with_suffix('.vsix').write_bytes(b'altered')
            with self.assertRaisesRegex(ValueError, 'changed'):
                release.aggregate(directory)
            self.fixture(directory)
            receipt.unlink()
            with self.assertRaisesRegex(ValueError, 'Both tested platform'):
                release.aggregate(directory)

    def test_download_checks_content_and_cache(self):
        with tempfile.TemporaryDirectory() as temp:
            directory = Path(temp)
            source = directory / 'source'
            source.write_bytes(b'upstream')
            cache = directory / 'cache'
            cache.mkdir()
            spec = {'url': source.as_uri(), 'sha256': hashlib.sha256(b'upstream').hexdigest()}
            result = bundle.download(spec, cache)
            result.write_bytes(b'corrupt cache')
            self.assertEqual(bundle.download(spec, cache).read_bytes(), b'upstream')
            result.unlink()
            source.write_bytes(b'corrupt upstream')
            with self.assertRaisesRegex(ValueError, 'Checksum mismatch'):
                bundle.download(spec, cache)
            self.assertFalse(result.exists())


if __name__ == '__main__':
    unittest.main()
