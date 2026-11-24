const vscode = require('vscode');
const fs = require('node:fs');
const path = require('node:path');
const { randomUUID } = require('node:crypto');
const { environment } = require('./runtime-env');
const { resolveXsct, saveXsct } = require('./tools');
const { portInUse } = require('./service');
const { settingsEnvironment } = require('./vitis-env');
const { bridge } = require('./debug-tools');
const { controller } = require('./debug-controller');
const { readHelp } = require('./cli-capabilities');
const { activateSerial } = require('./serial-controller');

const actions = {
  updatePackages: { label: 'Update Python packages', name: 'UltraZohm Update Python Packages', group: 'packages', icon: 'cloud-download' },
  launch: { label: 'Launch DataViewer', name: 'UltraZohm DataViewer', group: 'viewer', icon: 'graph' },
  cli: { label: 'Open interactive CLI', name: 'UltraZohm Interactive CLI', group: 'cli', icon: 'terminal' },
  venv: { label: 'Open Python environment', name: 'UltraZohm Python Environment', group: 'venv', icon: 'terminal' },
  generate: { label: 'Generate Vitis workspace', name: 'UltraZohm Generate', group: 'firmware', icon: 'new-folder' },
  build: { label: 'Build firmware', name: 'UltraZohm Build', group: 'firmware', icon: 'tools' },
  debug: { label: 'Debug', name: 'UltraZohm Debug', group: 'firmware', icon: 'debug-alt' },
  attach: { label: 'Attach debugger', name: 'UltraZohm Attach', group: 'firmware', icon: 'debug-disconnect' },
  flash: { label: 'Flash UZ', name: 'UltraZohm Flash UZ', group: 'firmware', icon: 'zap' },
  'build-clean': { label: 'Clean and build firmware', name: 'UltraZohm Clean Build', group: 'firmware', icon: 'tools' },
};

