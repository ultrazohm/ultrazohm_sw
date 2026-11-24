const { test } = require('node:test');
const assert = require('node:assert/strict');
const vm = require('node:vm');
const fs = require('node:fs');
const path = require('node:path');

function setup(mode = 'visible') {
  const settings = { 'launcher.source': 'local', 'dataviewer.channel': 'prerelease', 'dataviewer.terminal': mode };
  const commands = {}, errors = [], events = { providers: {} }, updates = [], saved = [];
  const folder = { uri: { scheme: 'file', fsPath: '/checkout with spaces' } };
  const state = { confirmation: undefined, confirmations: [], capabilities: { local: true, xsct: true, repo: true }, xsct: { reason: 'XSCT not found' }, occupied: false, debugActive: false, attaches: [], picked: undefined, quickPick: 'hidden', validRoots: new Set(['/checkout with spaces', '/selected uz']) };
  let reveals = 0;
  const disposable = { dispose() {} };
  const watcher = { ...disposable, onDidCreate: () => disposable, onDidChange: () => disposable, onDidDelete: () => disposable };
  const v = {
    EventEmitter: class { event = () => {}; fire() {} dispose() {} },
    TreeItem: class { constructor(label) { this.label = label; } },
    ThemeColor: class { constructor(id) { this.id = id; } },
    ThemeIcon: class { constructor(id, color) { this.id = id; this.color = color; } },
    Uri: { parse: s => ({ scheme: s.split(':')[0], value: s }), file: fsPath => ({ scheme: 'file', fsPath }) },
    RelativePattern: class { constructor(root, pattern) { Object.assign(this, { root, pattern }); } },
    workspace: {
      isTrusted: true, workspaceFolders: [folder],
      getConfiguration: () => ({ get: (key, fallback) => settings[key] ?? fallback,
        update: async (key, value, target) => { settings[key] = value; updates.push({ key, value, target }); } }),
      onDidChangeConfiguration: fn => { events.config = fn; return disposable; },
      onDidChangeWorkspaceFolders: () => disposable, onDidGrantWorkspaceTrust: () => disposable,
      createFileSystemWatcher: () => watcher,
    },
    env: {}, ProgressLocation: { Notification: 15 },
    window: {
      registerTreeDataProvider: (id, provider) => { events.providers[id] = provider; return disposable; },
      registerFileDecorationProvider: provider => { events.decorations = provider; return disposable; },
      onDidChangeWindowState: () => disposable, terminals: [],
      createOutputChannel: () => ({ appendLine() {}, show() {}, dispose() {} }),
      withProgress: async (_, task) => task({ report() {} }),
      showWarningMessage: async (...args) => { state.confirmations.push(args); return typeof state.confirmation === 'function' ? state.confirmation() : state.confirmation; },
      showOpenDialog: async () => state.picked,
      showQuickPick: async () => state.quickPick, showErrorMessage: m => errors.push(m),
    },
    commands: {
      registerCommand: (id, fn) => { commands[id] = fn; return disposable; },
      executeCommand: async (...args) => { events.executed = args; if (commands[args[0]]) return commands[args[0]](); },
    },
    tasks: {
      registerTaskProvider: () => disposable, taskExecutions: [], onDidEndTask: () => disposable,
      onDidEndTaskProcess: fn => { events.taskEnd = fn; return disposable; },
      executeTask: async task => {
        const execution = { task };
        v.tasks.taskExecutions.push(execution);
        v.window.terminals.push({ name: task.name, show() { reveals++; } });
        return execution;
      },
    },
    Task: class { constructor(definition, scope, name, source, execution) { Object.assign(this, { definition, scope, name, source, execution }); } },
    ProcessExecution: class { constructor(command, args, options) { Object.assign(this, { command, args, options }); } },
    TaskScope: { Global: 1 }, ConfigurationTarget: { Global: 1, WorkspaceFolder: 3, Workspace: 2 }, TaskRevealKind: { Always: 1, Never: 3 }, TaskPanelKind: { Dedicated: 2 },
  };
  const mockFs = {
    existsSync: f => [...state.validRoots].some(root => f.startsWith(root + '/')),
    mkdirSync() {}, statSync: () => ({ mtimeMs: 1 }),
    readFileSync: f => f.endsWith('.python-version') ? '3.12' : JSON.stringify({ platform: 'linux', arch: 'x64', python: 'python/bin/python3' }),
  };
  const tools = { resolveXsct: () => state.xsct, saveXsct: (root, selected) => { saved.push({ root, selected }); state.xsct = selected ? { path: selected } : { reason: 'XSCT not found' }; } };
  // The mocked extension runs Linux semantics even when tests are hosted on Windows.
  const runtimeModule = { exports: {} };
  vm.runInNewContext(fs.readFileSync(path.join(__dirname, '../runtime-env.js'), 'utf8'), { module: runtimeModule, require: () => path.posix });
  const exports = {};
  vm.runInNewContext(fs.readFileSync(path.join(__dirname, '../extension.js'), 'utf8'), {
    exports, require: n => n === 'vscode' ? v : n === 'node:fs' ? mockFs : n === 'node:path' ? path.posix : n === './debug-controller' ? { controller: () => ({ active: () => state.debugActive, prepare: async () => ({}), attach: async options => state.attaches.push(options) }) } : n === './debug-tools' ? { bridge: () => ({ launcher: '/private/debug/xsct', config: '/private/debug/bridge.json' }) } : n === './vitis-env' ? { settingsEnvironment: async () => ({ PATH: '/Vitis/bin', XILINX_VITIS: '/Vitis', UV_CACHE_DIR: '/bad-cache' }) } : n === './runtime-env' ? runtimeModule.exports : n === './tools' ? tools : n === './cli-capabilities' ? { readHelp: async () => state.capabilities } : n === './service' ? { portInUse: async () => state.occupied } : require(n),
    process: { platform: 'linux', arch: 'x64', env: { PATH: '/usr/bin' } },
  });
  exports.activate({ subscriptions: [], extensionPath: '/extension', globalStorageUri: { fsPath: '/private' } });
  return { commands, errors, v, events, settings, updates, state, saved, reveals: () => reveals,
    run: name => commands['ultrazohm.' + name](), tasks: () => v.tasks.taskExecutions.map(e => e.task) };
}

