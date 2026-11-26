const { test } = require('node:test');
const assert = require('node:assert/strict');
const net = require('node:net');
const { parseEndpoint, portInUse } = require('../service');
test('endpoint rejects invalid ports and nonlocal addresses', () => {
  for (const value of ['localhost:1', '127.0.0.1:0', '127.0.0.1:65536', 'remote:123']) assert.throws(() => parseEndpoint(value));
  assert.equal(parseEndpoint('127.0.0.1:19740').port, 19740);
});
test('occupied endpoint detection without sending protocol data', async () => {
  const server = net.createServer(socket => socket.end());
  await new Promise(resolve => server.listen(0, '127.0.0.1', resolve));
  const endpoint = '127.0.0.1:' + server.address().port;
  try { assert.equal(await portInUse(endpoint), true); }
  finally { await new Promise(resolve => server.close(resolve)); }
  assert.equal(await portInUse(endpoint), false);
});
