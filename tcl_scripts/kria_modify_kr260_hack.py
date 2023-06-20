# For external use only - UltraZohm Vitis workspace
#
# This code updates the vitis workspace for KR260 ROBOTICS usage.
#
# Author: Seray Oezcan
# 19/05/2023

import os
from pathlib import Path as plib
import shutil

abspath = os.path.abspath('..')
data_folder = plib(abspath)
vpath = data_folder / 'vitis/'

os.path.exists(vpath)
try:
    os.chdir(vpath)
    print("Current working directory: {0}".format(os.getcwd()))
except FileNotFoundError:
    print("Directory: {0} does not exist".format(vpath))
except NotADirectoryError:
    print("{0} is not a directory".format(vpath))
except PermissionError:
    print("You do not have permissions to change to {0}".format(vpath))

########## BSP HACK ##################

hack_path1 = vpath / 'workspace/UltraZohm/psu_cortexa53_0/FreeRTOS_domain/bsp/psu_cortexa53_0/'
hack_path = hack_path1 / 'libsrc/lwip211_v1_8/src/contrib/ports/xilinx/netif/xemacpsif_physpeed.c'

with open(hack_path, 'r') as file_r:
    hack_content = file_r.read()

hack_content = hack_content.replace("	for (phy_addr = 31; phy_addr > 0; phy_addr--) {",
                                    "	for (phy_addr = 31; phy_addr > 5; phy_addr--) {")

with open(hack_path, 'w') as file_w:
    file_w.write(hack_content)

print('The BSP Hack is successfully implemented')