test('viewer private runtime and rapid-click guard', async () => {
  const s = setup(); await Promise.all([s.run('launch'), s.run('launch')]); await s.run('launch');
  assert.equal(s.tasks().length, 1); assert.ok(s.reveals() > 0);
  const e = s.tasks()[0].execution;
  assert.equal(e.command, '/bin/bash'); assert.equal(e.args[0], '/checkout with spaces/uz');
  assert.equal(e.options.cwd, '/checkout with spaces'); assert.equal(e.args[2], 'prerelease');
  assert.equal(e.options.env.UV_PYTHON_DOWNLOADS, 'never'); assert.deepEqual(s.errors, []);
});

test('hidden viewer does not hide interactive CLI or environment; identities are independent', async () => {
  const s = setup('hidden'); await s.run('launch'); await s.run('launch');
  assert.equal(s.reveals(), 0); assert.equal(s.tasks()[0].presentationOptions.reveal, 3);
  await s.run('cli'); await s.run('venv');
  assert.equal(s.tasks().length, 3);
  assert.ok(s.tasks()[1].execution.args.includes('--interactive'));
  assert.equal(s.tasks()[1].presentationOptions.reveal, 1);
  assert.equal(s.tasks()[2].presentationOptions.reveal, 1);
  assert.deepEqual(Array.from(s.tasks()[2].execution.args).slice(1), ['venv', 'prerelease']);
  await s.run('cli'); assert.equal(s.tasks().length, 3);
  s.v.tasks.taskExecutions = []; await s.run('cli'); assert.equal(s.tasks().length, 1);
});

