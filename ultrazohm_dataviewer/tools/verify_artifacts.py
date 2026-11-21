"""Verify immutable release bytes before uploads and after publication."""

import argparse
import hashlib
import json
import os
import subprocess
import tempfile
import time
import urllib.error
import urllib.request
from pathlib import Path


def digest(path):
    with Path(path).open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def read_manifest(path):
    data = json.loads(Path(path).read_text())
    names = [e["file"] for e in data["artifacts"]]
    if len(names) != len(set(names)) or any(Path(n).name != n for n in names):
        raise ValueError("Invalid artifact filenames")
    return data


def check_pypi(data, *, complete=False, fetch=None):
    """Check both packages before either upload; postflight also hashes downloads."""
    fetch = fetch or urllib.request.urlopen
    missing = []
    for package in ("ultrazohm_cli", "ultrazohm_dataviewer"):
        expected = {
            e["file"]: e
            for e in data["artifacts"]
            if e["file"].startswith(package + "-") and e["file"].endswith(".whl")
        }
        if not expected:
            raise ValueError(f"No wheels for {package}")
        try:
            with fetch(
                f"https://pypi.org/pypi/{package}/{data['version']}/json", timeout=60
            ) as response:
                published = json.load(response)["urls"]
        except urllib.error.HTTPError as error:
            if error.code != 404:
                raise
            published = []
        seen = set()
        for item in published:
            name = item["filename"]
            entry = expected.get(name)
            if (
                entry is None
                or item["digests"]["sha256"] != entry["sha256"]
                or item["size"] != entry["size"]
            ):
                raise ValueError(f"PyPI artifact mismatch: {name}")
            seen.add(name)
            if complete:
                sha = hashlib.sha256()
                size = 0
                with fetch(item["url"], timeout=60) as response:
                    while block := response.read(1024 * 1024):
                        sha.update(block)
                        size += len(block)
                if sha.hexdigest() != entry["sha256"] or size != entry["size"]:
                    raise ValueError(f"PyPI download mismatch: {name}")
        missing.extend(sorted(expected.keys() - seen))
    return missing


def verify_pypi(path, complete=False, attempts=12):
    data = read_manifest(path)
    for attempt in range(attempts if complete else 1):
        missing = check_pypi(data, complete=complete)
        if not complete or not missing:
            return
        if attempt + 1 < attempts:
            time.sleep(10)
    raise ValueError(f"PyPI artifacts missing: {missing}")


def gh(*args):
    return subprocess.check_output(["gh", *args], text=True)


def publish_github(directory, tag, prerelease):
    """Resume matching drafts; never replace assets or accept incomplete releases."""
    directory = Path(directory).resolve()
    data = read_manifest(directory / "manifest.json")
    expected = {e["file"]: e["sha256"] for e in data["artifacts"]}
    for name in ("manifest.json", "SHA256SUMS"):
        expected[name] = digest(directory / name)
    for name, sha in expected.items():
        if digest(directory / name) != sha:
            raise ValueError(f"Local artifact mismatch: {name}")
    # Use the API so missing releases are distinguished from authentication/network failures.
    repo = os.environ["GH_REPO"]
    releases = json.loads(gh("api", "--paginate", "--slurp", f"repos/{repo}/releases"))
    release = next((r for page in releases for r in page if r["tag_name"] == tag), None)
    if release is None:
        gh(
            "release",
            "create",
            tag,
            "--target",
            os.environ["GITHUB_SHA"],
            "--draft",
            "--title",
            f"UltraZohm {data['version']}",
            "--notes-file",
            str(directory / "release-notes.md"),
            f"--prerelease={prerelease}",
            "--latest=false",
        )
        release = {"draft": True, "assets": []}
    present = {a["name"] for a in release["assets"]}
    if present - expected.keys():
        raise ValueError(f"Unexpected GitHub assets: {present - expected.keys()}")
    with tempfile.TemporaryDirectory() as temporary:
        for name in sorted(present):
            gh("release", "download", tag, "--pattern", name, "--dir", temporary)
            if digest(Path(temporary) / name) != expected[name]:
                raise ValueError(f"GitHub artifact mismatch: {name}")
    missing = expected.keys() - present
    if not release["draft"]:
        if missing:
            raise ValueError(
                f"Published GitHub release is incomplete: {sorted(missing)}"
            )
        return
    for name in sorted(missing):
        gh("release", "upload", tag, str(directory / name))
    # Verify bytes uploaded by this invocation before making the draft public.
    with tempfile.TemporaryDirectory() as temporary:
        gh("release", "download", tag, "--dir", temporary)
        for name, sha in expected.items():
            if digest(Path(temporary) / name) != sha:
                raise ValueError(f"GitHub download mismatch: {name}")
    gh(
        "release",
        "edit",
        tag,
        "--draft=false",
        f"--prerelease={prerelease}",
        "--latest=false",
    )


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    pypi = sub.add_parser("pypi")
    pypi.add_argument("manifest")
    pypi.add_argument("--complete", action="store_true")
    github = sub.add_parser("github")
    github.add_argument("directory")
    github.add_argument("tag")
    github.add_argument("prerelease", choices=("true", "false"))
    args = parser.parse_args()
    if args.command == "pypi":
        verify_pypi(args.manifest, args.complete)
    else:
        publish_github(args.directory, args.tag, args.prerelease)
