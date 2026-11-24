// Run with --extensionTestsPath in an isolated native VS Code profile and empty folder.
// Uses fake repository/vendor launchers; never downloads packages or touches hardware.
const vscode = require('vscode');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const net = require('node:net');
const assert = require('node:assert/strict');
const pause = ms => new Promise(resolve => setTimeout(resolve, ms));
async function until(fn) {
  for (let i = 0; i < 100; i++) { if (fn()) return; await pause(100); }
  throw new Error('Timed out waiting for task lifecycle');
}
async function unusedEndpoint() {
  const server = net.createServer();
  await new Promise((resolve, reject) => { server.once('error', reject); server.listen(0, '127.0.0.1', resolve); });
  const endpoint = '127.0.0.1:' + server.address().port;
  await new Promise(resolve => server.close(resolve));
  return endpoint;
}
exports.run = async function () {
  const windows = process.platform === 'win32';
  const opened = vscode.workspace.workspaceFolders[0];
  const base = fs.mkdtempSync(path.join(os.tmpdir(), 'uz-host-fixture-'));
  const root = path.join(base, 'selected uz');
  const output = path.join(opened.uri.fsPath, 'host-smoke-result.json');
  fs.mkdirSync(path.join(root, 'artifacts/_user'), { recursive: true });
  fs.writeFileSync(path.join(root, 'uz.py'), '# fixture\n');
  fs.writeFileSync(path.join(root, '.python-version'), '3.12\n');
  fs.writeFileSync(path.join(root, '.uv-version'), '0.13.1\n');
  fs.writeFileSync(path.join(root, 'uz'), `#!/bin/bash
if [[ " $* " == *" --help "* ]]; then
  echo '--local --xsct --repo --interactive --no-reconnect'
  exit 0
fi
printf '%s\\n' "$PWD" "$*" "$UV_CACHE_DIR" >> '${base}/commands.log'
sleep 120
`, { mode: 0o755 });
  fs.writeFileSync(path.join(root, 'uz.ps1'), `if ($args -contains '--help') { Write-Output '--local --xsct --repo --interactive --no-reconnect'; exit 0 }\nStart-Sleep -Seconds 120\n`);
  const xsct = path.join(base, windows ? 'xsct.bat' : 'xsct');
  fs.writeFileSync(xsct, windows ? '@exit /b 0\r\n' : '#!/bin/sh\nexit 0\n', { mode: 0o755 });
  const settingsScript = path.join(base, windows ? 'settings64.bat' : 'settings64.sh');
  fs.writeFileSync(settingsScript, windows ? `@echo off\r\nset "PATH=${base};%PATH%"\r\nset "XILINX_VITIS=${base}"\r\n` : `export PATH='${base}':"$PATH"\nexport XILINX_VITIS='${base}'\n`);
  const started = new Set();
  const startListener = vscode.tasks.onDidStartTaskProcess(e => started.add(e.execution));
  const active = () => vscode.tasks.taskExecutions.filter(e => e.task.definition.type === 'ultrazohm');
  // Firmware API integration is tested separately against a real published service.
  const originalExecuteTask = vscode.tasks.executeTask;
  vscode.tasks.executeTask = async task => {
    if (task.definition.operation === 'flash') {
      const expected = path.join(extensionPath, 'flash.py');
      assert(task.execution.args.some(arg => windows ? arg.toLowerCase() === expected.toLowerCase() : arg === expected), JSON.stringify(task.execution.args));
      task.execution = new vscode.ProcessExecution(windows ? path.join(process.env.SystemRoot, 'System32/WindowsPowerShell/v1.0/powershell.exe') : '/bin/bash', windows ? ['-NoProfile', '-File', path.join(root, 'uz.ps1')] : [path.join(root, 'uz')], task.execution.options);
    }
    return originalExecuteTask(task);
  };
  const extensionPath = vscode.extensions.getExtension('ZohmControlGmbH.ultrazohm-extension').extensionPath;
  const errors = [];
  const originalError = vscode.window.showErrorMessage;
  vscode.window.showErrorMessage = async message => { errors.push(message); console.error(message); };
  const originalConfirmation = vscode.window.showWarningMessage;
  let flashConfirmations = 0;
  vscode.window.showWarningMessage = async (message, options, ...items) => {
    assert.equal(message, 'Flash UZ?'); assert.equal(options.modal, true);
    assert(options.detail.includes(root)); assert(items.includes('Flash UZ'));
    flashConfirmations++; return 'Flash UZ';
  };
  try {
    const extension = vscode.extensions.getExtension('ZohmControlGmbH.ultrazohm-extension');
    assert(extension); await extension.activate();
    const commands = await vscode.commands.getCommands(true);
    for (const name of ['ultrazohm.debug', 'ultrazohm.attach']) assert(commands.includes(name), name + ' missing');
    const config = vscode.workspace.getConfiguration('ultrazohm', opened.uri);
    for (const [key, value] of Object.entries({ repository: root, 'launcher.source': 'local', 'dataviewer.channel': 'prerelease',
      'cli.endpoint': await unusedEndpoint(), 'dataviewer.terminal': 'hidden' })) {
      await config.update(key, value, vscode.ConfigurationTarget.WorkspaceFolder);
    }
    await config.update('vitis.settingsScript', settingsScript, vscode.ConfigurationTarget.Global);
    for (const section of ['setup', 'softwareBuild', 'control']) {
      await vscode.commands.executeCommand('ultrazohm.' + section + '.focus');
    }
    await vscode.commands.executeCommand('ultrazohm.launch');
    await vscode.commands.executeCommand('ultrazohm.launch');
    assert.equal(active().length, 1);
    await vscode.commands.executeCommand('ultrazohm.cli');
    await vscode.commands.executeCommand('ultrazohm.venv');
    assert.equal(active().length, 3);
    for (const e of active()) {
      assert.equal(e.task.definition.repository, root);
      assert.equal(e.task.execution.options.cwd, root);
      assert(e.task.execution.args.includes(path.join(root, windows ? 'uz.ps1' : 'uz')));
    }
    const viewer = active().find(e => e.task.definition.action === 'viewer');
    assert.equal(viewer.task.presentationOptions.reveal, vscode.TaskRevealKind.Never);
    fs.writeFileSync(path.join(root, 'artifacts/_user/tools.json'), JSON.stringify({ xsct }));
    await vscode.commands.executeCommand('ultrazohm.refresh');
    for (const operation of ['generate', 'build', 'build-clean', 'flash']) {
      if (operation === 'flash') {
        const cli = active().find(e => e.task.definition.action === 'cli');
        await until(() => started.has(cli)); cli.terminate();
        await until(() => !active().includes(cli));
      }
      await vscode.commands.executeCommand('ultrazohm.' + operation);
      if (operation === 'flash') assert(active().some(e => e.task.definition.action === 'cli'));
      assert.deepEqual(errors, [], 'Launcher errors: ' + errors.join('; '));
      const build = active().find(e => e.task.definition.action === 'firmware');
      assert(build); assert.equal(build.task.execution.options.env.XILINX_VITIS, base); assert.equal(build.task.definition.operation, operation);
      if (operation !== 'flash') assert(build.task.execution.args.includes('--local'));

      await vscode.commands.executeCommand('ultrazohm.build');
      assert.equal(active().filter(e => e.task.definition.action === 'firmware').length, 1);
      await until(() => started.has(build));
      await pause(300); build.terminate(); await until(() => !active().includes(build));
    }
    assert.equal(flashConfirmations, 1);
    await config.update('dataviewer.terminal', 'visible', vscode.ConfigurationTarget.WorkspaceFolder);
    await vscode.commands.executeCommand('ultrazohm.launch');
    await until(() => vscode.window.activeTerminal?.name.includes('UltraZohm DataViewer'));
  } catch (error) {
    fs.writeFileSync(output, JSON.stringify({ passed: false, error: error.stack }));
    throw error;
  } finally {
    for (const execution of active()) {
      await until(() => started.has(execution)); execution.terminate();
    }
    await until(() => active().length === 0);
    startListener.dispose();
    vscode.window.showWarningMessage = originalConfirmation;
    vscode.window.showErrorMessage = originalError;
    vscode.tasks.executeTask = originalExecuteTask;
  }
  fs.writeFileSync(output, JSON.stringify({ passed: true, actions: ['viewer', 'cli', 'venv', 'generate', 'build', 'build-clean', 'flash'], selectedRepository: root }));
};
