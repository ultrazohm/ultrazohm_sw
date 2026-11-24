"""Forward DAP to Microsoft C/C++; always detach hardware on Disconnect/Stop.

The remote target is already programmed. Custom GDB launch commands give us a
paused connection; DAP's default launch teardown would otherwise kill it.
"""
import json
import os
import subprocess
import sys
import threading


def messages(source):
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
        yield json.loads(body)


def write_message(destination, message):
    body = json.dumps(message).encode('utf-8')
    destination.write(b'Content-Length: ' + str(len(body)).encode('ascii') + b'\r\n\r\n' + body)
    destination.flush()


def foreign_source(source, root, core):
    """Only exclude files known to belong exclusively to the other application."""
    if not source or not root or core not in ('R5', 'A53'):
        return False
    other = 'FreeRTOS' if core == 'R5' else 'Baremetal'
    canonical = lambda value: os.path.normcase(os.path.realpath(value))
    source = canonical(source)
    for directory in ('software', 'workspace'):
        prefix = canonical(os.path.join(root, 'vitis', directory, other))
        if source.startswith(prefix + os.sep):
            return True
    return False


def forward_requests(source, destination, respond=None):
    root = core = None
    for message in messages(source):
        if message.get('type') == 'request':
            command = message.get('command')
            args = message.setdefault('arguments', {})
            if command == 'initialize':
                args['adapterID'] = 'cppdbg'
            elif command == 'launch':
                root = args.get('ultrazohmRepository')
                core = args.get('ultrazohmCore')
                args['type'] = 'cppdbg'
            elif command == 'disconnect':
                args['terminateDebuggee'] = False
            elif command == 'setBreakpoints' and respond is not None:
                if foreign_source(args.get('source', {}).get('path'), root, core):
                    # Do not even forward an empty request: GDB may match the
                    # basename and remove this core's legitimate breakpoints.
                    respond({'type': 'response', 'request_seq': message['seq'],
                             'command': command, 'success': True,
                             'body': {'breakpoints': [
                                 {'verified': False, 'line': bp.get('line'),
                                  'message': 'Source belongs to the other UltraZohm core.'}
                                 for bp in args.get('breakpoints', [])]}})
                    continue
        write_message(destination, message)


def main():
    adapter = subprocess.Popen([sys.argv[1]], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=sys.stderr.buffer)
    output_lock = threading.Lock()
    sequence = 0
    def respond(message):
        nonlocal sequence
        with output_lock:
            # Preserve adapter sequence IDs (VS Code may reply to its requests).
            # Synthetic responses use a separate range.
            if 'seq' not in message:
                sequence -= 1
                message['seq'] = sequence
            write_message(sys.stdout.buffer, message)
    def incoming():
        try:
            forward_requests(sys.stdin.buffer, adapter.stdin, respond)
        except (OSError, ValueError) as error:
            print('UltraZohm debugger: ' + str(error), file=sys.stderr)
        finally:
            adapter.stdin.close()
    thread = threading.Thread(target=incoming, daemon=True)
    thread.start()
    try:
        for message in messages(adapter.stdout):
            respond(message)
        return adapter.wait()
    finally:
        if adapter.poll() is None:
            adapter.terminate()
            adapter.wait()


if __name__ == '__main__':
    sys.exit(main())
