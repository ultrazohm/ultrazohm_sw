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
    def test_branch_channels_and_publication_gates(self):
        base = {'GITHUB_RUN_NUMBER': '42', 'GITHUB_REPOSITORY': 'ultrazohm/ultrazohm_sw'}
        for event in ['push', 'workflow_dispatch']:
            for branch in ['main', 'develop', 'feature/vscode-extension']:
                with self.subTest(event=event, branch=branch), patch.dict(os.environ, {**base, 'GITHUB_EVENT_NAME': event, 'GITHUB_REF': 'refs/heads/' + branch}, clear=True):
                    info = release.metadata()
                    self.assertEqual(info['version'], '0.1.42')
                    self.assertEqual(info['publish'], event == 'push' and branch in ['main', 'develop'])
                    self.assertEqual(info['prerelease'], not (event == 'push' and branch == 'main'))
        for extra in [
            {'GITHUB_EVENT_NAME': 'pull_request', 'GITHUB_REF': 'refs/heads/main'},
            {'GITHUB_EVENT_NAME': 'push', 'GITHUB_REF': 'refs/tags/ultrazohm-extension-v0.1.42'},
            {'GITHUB_EVENT_NAME': 'push', 'GITHUB_REF': 'refs/heads/main', 'GITHUB_REPOSITORY': 'someone/fork'},
        ]:
            with patch.dict(os.environ, {**base, **extra}, clear=True):
                self.assertFalse(release.metadata()['publish'])

    def test_explicit_manual_prerelease_is_restricted_and_never_stable(self):
        base = {'GITHUB_RUN_NUMBER': '44', 'GITHUB_REPOSITORY': 'ultrazohm/ultrazohm_sw',
                'GITHUB_EVENT_NAME': 'workflow_dispatch', 'UZ_EXTENSION_PUBLISH_PRERELEASE': 'true'}
        for branch in ['develop', 'feature/vscode-extension']:
            with patch.dict(os.environ, {**base, 'GITHUB_REF': 'refs/heads/' + branch}, clear=True):
                info = release.metadata()
                self.assertTrue(info['publish'])
                self.assertTrue(info['prerelease'])
                self.assertEqual(info['version'], '0.1.44')
                with patch.dict(os.environ, {'GITHUB_REPOSITORY': 'someone/fork'}):
                    self.assertFalse(release.metadata()['publish'])
                with patch.dict(os.environ, {'UZ_EXTENSION_PUBLISH_PRERELEASE': 'false'}):
                    self.assertFalse(release.metadata()['publish'])
        for ref in ['refs/heads/main', 'refs/heads/another-feature', 'refs/tags/v1']:
            with patch.dict(os.environ, {**base, 'GITHUB_REF': ref}, clear=True):
                with self.assertRaisesRegex(ValueError, 'restricted'):
                    release.metadata()
        for event in ['push', 'pull_request']:
            with patch.dict(os.environ, {**base, 'GITHUB_EVENT_NAME': event, 'GITHUB_REF': 'refs/heads/feature/vscode-extension'}, clear=True):
                self.assertFalse(release.metadata()['publish'])

    def test_version_stamping_is_idempotent_and_reruns_keep_version(self):
        with tempfile.TemporaryDirectory() as temp, patch.object(release, 'ROOT', Path(temp)):
            root = Path(temp)
            (root/'package.json').write_text(json.dumps({'name': 'ultrazohm-extension', 'version': '0.1.12'}))
            (root/'package-lock.json').write_text(json.dumps({'version': '0.1.12', 'packages': {'': {'version': '0.1.12'}}}))
            with patch.dict(os.environ, {'GITHUB_RUN_NUMBER': '43'}, clear=True):
                self.assertEqual(release.metadata(True)['version'], '0.1.43')
                self.assertEqual(release.metadata(True)['version'], '0.1.43')
                with patch.dict(os.environ, {'GITHUB_RUN_ATTEMPT': '2'}):
                    self.assertEqual(release.metadata()['version'], '0.1.43')
                self.assertEqual(json.loads((root/'package-lock.json').read_text())['packages']['']['version'], '0.1.43')
            for value in ['0', '-1', 'oops']:
                with patch.dict(os.environ, {'GITHUB_RUN_NUMBER': value}, clear=True):
                    with self.assertRaisesRegex(ValueError, 'run number'):
                        release.metadata()
            with patch.dict(os.environ, {}, clear=True):
                self.assertFalse(release.metadata()['publish'])

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
        with tempfile.TemporaryDirectory() as temp, patch.dict(os.environ, {'GITHUB_REF': '', 'UZ_EXTENSION_PUBLISH_PRERELEASE': ''}):
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
