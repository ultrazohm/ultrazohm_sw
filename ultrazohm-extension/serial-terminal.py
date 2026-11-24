"""Private pySerial transport; newline JSON framing keeps serial bytes out of IPC."""
import argparse
import base64
import json
from pathlib import Path
import queue
import re
import sys
import threading

sys.path.insert(0, str(Path(__file__).resolve().parent / 'runtime' / 'serial'))


def emit(event, **values):
    print(json.dumps({'event': event, **values}), flush=True)


def interface_number(port):
    if sys.platform.startswith('linux'):
        device = (Path('/sys/class/tty') / Path(port.device).name / 'device').resolve()
        for parent in [device, *device.parents]:
            try:
                return int((parent / 'bInterfaceNumber').read_text().strip(), 16)
            except (OSError, ValueError):
                pass
    match = re.search(r'MI_([0-9a-f]{2})', port.hwid or '', re.I)
    return int(match[1], 16) if match else None


def ports():
    from serial.tools import list_ports
    return [{'device': p.device, 'description': p.description, 'vid': p.vid, 'pid': p.pid,
             'serialNumber': p.serial_number, 'interface': p.interface, 'location': p.location,
             'product': p.product, 'interfaceNumber': interface_number(p)}
            for p in sorted(list_ports.comports())]


def connect(settings):
    import serial
    incoming = queue.Queue(maxsize=128)
    def receive():
        try:
            for line in sys.stdin:
                incoming.put(json.loads(line))
        except (ValueError, OSError):
            incoming.put({'command': 'close'})
        finally:
            incoming.put({'command': 'close'})
    # Open only a native serial device, never a serial URL or network endpoint.
    with serial.Serial(port=settings['device'], baudrate=settings['baud'],
                       bytesize=settings['dataBits'], parity=settings['parity'],
                       stopbits=settings['stopBits'], timeout=0.05, write_timeout=0.5,
                       xonxoff=settings['flowControl'] == 'xonxoff',
                       rtscts=settings['flowControl'] == 'rtscts',
                       **({'exclusive': True} if sys.platform != 'win32' else {})) as port:
        threading.Thread(target=receive, daemon=True).start()
        emit('connected', device=port.port)
        while True:
            for _ in range(128):
                try:
                    message = incoming.get_nowait()
                except queue.Empty:
                    break
                if message.get('command') == 'close':
                    return
                if message.get('command') == 'write':
                    port.write(base64.b64decode(message['data'], validate=True))
            data = port.read(min(port.in_waiting or 1, 4096))
            if data:
                emit('data', data=base64.b64encode(data).decode('ascii'))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('operation', choices=['list', 'connect', 'self-test'])
    parser.add_argument('--settings')
    args = parser.parse_args()
    try:
        if args.operation == 'list':
            print(json.dumps(ports()))
        elif args.operation == 'self-test':
            import serial
            with serial.serial_for_url('loop://', timeout=1) as port:
                port.write(b'UltraZohm serial\r\n')
                assert port.read(18) == b'UltraZohm serial\r\n'
            print('Bundled pySerial loopback passed')
        else:
            connect(json.loads(args.settings))
    except Exception as error:
        emit('error', message=str(error))
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
