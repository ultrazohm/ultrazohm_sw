const fs = require('node:fs');
const path = require('node:path');
const { execFile } = require('node:child_process');

function validateSettings(file, platform = process.platform) {
  const expected = platform === 'win32' ? 'settings64.bat' : 'settings64.sh';
  if (!path.isAbsolute(file) || path.basename(file).toLowerCase() !== expected || !fs.statSync(file).isFile()) {
    throw new Error(`Select an absolute path to ${expected}.`);
  }
  fs.accessSync(file, fs.constants.R_OK); // Sourced scripts need not be executable.
  if (platform === 'win32' && /[%\r\n]/.test(file)) throw new Error('The Vitis settings path must not contain percent signs or newlines.');
}
function settingsEnvironment(file, inherited = process.env, platform = process.platform) {
  validateSettings(file, platform);
  const windows = platform === 'win32';
  const executable = windows ? path.join(inherited.SystemRoot || 'C:\\Windows', 'System32', 'cmd.exe') : '/bin/bash';
  const args = windows ? ['/d', '/u', '/s', '/c', '"call "%UZ_VITIS_SETTINGS%" >nul && set"']
    : ['--noprofile', '--norc', '-c', 'source "$1" >/dev/null && /usr/bin/env -0', 'uz-vitis', file];
  return new Promise((resolve, reject) => {
    execFile(executable, args, { env: { ...inherited, UZ_VITIS_SETTINGS: file }, encoding: windows ? 'utf16le' : 'utf8', windowsVerbatimArguments: windows, timeout: 30000, maxBuffer: 4 * 1024 * 1024, windowsHide: true }, (error, stdout, stderr) => {
      if (error) { reject(new Error(`Vitis settings failed: ${stderr || error.message}`)); return; }
      const result = {};
      for (const entry of stdout.split(windows ? /\r?\n/ : '\0')) {
        const separator = entry.indexOf('=');
        if (separator > 0) result[entry.slice(0, separator)] = entry.slice(separator + 1);
      }
      delete result.UZ_VITIS_SETTINGS;
      resolve(result);
    });
  });
}
module.exports = { validateSettings, settingsEnvironment };
