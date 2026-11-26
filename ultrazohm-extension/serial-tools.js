const defaults = { baud: 115200, dataBits: 8, parity: 'N', stopBits: 1, flowControl: 'none', lineEnding: 'CR', localEcho: false };
function identity(port) {
  return Object.fromEntries(['vid', 'pid', 'serialNumber', 'interface', 'location', 'interfaceNumber'].map(key => [key, port[key] ?? null]));
}
function matchingPorts(ports, mode, device, saved) {
  if (mode === 'device') return ports.filter(p => p.device === device);
  if (!saved?.serialNumber) return [];
  let found = ports.filter(p => ['vid', 'pid', 'serialNumber'].every(key => p[key] === saved[key]));
  // Composite USB adapters may share a serial number across UART interfaces.
  if (saved.interfaceNumber != null) found = found.filter(p => p.interfaceNumber === saved.interfaceNumber);
  if (saved.interface) found = found.filter(p => p.interface === saved.interface);
  if (found.length > 1 && saved.location) found = found.filter(p => p.location === saved.location);
  return found;
}
function defaultPort(ports) {
  // USB interface 02 is IsoJTAG channel C, independent of its COM/tty number.
  const candidates = ports.filter(p => /ultrazohm/i.test((p.product || '') + ' ' + (p.description || '')) && p.interfaceNumber === 2);
  return candidates.length === 1 ? candidates[0] : undefined;
}
function settings(config, device) {
  const result = { device };
  for (const [key, value] of Object.entries(defaults)) result[key] = config.get('serial.' + key, value);
  if (!Number.isInteger(result.baud) || result.baud < 1 || result.baud > 4000000 ||
      ![5,6,7,8].includes(result.dataBits) || !['N','E','O','M','S'].includes(result.parity) ||
      ![1,1.5,2].includes(result.stopBits) || !['none','rtscts','xonxoff'].includes(result.flowControl) ||
      !['CR','LF','CRLF'].includes(result.lineEnding) || typeof result.localEcho !== 'boolean') throw new Error('Invalid serial settings. Check the Serial section.');
  return result;
}
function encodeInput(text, ending) {
  return Buffer.from(text.replace(/\r\n|\r|\n/g, { CR: '\r', LF: '\n', CRLF: '\r\n' }[ending]), 'utf8');
}
module.exports = { defaults, identity, matchingPorts, defaultPort, settings, encodeInput };
