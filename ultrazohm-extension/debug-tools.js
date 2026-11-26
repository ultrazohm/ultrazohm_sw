const fs = require('node:fs');
const path = require('node:path');
const { randomUUID } = require('node:crypto');
const { usable } = require('./tools');
const cores = [
  { id: 'R5', app: 'Baremetal', port: 3000, gdb: 'armr5-none-eabi-gdb', directory: ['armr5', 'gcc-arm-none-eabi'] },
  { id: 'A53', app: 'FreeRTOS', port: 3001, gdb: 'aarch64-none-elf-gdb', directory: ['aarch64', 'aarch64-none'] },
];
function toolsForDebug(xsct, config, platform = process.platform) {
  const roots = [xsct.env?.XILINX_VITIS, path.dirname(path.dirname(fs.realpathSync(xsct.path)))].filter(Boolean);
  const windows = platform === 'win32';
  const find = candidates => candidates.find(file => usable(file, platform));
  const result = cores.map(core => {
    const override = config.get('debug.' + core.id.toLowerCase() + 'Gdb', '');
    const candidates = override ? [override] : roots.map(root => path.join(root, 'gnu', core.directory[0], windows ? 'nt' : 'lin', core.directory[1], 'bin', core.gdb + (windows ? '.exe' : '')));
    const gdb = find(candidates);
    if (!gdb) throw new Error(`${core.id} GDB not found in Vitis. Select Vitis settings or set ultrazohm.debug.${core.id.toLowerCase()}Gdb.`);
    return { ...core, gdb };
  });
  const server = find(roots.map(root => path.join(root, 'bin', windows ? 'hw_server.bat' : 'hw_server')));
  if (!server) throw new Error('Vitis hw_server not found beside XSCT. Select the Vitis installation containing hw_server.');
  return { cores: result, server };
}
function configuration(core, root, id) {
  if (id !== 1) throw new Error(`Expected ${core.id} #0 to be hw_server's first processor (ID 1), got ${id}. Use one connected board with the default hw_server configuration.`);
  const program = path.join(root, 'vitis', 'workspace', core.app, 'Debug', core.app + '.elf');
  if (!fs.existsSync(program)) throw new Error(`Missing ${program}. Build the firmware first; Attach requires the ELF that is running on the board.`);
  return {
    name: `UltraZohm ${core.id}`, type: 'ultrazohm-gdb', request: 'launch', MIMode: 'gdb',
    cwd: root, targetArchitecture: core.id === 'R5' ? 'arm' : 'arm64',
    miDebuggerPath: core.gdb, miDebuggerArgs: '-nx', program,
    miDebuggerServerAddress: `127.0.0.1:${core.port}`,
    customLaunchSetupCommands: [
      { text: '-file-exec-and-symbols ' + JSON.stringify(program.replaceAll('\\', '/')), ignoreFailures: false },
      { text: `-target-select remote 127.0.0.1:${core.port}`, ignoreFailures: false },
    ],
    stopAtConnect: true, launchCompleteCommand: 'None',
    setupCommands: [{ text: '-gdb-set remotetimeout 10', ignoreFailures: false }],
    ultrazohmRepository: root, ultrazohmCore: core.id,
  };
}
function bridge(extension, storage, python, root, xsct, endpoint) {
  // A unique immutable directory per service. Never save the proxy as shared XSCT.
  const directory = path.join(storage, 'debug', randomUUID());
  fs.mkdirSync(directory, { recursive: true });
  const config = path.join(directory, 'bridge.json');
  fs.writeFileSync(config, JSON.stringify({ root, xsct, endpoint, ticket: path.join(directory, 'request.json'), proof: path.join(directory, 'stopped.json') }));
  const launcher = path.join(directory, process.platform === 'win32' ? 'xsct.cmd' : 'xsct');
  const helper = path.join(extension, 'debug-xsct.py');
  const quote = s => "'" + s.replaceAll("'", "'\\''") + "'";
  // cmd.exe expands percent signs even inside quotes. These unusual paths are not
  // representable by this batch wrapper; reject instead of executing another path.
  if (process.platform === 'win32' && [python, helper, config].some(s => /[%\r\n"]/u.test(s))) throw new Error('Debug tooling paths cannot contain percent signs, quotes or newlines on Windows.');
  fs.writeFileSync(launcher, process.platform === 'win32'
    ? `@echo off\r\n"${python}" -B "${helper}" "${config}" %*\r\nexit /b %errorlevel%\r\n`
    : `#!/bin/sh\nexec ${quote(python)} -B ${quote(helper)} ${quote(config)} "$@"\n`, { mode: 0o700 });
  return { launcher, config };
}
module.exports = { cores, toolsForDebug, configuration, bridge };
