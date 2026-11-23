// Runs the packaged extension, with hardware-free fixture tasks, in real VS Code.
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const assert = require('node:assert/strict');
const { runTests } = require('@vscode/test-electron');
(async () => {
  const directory = fs.mkdtempSync(path.join(os.tmpdir(), 'ultrazohm-extension-test-'));
  const workspace = path.join(directory, 'workspace');
  fs.mkdirSync(workspace);
  const extension = path.resolve(process.env.UZ_EXTENSION_TEST_PATH || path.join(__dirname, '..'));
  // Keep tests inside the extension path so VS Code supplies the same scoped API
  // object, including the fixture's confirmation override. The VSIX stays unchanged.
  const testDirectory = path.join(extension, '.host-tests');
  fs.mkdirSync(testDirectory, { recursive: true });
  const testPath = path.join(testDirectory, 'host-smoke.js');
  fs.copyFileSync(path.join(__dirname, '../test/host-smoke.js'), testPath);
  const launchArgs = [workspace, '--user-data-dir', path.join(directory, 'user'), '--extensions-dir', path.join(directory, 'extensions'),
    '--disable-workspace-trust', '--skip-welcome', '--skip-release-notes', '--disable-gpu'];
  if (process.platform === 'linux') launchArgs.push('--no-sandbox');
  console.log(`Testing ${extension}; isolated profile: ${directory}`);
  try { await runTests({
    version: process.env.VSCODE_TEST_VERSION || 'stable',
    ...(process.env.VSCODE_TEST_EXECUTABLE ? { vscodeExecutablePath: process.env.VSCODE_TEST_EXECUTABLE } : {}),
    extensionDevelopmentPath: extension,
    extensionTestsPath: testPath, launchArgs,
  }); } finally { fs.rmSync(testDirectory, { recursive: true, force: true }); }
  assert.equal(JSON.parse(fs.readFileSync(path.join(workspace, 'host-smoke-result.json'))).passed, true);
  console.log('Packaged extension host smoke test passed.');
})().catch(error => { console.error(error); process.exitCode = 1; });
