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
        with self.assertRaisesRegex(ValueError, "schema_version"):
            remap_profile(
                channel_mapping(ROOT), {**default_profile(), "schema_version": 2}
            )

    def test_circular_input_raises_instead_of_crashing(self):
        profile = default_profile(ROOT)
        profile["extra"] = profile
        with self.assertRaisesRegex(ValueError, "Circular reference"):
            validate_profile(profile)

    def test_integer_channel_keys_are_accepted(self):
        profile = default_profile(ROOT)
        numeric = {
            **profile,
            "initial_channels": {
                int(channel): name
                for channel, name in profile["initial_channels"].items()
            },
        }
        self.assertEqual(validate_profile(numeric), validate_profile(profile))

    def test_non_finite_numbers_are_rejected_before_sending(self):
        from ultrazohm_cli import Client

        for value in (float("nan"), float("inf"), -float("inf")):
            with self.subTest(value=value):
                with self.assertRaisesRegex(ValueError, "not JSON compliant"):
                    validate_profile({**default_profile(), "sample_period_us": value})
                # Rejected locally: no service listens on this endpoint.
                with self.assertRaisesRegex(ValueError, "not JSON compliant"):
                    Client("127.0.0.1:9").set_variable("send_field_1", value)
