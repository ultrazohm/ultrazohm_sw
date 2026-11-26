import importlib.util
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch
from types import SimpleNamespace

spec = importlib.util.spec_from_file_location('publish_release', Path(__file__).with_name('publish-release.py'))
publish = importlib.util.module_from_spec(spec)
spec.loader.exec_module(publish)

class PublishTest(unittest.TestCase):
    def test_retry_checks_assets_and_only_uploads_missing_draft_assets(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            for name in ['example.vsix', 'SHA256SUMS', 'release-manifest.json']:
                (root/name).write_text('original')
            calls = []
            def run(args, **kwargs):
                calls.append(args)
                if args[1:3] == ['release', 'view']:
                    return SimpleNamespace(returncode=0, stdout=json.dumps({'isDraft': True, 'assets': [{'name': 'example.vsix'}]}))
                if args[1:3] == ['release', 'download']:
                    (Path(args[args.index('--dir')+1])/'example.vsix').write_text('original')
                return SimpleNamespace(returncode=0, stdout='')
            with patch.object(publish.release, 'aggregate'), patch.object(publish.release, 'metadata', return_value={'tag':'test','version':'1','prerelease':True}), patch.object(publish.subprocess, 'run', side_effect=run):
                publish.publish(root)
            uploads = [a[-1] for a in calls if a[1:3] == ['release', 'upload']]
            self.assertEqual(uploads, [str(root/'SHA256SUMS'), str(root/'release-manifest.json')])
            self.assertFalse(any('--clobber' in a for a in calls))

    def test_conflicting_existing_asset_blocks_publication(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root/'example.vsix').write_text('new')
            def run(args, **kwargs):
                if args[1:3] == ['release', 'view']:
                    return SimpleNamespace(returncode=0, stdout=json.dumps({'isDraft':False,'assets':[{'name':'example.vsix'}]}))
                if args[1:3] == ['release', 'download']:
                    (Path(args[args.index('--dir')+1])/'example.vsix').write_text('old')
                else:
                    self.fail('Unexpected mutation '+str(args))
                return SimpleNamespace(returncode=0, stdout='')
            with patch.object(publish.release, 'aggregate'), patch.object(publish.release, 'metadata', return_value={'tag':'test'}), patch.object(publish.subprocess, 'run', side_effect=run):
                with self.assertRaisesRegex(ValueError, 'differs'):
                    publish.publish(root)
