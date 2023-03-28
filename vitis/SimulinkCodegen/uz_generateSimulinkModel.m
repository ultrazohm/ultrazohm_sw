[filepath,~,~] = fileparts(mfilename('fullpath')); % Get absolute filepath to this file
newStr = erase(filepath,mfilename); % gets rid of name of the script
cd(newStr); % cd to ultrazohm_sw/vitis/SimulinkCodegen
uz_setCodegenPaths;
open_system('uz_codegen');
rtwbuild('uz_codegen/uz_codegen');