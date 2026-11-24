// Read hw_server's processor list without issuing attach, stop, reset or continue.
const net = require('node:net');
function packet(payload) {
  const checksum = Buffer.from(payload).reduce((sum, byte) => (sum + byte) & 255, 0);
  return '$' + payload + '#' + checksum.toString(16).padStart(2, '0');
}
function processors(port, timeout = 5000) {
  return new Promise((resolve, reject) => {
    let buffer = '', output = '', finished = false, handshake = true;
    const socket = net.createConnection({ host: '127.0.0.1', port });
    const timer = setTimeout(() => finish(new Error(`hw_server on port ${port} did not answer monitor ps.`)), timeout);
    function finish(error) {
      if (finished) return;
      finished = true; clearTimeout(timer); socket.destroy();
      error ? reject(error) : resolve(output);
    }
    socket.on('error', finish);
    socket.on('end', () => finish(new Error('hw_server closed the processor query.')));
    socket.on('connect', () => socket.write('+' + packet('qSupported:multiprocess+')));
    socket.on('data', data => {
      buffer += data.toString('ascii');
      if (buffer.length + output.length > 1024 * 1024) return finish(new Error('hw_server processor response is too large.'));
      while (!finished) {
        const start = buffer.indexOf('$');
        if (start < 0) {
          if (buffer.includes('-')) return finish(new Error('hw_server rejected monitor ps.'));
          buffer = ''; return;
        }
        const end = buffer.indexOf('#', start);
        if (end < 0 || buffer.length < end + 3) return;
        const payload = buffer.slice(start + 1, end);
        if (packet(payload).slice(-2) !== buffer.slice(end + 1, end + 3).toLowerCase()) return finish(new Error('Invalid hw_server packet checksum.'));
        buffer = buffer.slice(end + 3); socket.write('+');
        if (handshake) {
          handshake = false;
          socket.write(packet('qRcmd,' + Buffer.from('ps').toString('hex')));
          continue;
        }
        if (payload === 'OK') return finish();
        if (/^O(?:[0-9a-f]{2})*$/i.test(payload)) output += Buffer.from(payload.slice(1), 'hex').toString('utf8');
        else if (/^(?:[0-9a-f]{2})+$/i.test(payload)) {
          // qRcmd may return a final hex-encoded OUTPUT response instead of
          // intermediate O packets followed by OK (Vitis 2022.2 uses this).
          output += Buffer.from(payload, 'hex').toString('utf8');
          return finish();
        } else return finish(new Error('hw_server does not support monitor ps: ' + payload));
      }
    });
  });
}
function processorId(text, core) {
  const pattern = new RegExp('^\\s*(\\d+):\\s+Cortex-' + core + '\\s+#0(?:\\s|$)', 'gmi');
  const matches = [...text.matchAll(pattern)];
  if (matches.length !== 1) throw new Error(`Expected exactly one Cortex-${core} #0 in hw_server; found ${matches.length}. Connect one UltraZohm board.\n${text}`);
  return Number(matches[0][1]);
}
module.exports = { packet, processors, processorId };