test('no background service and occupied CLI endpoint does not spawn or terminate', async () => {
  const s = setup(); s.state.occupied = true; await s.run('cli');
  assert.equal(s.tasks().length, 0); assert.match(s.errors[0], /already occupies/);
  assert.equal(s.commands['ultrazohm.service'], undefined);
});

test('missing XSCT disables firmware rows and guards command-palette invocation', async () => {
  const s = setup();
  for (const key of ['generate', 'build', 'build-clean', 'flash']) {
    const row = (await s.events.providers['ultrazohm.softwareBuild'].getChildren()).find(x => x.id === key);
    assert.equal(row.command, undefined); assert.equal(row.iconPath.color.id, 'disabledForeground');
    assert.equal(s.events.decorations.provideFileDecoration(row.resourceUri).color.id, 'disabledForeground');
    await s.run(key);
  }
  assert.equal(s.tasks().length, 0); assert.equal(s.errors.length, 4);
});

test('all firmware commands run locally and serialize per checkout', async () => {
  const s = setup(); s.state.xsct = { path: '/Vitis bin/xsct' };
  for (const key of ['generate', 'build', 'build-clean']) {
    assert.ok((await s.events.providers['ultrazohm.softwareBuild'].getChildren()).find(x => x.id === key).command);
    await s.run(key);
    const task = s.tasks()[0];
    assert.deepEqual(Array.from(task.execution.args).slice(1), ['cli', 'prerelease', '--', key, '--local', '--repo', '/checkout with spaces']);
    await s.run('build'); assert.equal(s.tasks().length, 1);
    s.v.tasks.taskExecutions = [];
  }
});

test('selected checkout overrides unrelated VS Code workspace for every action', async () => {
  const s = setup(); s.v.workspace.workspaceFolders[0].uri.fsPath = '/unrelated';
  await s.run('launch'); assert.equal(s.tasks().length, 0);
  s.state.picked = [{ fsPath: '/selected uz' }]; await s.run('repository');
  assert.deepEqual(s.updates[0], { key: 'repository', value: '/selected uz', target: 3 });
  s.state.xsct = { path: '/Vitis/xsct' };
  for (const name of ['launch', 'cli', 'venv', 'generate']) {
    await s.run(name);
    const task = s.tasks().at(-1);
    assert.equal(task.execution.options.cwd, '/selected uz');
    assert.equal(task.execution.args[0], '/selected uz/uz');
    assert.equal(task.definition.repository, '/selected uz');
  }
});

test('invalid or cancelled selection preserves repository; empty window opens selected checkout', async () => {
  const s = setup(); await s.run('repository'); assert.equal(s.updates.length, 0);
  s.state.picked = [{ fsPath: '/wrong' }]; await s.run('repository'); assert.equal(s.updates.length, 0);
  s.v.workspace.workspaceFolders = []; s.state.picked = [{ fsPath: '/selected uz' }]; await s.run('repository');
  assert.equal(s.events.executed[0], 'vscode.openFolder');
  assert.equal(s.events.executed[1].fsPath, '/selected uz');
});

test('XSCT picker saves shared preferences in selected checkout and can reset to PATH', async () => {
  const s = setup(); s.settings.repository = '/selected uz'; s.state.picked = [{ fsPath: '/Vitis bin/xsct' }];
  await s.run('xsct'); assert.deepEqual(s.saved, [{ root: '/selected uz', selected: '/Vitis bin/xsct' }]);
  assert.ok((await s.events.providers['ultrazohm.softwareBuild'].getChildren()).find(row => row.id === 'build').command);
  await s.run('cli'); assert.equal(s.tasks()[0].execution.args.at(-1), '/private/debug/xsct');
  await s.run('xsctPath'); assert.equal(s.saved.at(-1).selected, null);
  s.state.picked = [{ fsPath: '/Vitis/vitis' }]; await s.run('xsct'); assert.equal(s.saved.length, 2);
});

