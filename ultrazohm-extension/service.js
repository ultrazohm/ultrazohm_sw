const net = require('node:net');
function parseEndpoint(endpoint) {
  const match = /^127\.0\.0\.1:(\d+)$/.exec(endpoint);
  if (!match || Number(match[1]) < 1 || Number(match[1]) > 65535) {
    throw new Error('CLI endpoint must be 127.0.0.1:<port>, with a port between 1 and 65535.');
  }
  return { host: '127.0.0.1', port: Number(match[1]) };
}
function portInUse(endpoint) {
  const options = parseEndpoint(endpoint);
  return new Promise((resolve, reject) => {
    const socket = net.createConnection(options);
    const finish = (error, occupied) => { socket.destroy(); error ? reject(error) : resolve(occupied); };
    socket.once('connect', () => finish(null, true));
    socket.once('error', e => e.code === 'ECONNREFUSED' ? finish(null, false) : finish(e));
    socket.setTimeout(1500, () => finish(new Error('Could not check the CLI endpoint: connection timed out.')));
  });
}
module.exports = { portInUse, parseEndpoint };
