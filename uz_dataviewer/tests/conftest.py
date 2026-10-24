"""Keep persisted indexes and lazy CSV conversions out of the user's cache."""
import pytest


@pytest.fixture(autouse=True)
def isolated_app_cache(tmp_path, monkeypatch):
    monkeypatch.setenv('UZ_DATAVIEWER_CACHE', str(tmp_path / 'app-cache'))
