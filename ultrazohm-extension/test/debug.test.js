const { test } = require('node:test');
const assert = require('node:assert/strict');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const net = require('node:net');
const { packet, processors, processorId } = require('../debug-rsp');
const { toolsForDebug, configuration, bridge } = require('../debug-tools');

test('hw_server processor query handles split packets, verifies checksums and never attaches', async () => {
 const requests=[];
 const server=net.createServer(socket=>socket.on('data',data=>{
  requests.push(data.toString());
  if(data.toString().includes('qSupported:')) socket.write('+'+packet('PacketSize=4000'));
  else if(data.toString().includes('$')) {
   const response=packet('O'+Buffer.from('1: Cortex-R5 #0 (Stopped)\n2: Cortex-R5 #1 (Reset)\n').toString('hex'))+packet('OK');
   socket.write('+'+response.slice(0,7));setImmediate(()=>socket.write(response.slice(7)));
  }
 }));
 await new Promise(resolve=>server.listen(0,'127.0.0.1',resolve));
 try {
  const list=await processors(server.address().port);
  assert.equal(processorId(list,'R5'),1);
  assert(requests.join('').includes(packet('qSupported:multiprocess+')));
  assert(requests.join('').includes(packet('qRcmd,7073')));
  assert(!requests.join('').match(/vAttach|vCont|qRcmd,7265736574/));
 } finally { await new Promise(resolve=>server.close(resolve)); }
});
test('ambiguous/missing processors are rejected instead of selecting the first board',()=>{
 assert.throws(()=>processorId('1: Cortex-A53 #0 (Stopped)\n5: Cortex-A53 #0 (Running)','A53'),/found 2/);
 assert.throws(()=>processorId('1: Cortex-A53 #1','A53'),/found 0/);
 assert.equal(processorId('7: Cortex-A53 #0 (Running)','A53'),7);
});
test('Vitis discovery and configuration use native architecture-specific GDB and attach without reset/download',()=>{
 const root=fs.mkdtempSync(path.join(os.tmpdir(),'uz-debug-'));
 try {
  const touch=relative=>{const file=path.join(root,relative);fs.mkdirSync(path.dirname(file),{recursive:true});fs.writeFileSync(file,'',{mode:0o700});return file;};
  const windows=process.platform==='win32';
  const xsct=touch('bin/'+(windows?'xsct.bat':'xsct'));
  touch('bin/'+(windows?'hw_server.bat':'hw_server'));
  for(const [arch,sub,bin] of [['armr5','gcc-arm-none-eabi','armr5-none-eabi-gdb'],['aarch64','aarch64-none','aarch64-none-elf-gdb']]) touch(`gnu/${arch}/${windows?'nt':'lin'}/${sub}/bin/${bin}${windows?'.exe':''}`);
  const tools=toolsForDebug({path:xsct},{get:(_,fallback)=>fallback});
  for(const core of tools.cores) {
   assert.throws(()=>configuration(core,root,1),/Missing/);
   touch(`vitis/workspace/${core.app}/Debug/${core.app}.elf`);
   const config=configuration(core,root,1);
   assert.equal(config.request,'launch');assert.equal(config.type,'ultrazohm-gdb');assert.equal(config.stopAtConnect,true);assert.equal(config.launchCompleteCommand,'None');
   assert.throws(()=>configuration(core,root,9),/first processor/);
   assert.equal(config.miDebuggerPath,core.gdb);assert.equal(config.miDebuggerArgs,'-nx');
   assert(!JSON.stringify(config).match(/-exec-run|monitor reset|target-download/));
  }
  const privateBridge=bridge(root,root,process.execPath,root,xsct,'127.0.0.1:19740');
  const saved=JSON.parse(fs.readFileSync(privateBridge.config,'utf8'));
  assert.equal(saved.xsct,xsct);assert.equal(saved.root,root);assert(fs.existsSync(privateBridge.launcher));
  assert.notEqual(bridge(root,root,process.execPath,root,xsct,'127.0.0.1:19740').launcher,privateBridge.launcher);
 } finally {fs.rmSync(root,{recursive:true,force:true});}
});
