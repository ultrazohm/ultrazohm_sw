const fs = require('node:fs');
const path = require('node:path');
const { randomUUID } = require('node:crypto');

function readTools(root) {
  if (!root) return {};
  const file = path.join(root, 'artifacts', '_user', 'tools.json');
  if (!fs.existsSync(file)) return {};
  const value = JSON.parse(fs.readFileSync(file, 'utf8'));
  if (!value || Array.isArray(value) || typeof value !== 'object') {
    throw new Error('Invalid artifacts/_user/tools.json: expected an object.');
  }
  return value;
}

function usable(file, platform = process.platform) {
  try {
    if (!fs.statSync(file).isFile()) return false;
    fs.accessSync(file, platform === 'win32' ? fs.constants.F_OK : fs.constants.X_OK);
    return true;
  } catch { return false; }
}

function resolveXsct(root, env = process.env, platform = process.platform) {
  try {
    const saved = readTools(root).xsct;
    if (saved != null) {
      if (typeof saved !== 'string' || !path.isAbsolute(saved) || !usable(saved, platform)) {
        return { reason: 'Saved XSCT launcher is missing or not executable. Select XSCT again.' };
      }
      return { path: saved, source: 'saved' };
    }
    const key = Object.keys(env).find(k => k.toLowerCase() === 'path');
    const names = platform === 'win32' ? ['xsct.exe', 'xsct.cmd', 'xsct.bat'] : ['xsct'];
    for (const dir of (env[key] || '').split(platform === 'win32' ? ';' : ':')) {
      if (!dir) continue;
      for (const name of names) {
        const file = path.resolve(dir, name);
        if (usable(file, platform)) return { path: file, source: 'PATH' };
      }
    }
    return { reason: 'XSCT not found. Select the Vitis XSCT launcher to enable firmware actions.' };
  } catch (e) { return { reason: `Cannot read XSCT settings: ${e.message}` }; }
}

function saveXsct(root, selected) {
  if (selected !== null && (!path.isAbsolute(selected) || !usable(selected))) {
    throw new Error('Select an existing, executable XSCT launcher.');
  }
  const value = readTools(root);
  value.xsct = selected;
  const dir = path.join(root, 'artifacts', '_user');
  fs.mkdirSync(dir, { recursive: true });
  const temporary = path.join(dir, `tools-${randomUUID()}.tmp`);
  try {
    fs.writeFileSync(temporary, JSON.stringify(value, null, 2) + '\n', { flag: 'wx' });
    fs.renameSync(temporary, path.join(dir, 'tools.json'));
  } finally {
    if (fs.existsSync(temporary)) fs.unlinkSync(temporary);
  }
}
module.exports = { resolveXsct, saveXsct, usable };
