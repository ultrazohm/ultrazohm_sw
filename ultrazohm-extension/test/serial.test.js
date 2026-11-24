const { test } = require('node:test');
const assert = require('node:assert/strict');
const { EventEmitter } = require('node:events');
const { PassThrough } = require('node:stream');
const fs = require('node:fs');
const path = require('node:path');
const vm = require('node:vm');
const { identity, matchingPorts, settings, encodeInput } = require('../serial-tools');
test('serial identity follows renumbered ports and rejects ambiguous/missing interfaces', () => {
 const a={device:'COM9',vid:1,pid:2,serialNumber:'ABC',interface:'C',location:'1.3'};
 const saved=identity(a), moved={...a,device:'COM14',location:'2.3'};
 assert.deepEqual(matchingPorts([moved],'identity','COM9',saved),[moved]);
 assert.deepEqual(matchingPorts([{...moved,interface:'D'}],'identity','COM9',saved),[]);
 assert.equal(matchingPorts([moved,{...moved,device:'COM15'}],'identity','COM9',{...saved,location:null}).length,2);
 assert.deepEqual(matchingPorts([moved],'identity','COM14',{}),[]);
 assert.deepEqual(matchingPorts([moved],'device','COM14',{}),[moved]);
});
test('serial defaults and input encoding match the UART configuration', () => {
 const result=settings({get:(_,fallback)=>fallback},'COM9');
 assert.equal(result.baud,115200);assert.equal(result.parity,'N');assert.equal(result.flowControl,'none');
 assert.equal(encodeInput('a\r\nb\rc\n','CRLF').toString(),'a\r\nb\r\nc\r\n');
 assert.throws(()=>settings({get:(key,fallback)=>key==='serial.baud'?0:fallback},'COM9'),/Invalid serial/);
});
function setup() {
 const commands={}, saved={}, messages=[], terminals=[], children=[], state={ports:[{device:'/dev/ttyUSB2',description:'UART',vid:1,pid:2,serialNumber:'serial',interface:'C'}]};
 const config={get:(key,fallback)=>saved[key]??fallback,update:async(key,value)=>{saved[key]=value;}};
 const disposable={dispose(){}};
 class Emitter { constructor(){this.listeners=[];this.event=fn=>{this.listeners.push(fn);return disposable;};} fire(v){for(const fn of this.listeners)fn(v);} dispose(){} }
 const vscode={EventEmitter:Emitter,env:{},ConfigurationTarget:{Global:1},
  workspace:{isTrusted:true,getConfiguration:()=>config,onDidChangeConfiguration:()=>disposable},
  commands:{registerCommand:(name,fn)=>{commands[name]=fn;return disposable;}},
  window:{registerTreeDataProvider:(_,provider)=>{state.provider=provider;return disposable;},showErrorMessage:m=>messages.push(m),
   showQuickPick:async entries=>state.cancel?undefined:entries[0],showInputBox:async()=>'/dev/ttyUSB3',
   createTerminal:options=>{const output=[];options.pty.onDidWrite(s=>output.push(s));let ended;
    options.pty.onDidClose(code=>{ended=code;});
    const term={...options,output,show(){this.shown=true;if(!this.opened){this.opened=true;options.pty.open();}},dispose(){options.pty.close();},get ended(){return ended;}};
    terminals.push(term);return term;},
  }};
 const childProcess={execFile:(_python,args,_options,cb)=>{assert.equal(args[3],'list');cb(null,JSON.stringify(state.ports));},
  spawn:(_python,args)=>{assert.equal(args[3],'connect');const child=new EventEmitter();child.stdin=new PassThrough();child.stdout=new PassThrough();child.stderr=new PassThrough();child.kill=()=>child.emit('close',1);children.push(child);return child;}};
 const module={exports:{}};
 vm.runInNewContext(fs.readFileSync(path.join(__dirname,'../serial-controller.js'),'utf8'),{module,require:name=>name==='vscode'?vscode:name==='node:child_process'?childProcess:name==='node:fs'?{readFileSync:()=>JSON.stringify({platform:'linux',arch:'x64',python:'python/bin/python3'}),mkdirSync(){}}:name==='./runtime-env'?{environment:()=>({})}:name==='./serial-tools'?require('../serial-tools'):require(name),process:{platform:'linux',arch:'x64',env:{}},Buffer,setTimeout,clearTimeout});
 module.exports.activateSerial({subscriptions:[],extensionPath:'/extension',globalStorageUri:{fsPath:'/private'}});
 return {state,saved,messages,terminals,children,vscode,run:key=>commands['ultrazohm.serial.'+key]()};
}
test('Serial pane connects without a checkout, forwards bytes, reveals one session, and releases on close',async()=>{
 const s=setup();assert.equal(s.state.provider.getChildren()[0].label,'Connect');
 await Promise.all([s.run('connect'),s.run('connect')]);assert.deepEqual(s.messages,[]);assert.equal(s.terminals.length,1);
 assert.equal(s.saved['serial.identity'].serialNumber,'serial');
 const child=s.children[0], term=s.terminals[0];child.stdout.write('{"event":"connected"}\n');
 child.stdout.write(JSON.stringify({event:'data',data:Buffer.from('hello\n').toString('base64')})+'\n');
 assert(term.output.join('').includes('hello\r\n'));
 for (const chunk of ['one\r', '\n\n']) child.stdout.write(JSON.stringify({event:'data',data:Buffer.from(chunk).toString('base64')})+'\n');
 assert(term.output.join('').includes('one\r\n\r\n'));
 const unicode=Buffer.from('ä');
 for (const byte of unicode) child.stdout.write(JSON.stringify({event:'data',data:Buffer.from([byte]).toString('base64')})+'\n');
 assert(term.output.join('').endsWith('ä'));

 term.pty.handleInput('test\r');const message=JSON.parse(child.stdin.read().toString());assert.equal(Buffer.from(message.data,'base64').toString(),'test\r');
 await s.run('connect');assert.equal(s.terminals.length,1);
 await s.run('baud');assert.match(s.messages[0],/Disconnect/);
 term.dispose();assert(child.stdin.writableEnded);child.emit('close',0);
 assert.equal(term.ended,0);assert.equal(s.state.provider.getChildren()[0].label,'Connect');
});
test('cancel, untrusted windows, and helper errors are handled without opening extra ports',async()=>{
 const s=setup();s.state.cancel=true;await s.run('connect');assert.equal(s.children.length,0);
 s.state.cancel=false;s.vscode.workspace.isTrusted=false;await s.run('connect');assert.match(s.messages[0],/trusted local/);
 s.vscode.workspace.isTrusted=true;await s.run('connect');
 s.children[0].stdout.write('{"event":"error","message":"Access denied"}\n');s.children[0].emit('close',1);
 assert(s.terminals[0].output.join('').includes('Access denied'));assert.equal(s.state.provider.getChildren()[0].label,'Connect');
});
test('first connection defaults to UltraZohm interface 02 even when tty numbering changes', async () => {
 const s=setup();
 s.state.ports=[{device:'/dev/ttyUSB9',description:'UltraZohm',vid:null,pid:null,serialNumber:'UZ',interfaceNumber:3},
                {device:'/dev/ttyUSB8',description:'UltraZohm',vid:null,pid:null,serialNumber:'UZ',interfaceNumber:2}];
 s.state.cancel=true; // No picker should be needed for an unambiguous default.
 await s.run('connect');assert.equal(s.saved['serial.device'],'/dev/ttyUSB8');
 s.children[0].emit('close',0);
 s.saved['serial.identity']=identity(s.state.ports[0]);s.saved['serial.device']='/dev/ttyUSB9';
 await s.run('connect');assert.equal(s.saved['serial.device'],'/dev/ttyUSB9');s.children[1].emit('close',0);
});
test('automatic UART selection never guesses for unrelated devices or multiple adapters', () => {
 const {defaultPort}=require('../serial-tools');
 assert.equal(defaultPort([{device:'/dev/ttyUSB2',description:'Other adapter',interfaceNumber:2}]),undefined);
 const port={description:'UltraZohm',interfaceNumber:2};
 assert.equal(defaultPort([port,{...port,device:'COM9'}]),undefined);
 assert.equal(defaultPort([{...port,interfaceNumber:null}]),undefined);
});