test('visibility selector still persists per workspace', async () => {
  const s = setup(); await s.run('terminal');
  assert.deepEqual(s.updates, [{ key: 'dataviewer.terminal', value: 'hidden', target: 3 }]);
  assert.ok((await s.events.providers['ultrazohm.setup'].getChildren()).some(row => row.label === 'Terminal: hidden'));
});

test('older PyPI CLI uses local firmware commands without --local and gets XSCT through task PATH', async () => {
  const s = setup(); s.state.capabilities = { local: false, xsct: false, repo: true }; s.state.xsct = { path: '/Vitis bin/xsct' };
  await s.run('generate'); const task = s.tasks()[0];
  assert.equal(task.execution.args.includes('--local'), false);
  assert.ok(task.execution.options.env.PATH.startsWith('/Vitis bin:'));
  await s.run('cli'); assert.equal(s.tasks()[1].execution.args.includes('--xsct'), false);
});

 test('bundled apps run in an unrelated folder without a checkout', async () => {
  const s = setup(); s.settings['launcher.source'] = 'bundled';
  s.v.workspace.workspaceFolders[0].uri.fsPath = '/unrelated';
  for (const key of ['launch', 'venv']) await s.run(key);
  assert.deepEqual(s.errors, []); assert.equal(s.tasks().length, 2);
  for (const task of s.tasks()) {
    assert.equal(task.execution.args[0], '/extension/launcher/uz');
    assert.equal(task.execution.options.cwd, '/unrelated');
    assert.equal(task.execution.args.includes('--repo'), false);
    assert.equal(task.execution.args.includes('--live-repo'), false);
  }
  await s.run('build'); await s.run('cli'); assert.equal(s.tasks().length, 2);
  await s.run('launch'); assert.equal(s.tasks().length, 2);
 });
 test('bundled launcher keeps the chosen firmware repository separate', async () => {
  const s = setup(); s.settings['launcher.source'] = 'bundled';
  s.state.xsct = { path: '/Vitis/xsct' }; await s.run('build');
  const task = s.tasks()[0];
  assert.equal(task.execution.args[0], '/extension/launcher/uz');
  assert.equal(task.execution.options.cwd, '/checkout with spaces');
  assert.equal(task.execution.args.at(-1), '/checkout with spaces');
 });
 test('launcher selector is available without a checkout and persists globally in empty windows', async () => {
  const s = setup(); s.v.workspace.workspaceFolders = []; s.state.quickPick = 'bundled';
  await s.run('launcherSource');
  assert.deepEqual(s.updates[0], {key:'launcher.source',value:'bundled',target:1});
 });

test('empty window explains task folder requirement without launching', async () => {
 const s=setup(); s.settings['launcher.source']='bundled'; s.v.workspace.workspaceFolders=[];
 await s.run('venv'); assert.equal(s.tasks().length,0); assert.match(s.errors[0], /Open any local folder/);
});

test('Vitis setup selection persists at user scope and supplies task environment', async () => {
 const s=setup(); s.state.xsct={path:'/Vitis/bin/xsct'};
 s.state.picked=[{fsPath:'/Vitis/settings64.sh'}];await s.run('xsct');
 assert.deepEqual(s.updates[0],{key:'vitis.settingsScript',value:'/Vitis/settings64.sh',target:1});
 await s.run('build'); const task=s.tasks()[0];
 assert.equal(task.execution.options.env.XILINX_VITIS,'/Vitis');
 assert.equal(task.execution.options.env.UV_CACHE_DIR,'/private/cache');
 assert.deepEqual(s.saved.at(-1),{root:'/checkout with spaces',selected:'/Vitis/bin/xsct'});
 await s.run('xsctPath'); assert.equal(s.settings['vitis.settingsScript'],'');
});

