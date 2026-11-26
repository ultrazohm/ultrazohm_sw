const { test } = require('node:test');
const assert = require('node:assert/strict');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const { settingsEnvironment } = require('../vitis-env');
const { resolveXsct } = require('../tools');
const { environment } = require('../runtime-env');

test('source a nonexecutable settings script with spaces and preserve private runtime', { skip: process.platform !== 'linux' }, async t => {
 const dir=fs.mkdtempSync(path.join(os.tmpdir(), 'Vitis setup $ '));t.after(()=>fs.rmSync(dir,{recursive:true,force:true}));
 const bin=path.join(dir,'bin');fs.mkdirSync(bin);fs.writeFileSync(path.join(bin,'xsct'),'#!/bin/sh\n');fs.chmodSync(path.join(bin,'xsct'),0o755);
 const file=path.join(dir,'settings64.sh');
 fs.writeFileSync(file, 'echo "vendor banner"\nexport XILINX_VITIS="$(dirname "${BASH_SOURCE[0]}")"\nexport PATH="$XILINX_VITIS/bin:$PATH"\nexport UV_CACHE_DIR=/unwanted\nexport PYTHONPATH=/unwanted\nexport TEST_VALUE="a=b"\n');
 const env=await settingsEnvironment(file,{PATH:'/usr/bin'});
 assert.equal(env.XILINX_VITIS,dir);assert.equal(env.TEST_VALUE,'a=b');
 assert.equal(resolveXsct(undefined,env).path,path.join(bin,'xsct'));
 const privateEnv=environment('/bundle','/storage',env);
 assert.equal(privateEnv.UV_CACHE_DIR,'/storage/cache');assert.equal(privateEnv.PYTHONPATH,undefined);
 assert.equal(privateEnv.XILINX_VITIS,dir);
 fs.writeFileSync(file,'return 9\n');await assert.rejects(settingsEnvironment(file),/Vitis settings failed/);
});


test('Windows settings64.bat propagates PATH and Unicode values', { skip: process.platform !== 'win32' }, async t => {
 const dir=fs.mkdtempSync(path.join(os.tmpdir(), 'Vitis setup '));t.after(()=>fs.rmSync(dir,{recursive:true,force:true}));
 const file=path.join(dir,'settings64.bat');
 fs.writeFileSync(path.join(dir,'xsct.bat'),'@exit /b 0\r\n');
 fs.writeFileSync(file, `@echo off\r\nset "PATH=${dir};%PATH%"\r\nset "XILINX_VITIS=${dir}"\r\nset "TEST_EQUALS=a=b"\r\n`);
 const env=await settingsEnvironment(file,{...process.env,UZ_TEST_UNICODE:'Grüße'});
 assert.equal(resolveXsct(undefined,env).path,path.join(dir,'xsct.bat'));
 assert.equal(env.XILINX_VITIS,dir);assert.equal(env.TEST_EQUALS,'a=b');assert.equal(env.UZ_TEST_UNICODE,'Grüße');
 fs.writeFileSync(file,'@exit /b 9\r\n');await assert.rejects(settingsEnvironment(file),/Vitis settings failed/);
});
