from __future__ import annotations

import json

import pytest

from uz_scope.config import (
    ChannelSettings,
    ImportReport,
    ScopeConfig,
    import_properties,
)
from uz_scope.protocol import FrameGeometry


def test_defaults():
    cfg = ScopeConfig()
    assert cfg.ip == "192.168.1.233"
    assert cfg.port == 1000
    assert cfg.geometry == FrameGeometry(20, 15)
    assert cfg.ack_pacing is True
    assert len(cfg.channel_settings) == 20
    assert cfg.logging.format == "parquet"


def test_json_roundtrip(tmp_path):
    cfg = ScopeConfig()
    cfg.ip = "10.0.0.5"
    cfg.channels = 200
    cfg.ensure_channel_count()
    cfg.channel_settings[7] = ChannelSettings(observable=46, visible=True, scale=2.0)
    cfg.trigger.edge = "falling"
    cfg.logging.format = "csv"
    path = tmp_path / "settings.json"
    cfg.save(path)

    loaded = ScopeConfig.load(path)
    assert loaded.ip == "10.0.0.5"
    assert loaded.channels == 200
    assert len(loaded.channel_settings) == 200
    assert loaded.channel_settings[7].observable == 46
    assert loaded.channel_settings[7].visible is True
    assert loaded.channel_settings[7].scale == 2.0
    assert loaded.trigger.edge == "falling"
    assert loaded.logging.format == "csv"


def test_load_ignores_unknown_keys(tmp_path):
    data = ScopeConfig().to_json()
    obj = json.loads(data)
    obj["some_future_key"] = {"nested": True}
    obj["trigger"]["another_future_key"] = 1
    path = tmp_path / "settings.json"
    path.write_text(json.dumps(obj), encoding="utf-8")
    loaded = ScopeConfig.load(path)  # must not raise
    assert loaded.port == 1000


def test_load_rejects_non_object(tmp_path):
    path = tmp_path / "bad.json"
    path.write_text("[1, 2, 3]", encoding="utf-8")
    with pytest.raises(ValueError):
        ScopeConfig.load(path)


def test_ensure_channel_count_truncates_and_pads():
    cfg = ScopeConfig()
    cfg.channels = 3
    cfg.ensure_channel_count()
    assert len(cfg.channel_settings) == 3
    cfg.channels = 5
    cfg.ensure_channel_count()
    assert len(cfg.channel_settings) == 5


def test_import_real_properties(real_properties_path):
    cfg = ScopeConfig()
    report = import_properties(real_properties_path, cfg)
    assert isinstance(report, ImportReport)
    assert report.errors == []

    assert cfg.ip == "192.168.1.233"
    assert cfg.samples_per_packet == 15
    assert cfg.channels == 20
    assert cfg.timestep_usec == 100.0
    assert cfg.auto_detect_rate is True
    # sendZeroAckCommand = 0 in the repo file -> ack pacing off.
    assert cfg.ack_pacing is False

    assert cfg.trigger.channel == 0
    assert cfg.trigger.edge == "rising"
    assert cfg.trigger.level == 0.0
    assert cfg.trigger.pretrigger == 0.5

    # preSelectedChannelNumbers = 1 ; 3 ; 2 ; 46 ; ...
    assert cfg.channel_settings[0].observable == 1
    assert cfg.channel_settings[1].observable == 3
    assert cfg.channel_settings[3].observable == 46
    # preSelectedChannelVisibility = 1 ; 0 ; 1 ; ...
    assert cfg.channel_settings[0].visible is True
    assert cfg.channel_settings[1].visible is False
    assert all(ch.scale == 1.0 for ch in cfg.channel_settings)
    assert all(ch.offset == 0.0 for ch in cfg.channel_settings)

    # ParameterID / ScopeDevTab are intentionally not part of uz_scope.
    assert "ParameterID" in report.ignored
    assert "ScopeDevTab" in report.ignored


def test_import_properties_edge_cases(tmp_path):
    path = tmp_path / "props.ini"
    path.write_text(
        "\n".join(
            [
                "# comment",
                "ipAdress = 127.0.0.1",
                "triggerEdge = 2",
                "pretrigger = 1.5",
                "sendZeroAckCommand = 1",
                "bogusKey = 42",
                "scopeChannelNumber = notanumber",
            ]
        ),
        encoding="utf-8",
    )
    cfg = ScopeConfig()
    report = import_properties(path, cfg)
    assert cfg.ip == "127.0.0.1"
    assert cfg.trigger.edge == "falling"
    assert cfg.trigger.pretrigger == 1.0  # clamped
    assert cfg.ack_pacing is True
    assert "bogusKey" in report.ignored
    assert any("scopeChannelNumber" in e for e in report.errors)
    assert cfg.channels == 20  # unchanged after the bad value
