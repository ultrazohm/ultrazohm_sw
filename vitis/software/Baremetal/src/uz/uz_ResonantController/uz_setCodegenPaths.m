%% run this script in sections:
%1. Set path



% Get the current configuration
cfg = Simulink.fileGenControl('getConfig');

% Change the parameters to non-default locations
% for the cache and code generation folders
cfg.CacheFolder = pwd;
% cfg.CodeGenFolder = fullfile('..','software','Baremetal','src','Codegen');
cfg.CodeGenFolder = fullfile('..','uz_ResonantController');
cfg.CodeGenFolderStructure='ModelSpecific';
Simulink.fileGenControl('setConfig', 'config', cfg)






%%
% 2. copy shared files

% copy utility-functions form shared folder to other folder
source_folder_path = 'slprj/ert/_sharedutils'
destination_folder_path = 'Resonant_Controller_ert_rtw'

sharedCodeUpdate(source_folder_path, destination_folder_path, 'ExistingCodeSubfolder', '')
