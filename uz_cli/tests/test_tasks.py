"""Task orchestration and CI release versions; no packages are built or installed."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from tasks import release_version


class ReleaseVersionTest(unittest.TestCase):
    def test_versions_order_by_run_and_mark_prereleases(self):
        self.assertEqual(release_version("0.2.0", "main", 42), "0.2.42")
        self.assertEqual(release_version("0.2.0", "develop", 43), "0.2.43.dev0")
        self.assertEqual(release_version("0.2.0", "feature/x", 44), "0.2.44.dev0")

    def test_versions_sort_above_the_former_post_releases(self):
        from packaging.version import Version
        newest_old = Version("0.1.0.post999999")
        self.assertGreater(Version(release_version("0.1.0", "main", 1)), newest_old)
        self.assertGreater(Version(release_version("0.1.0", "develop", 1)), newest_old)
        self.assertLess(Version(release_version("0.1.0", "develop", 5)),
                        Version(release_version("0.1.0", "main", 5)))

    def test_invalid_input(self):
        for base, run in (("0.2", 1), ("0.2.0", 0)):
            with self.assertRaises(ValueError):
                release_version(base, "main", run)


if __name__ == "__main__":
    unittest.main()
