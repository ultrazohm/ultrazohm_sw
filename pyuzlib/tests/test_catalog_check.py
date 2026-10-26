from pathlib import Path

import pytest

from pyuzlib import flux_map_catalog, machine_catalog


@pytest.fixture(params=[machine_catalog, flux_map_catalog], ids=["machines", "maps"])
def catalog_cli(request):
    module = request.param
    output_options = (
        ("--inventory-output", "--header-output")
        if module is machine_catalog
        else ("--header-output", "--diffind-header-output")
    )
    return module.main, output_options


def cli_outputs(directory, options):
    paths = [directory / f"artifact-{index}" for index in range(len(options))]
    args = [arg for option, path in zip(options, paths) for arg in (option, str(path))]
    return paths, args


def forbid_writes(monkeypatch):
    def fail(*args, **kwargs):
        pytest.fail("--check attempted a filesystem write")

    original_open = Path.open

    def read_only_open(path, mode="r", *args, **kwargs):
        if any(flag in mode for flag in "wax+"):
            fail()
        return original_open(path, mode, *args, **kwargs)

    monkeypatch.setattr(Path, "open", read_only_open)
    for method in ("mkdir", "write_text", "write_bytes", "unlink", "rename", "replace"):
        monkeypatch.setattr(Path, method, fail)


@pytest.mark.parametrize("stale_indices", [(), (0,), (1,), (0, 1)])
def test_check_is_read_only_and_reports_every_stale_output(
    catalog_cli, tmp_path, monkeypatch, capsys, stale_indices
):
    main, options = catalog_cli
    paths, args = cli_outputs(tmp_path, options)
    assert main(args) == 0
    for index in stale_indices:
        paths[index].write_text("stale artifact\n", encoding="utf-8")
    before = [(path.read_bytes(), path.stat().st_mtime_ns) for path in paths]
    capsys.readouterr()
    forbid_writes(monkeypatch)

    assert main(["--check", *args]) == (1 if stale_indices else 0)

    assert [(path.read_bytes(), path.stat().st_mtime_ns) for path in paths] == before
    output = capsys.readouterr().out
    if stale_indices:
        for index in stale_indices:
            assert f"Stale generated artifact: {paths[index]}" in output
            assert f"--- {paths[index]}" in output
            assert f"+++ {paths[index]} (expected)" in output
        assert "Regenerate" in output
        assert "--check" not in output
    else:
        assert "up-to-date" in output


def test_check_missing_outputs_does_not_create_directories(
    catalog_cli, tmp_path, monkeypatch, capsys
):
    main, options = catalog_cli
    directory = tmp_path / "missing" / "nested"
    paths, args = cli_outputs(directory, options)
    forbid_writes(monkeypatch)

    assert main(["--check", *args]) == 1

    output = capsys.readouterr().out
    for path in paths:
        assert f"Missing generated artifact: {path}" in output
        assert not path.exists()
    assert not directory.parent.exists()


def test_generated_content_is_independent_of_output_directory(catalog_cli, tmp_path):
    main, options = catalog_cli
    first, first_args = cli_outputs(tmp_path / "first", options)
    second, second_args = cli_outputs(tmp_path / "second", options)
    assert main(first_args) == main(second_args) == 0
    assert [path.read_bytes() for path in first] == [path.read_bytes() for path in second]


def test_check_reports_missing_and_stale_outputs_together(
    catalog_cli, tmp_path, monkeypatch, capsys
):
    main, options = catalog_cli
    paths, args = cli_outputs(tmp_path, options)
    paths[1].write_bytes(b"stale\n")
    forbid_writes(monkeypatch)

    assert main(["--check", *args]) == 1

    output = capsys.readouterr().out
    assert f"Missing generated artifact: {paths[0]}" in output
    assert f"Stale generated artifact: {paths[1]}" in output


def test_check_matches_committed_outputs(catalog_cli, monkeypatch):
    main, _ = catalog_cli
    forbid_writes(monkeypatch)
    assert main(["--check"]) == 0


@pytest.mark.parametrize("mutation", [["--renumber"], ["add_machine", "motor", "dataset"]])
def test_check_rejects_mutating_commands_before_touching_sources(
    tmp_path, monkeypatch, capsys, mutation
):
    source = tmp_path / "must-not-be-created"
    forbid_writes(monkeypatch)
    with pytest.raises(SystemExit) as error:
        machine_catalog.main(["--uz-pmsm-dir", str(source), "--check", *mutation])
    assert error.value.code == 2
    assert "--check cannot be combined" in capsys.readouterr().err
    assert not source.exists()


def test_check_is_byte_exact(tmp_path, capsys):
    from pyuzlib._generated_artifacts import check_generated_artifacts

    artifact = tmp_path / "artifact"
    artifact.write_bytes(b"same text\r\n")
    assert check_generated_artifacts(
        {artifact: "same text\n"}, regenerate_args=["generator", "path with spaces"]
    ) == 1
    output = capsys.readouterr().out
    assert "Stale" in output
    assert "'path with spaces'" in output