test('Flash UZ opens an interactive CLI then validates and follows its service job', async () => {
 const s=setup('hidden');s.state.xsct={path:'/Vitis/xsct'};
 s.state.capabilities={repo:true,xsct:true,noReconnect:true};s.state.confirmation='Flash UZ';
 await s.run('flash');assert.deepEqual(s.errors,[]);assert.equal(s.tasks().length,2);
 assert.equal(s.tasks()[0].definition.action,'cli');
 const task=s.tasks()[1];assert.equal(task.execution.command,'/extension/runtime/bin/uv');
 assert(task.execution.args.includes('/extension/flash.py'));
 assert(task.execution.args.includes('/checkout with spaces'));
 assert.equal(task.execution.args.at(-1),'30');assert.equal(task.presentationOptions.reveal,1);
 assert.match(s.state.confirmations[0][1].detail,/finalizes recordings/);
 await s.run('build');await s.run('flash');assert.equal(s.tasks().length,2);
});
test('Flash reuses a listening service and passes the configured endpoint to validation', async () => {
 const s=setup();s.state.xsct={path:'/Vitis/xsct'};s.state.occupied=true;
 s.state.capabilities={noReconnect:true};s.state.confirmation='Flash UZ';s.settings['cli.endpoint']='127.0.0.1:19800';
 await s.run('flash');assert.deepEqual(s.errors,[]);assert.equal(s.tasks().length,1);
 assert(s.tasks()[0].execution.args.includes('127.0.0.1:19800'));assert.equal(s.tasks()[0].execution.args.at(-1),'0');
});
test('cancelled Flash starts neither service nor job', async () => {
 const s=setup();s.state.xsct={path:'/Vitis/xsct'};s.state.capabilities={noReconnect:true};
 await s.run('flash');assert.equal(s.tasks().length,0);
});
test('Flash rejects obsolete standalone CLI before starting anything', async () => {
 const s=setup();s.state.xsct={path:'/Vitis/xsct'};s.state.capabilities={repo:true,profile:true};
 await s.run('flash');assert.equal(s.tasks().length,0);assert.match(s.errors[0],/current CLI/);
});
test('Flash pending confirmation prevents concurrent firmware starts', async () => {
 const s=setup();s.state.xsct={path:'/Vitis/xsct'};s.state.capabilities={noReconnect:true};s.state.occupied=true;
 let accept;let opened;const ready=new Promise(resolve=>opened=resolve);
 s.state.confirmation=()=>new Promise(resolve=>{accept=resolve;opened();});
 const pending=s.run('flash');await ready;await s.run('flash');await s.run('build');
 assert.equal(s.state.confirmations.length,1);assert.equal(s.tasks().length,0);
 accept('Flash UZ');await pending;assert.equal(s.tasks().length,1);
});

test('Setup package update uses private tooling, selected requirements and visible terminal without XSCT', async () => {
  const s = setup('hidden');
  s.settings['launcher.source'] = 'bundled';
  s.v.workspace.workspaceFolders[0].uri.fsPath = '/unrelated';
  s.settings['dataviewer.channel'] = 'stable';
  const rows = await s.events.providers['ultrazohm.setup'].getChildren();
  assert(rows.some(row => row.command?.command === 'ultrazohm.updatePackages'));
  await Promise.all([s.run('updatePackages'), s.run('updatePackages')]);
  await s.run('updatePackages');
  assert.equal(s.tasks().length, 1);
  const task = s.tasks()[0];
  assert.equal(task.execution.command, '/extension/runtime/python/bin/python3');
  assert.deepEqual(Array.from(task.execution.args), ['-B', '/extension/update-packages.py', '--uv', '/extension/runtime/bin/uv', '--channel', 'stable', '--requirements', '/extension/launcher/requirements.txt']);
  assert.equal(task.execution.options.env.UV_CACHE_DIR, '/private/cache');
  assert.equal(task.presentationOptions.reveal, 1);
  assert(s.reveals() > 0);
  await s.run('launch');
  assert.equal(s.tasks().length, 1);
  assert.match(s.errors.at(-1), /Wait for Update/);
  s.v.tasks.taskExecutions = [];
  await s.run('launch');
  assert.equal(s.tasks()[0].definition.action, 'viewer');
});

