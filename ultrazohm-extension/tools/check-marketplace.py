"""Report per-platform public availability after upload; never republish."""
import time
import urllib.error
import urllib.request
import release

version = release.metadata()['version']
pending = set(release.TARGETS)
deadline = time.monotonic() + 120
while pending:
    for target in sorted(pending):
        url = f'https://marketplace.visualstudio.com/_apis/public/gallery/publishers/ZohmControlGmbH/vsextensions/ultrazohm-extension/{version}/vspackage?targetPlatform={target}'
        try:
            with urllib.request.urlopen(url, timeout=15) as response:
                response.read(1)
            print(f'{target} {version}: publicly available', flush=True)
            pending.remove(target)
        except (urllib.error.URLError, TimeoutError) as error:
            print(f'{target}: availability not confirmed: {error}', flush=True)
    if not pending or time.monotonic() >= deadline:
        break
    time.sleep(10)
if pending:
    print('::warning::Upload completed; public availability remains unconfirmed for '+', '.join(sorted(pending))+'. Check publisher processing status; do not rebuild.')
