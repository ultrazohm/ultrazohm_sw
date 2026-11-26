"""Publication reruns must fail closed when version names hide different bytes."""

import hashlib
import io
import json
import sys
import urllib.error
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import verify_artifacts as verify


@pytest.fixture
def release():
    return {
        "version": "1.0.0",
        "artifacts": [
            {
                "file": f"{name}-1.0.0-test.whl",
                "sha256": hashlib.sha256(b"wheel").hexdigest(),
                "size": 5,
            }
            for name in ("ultrazohm_cli", "ultrazohm_dataviewer")
        ],
    }


def fetcher(release, *, mismatch=False, body=b"wheel", missing=False):
    def fetch(url, **kwargs):
        if not url.endswith("/json"):
            return io.BytesIO(body)
        if missing:
            raise urllib.error.HTTPError(url, 404, "missing", {}, None)
        entry = next(
            e for e in release["artifacts"] if url.split("/")[-3] + "-" in e["file"]
        )
        return io.BytesIO(
            json.dumps(
                {
                    "urls": [
                        {
                            "filename": entry["file"],
                            "size": 5,
                            "digests": {
                                "sha256": "bad" if mismatch else entry["sha256"]
                            },
                            "url": "https://files.pythonhosted.org/wheel",
                        }
                    ]
                }
            ).encode()
        )

    return fetch


def test_pypi_rerun_matching_missing_and_mismatched(release):
    assert not verify.check_pypi(release, fetch=fetcher(release), complete=True)
    assert len(verify.check_pypi(release, fetch=fetcher(release, missing=True))) == 2
    with pytest.raises(ValueError, match="artifact mismatch"):
        verify.check_pypi(release, fetch=fetcher(release, mismatch=True))
    with pytest.raises(ValueError, match="download mismatch"):
        verify.check_pypi(release, fetch=fetcher(release, body=b"other"), complete=True)


@pytest.mark.parametrize("draft", [True, False])
@pytest.mark.parametrize("matching", [True, False])
def test_existing_github_assets_are_never_overwritten(
    tmp_path, monkeypatch, release, draft, matching
):
    for entry in release["artifacts"]:
        (tmp_path / entry["file"]).write_bytes(b"wheel")
    (tmp_path / "manifest.json").write_text(json.dumps(release))
    (tmp_path / "SHA256SUMS").write_text("checksums")
    names = [e["file"] for e in release["artifacts"]] + ["manifest.json", "SHA256SUMS"]
    calls = []

    def gh(*args):
        calls.append(args)
        if args[0] == "api":
            return json.dumps(
                [
                    [
                        {
                            "tag_name": "tag",
                            "draft": draft,
                            "assets": [{"name": n} for n in names],
                        }
                    ]
                ]
            )
        if args[:2] == ("release", "download"):
            output = Path(args[args.index("--dir") + 1])
            selected = (
                [args[args.index("--pattern") + 1]] if "--pattern" in args else names
            )
            for name in selected:
                (output / name).write_bytes(
                    (tmp_path / name).read_bytes() if matching else b"different"
                )
        return ""

    monkeypatch.setenv("GH_REPO", "owner/repo")
    monkeypatch.setattr(verify, "gh", gh)
    if matching:
        verify.publish_github(tmp_path, "tag", "true")
    else:
        with pytest.raises(ValueError, match="artifact mismatch"):
            verify.publish_github(tmp_path, "tag", "true")
        assert not any(c[:2] == ("release", "edit") for c in calls)
    assert not any(c[:2] == ("release", "upload") for c in calls)


@pytest.mark.parametrize("draft", [True, False])
def test_github_partial_release_only_uploads_missing_draft_assets(
    tmp_path, monkeypatch, release, draft
):
    for entry in release["artifacts"]:
        (tmp_path / entry["file"]).write_bytes(b"wheel")
    (tmp_path / "manifest.json").write_text(json.dumps(release))
    (tmp_path / "SHA256SUMS").write_text("checksums")
    names = [e["file"] for e in release["artifacts"]] + ["manifest.json", "SHA256SUMS"]
    calls = []

    def gh(*args):
        calls.append(args)
        if args[0] == "api":
            return json.dumps(
                [[{"tag_name": "tag", "draft": draft, "assets": [{"name": names[0]}]}]]
            )
        if args[:2] == ("release", "download"):
            output = Path(args[args.index("--dir") + 1])
            selected = (
                [args[args.index("--pattern") + 1]] if "--pattern" in args else names
            )
            for name in selected:
                (output / name).write_bytes((tmp_path / name).read_bytes())
        return ""

    monkeypatch.setenv("GH_REPO", "owner/repo")
    monkeypatch.setattr(verify, "gh", gh)
    if draft:
        verify.publish_github(tmp_path, "tag", "true")
        uploads = [Path(c[-1]).name for c in calls if c[:2] == ("release", "upload")]
        assert set(uploads) == set(names[1:])
        assert calls[-1][:2] == ("release", "edit")
    else:
        with pytest.raises(ValueError, match="incomplete"):
            verify.publish_github(tmp_path, "tag", "true")
        assert not any(c[:2] == ("release", "upload") for c in calls)
