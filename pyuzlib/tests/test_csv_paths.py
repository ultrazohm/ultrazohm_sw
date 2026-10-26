import pytest

from pyuzlib.pmsm import flux_map


@pytest.fixture
def checkout(tmp_path, monkeypatch):
    root = tmp_path / "checkout"
    (root / "pyuzlib").mkdir(parents=True)
    (root / "pyuzlib/pyproject.toml").touch()
    (root / "vitis").mkdir()
    # Deliberately use a different depth from the real package layout.
    module = root / "nested/package/flux_map.py"
    module.parent.mkdir(parents=True)
    module.touch()
    monkeypatch.setattr(flux_map, "__file__", str(module))
    (root / "data.csv").write_text("checkout data", encoding="utf-8")
    return root


@pytest.mark.parametrize("cwd", ["docs", "unrelated"])
def test_repository_fallback_uses_markers_not_parent_depth(checkout, tmp_path, monkeypatch, cwd):
    directory = checkout / "docs" if cwd == "docs" else tmp_path / "unrelated"
    directory.mkdir()
    monkeypatch.chdir(directory)

    assert flux_map.resolve_csv_path("data.csv") == checkout / "data.csv"


def test_cwd_file_takes_precedence_over_repository_file(checkout, tmp_path, monkeypatch):
    local = tmp_path / "data.csv"
    local.write_text("local data", encoding="utf-8")
    monkeypatch.chdir(tmp_path)

    assert flux_map.resolve_csv_path("data.csv") == local


def test_missing_checkout_file_raises_file_not_found(checkout, monkeypatch):
    monkeypatch.chdir(checkout)

    with pytest.raises(FileNotFoundError, match="missing.csv"):
        flux_map.resolve_csv_path("missing.csv")


@pytest.mark.parametrize("absolute", [False, True])
def test_standalone_install_accepts_existing_files(tmp_path, monkeypatch, absolute):
    monkeypatch.setattr(flux_map, "__file__", str(tmp_path / "site-packages/pyuzlib/pmsm/flux_map.py"))
    monkeypatch.chdir(tmp_path)
    local = tmp_path / "data.csv"
    local.write_text("local data", encoding="utf-8")

    assert flux_map.resolve_csv_path(local if absolute else "data.csv") == local


def test_standalone_install_does_not_search_arbitrary_ancestors(tmp_path, monkeypatch):
    module = tmp_path / "install/lib/python/site-packages/pyuzlib/pmsm/flux_map.py"
    monkeypatch.setattr(flux_map, "__file__", str(module))
    # The former parents[4] fallback would incorrectly select this file.
    stray = tmp_path / "install/lib/data.csv"
    stray.parent.mkdir(parents=True)
    stray.write_text("unrelated data", encoding="utf-8")
    monkeypatch.chdir(tmp_path)

    with pytest.raises(FileNotFoundError, match="data.csv"):
        flux_map.resolve_csv_path("data.csv")


def test_missing_absolute_path_does_not_try_repository_fallback(tmp_path, monkeypatch):
    def unexpected_lookup(_):
        pytest.fail("An absolute path must not trigger repository lookup")

    monkeypatch.setattr(flux_map, "repo_root_from", unexpected_lookup)

    with pytest.raises(FileNotFoundError, match="missing.csv"):
        flux_map.resolve_csv_path(tmp_path / "missing.csv")


def test_directory_is_not_a_csv_file(tmp_path, monkeypatch):
    monkeypatch.chdir(tmp_path)
    directory = tmp_path / "directory.csv"
    directory.mkdir()

    with pytest.raises(FileNotFoundError, match="directory.csv"):
        flux_map.resolve_csv_path(directory)
