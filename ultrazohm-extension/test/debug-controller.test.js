const {test}=require('node:test');
const assert=require('node:assert/strict');
const fs=require('node:fs');
const path=require('node:path');
const vm=require('node:vm');
function setup() {
 const events={},configs=[],messages=[],factories={},disposable={dispose(){}};
 let id=0;
 const state={failCore:undefined,frame:'main()',missingTools:false};
 const vscode={debug:{
  registerDebugAdapterDescriptorFactory:(name,factory)=>{factories[name]=factory;return disposable;},
  onDidStartDebugSession:fn=>{events.start=fn;return disposable;},onDidTerminateDebugSession:fn=>{events.end=fn;return disposable;},
  startDebugging:async(scope,config)=>{
   if(config.ultrazohmCore===state.failCore)return false;
   configs.push(config);const session={id:String(++id),name:config.name,configuration:config,customRequest:async op=>op==='threads'?{threads:[{id:1}]}:{stackFrames:[{name:state.frame}]}};
   events.start(session);return true;
  }},extensions:{getExtension:()=>state.missingTools?undefined:{extensionPath:'/cpp',activate:async()=>{}}},
  window:{showInformationMessage:async text=>messages.push(text)},
  DebugAdapterExecutable:class{constructor(command,args,options){Object.assign(this,{command,args,options});}},
 };
 const module={exports:{}};
 vm.runInNewContext(fs.readFileSync(path.join(__dirname,'../debug-controller.js'),'utf8'),{module,require:name=>{
  if(name==='vscode')return vscode;
  if(name==='node:fs')return {existsSync:()=>true};
  if(name==='node:path')return path.posix;
  if(name==='./debug-tools')return {toolsForDebug:()=>({cores:[{id:'R5',port:3000},{id:'A53',port:3001}],server:'/vitis/hw_server'}),configuration:(core,root)=>({name:core.id,ultrazohmCore:core.id,ultrazohmRepository:root})};
  if(name==='./debug-rsp')return {processors:async()=>'',processorId:()=>1};
  if(name==='./service')return {portInUse:async()=>true};
  throw Error(name);
 },process:{platform:'linux'},setTimeout});
 const api=module.exports.controller({subscriptions:[],extensionPath:'/extension'},()=>{});
 return {api,state,configs,messages,factories,events};
}
test('both cores attach paused and use the bundled adapter proxy with the Vitis environment',async()=>{
 const s=setup();const tools=await s.api.prepare({},{});
 await s.api.attach({root:'/repo',scope:{},tools,env:{VITIS:'yes'},python:'/private/python',atMain:true});
 assert.equal(s.configs.length,2);assert(s.api.active('/repo'));assert(!s.api.active('/another'));
 assert.match(s.messages[0],/R5 and A53 are stopped/);
 const descriptor=s.factories['ultrazohm-gdb'].createDebugAdapterDescriptor({configuration:s.configs[0]});
 assert.equal(descriptor.command,'/private/python');assert.equal(descriptor.args[1],'/extension/debug-adapter.py');assert.equal(descriptor.options.env.VITIS,'yes');
 await assert.rejects(s.api.attach({root:'/repo'}),/Disconnect/);
 s.events.end({id:'1'});s.events.end({id:'2'});assert(!s.api.active());
});
test('partial attachment and wrong main handoff are reported without auto-detaching/resuming a core',async()=>{
 for(const mode of ['fail','frame']) {
  const s=setup();if(mode==='fail')s.state.failCore='A53';else s.state.frame='unexpected_function';
  const tools=await s.api.prepare({},{});
  await assert.rejects(s.api.attach({root:'/repo',tools,env:{},python:'/python',atMain:true}),/left open/);
  assert(s.api.active('/repo'));assert.equal(s.messages.length,0);
 }
});
test('missing C++ tools gives an actionable error before touching the hardware server',async()=>{
 const s=setup();s.state.missingTools=true;await assert.rejects(s.api.prepare({},{}),/Install Microsoft C\/C\+\+/);assert.equal(s.configs.length,0);
});