test('package update refuses running tasks and respects local requirements', async () => {
  const s = setup();
  await s.run('venv'); await s.run('updatePackages');
  assert.equal(s.tasks().length, 1);
  assert.match(s.errors.at(-1), /Close running/);
  s.v.tasks.taskExecutions = [];
  await s.run('updatePackages');
  assert(s.tasks()[0].execution.args.includes('/checkout with spaces/requirements.txt'));
});

test('Attach starts both debugger sessions without a CLI or firmware task', async () => {
 const s=setup();s.state.xsct={path:'/Vitis/xsct'};s.state.confirmation='Attach';
 await s.run('attach');assert.deepEqual(s.errors,[]);assert.equal(s.tasks().length,0);
 assert.equal(s.state.attaches.length,1);assert.equal(s.state.attaches[0].root,'/checkout with spaces');
});
test('Debug starts a capable CLI, requests service-managed programming and attaches only on success', async () => {
 const s=setup();s.state.xsct={path:'/Vitis/xsct'};s.state.capabilities={repo:true,xsct:true,noReconnect:true};s.state.confirmation='Debug';
 await s.run('debug');assert.deepEqual(s.errors,[]);assert.equal(s.tasks().length,2);
 assert.equal(s.tasks()[0].definition.debugBridge,'/private/debug/bridge.json');
 const task=s.tasks()[1];assert(task.execution.args.includes('--debug-config'));
 assert.equal(task.execution.args.at(-1),'/private/debug/bridge.json');
 assert.equal(s.state.attaches.length,0);
 // VS Code may reconstruct task objects; correlate the serialized run ID.
 await s.events.taskEnd({execution:{task:JSON.parse(JSON.stringify(task))},exitCode:0});
 await s.events.taskEnd({execution:s.v.tasks.taskExecutions[1],exitCode:0});
 assert.equal(s.state.attaches.length,1);assert.equal(s.state.attaches[0].atMain,true);
});
test('Debug completion before executeTask resolves attaches once and ignores unrelated tasks', async () => {
 const s=setup();s.state.xsct={path:'/Vitis/xsct'};s.state.capabilities={repo:true,xsct:true,noReconnect:true};s.state.confirmation='Debug';
 const execute=s.v.tasks.executeTask;
 s.v.tasks.executeTask=async task=>{
  const execution=await execute(task);
  if(task.definition.operation==='debug') {
   await s.events.taskEnd({execution:{task:{definition:{debugRun:'another-run'}}},exitCode:0});
   assert.equal(s.state.attaches.length,0);
   await s.events.taskEnd({execution:{task:JSON.parse(JSON.stringify(task))},exitCode:0});
  }
  return execution;
 };
 await s.run('debug');
 assert.deepEqual(s.errors,[]);assert.equal(s.state.attaches.length,1);
});
test('failed/cancelled Debug never attaches, and an external service is not replaced', async () => {
 for (const code of [1,undefined]) {
  const s=setup();s.state.xsct={path:'/Vitis/xsct'};s.state.capabilities={repo:true,xsct:true,noReconnect:true};s.state.confirmation='Debug';
  await s.run('debug');await s.events.taskEnd({execution:s.v.tasks.taskExecutions[1],exitCode:code});
  assert.equal(s.state.attaches.length,0);
 }
 const s=setup();s.state.xsct={path:'/Vitis/xsct'};s.state.capabilities={noReconnect:true};s.state.confirmation='Debug';s.state.occupied=true;
 await s.run('debug');assert.equal(s.tasks().length,0);assert.match(s.errors[0],/interactive CLI opened by this extension/);
});
test('active debugger blocks firmware commands and package updates but allows control tools', async () => {
 const s=setup();s.state.xsct={path:'/Vitis/xsct'};s.state.debugActive=true;
 for(const key of ['build','generate','build-clean','flash','debug','attach','updatePackages']) await s.run(key);
 assert.equal(s.tasks().length,0);assert.equal(s.errors.length,7);
 await s.run('venv');assert.equal(s.tasks().length,1);
});
