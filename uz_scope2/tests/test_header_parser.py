from __future__ import annotations

from uz_scope2.javascope_header import (
    find_header,
    parse_header,
    parse_header_text,
)
from uz_scope2.protocol import slow_is_float


def test_parse_real_header_observables(real_header_path):
    cfg = parse_header(real_header_path)
    assert cfg.observables[0] == "JSO_ZEROVALUE"
    assert cfg.observables[1] == "JSO_ISR_ExecTime_us"
    assert cfg.observables[3] == "JSO_lifecheck"
    assert cfg.observables[4] == "JSO_ADC_A1_CH0"  # wizard-block entries included
    assert "JSO_ENDMARKER" not in cfg.observables
    assert cfg.observable_index["JSO_lifecheck"] == 3


def test_parse_real_header_buttons(real_header_path):
    cfg = parse_header(real_header_path)
    ids = cfg.button_id
    assert ids["Enable_System"] == 1
    assert ids["Enable_Control"] == 2
    assert ids["Stop"] == 3
    assert ids["Set_Send_Field_1"] == 4
    assert ids["Set_Send_Field_20"] == 23
    assert ids["My_Button_1"] == 24
    assert ids["My_Button_8"] == 31
    # The canonical id — test_server.py hardcodes 33, the header says 32.
    assert ids["Error_Reset"] == 32


def test_parse_real_header_slowdata(real_header_path):
    cfg = parse_header(real_header_path)
    assert cfg.slowdata[0] == "JSSD_ZEROVALUE"
    assert cfg.slowdata[5] == "JSSD_FLOAT_Error_Code"
    assert slow_is_float(cfg.slowdata[5])
    assert not slow_is_float(cfg.slowdata[0])


def test_parse_real_header_config_block(real_header_path):
    cfg = parse_header(real_header_path)
    # 0 = zerovalue entry, 1..20 = the visible fields.
    assert len(cfg.send_field_names) == 21
    assert cfg.send_field_names[1] == "dut_n_ref_rpm"
    assert cfg.send_field_units[2] == "rpm"
    assert cfg.send_field_units[7] == "-"
    assert len(cfg.receive_field_names) == 21
    assert cfg.receive_field_names[1] == "SecondsSinceSystemStart"
    assert cfg.receive_field_units[1] == "s"
    assert cfg.mybutton_labels[1] == "PT1_Eval_Profile"
    assert len(cfg.mybutton_labels) == 9  # zerovalue + 8 buttons
    # Receive-field data sources: entry 21 is the error-code source.
    assert len(cfg.slowdata_display) == 22
    assert cfg.slowdata_display[1] == "JSSD_FLOAT_SecondsSinceSystemStart"
    assert cfg.slowdata_display[5] == "JSSD_FLOAT_ZEROVALUE"
    assert cfg.slowdata_display[21] == "JSSD_FLOAT_Error_Code"


def test_parse_real_header_is_clean(real_header_path):
    cfg = parse_header(real_header_path)
    assert cfg.warnings == []


def test_find_header_from_repo(repo_root, real_header_path):
    assert find_header(repo_root) == real_header_path
    assert find_header(repo_root / "uz_scope2" / "tests") == real_header_path


def test_marker_diagnostics_on_broken_header():
    cfg = parse_header_text(
        """
        enum X {
            JSO_ZEROVALUE = 0,
            JSO_something,
        };
        """
    )
    assert any("JSO_ZEROVALUE..JSO_ENDMARKER" in w for w in cfg.warnings)
    assert cfg.observables == ["JSO_ZEROVALUE", "JSO_something"]


def test_comment_stripping():
    cfg = parse_header_text(
        """
        JSO_ZEROVALUE = 0, // zero
        JSO_a, /* inline */
        // JSO_commented_out,
        JSO_b,
        JSO_ENDMARKER
        """
    )
    assert cfg.observables == ["JSO_ZEROVALUE", "JSO_a", "JSO_b"]