function activate(context) {
  activateSerial(context);
  const pending = new Map();
  const debugOutput = vscode.window.createOutputChannel('UltraZohm Debug');
  context.subscriptions.push(debugOutput);
  const logDebug = message => debugOutput.appendLine(`${new Date().toISOString()} ${message}`);
  const changed = new vscode.EventEmitter();
  const debuggerControl = controller(context, () => changed.fire());
  let watcher;
  let settingsCache;
  const config = () => vscode.workspace.getConfiguration('ultrazohm', vscode.workspace.workspaceFolders?.[0]?.uri);
  const channel = () => config().get('dataviewer.channel', 'stable'); // Preserve existing saved choices.
  const visible = () => config().get('dataviewer.terminal', 'visible') !== 'hidden';
  const launcherSource = () => config().get('launcher.source', 'bundled');
  const endpoint = () => config().get('cli.endpoint', '127.0.0.1:19740');
  function requireLocal() {
    if (!vscode.workspace.isTrusted || vscode.env.remoteName || !['linux', 'win32'].includes(process.platform)) {
      throw new Error('Use a trusted local VS Code window on Linux or Windows.');
    }
  }
  function validateRoot(root, scripts = launcherSource() === 'local') {
    if (!path.isAbsolute(root)) throw new Error('Select an absolute UltraZohm checkout path.');
    const names = scripts ? ['uz.py', '.python-version', '.uv-version', process.platform === 'win32' ? 'uz.ps1' : 'uz'] : ['vitis', 'ip_cores'];
    if (names.some(name => !fs.existsSync(path.join(root, name)))) {
      throw new Error('Use Find ultrazohm_sw directory to select an UltraZohm checkout (local mode also requires its launcher scripts).');
    }
    if (scripts && fs.readFileSync(path.join(root, '.python-version'), 'utf8').trim() !== '3.12') {
      throw new Error('This extension bundles Python 3.12; the selected checkout requests another version.');
    }
    return path.resolve(root);
  }
  function workspace() {
    requireLocal();
    const folders = vscode.workspace.workspaceFolders || [];
    if (!folders.length) throw new Error('Use Find ultrazohm_sw directory to open an UltraZohm checkout.');
    if (folders.some(f => f.uri.scheme !== 'file')) throw new Error('Use a local filesystem workspace.');
    const selected = config().get('repository', '');
    if (!selected && folders.length !== 1) throw new Error('Use Find ultrazohm_sw directory to select a checkout for this window.');
    return { root: validateRoot(selected || folders[0].uri.fsPath), scope: folders[0] };
  }
  function launchContext(key) {
    requireLocal();
    const source = launcherSource();
    if (!['bundled', 'local'].includes(source)) throw new Error('Invalid launcher source.');
    let selected;
    try { selected = workspace(); } catch (error) {
      if (source === 'local' || config().get('repository', '') || key === 'cli' || actions[key].group === 'firmware') throw error;
    }
    const launcherRoot = source === 'local' ? selected.root : path.join(context.extensionPath, 'launcher');
    const folder = vscode.workspace.workspaceFolders?.[0];
    if (!folder || folder.uri.scheme !== 'file') throw new Error('Open any local folder in VS Code to run launcher tasks; bundled mode does not require an UltraZohm checkout.');
    const root = selected?.root;
    const cwd = root || folder.uri.fsPath;
    return { root, cwd, launcherRoot, source, scope: folder };
  }
  async function update(key, value) {
    const folders = vscode.workspace.workspaceFolders || [];
    const target = !folders.length ? vscode.ConfigurationTarget.Global : folders.length === 1 ? vscode.ConfigurationTarget.WorkspaceFolder : vscode.ConfigurationTarget.Workspace;
    await config().update(key, value, target);
    changed.fire();
  }
  async function vitis(root) {
    const script = config().get('vitis.settingsScript', '');
    if (!script) return { ...resolveXsct(root), env: process.env };
    try {
      const stamp = fs.statSync(script).mtimeMs;
      if (!settingsCache || settingsCache.script !== script || settingsCache.stamp !== stamp) {
        requireLocal();
        settingsCache = { script, stamp, pending: settingsEnvironment(script) };
      }
      const env = await settingsCache.pending;
      return { ...resolveXsct(undefined, env), env, script };
    } catch (error) { return { reason: error.message, script }; }
  }
  function refresh() { changed.fire(); }
  function watchRoot() {
    watcher?.dispose();
    watcher = undefined;
    try {
      const { root } = workspace();
      watcher = vscode.workspace.createFileSystemWatcher(new vscode.RelativePattern(root, 'artifacts/_user/tools.json'));
      watcher.onDidCreate(refresh); watcher.onDidChange(refresh); watcher.onDidDelete(refresh);
    } catch { /* The view explains invalid workspace selections. */ }
    refresh();
  }
  function taskMatches(execution, root, group) {
    const task = execution.task;
    if (task.definition.type !== 'ultrazohm') return false;
    const taskRoot = task.definition.repository ?? task.scope?.uri?.fsPath;
    return taskRoot === root && (task.definition.action || 'viewer') === group;
  }
  function running(root, group) {
    return vscode.tasks.taskExecutions.find(e => taskMatches(e, root, group));
  }
  function reveal(taskName) {
    vscode.window.terminals.find(t => t.name === taskName || t.name.endsWith(': ' + taskName))?.show();
  }
  function row(key, unavailable) {
    const action = actions[key];
    const item = new vscode.TreeItem(action.label);
    item.id = key;
    item.tooltip = unavailable || action.label;
    item.iconPath = new vscode.ThemeIcon(action.icon, unavailable ? new vscode.ThemeColor('disabledForeground') : undefined);
    if (unavailable) {
      item.description = 'Unavailable';
      item.resourceUri = vscode.Uri.parse('ultrazohm-disabled:/' + key);
    } else item.command = { command: 'ultrazohm.' + key, title: action.label };
    return item;
  }
  function viewProvider(section) {
    return {
      onDidChangeTreeData: changed.event,
      getTreeItem: item => item,
      getChildren: async () => {
        let selected, reason;
        try { selected = workspace(); } catch (e) { reason = e.message; }
        const xsct = section === 'control' ? {} : await vitis(selected?.root);
        if (section === 'setup') return [
          { label: 'Find ultrazohm_sw directory…', description: selected?.root, tooltip: reason || selected?.root,
            command: { command: 'ultrazohm.repository', title: 'Find ultrazohm_sw directory' } },
          { label: 'Launcher: ' + launcherSource(), command: { command: 'ultrazohm.launcherSource', title: 'Select launcher source' } },
          { label: 'Vitis / XSCT: ' + (xsct.script ? path.basename(xsct.script) : xsct.path ? path.basename(xsct.path) : 'not found'),
            tooltip: xsct.script || xsct.path || xsct.reason || reason,
            command: { command: 'ultrazohm.xsct', title: 'Select Vitis settings or XSCT' } },
          { label: 'Release channel: ' + channel(), command: { command: 'ultrazohm.channel', title: 'Select channel' } },
          row('updatePackages'),
          { label: 'Terminal: ' + (visible() ? 'visible' : 'hidden'), tooltip: 'DataViewer only. CLI, environment, and firmware terminals are always visible.',
            command: { command: 'ultrazohm.terminal', title: 'Select terminal visibility' } },
        ];
        const keys = section === 'softwareBuild' ? ['generate', 'build', 'flash', 'debug', 'attach', 'build-clean'] : ['launch', 'cli', 'venv'];
        return keys.map(key => {
          try { launchContext(key); return row(key, actions[key].group === 'firmware' ? xsct.reason : undefined); }
          catch (error) { return row(key, error.message); }
        });
      },
    };
  }
  function command(id, fn) {
    context.subscriptions.push(vscode.commands.registerCommand('ultrazohm.' + id, async () => {
      try { await fn(); } catch (e) { vscode.window.showErrorMessage('UltraZohm: ' + e.message); }
    }));
  }
  context.subscriptions.push(changed,
    ...['setup', 'softwareBuild', 'control'].map(section => vscode.window.registerTreeDataProvider('ultrazohm.' + section, viewProvider(section))),
    vscode.window.registerFileDecorationProvider({ provideFileDecoration: uri => uri.scheme === 'ultrazohm-disabled' ? { color: new vscode.ThemeColor('disabledForeground') } : undefined }),
    vscode.workspace.onDidChangeConfiguration(watchRoot), vscode.workspace.onDidChangeWorkspaceFolders(watchRoot),
    vscode.workspace.onDidGrantWorkspaceTrust(watchRoot),
    vscode.window.onDidChangeWindowState(state => { if (state.focused) refresh(); }),
    vscode.tasks.onDidEndTask(refresh), { dispose: () => watcher?.dispose() });
  command('refresh', () => { settingsCache = undefined; refresh(); });
  command('repository', async () => {
    requireLocal();
    const picked = await vscode.window.showOpenDialog({ canSelectFiles: false, canSelectFolders: true, canSelectMany: false, title: 'Find ultrazohm_sw directory', openLabel: 'Use ultrazohm_sw directory' });
    if (!picked?.length) return;
    const root = validateRoot(picked[0].fsPath);
    if (!vscode.workspace.workspaceFolders?.length) {
      await vscode.commands.executeCommand('vscode.openFolder', vscode.Uri.file(root));
      return;
    }
    await update('repository', root);
    watchRoot();
  });
  command('xsct', async () => {
    requireLocal();
    const picked = await vscode.window.showOpenDialog({ canSelectFiles: true, canSelectFolders: false, canSelectMany: false,
      title: 'Select Vitis settings64.sh / settings64.bat or XSCT launcher', openLabel: 'Use Vitis tools' });
    if (!picked?.length) return;
    const file = picked[0].fsPath;
    if (/^settings64\.(sh|bat)$/i.test(path.basename(file))) {
      const env = await vscode.window.withProgress({ location: vscode.ProgressLocation.Notification, title: 'Checking Vitis settings…' }, () => settingsEnvironment(file));
      const found = resolveXsct(undefined, env);
      if (!found.path) throw new Error('The setup script did not make XSCT available on PATH. ' + found.reason);
      await config().update('vitis.settingsScript', file, vscode.ConfigurationTarget.Global);
      settingsCache = undefined;
    } else {
      if (!(process.platform === 'win32' ? /^xsct\.(?:bat|cmd|exe)$/i : /^xsct$/).test(path.basename(file))) {
        throw new Error('Select settings64.sh (Linux), settings64.bat (Windows), or the XSCT launcher.');
      }
      saveXsct(workspace().root, file);
      await config().update('vitis.settingsScript', '', vscode.ConfigurationTarget.Global);
      settingsCache = undefined;
    }
    refresh();
  });
  command('xsctPath', async () => {
    requireLocal();
    await config().update('vitis.settingsScript', '', vscode.ConfigurationTarget.Global);
    settingsCache = undefined;
    let root; try { root = workspace().root; } catch { /* Standalone mode has no shared tools file. */ }
    if (root) saveXsct(root, null);
    refresh();
  });
  command('launcherSource', async () => {
    requireLocal();
    const value = await vscode.window.showQuickPick(['bundled', 'local'], { placeHolder: 'Bundled scripts or scripts from the selected UltraZohm checkout' });
    if (value) await update('launcher.source', value);
  });
  command('channel', async () => {
    requireLocal();
    const value = await vscode.window.showQuickPick(['stable', 'prerelease'], { placeHolder: 'Package channel for all UltraZohm actions' });
    if (value) await update('dataviewer.channel', value);
  });
  command('terminal', async () => {
    requireLocal();
    const value = await vscode.window.showQuickPick(['visible', 'hidden'], { placeHolder: 'DataViewer terminal visibility' });
    if (value) await update('dataviewer.terminal', value);
  });
  for (const [key, action] of Object.entries(actions)) command(key, async () => {
    const { root, cwd, launcherRoot, source, scope } = launchContext(key);
    const identity = root || '';
    const show = key !== 'launch' || visible();
    const token = key === 'updatePackages' ? 'packages' : identity + '\0' + action.group;
    if (pending.has(token)) { if (show) reveal(pending.get(token)); return; }
    const packageTask = vscode.tasks.taskExecutions.find(e => e.task.definition.type === 'ultrazohm' && e.task.definition.action === 'packages');
    const active = key === 'updatePackages' ? packageTask : running(identity, action.group);
    if (active) { if (show) reveal(active.task.name); return; }
    if (key === 'updatePackages' && (pending.size || vscode.tasks.taskExecutions.some(e => e.task.definition.type === 'ultrazohm'))) {
      throw new Error('Close running UltraZohm tasks before updating Python packages.');
    }
    if (key !== 'updatePackages' && (pending.has('packages') || packageTask)) {
      throw new Error('Wait for Update Python packages to finish before launching another UltraZohm task.');
    }
    if ((action.group === 'firmware' || key === 'updatePackages') && debuggerControl.active()) {
      throw new Error('Disconnect the UltraZohm debugger sessions before building, flashing, attaching or updating packages.');
    }
    pending.set(token, action.name);
    try {
      const selected = channel();
      if (!['stable', 'prerelease'].includes(selected)) throw new Error('Invalid release channel.');
      const xsct = key === 'updatePackages' ? { env: process.env } : await vitis(root);
      if (xsct.script && xsct.reason && (key === 'cli' || action.group === 'firmware')) throw new Error(xsct.reason);
      if (xsct.script && xsct.path && root) saveXsct(root, xsct.path);
      if (action.group === 'firmware' && !xsct.path) throw new Error(xsct.reason);
      const base = path.join(context.extensionPath, 'runtime');
      const runtime = JSON.parse(fs.readFileSync(path.join(base, 'manifest.json'), 'utf8'));
      if (runtime.platform !== process.platform || runtime.arch !== process.arch) throw new Error('Install the VSIX for this OS and architecture.');
      const storage = context.globalStorageUri.fsPath;
      fs.mkdirSync(path.join(storage, 'tmp'), { recursive: true });
      fs.mkdirSync(path.join(storage, 'shell'), { recursive: true });
      const env = environment(base, storage, xsct.env || process.env);
      env.UZ_BUNDLED_PYTHON = path.join(base, runtime.python);
      env.UZ_PRIVATE_SHELL_DIR = path.join(storage, 'shell');
      const windows = process.platform === 'win32';
      const executable = key === 'updatePackages' ? env.UZ_BUNDLED_PYTHON : windows ? path.join(process.env.SystemRoot, 'System32', 'WindowsPowerShell', 'v1.0', 'powershell.exe') : '/bin/bash';
      const launcher = path.join(launcherRoot, windows ? 'uz.ps1' : 'uz');
      const invoke = args => windows ? ['-NoProfile', '-ExecutionPolicy', 'Bypass', '-File', launcher, ...args] : [launcher, ...args];
      if (xsct.path) {
        const pathKey = Object.keys(env).find(k => k.toLowerCase() === 'path') || 'PATH';
        env[pathKey] = path.dirname(xsct.path) + path.delimiter + (env[pathKey] || '');
      }
      let debugTools;
      if (key === 'debug' || key === 'attach') debugTools = await debuggerControl.prepare(xsct, config());
      if (key === 'attach') {
        const choice = await vscode.window.showWarningMessage('Attach to UltraZohm?', { modal: true, detail: 'Connect debuggers to R5 and A53 without building or programming. The cores may pause. Use the ELF files from the exact firmware currently running on the board. Stop acquisition first and use a safe hardware state.' }, 'Attach');
        if (choice === 'Attach') await attachDebugger(false);
        return;
      }
      async function attachDebugger(atMain) {
        debugOutput.show(true);
        return vscode.window.withProgress({ location: vscode.ProgressLocation.Notification, title: 'Attaching UltraZohm debuggers…' },
          progress => debuggerControl.attach({ root, scope, tools: debugTools, env, python: env.UZ_BUNDLED_PYTHON, atMain,
            report: message => { logDebug(message); progress.report({ message }); } }));
      }
      let capabilities;
      let debugBridge;
      if (key === 'cli' || action.group === 'firmware') {
        if (key === 'cli' && await portInUse(endpoint())) throw new Error(`A service already occupies ${endpoint()}. Use its existing console or choose another ultrazohm.cli.endpoint. No service was stopped.`);
        capabilities = await vscode.window.withProgress({ location: vscode.ProgressLocation.Notification, title: 'Preparing UltraZohm CLI…' },
          () => readHelp(executable, invoke(['cli', selected, '--', key === 'cli' ? 'serve' : key === 'debug' ? 'flash' : key, '--help']), { cwd, env }));
        if ((key === 'flash' || key === 'debug') && !capabilities.noReconnect) {
          throw new Error('Flash UZ requires a current CLI with service-managed flashing. Use Update Python packages for the selected channel.');
        }
        if (key !== 'flash' && key !== 'debug' && root && !capabilities.repo) throw new Error('This CLI package does not support selecting a repository. Choose a compatible release channel.');
      }
      let args;
      if (key === 'updatePackages') args = ['-B', path.join(context.extensionPath, 'update-packages.py'),
        '--uv', path.join(base, 'bin', windows ? 'uv.exe' : 'uv'), '--channel', selected,
        '--requirements', path.join(launcherRoot, 'requirements.txt')];
      else if (key === 'launch') args = ['dataviewer', selected, '--', 'gui', ...(root ? ['--live-repo', root] : [])];
      else if (key === 'venv') args = ['venv', selected];
      else if (key === 'cli') {
        const address = endpoint();
        if (await portInUse(address)) throw new Error(`A service already occupies ${address}. Use its existing console or choose another ultrazohm.cli.endpoint. No service was stopped.`);
        args = ['cli', selected, '--', '--endpoint', address, 'serve', '--interactive', ...(root ? ['--repo', root] : [])];
        if (xsct.path && capabilities.xsct) {
          debugBridge = bridge(context.extensionPath, storage, env.UZ_BUNDLED_PYTHON, root, xsct.path, address);
          args.push('--xsct', debugBridge.launcher);
        }
      } else if (key === 'flash' || key === 'debug') {
        const choice = await vscode.window.showWarningMessage(key === 'debug' ? 'Debug UltraZohm?' : 'Flash UZ?', { modal: true,
          detail: key === 'debug' ? `Build and program through the CLI Flash workflow, stopping acquisition and finalizing recordings. Both A53 and R5 stop on a hardware breakpoint at main; you resume each core in VS Code. The service stays disconnected until you reconnect after resuming both cores.\n\nDirectory: ${root}\nAn interactive CLI started by this extension is required. Closing this terminal does not cancel the programming job.` : `Build firmware, program via JTAG and start UltraZohm. This does not write persistent flash memory.\n\nDirectory: ${root}\nRelease channel: ${selected}\n\nThe CLI service stops acquisition and finalizes recordings before programming. It reconnects if a device target is known; otherwise it programs without reconnecting. An interactive CLI is opened if needed. Closing the flash terminal does not cancel an accepted firmware job.` }, key === 'debug' ? 'Debug' : 'Flash UZ');
        if (choice !== (key === 'debug' ? 'Debug' : 'Flash UZ')) return;
        const address = endpoint();
        const startService = !(await portInUse(address));
        if (startService) {
          await vscode.commands.executeCommand('ultrazohm.cli');
          if (!running(identity, 'cli')) throw new Error('Could not open the interactive CLI. Check its terminal before retrying Flash UZ.');
        }
        const cliTask = running(identity, 'cli')?.task;
        if (key === 'debug' && (!cliTask?.definition.debugBridge || cliTask.definition.cliEndpoint !== address || cliTask.definition.debugXsct !== xsct.path)) {
          throw new Error('Debug needs an interactive CLI opened by this extension with the current Vitis tools and endpoint. Close the existing service yourself, then use Open interactive CLI and retry. No service was stopped.');
        }
        args = ['tool', 'run', '--isolated', '--python', '3.12', '--prerelease', selected === 'prerelease' ? 'allow' : 'disallow',
          '--from', 'ultrazohm-cli', 'python', path.join(context.extensionPath, 'flash.py'),
          '--endpoint', address, '--repo', root, '--wait-service', startService ? '30' : '0'];
        if (key === 'debug') args.push('--debug-config', cliTask.definition.debugBridge);
      } else args = ['cli', selected, '--', key, ...(capabilities.local ? ['--local'] : []), '--repo', root];
      const invocation = key === 'updatePackages' || key === 'flash' || key === 'debug' ? args : invoke(args);
      const debugRun = key === 'debug' ? randomUUID() : undefined;
      const task = new vscode.Task({ ...(debugRun ? { debugRun } : {}), type: 'ultrazohm', action: action.group, operation: key, repository: identity, launcherSource: source, ...(debugBridge ? { debugBridge: debugBridge.config, cliEndpoint: endpoint(), debugXsct: xsct.path } : {}) }, scope,
        action.name, 'UltraZohm', new vscode.ProcessExecution(key === 'flash' || key === 'debug' ? path.join(base, 'bin', windows ? 'uv.exe' : 'uv') : executable, invocation, { cwd, env }), []);
      task.presentationOptions = { reveal: show ? vscode.TaskRevealKind.Always : vscode.TaskRevealKind.Never,
        focus: show, panel: vscode.TaskPanelKind.Dedicated, close: false };
      if (key === 'debug') {
        // The CLI owns the accepted job; attach only after its monitor confirms
        // success and the XSCT wrapper confirms both stops at main.
        let completed = false;
        logDebug(`Debug ${debugRun}: starting programming task for ${root}.`);
        const listener = vscode.tasks.onDidEndTaskProcess(async event => {
          if (completed || event.execution.task.definition.debugRun !== debugRun) return;
          completed = true;
          listener.dispose();
          logDebug(`Debug ${debugRun}: programming task exited with ${event.exitCode}.`);
          if (event.exitCode !== 0) {
            debugOutput.show(true);
            vscode.window.showErrorMessage('UltraZohm: Debug programming did not complete successfully. See its task terminal.');
            return;
          }
          pending.set(token, action.name);
          try { await attachDebugger(true); }
          catch (error) { logDebug(error.stack || error.message); debugOutput.show(true); vscode.window.showErrorMessage('UltraZohm: ' + error.message); }
          finally { pending.delete(token); refresh(); }
        });
        context.subscriptions.push(listener);
        try { await vscode.tasks.executeTask(task); } catch (error) { listener.dispose(); throw error; }
      } else await vscode.tasks.executeTask(task);
    } finally { pending.delete(token); refresh(); }
  });
  context.subscriptions.push(vscode.tasks.registerTaskProvider('ultrazohm', { provideTasks: () => [], resolveTask: task => task.execution ? task : undefined }));
  watchRoot();
}
exports.activate = activate;
