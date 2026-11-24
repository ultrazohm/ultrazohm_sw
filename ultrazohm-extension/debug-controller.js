const vscode = require('vscode');
const fs = require('node:fs');
const path = require('node:path');
const { toolsForDebug, configuration } = require('./debug-tools');
const { processors, processorId } = require('./debug-rsp');
const { portInUse } = require('./service');
const pause = ms => new Promise(resolve => setTimeout(resolve, ms));
function controller(context, refresh) {
  const sessions = new Map();
  const environments = new Map();
  context.subscriptions.push(vscode.debug.registerDebugAdapterDescriptorFactory('ultrazohm-gdb', {
    createDebugAdapterDescriptor(session) {
      const launch = environments.get(session.configuration.ultrazohmRepository);
      if (!launch) throw new Error('Start this debugger with the UltraZohm Debug or Attach button.');
      return new vscode.DebugAdapterExecutable(launch.python, ['-B', path.join(context.extensionPath, 'debug-adapter.py'), launch.adapter], { env: launch.env });
    },
  }));
  context.subscriptions.push(vscode.debug.onDidStartDebugSession(session => {
    if (session.configuration.ultrazohmRepository) { sessions.set(session.id, session); refresh(); }
  }), vscode.debug.onDidTerminateDebugSession(session => { sessions.delete(session.id); refresh(); }));
  const active = root => [...sessions.values()].some(s => !root || s.configuration.ultrazohmRepository === root);
  async function prepare(xsct, config) {
    const extension = vscode.extensions.getExtension('ms-vscode.cpptools');
    if (!extension) throw new Error('Install Microsoft C/C++ (ms-vscode.cpptools) in VS Code to use Debug or Attach.');
    await extension.activate();
    const adapter = path.join(extension.extensionPath, 'debugAdapters', 'bin', process.platform === 'win32' ? 'OpenDebugAD7.exe' : 'OpenDebugAD7');
    if (!fs.existsSync(adapter)) throw new Error('Microsoft C/C++ debug adapter is missing. Reinstall that extension.');
    return { ...toolsForDebug(xsct, config), adapter };
  }
  async function attach({ root, scope, tools, env, python, atMain = false }) {
    if (active()) throw new Error('Disconnect the existing UltraZohm debugger sessions first.');
    // Check both ELFs before starting a hardware server or attaching either core.
    tools.cores.forEach(core => configuration(core, root, 1));
    if (!(await portInUse('127.0.0.1:3121'))) {
      // Keep the server in a user-visible task. It may be used by CLI/XSCT too,
      // so debugger disconnect never kills it or an externally started server.
      const task = new vscode.Task({ type: 'ultrazohm', action: 'debugserver', repository: root }, scope,
        'UltraZohm Hardware Server', 'UltraZohm', new vscode.ProcessExecution(python,
          ['-B', path.join(context.extensionPath, 'debug-server.py'), tools.server], { cwd: root, env }), []);
      task.presentationOptions = { reveal: vscode.TaskRevealKind.Always, focus: false, panel: vscode.TaskPanelKind.Dedicated };
      await vscode.tasks.executeTask(task);
    }
    const deadline = Date.now() + 15000;
    while (!(await portInUse('127.0.0.1:3000')) || !(await portInUse('127.0.0.1:3001'))) {
      if (Date.now() > deadline) throw new Error('hw_server GDB ports 3000/3001 are unavailable. Check the Hardware Server terminal and close other debuggers.');
      await pause(200);
    }
    environments.set(root, { python, env, adapter: tools.adapter });
    const configs = [];
    for (const core of tools.cores) configs.push(configuration(core, root, processorId(await processors(core.port), core.id)));
    const started = [];
    try {
      for (const config of configs) {
        if (!await vscode.debug.startDebugging(scope, config)) throw new Error(`Could not attach ${config.name}. See the Debug Console.`);
        const session = [...sessions.values()].find(s => s.configuration.ultrazohmRepository === root && s.configuration.ultrazohmCore === config.ultrazohmCore);
        if (!session) throw new Error(`The ${config.name} debugger did not start.`);
        started.push(session);
      }
      if (atMain) {
        // Verify the handoff too: an unexpected adapter resume must not be
        // reported as successful stop-at-main debugging.
        for (const session of started) {
          let frame;
          const end = Date.now() + 10000;
          while (Date.now() < end) {
            try {
              const { threads } = await session.customRequest('threads');
              const trace = await session.customRequest('stackTrace', { threadId: threads[0].id, startFrame: 0, levels: 1 });
              frame = trace.stackFrames[0];
              if (frame) break;
            } catch { /* Adapter initialization may still be completing. */ }
            await pause(100);
          }
          if (!frame || !/^main(?:\b|\()/u.test(frame.name)) throw new Error(`${session.name} is not confirmed stopped in main. Keep the sessions open and inspect the Debug Console.`);
        }
      }
      await vscode.window.showInformationMessage(atMain
        ? 'R5 and A53 are stopped at main. Select each session in Run and Debug and press Continue to resume that core. Reconnect the CLI/DataViewer after both cores are running.'
        : 'Attached to R5 and A53. Select each session in Run and Debug to inspect or resume that core.');
    } catch (error) {
      // Detaching a partially attached core can resume it. Leave successful
      // sessions available for inspection and explicit user control.
      if (started.length) error.message += ' Existing sessions were left open; inspect both cores before continuing.';
      throw error;
    }
  }
  return { active, prepare, attach };
}
module.exports = { controller };
