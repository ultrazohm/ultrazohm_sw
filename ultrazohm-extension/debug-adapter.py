"""Forward DAP to Microsoft C/C++; always detach hardware on Disconnect/Stop.

The remote target is already programmed. Custom GDB launch commands give us a
paused connection; DAP's default launch teardown would otherwise kill it.
"""
import json
import subprocess
import sys
import threading


def forward_requests(source, destination):
    while True:
        header = source.readline()
        if not header:
            return
        length = None
        while header not in (b'\r\n', b'\n', b''):
            key, _, value = header.partition(b':')
            if key.lower() == b'content-length':
                length = int(value)
            header = source.readline()
        if length is None or length > 16 * 1024 * 1024:
            raise ValueError('Invalid debug adapter frame')
        body = source.read(length)
        if len(body) != length:
            return
        message = json.loads(body)
        if message.get('type') == 'request':
            if message.get('command') == 'initialize':
                message.setdefault('arguments', {})['adapterID'] = 'cppdbg'
            elif message.get('command') == 'launch':
                message.setdefault('arguments', {})['type'] = 'cppdbg'
            elif message.get('command') == 'disconnect':
                message.setdefault('arguments', {})['terminateDebuggee'] = False
        body = json.dumps(message).encode('utf-8')
        destination.write(b'Content-Length: ' + str(len(body)).encode('ascii') + b'\r\n\r\n' + body)
        destination.flush()


def main():
    adapter = subprocess.Popen([sys.argv[1]], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=sys.stderr.buffer)
    def incoming():
        try:
            forward_requests(sys.stdin.buffer, adapter.stdin)
        except (OSError, ValueError) as error:
            print('UltraZohm debugger: ' + str(error), file=sys.stderr)
        finally:
            adapter.stdin.close()
    thread = threading.Thread(target=incoming, daemon=True)
    thread.start()
    try:
        while data := adapter.stdout.read1(65536):
            sys.stdout.buffer.write(data)
            sys.stdout.buffer.flush()
        return adapter.wait()
    finally:
        if adapter.poll() is None:
            adapter.terminate()
            adapter.wait()


if __name__ == '__main__':
    sys.exit(main())
