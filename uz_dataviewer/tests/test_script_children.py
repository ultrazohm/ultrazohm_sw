"""Worker completion must not leave background automation alive."""
import time
import pytest
from uz_dataviewer.scripting import ScriptRunner


def test_script_completion_terminates_background_child(tmp_path):
    pytest.importorskip('ultrazohm')
    ready, release, action = [tmp_path/name for name in ('ready', 'release', 'action')]
    child = tmp_path/'child.py'
    child.write_text('from pathlib import Path\nimport time\n'
        f'Path({str(ready)!r}).touch()\n'
        f'while not Path({str(release)!r}).exists(): time.sleep(.01)\n'
        f'Path({str(action)!r}).touch()\n')
    parent = tmp_path/'parent.py'
    parent.write_text('import subprocess,sys,time\nfrom pathlib import Path\n'
        'def run(uz):\n'
        f'    subprocess.Popen([sys.executable,{str(child)!r}])\n'
        f'    while not Path({str(ready)!r}).exists(): time.sleep(.01)\n')
    class Client:
        def stop(self): pass
    runner = ScriptRunner(lambda _: Client())
    try:
        runner.start(parent, '127.0.0.1:19740')
        deadline = time.monotonic()+10
        while runner.busy:
            runner.poll()
            assert time.monotonic()<deadline
            time.sleep(.01)
        assert ready.exists()
        release.touch()
        time.sleep(.2)
        assert not action.exists()
    finally:
        release.touch()
        runner.close()
