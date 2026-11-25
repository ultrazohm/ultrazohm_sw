"""Offline Python configuration follows the service's Rust rules."""

import unittest
from pathlib import Path

from ultrazohm_cli.configuration import (
    channel_mapping,
    default_profile,
    remap_profile,
    validate_profile,
)

ROOT = Path(__file__).resolve().parents[2]


class ConfigurationTest(unittest.TestCase):
    def test_defaults_are_valid_for_checkout(self):
        mapping = channel_mapping(ROOT)
        profile = default_profile(ROOT)
        updated, removed = remap_profile(mapping, profile)
        self.assertEqual(removed, [])
        self.assertEqual(updated, validate_profile(profile))

    def test_remapping_resolves_alias_and_reports_removed_names(self):
        mapping = channel_mapping(ROOT)
        profile = default_profile()
        profile["sample_period_us"] = 50
        updated, removed = remap_profile(
            mapping, profile, {"1": "lifecheck", "2": "MISSING_SIGNAL"}
        )
        self.assertEqual(updated["initial_channels"], {"1": "JSO_lifecheck"})
        self.assertEqual(updated["sample_period_us"], 50)
        self.assertEqual(removed, ["MISSING_SIGNAL"])

    def test_invalid_preferences_are_rejected(self):
        for changes in ({"schema_version": 2}, {"sample_period_us": 0}, {"name": None}):
            with self.subTest(changes=changes):
                with self.assertRaises(ValueError):
                    validate_profile({**default_profile(), **changes})

    def test_remapping_rejects_unsupported_profile_schema(self):
        with self.assertRaisesRegex(RuntimeError, "schema_version"):
            remap_profile(
                channel_mapping(ROOT), {**default_profile(), "schema_version": 2}
            )
