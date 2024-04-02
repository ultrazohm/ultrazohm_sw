% Get the current configuration
cfg = Simulink.fileGenControl('getConfig');

% Change the parameters to non-default locations
% for the cache and code generation folders
cfg.CacheFolder = pwd;
%cfg.CodeGenFolder = fullfile('..','software','Baremetal','src','Codegen');
cfg.CodeGenFolder = fullfile('..','uz_CurrentControl_Kp_iq_adjustment');
cfg.CodeGenFolderStructure='ModelSpecific';
Simulink.fileGenControl('setConfig', 'config', cfg)