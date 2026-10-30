"""Select and download public GitHub CLI release wheels (no build tools needed)."""
import configparser
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import tempfile
from zipfile import BadZipFile, ZipFile
from urllib.parse import urlparse
from urllib.request import Request, urlopen

REPOSITORY = "ultrazohm/ultrazohm_sw"
TESTING_BRANCH = "feature/uz_cli26"
TAG_PREFIXES = {"stable": "uz-cli-v", "testing": "uz-cli-testing-v"}


def detect_channel(repository):
    try:
        result = subprocess.run(["git", "branch", "--show-current"], cwd=repository,
                                capture_output=True, text=True, check=True)
        return "testing" if result.stdout.strip() == TESTING_BRANCH else "stable"
    except (OSError, subprocess.CalledProcessError):
        return "stable"


def compatible_wheels(names, python, env):
    """Use tags from the destination interpreter, sorted by version and tag rank."""
    code = '''
import json, sys
from pathlib import Path
from packaging.tags import sys_tags
from packaging.utils import parse_wheel_filename
supported = {tag: index for index, tag in enumerate(sys_tags())}
found = []
for name in json.load(sys.stdin):
    try:
        package, version, build, tags = parse_wheel_filename(Path(name).name)
        ranks = [supported[tag] for tag in tags if tag in supported]
        if package == 'ultrazohm' and ranks:
            found.append((version, -min(ranks), name))
    except ValueError:
        pass
print(json.dumps([name for _, _, name in sorted(found, reverse=True)]))
'''
    result = subprocess.run([str(python), "-c", code], input=json.dumps([str(n) for n in names]),
                            env=env, capture_output=True, text=True, check=True)
    return json.loads(result.stdout)


def validate_cli_wheel(path):
    """Reject legacy library-only wheels before replacing a working CLI install."""
    try:
        with ZipFile(path) as wheel:
            entries = [name for name in wheel.namelist()
                       if name.endswith(".dist-info/entry_points.txt")]
            if len(entries) == 1:
                config = configparser.ConfigParser(interpolation=None)
                config.read_string(wheel.read(entries[0]).decode("utf-8"))
                if config.get("console_scripts", "ultrazohm", fallback="").strip():
                    return
    except (BadZipFile, UnicodeError, configparser.Error) as error:
        raise ValueError(f"Invalid CLI wheel {Path(path).name}: {error}") from error
    raise ValueError(f"Wheel {Path(path).name} has no ultrazohm console command; "
                     "use a newer CLI wheel or --latest")


def local_cli_wheels(names, python, env):
    """Compatible CLI wheels, newest file first (versions may repeat locally)."""
    valid = []
    for name in compatible_wheels(names, python, env):
        path = Path(name)
        try:
            validate_cli_wheel(path)
        except ValueError as error:
            print(f"Skipping local wheel: {error}", flush=True)
            continue
        valid.append(path)
    # Stable sorting preserves version/tag preference for equal timestamps.
    return sorted(valid, key=lambda path: path.stat().st_mtime_ns, reverse=True)


def choose_local(wheels, channel, interactive, input_fn=input):
    """None means download newest; never silently choose a local build in CI."""
    if not wheels:
        return None
    if not interactive:
        raise ValueError("Compatible local wheels exist; use --wheel PATH, --local-newest, "
                         "or --latest when standard input is not interactive.")
    newest = Path(wheels[0])  # Already sorted by local file modification time.
    print("Choose an UltraZohm wheel:")
    print(f"  1. Use latest local build: {newest.name}")
    print(f"  2. Download latest from GitHub ({channel})")
    while True:
        answer = input_fn("Selection [1]: ").strip() or "1"
        if answer == "1":
            return newest
        if answer == "2":
            return None
        print("Enter 1 or 2.")


def read_url(url):
    request = Request(url, headers={"User-Agent": "ultrazohm-wheel-setup",
                                    "Accept": "application/vnd.github+json"})
    with urlopen(request, timeout=60) as response:
        return response.read()


def latest_release(channel, fetch=read_url):
    # Do not use /releases/latest: that endpoint also includes unrelated releases
    # and excludes the testing channel. Scan all pages, then order by publication.
    releases = []
    page = 1
    while True:
        batch = json.loads(fetch(f"https://api.github.com/repos/{REPOSITORY}/releases?per_page=100&page={page}"))
        for release in batch:
            if (not release["draft"] and release["tag_name"].startswith(TAG_PREFIXES[channel])
                    and release["prerelease"] == (channel == "testing")):
                releases.append(release)
        if len(batch) < 100:
            break
        page += 1
    if not releases:
        raise ValueError(f"No published {channel} CLI release exists in {REPOSITORY} yet. "
                         "Use --wheel PATH or select another --channel.")
    return max(releases, key=lambda release: (release["published_at"], release["id"]))


def asset_url(asset):
    url = asset["browser_download_url"]
    parsed = urlparse(url)
    if (parsed.scheme != "https" or parsed.netloc != "github.com"
            or not parsed.path.startswith(f"/{REPOSITORY}/releases/download/")):
        raise ValueError("Release asset has an unexpected download URL")
    return url


def download_latest(channel, destination, python, env, fetch=read_url):
    release = latest_release(channel, fetch)
    assets = {asset["name"]: asset for asset in release["assets"]}
    names = [name for name in assets if re.fullmatch(r"ultrazohm-[A-Za-z0-9_.+-]+\.whl", name)]
    matches = compatible_wheels(names, python, env)
    if not matches:
        raise ValueError(f"Newest {channel} release {release['tag_name']} has no wheel compatible "
                         "with this Python/OS/architecture. No older release was selected.")
    name = matches[0]
    if "SHA256SUMS" not in assets:
        raise ValueError(f"Release {release['tag_name']} is missing SHA256SUMS")
    checksums = fetch(asset_url(assets["SHA256SUMS"])).decode("utf-8")
    expected = None
    for line in checksums.splitlines():
        parts = line.split()
        if len(parts) == 2 and parts[1].lstrip("*") == name:
            if expected is not None or not re.fullmatch(r"[0-9a-fA-F]{64}", parts[0]):
                raise ValueError("Invalid or duplicate wheel checksum")
            expected = parts[0].lower()
    if expected is None:
        raise ValueError(f"No checksum provided for {name}")
    print(f"Downloading {release['tag_name']}: {name}", flush=True)
    content = fetch(asset_url(assets[name]))
    if hashlib.sha256(content).hexdigest() != expected:
        raise ValueError(f"Checksum mismatch for {name}; download was not installed")
    destination.mkdir(parents=True, exist_ok=True)
    target = destination / name
    # Only replace an existing cached wheel after verification is complete.
    temporary = None
    try:
        with tempfile.NamedTemporaryFile(dir=destination, suffix=".download", delete=False) as stream:
            temporary = Path(stream.name)
            stream.write(content)
        os.replace(temporary, target)
    finally:
        if temporary is not None:
            temporary.unlink(missing_ok=True)
    return target
