const { execFile } = require('node:child_process');
function readHelp(executable, args, options) {
  return new Promise((resolve, reject) => {
    execFile(executable, args, { ...options, encoding: 'utf8', timeout: 180000, maxBuffer: 4 * 1024 * 1024, windowsHide: true }, (error, stdout, stderr) => {
      if (error) { reject(new Error(`Could not prepare the CLI: ${stderr || error.message}`)); return; }
      resolve({ profile: /(?:^|\s)--profile(?:\s|$)/m.test(stdout), noReconnect: /(?:^|\s)--no-reconnect(?:\s|$)/m.test(stdout), local: /(?:^|\s)--local(?:\s|$)/m.test(stdout), xsct: /(?:^|\s)--xsct(?:\s|$)/m.test(stdout), repo: /(?:^|\s)--repo(?:\s|$)/m.test(stdout) });
    });
  });
}
module.exports = { readHelp };
