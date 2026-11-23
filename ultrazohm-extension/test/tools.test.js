const { test } = require('node:test');
const assert = require('node:assert/strict');
const fs = require('node:fs');
const path = require('node:path');
const os = require('node:os');
const { resolveXsct, saveXsct } = require('../tools');

test('XSCT detection, saved preference precedence, preservation, and missing launcher', t => {
  const root = fs.mkdtempSync(path.join(os.tmpdir(), 'uz tools '));
  t.after(() => fs.rmSync(root, { recursive: true, force: true }));
  const bin = path.join(root, 'Vitis bin'); fs.mkdirSync(bin);
  const tool = path.join(bin, process.platform === 'win32' ? 'xsct.bat' : 'xsct');
  fs.writeFileSync(tool, 'test'); fs.chmodSync(tool, 0o755);
  assert.equal(resolveXsct(root, { PATH: bin }).path, tool);
  assert.ok(resolveXsct(root, { PATH: '' }).reason);
  const dir = path.join(root, 'artifacts', '_user'); fs.mkdirSync(dir, { recursive: true });
  fs.writeFileSync(path.join(dir, 'tools.json'), JSON.stringify({ other: 42 }));
  saveXsct(root, tool); assert.equal(resolveXsct(root, { PATH: '' }).path, tool);
  assert.equal(JSON.parse(fs.readFileSync(path.join(dir, 'tools.json'))).other, 42);
  fs.unlinkSync(tool); assert.ok(resolveXsct(root, { PATH: bin }).reason);
  saveXsct(root, null); assert.equal(JSON.parse(fs.readFileSync(path.join(dir, 'tools.json'))).xsct, null);
  fs.writeFileSync(path.join(dir, 'tools.json'), 'broken');
  assert.match(resolveXsct(root).reason, /Cannot read/); assert.throws(() => saveXsct(root, null));
});

test('nonexecutable Linux files and directories do not enable firmware', { skip: process.platform === 'win32' }, t => {
  const root = fs.mkdtempSync(path.join(os.tmpdir(), 'uz nonexec '));
  t.after(() => fs.rmSync(root, { recursive: true, force: true }));
  const tool = path.join(root, 'xsct'); fs.writeFileSync(tool, 'test'); fs.chmodSync(tool, 0o644);
  assert.ok(resolveXsct(root, { PATH: root }).reason); assert.throws(() => saveXsct(root, tool));
});
