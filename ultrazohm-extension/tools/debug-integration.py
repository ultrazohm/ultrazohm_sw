"""Exercise the real Microsoft adapter through our DAP proxy against local GDB."""
import argparse
import gzip
import json
import os
from pathlib import Path
import queue
import re
import shutil
import socket
import subprocess
import sys
import tempfile
import threading
import time
import urllib.request
import zipfile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from importlib.util import spec_from_file_location, module_from_spec
spec = spec_from_file_location('proxy', ROOT / 'debug-adapter.py')
proxy = module_from_spec(spec)
spec.loader.exec_module(proxy)

def run(adapter=None):
    with tempfile.TemporaryDirectory(prefix='uz-adapter-test-') as directory:
        root = Path(directory)
        if not adapter:
            archive = root/'cpp.vsix'
            url = 'https://marketplace.visualstudio.com/_apis/public/gallery/publishers/ms-vscode/vsextensions/cpptools/1.35.6/vspackage?targetPlatform=linux-x64'
            with urllib.request.urlopen(url, timeout=60) as response, archive.open('wb') as output:
                if response.headers.get('Content-Encoding') == 'gzip':
                    with gzip.GzipFile(fileobj=response) as decoded:
                        shutil.copyfileobj(decoded, output)
                else:
                    shutil.copyfileobj(response, output)
            with zipfile.ZipFile(archive) as package:
                manifest = json.loads(package.read('extension/package.json'))
                assert (manifest['publisher'], manifest['name'], manifest['version']) == ('ms-vscode', 'cpptools', '1.35.6'), manifest
                package.extractall(root/'cpp')
                for entry in package.infolist():
                    if entry.external_attr >> 16:
                        (root/'cpp'/entry.filename).chmod((entry.external_attr >> 16) & 0o777)
            adapter = root/'cpp/extension/debugAdapters/bin/OpenDebugAD7'
            # C/C++ restores executable permissions during extension activation.
            adapter.chmod(0o755)
        source = root/'vitis/software/Baremetal/main.c'
        source.parent.mkdir(parents=True)
        source.write_text('volatile int running = 1;\nint main(void) {\n  while (running) {}\n  return 0;\n}\n')
        executable = root/'target'
        subprocess.run(['gcc','-g','-O0',str(source),'-o',str(executable)],check=True)
        with socket.socket() as sock:
            sock.bind(('127.0.0.1',0)); port = sock.getsockname()[1]
        log = open(root/'server.log','w+')
        server = subprocess.Popen(['gdbserver','--once',f'127.0.0.1:{port}',str(executable)],stdout=log,stderr=log)
        debugger = None
        target_pid = None
        try:
            for _ in range(100):
                log.seek(0); output=log.read()
                match=re.search(r'pid = (\d+)',output)
                if match: target_pid=int(match[1])
                if 'Listening on port' in output: break
                if server.poll() is not None: raise RuntimeError(output)
                time.sleep(.05)
            else: raise RuntimeError('gdbserver startup timed out')
            debugger = subprocess.Popen([sys.executable,str(ROOT/'debug-adapter.py'),str(adapter)],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
            messages=queue.Queue()
            def receive():
                try:
                    for message in proxy.messages(debugger.stdout): messages.put(message)
                finally: messages.put({'event':'adapter-exited'})
            threading.Thread(target=receive,daemon=True).start()
            seq=0
            backlog=[]
            def send(command,arguments):
                nonlocal seq
                seq+=1
                proxy.write_message(debugger.stdin,{'seq':seq,'type':'request','command':command,'arguments':arguments})
                return seq
            def wait(predicate):
                deadline=time.monotonic()+30
                while time.monotonic()<deadline:
                    for i,message in enumerate(backlog):
                        if predicate(message): return backlog.pop(i)
                    message=messages.get(timeout=max(.1,deadline-time.monotonic()))
                    if message.get('event')=='adapter-exited': raise RuntimeError('Adapter exited unexpectedly')
                    backlog.append(message)
                raise RuntimeError('DAP request timed out')
            def response(request):
                reply=wait(lambda m:m.get('type')=='response' and m.get('request_seq')==request)
                assert reply.get('success'), reply
                return reply
            response(send('initialize',{'adapterID':'ultrazohm-gdb','linesStartAt1':True,'columnsStartAt1':True,'pathFormat':'path'}))
            launch=send('launch',{'type':'ultrazohm-gdb','request':'launch','name':'test','MIMode':'gdb','miDebuggerPath':shutil.which('gdb'),'program':str(executable),'cwd':str(root),'miDebuggerServerAddress':f'127.0.0.1:{port}','launchCompleteCommand':'None','stopAtConnect':True,'ultrazohmRepository':str(root),'ultrazohmCore':'R5'})
            wait(lambda m:m.get('event')=='initialized')
            foreign=response(send('setBreakpoints',{'source':{'path':str(root/'vitis/software/FreeRTOS/main.c')},'breakpoints':[{'line':3}]}))
            assert foreign['body']['breakpoints'][0]['verified'] is False
            own = response(send('setBreakpoints',{'source':{'path':str(source)},'breakpoints':[{'line':3}]}))
            assert own['body']['breakpoints'][0]['verified'], own
            response(send('configurationDone',{})); response(launch)
            # Disconnect must detach, leaving the simulated target alive.
            response(send('disconnect',{'terminateDebuggee':True}))
            assert debugger.wait(timeout=10) == 0, "DAP proxy failed during shutdown"
            assert target_pid, output
            os.kill(target_pid,0)
            assert Path(f'/proc/{target_pid}/stat').read_text().split()[2] != 'Z', 'Target was terminated instead of detached'
            print('Real C/C++ adapter: initialize, launch, breakpoint filtering and detach passed.')
        finally:
            if debugger and debugger.poll() is None: debugger.kill(); debugger.wait()
            if target_pid:
                try: os.kill(target_pid,9)
                except ProcessLookupError: pass
            if server.poll() is None: server.terminate()
            server.wait(timeout=10); log.close()

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--adapter',type=Path)
    run(parser.parse_args().adapter)
