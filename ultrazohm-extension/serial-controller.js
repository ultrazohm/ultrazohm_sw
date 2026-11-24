const vscode = require('vscode');
const fs = require('node:fs');
const path = require('node:path');
const { spawn, execFile } = require('node:child_process');
const { StringDecoder } = require('node:string_decoder');
const { environment } = require('./runtime-env');
const { defaults, identity, matchingPorts, defaultPort, settings, encodeInput } = require('./serial-tools');
function activateSerial(context) {
  const changed = new vscode.EventEmitter();
  let active, busy = false;
  const config = () => vscode.workspace.getConfiguration('ultrazohm');
  const refresh = () => changed.fire();
  function local() {
    if (!vscode.workspace.isTrusted || vscode.env.remoteName || !['linux', 'win32'].includes(process.platform)) throw new Error('Use a trusted local VS Code window on Linux or Windows for serial access.');
  }
  function runtime() {
    local();
    const base = path.join(context.extensionPath, 'runtime');
    const manifest = JSON.parse(fs.readFileSync(path.join(base, 'manifest.json'), 'utf8'));
    if (manifest.platform !== process.platform || manifest.arch !== process.arch) throw new Error('Install the VSIX for this OS and architecture.');
    const storage = context.globalStorageUri.fsPath;
    fs.mkdirSync(path.join(storage, 'tmp'), { recursive: true });
    return { python: path.join(base, manifest.python), helper: path.join(context.extensionPath, 'serial-terminal.py'), env: environment(base, storage, process.env) };
  }
  async function save(key, value) { await config().update('serial.' + key, value, vscode.ConfigurationTarget.Global); refresh(); }
  async function list() {
    const { python, helper, env } = runtime();
    return new Promise((resolve, reject) => execFile(python, ['-I', '-B', helper, 'list'], { env, timeout: 10000, maxBuffer: 1024 * 1024 }, (error, stdout) => {
      if (error) return reject(new Error('Could not list serial ports: ' + (stdout || error.message)));
      try { const ports = JSON.parse(stdout); if (!Array.isArray(ports)) throw new Error('Invalid port list'); resolve(ports); } catch (e) { reject(e); }
    }));
  }
  async function rememberPort(port) {
    await save('device', port.device);
    await save('identity', identity(port));
    await save('matchBy', port.serialNumber ? 'identity' : 'device');
    return port.device;
  }
  async function selectPort(ports = undefined) {
    ports = ports || await list();
    if (!ports.length) throw new Error('No serial ports found. Connect the USB UART adapter and check its driver/permissions, or set Device name manually.');
    const item = await vscode.window.showQuickPick(ports.map(p => ({ label: p.device, description: p.description,
      detail: `USB ${p.vid?.toString(16) || '?'}:${p.pid?.toString(16) || '?'} · Serial ${p.serialNumber || 'unavailable'} · ${p.interface || p.location || ''}`, port: p })), { title: 'Select UltraZohm UART port', placeHolder: 'Select the SoM UART interface, not JTAG or an unused channel' });
    if (!item) return;
    return rememberPort(item.port);
  }
  function stop() {
    if (!active || active.closing) return;
    active.closing = true;
    active.child?.stdin.end();
    if (active.child) {
      const child = active.child;
      active.killTimer = setTimeout(() => child.kill(), 1500);
    }
  }
  async function connect() {
    local();
    if (active) { active.terminal.show(); return; }
    if (busy) return;
    busy = true; refresh();
    try {
      const cfg = config();
      const mode = cfg.get('serial.matchBy', 'identity');
      if (!['identity', 'device'].includes(mode)) throw new Error('Choose USB identity or device name matching in Serial.');
      let device = cfg.get('serial.device', '');
      if (mode === 'identity') {
        const ports = await list();
        const saved = cfg.get('serial.identity', {});
        const matches = matchingPorts(ports, mode, device, saved);
        const preferred = !device && !Object.keys(saved).length ? defaultPort(ports) : undefined;
        device = matches.length === 1 ? matches[0].device : preferred ? await rememberPort(preferred) : await selectPort(ports);
      } else if (!device) device = await selectPort();
      if (!device) return;
      if (device !== config().get('serial.device', '')) await save('device', device);
      const options = settings(config(), device);
      const { python, helper, env } = runtime();
      const write = new vscode.EventEmitter(), closed = new vscode.EventEmitter();
      const decoder = new StringDecoder('utf8');
      let previousCR = false;
      const render = text => {
        const output = text.replace(/\n/g, (_, offset) => (offset === 0 ? previousCR : text[offset - 1] === '\r') ? '\n' : '\r\n');
        if (text) previousCR = text.endsWith('\r');
        return output;
      };
      const session = { child: undefined, terminal: undefined, closing: false, connected: false };
      const line = text => write.fire(text + '\r\n');
      const pty = {
        onDidWrite: write.event, onDidClose: closed.event,
        open() {
          line(`UltraZohm Serial — ${device} — ${options.baud} ${options.dataBits}${options.parity}${options.stopBits}, flow ${options.flowControl}`);
          line('Connecting… Close this terminal or use Disconnect to release the port.');
          const child = session.child = spawn(python, ['-I', '-B', helper, 'connect', '--settings', JSON.stringify(options)], { env, windowsHide: true, stdio: ['pipe', 'pipe', 'pipe'] });
          let buffer = '', ended = false;
          function finish(code) {
            if (ended) return; ended = true;
            clearTimeout(session.killTimer);
            line('\r\nDisconnected.');
            if (active === session) active = undefined;
            refresh(); closed.fire(code || 0);
            write.dispose(); closed.dispose();
          }
          child.stdout.setEncoding('utf8');
          child.stdout.on('data', chunk => {
            buffer += chunk;
            if (buffer.length > 1024 * 1024) { line('Invalid serial helper response.'); stop(); return; }
            let end;
            while ((end = buffer.indexOf('\n')) >= 0) {
              const raw = buffer.slice(0, end); buffer = buffer.slice(end + 1);
              try {
                const message = JSON.parse(raw);
                if (message.event === 'connected') { session.connected = true; line('Connected.'); refresh(); }
                else if (message.event === 'data') write.fire(render(decoder.write(Buffer.from(message.data, 'base64'))));
                else if (message.event === 'error') line('Serial error: ' + message.message + '\r\nCheck the port selection, OS permissions, and whether Vitis or another terminal has it open.');
              } catch { line('Invalid serial helper response.'); stop(); }
            }
          });
          child.stderr.on('data', chunk => line(chunk.toString()));
          child.stdin.on('error', () => {}); // Process exit/unplug can close stdin during typing.
          child.on('error', error => { line('Could not start serial helper: ' + error.message); finish(1); });
          child.on('close', finish);
          if (session.closing) child.stdin.end();
        },
        handleInput(text) {
          if (!session.connected || session.closing || !session.child?.stdin.writable) return;
          if (session.child.stdin.writableLength > 65536) { line('\r\nSerial input buffer is full; wait before sending more.'); return; }
          const data = encodeInput(text, options.lineEnding);
          if (data.length > 65536) { line('\r\nPaste is too large; send at most 64 KiB at a time.'); return; }
          for (let offset = 0; offset < data.length; offset += 4096) session.child.stdin.write(JSON.stringify({ command: 'write', data: data.subarray(offset, offset + 4096).toString('base64') }) + '\n');
          if (options.localEcho) write.fire(text.replace(/\r\n|\r|\n/g, '\r\n'));
        },
        close() { if (active === session) stop(); },
      };
      active = session;
      session.terminal = vscode.window.createTerminal({ name: `UltraZohm Serial: ${device}`, pty, isTransient: true });
      session.terminal.show();
    } finally { busy = false; refresh(); }
  }
  const options = { matchBy: ['identity', 'device'], baud: [9600,19200,38400,57600,115200,230400,460800,921600], dataBits: [5,6,7,8], parity: ['N','E','O','M','S'], stopBits: [1,1.5,2], flowControl: ['none','rtscts','xonxoff'], lineEnding: ['CR','LF','CRLF'], localEcho: [false,true] };
  const labels = { matchBy: 'Match by', baud: 'Baud rate', dataBits: 'Data bits', parity: 'Parity', stopBits: 'Stop bits', flowControl: 'Flow control', lineEnding: 'Enter sends', localEcho: 'Local echo' };
  function command(name, fn, edit = false) {
    context.subscriptions.push(vscode.commands.registerCommand('ultrazohm.serial.' + name, async () => {
      try { local(); if (edit && (active || busy)) throw new Error('Disconnect the serial terminal before changing its settings.'); await fn(); }
      catch (error) { vscode.window.showErrorMessage('UltraZohm: ' + error.message); }
    }));
  }
  command('connect', connect); command('disconnect', stop);
  command('select', () => selectPort(), true);
  command('device', async () => {
    const value = await vscode.window.showInputBox({ title: 'Serial device name', prompt: 'For example COM9 or /dev/ttyUSB2. Selecting a name switches matching to device name.', value: config().get('serial.device', ''), validateInput: v => !v.trim() || /[\r\n\0]/.test(v) ? 'Enter a native serial device name.' : undefined });
    if (value !== undefined) { await save('device', value.trim()); await save('matchBy', 'device'); }
  }, true);
  for (const [key, values] of Object.entries(options)) command(key, async () => {
    const value = await vscode.window.showQuickPick(values.map(value => ({ label: String(value), value })), { title: labels[key] });
    if (value) await save(key, value.value);
  }, true);
  const item = (label, command, tooltip) => ({ label, tooltip, command: { command: 'ultrazohm.serial.' + command, title: label } });
  context.subscriptions.push(changed, vscode.workspace.onDidChangeConfiguration(refresh), vscode.window.registerTreeDataProvider('ultrazohm.serial', {
    onDidChangeTreeData: changed.event, getTreeItem: item => item,
    getChildren() {
      const cfg = config(), saved = cfg.get('serial.identity', {});
      return [item(active ? 'Show serial terminal' : busy ? 'Connecting…' : 'Connect', 'connect'),
        ...(active ? [item('Disconnect', 'disconnect')] : []), item('Select serial port…', 'select'),
        item('Device name: ' + (cfg.get('serial.device', '') || 'not selected'), 'device'),
        item('USB identity: ' + (saved.serialNumber || 'not selected'), 'select', JSON.stringify(saved)),
        ...Object.keys(options).map(key => item(labels[key] + ': ' + cfg.get('serial.' + key, defaults[key] ?? 'identity'), key))];
    },
  }), { dispose() { stop(); active?.terminal.dispose(); } });
}
module.exports = { activateSerial };
