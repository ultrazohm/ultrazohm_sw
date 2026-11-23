const path = require('path');
function environment(base, storage, inherited) {
 const env = {...inherited};
 for (const key of Object.keys(env)) if (/^UV_|^PYTHON|^VIRTUAL_ENV$|^CONDA_PREFIX$/.test(key)) delete env[key];
 Object.assign(env, {UZ_BUNDLED_RUNTIME:base, UV_PYTHON_INSTALL_DIR:path.join(base,'python'), UV_PYTHON_PREFERENCE:'only-managed', UV_PYTHON_DOWNLOADS:'never', UV_PYTHON_NO_REGISTRY:'1', UV_PYTHON_INSTALL_REGISTRY:'0', UV_PYTHON_INSTALL_BIN:'0', UV_NO_CONFIG:'1', UV_CACHE_DIR:path.join(storage,'cache'), UV_TOOL_DIR:path.join(storage,'tools'), UV_TOOL_BIN_DIR:path.join(storage,'bin'), PYTHONDONTWRITEBYTECODE:'1', PYTHONNOUSERSITE:'1', TMPDIR:path.join(storage,'tmp'), TEMP:path.join(storage,'tmp'), TMP:path.join(storage,'tmp')});
 const key=Object.keys(env).find(k=>k.toLowerCase()==='path') || 'PATH';
 env[key]=path.join(base,'bin')+path.delimiter+(env[key]||'');
 return env;
}
module.exports={environment};
