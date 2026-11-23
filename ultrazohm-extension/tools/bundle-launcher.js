// Snapshot the shared launcher at packaging time; do not maintain a fork.
const fs = require('node:fs');
const path = require('node:path');
const root = path.resolve(__dirname, '../..');
const target = path.resolve(__dirname, '../launcher');
fs.mkdirSync(target, { recursive: true });
for (const name of ['uz', 'uz.ps1', 'uz.py', 'uz_bootstrap.sh', 'uz_bootstrap.ps1', 'uz_shell.py', 'uz_venv.py', '.python-version', '.uv-version', 'requirements.txt']) {
  fs.copyFileSync(path.join(root, name), path.join(target, name));
}
