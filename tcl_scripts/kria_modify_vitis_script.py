# For external use only - UltraZohm Vitis workspace
#
# This code updates the vitis workspace for K26 starter kits usage.
# 
# Author: Seray Oezcan
# 15/05/2023 

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

#################################### Baremetal ######################################

# uz_MioGpio_mediator
mio_gpio_mediator_path = vpath / 'software/Baremetal/src/uz/uz_MioGpio_mediator/uz_MioGpio_mediator.c'

with open(mio_gpio_mediator_path, 'r') as file_r:
    mio_gpio_mediator_content = file_r.read()

mio_gpio_mediator_content = mio_gpio_mediator_content.replace("	enableAllMioWithLEDsAttached();",
                                                              "    //enableAllMioWithLEDsAttached();")
mio_gpio_mediator_content = mio_gpio_mediator_content.replace("	enableAllMioWithButonsAttached();",
                                                              "	//enableAllMioWithButonsAttached();")

with open(mio_gpio_mediator_path, 'w') as file_w:
    file_w.write(mio_gpio_mediator_content)

# uz_GPIO
gpio_path = vpath / "software/Baremetal/src/uz/uz_GPIO/uz_gpio.c"

with open(gpio_path, 'r') as file_r:
    gpio_content = file_r.read()

gpio_content = gpio_content.replace("	uz_assert( uz_gpio_get_enable_output(self) );",
                                    "	//uz_assert( uz_gpio_get_enable_output(self));")

with open(gpio_path, 'w') as file_w:
    file_w.write(gpio_content)

# uz_platform_state_machine
platform_state_machine_path = vpath / 'software/Baremetal/src/hw_init/uz_platform_state_machine.c'

with open(platform_state_machine_path, 'r') as file_r:
    platform_state_machine_content = file_r.read()

platform_state_machine_content = platform_state_machine_content.replace(
    "ultrazohm_state.stop_flag = !(uz_GetPushButtonStop());",
    "ultrazohm_state.stop_flag = 0;")

with open(platform_state_machine_path, 'w') as file_w:
    file_w.write(platform_state_machine_content)

print("Baremetal Update successful")
################################ FreeRTOS ########################################


#remove can files
c_vpath = vpath / 'software/FreeRTOS/sw/can.c'
if os.path.isfile(c_vpath):
    os.remove(c_vpath)
    print("The can.c is removed")
else:
    print("The can.c does not exist")
h_vpath = vpath / 'software/FreeRTOS/include/can.h'
if os.path.exists(h_vpath):
    os.remove(h_vpath)
    print("The can.h is removed")
else:
    print("The can.h does not exist")

# main.c
main_c_path = vpath / 'software/FreeRTOS/main.c'

with open(main_c_path, 'r') as file_r:
    rtos_content = file_r.read()

rtos_content = rtos_content.replace("		if (mscnt >= DHCP_COARSE_TIMER_SECS*1000) ",
                                    "		if (mscnt >= DHCP_COARSE_TIMER_SECS*2000) ")

with open(main_c_path, 'w') as file_w:
    file_w.write(rtos_content)

# CAN delete from main
with open(main_c_path, 'r') as file_r:
    main_c_content = file_r.readlines()

lines_to_delete = set(range(25, 29)).union(set(range(157, 165))).union(set(range(173, 196))).union(set(range(303, 371)))

with open(main_c_path, 'w') as file_w:
    for number, line in enumerate(main_c_content):
        if number not in lines_to_delete:
            file_w.write(line)

# main.h
main_h_path = vpath / 'software/FreeRTOS/main.h'
add = "#define OS_IS_FREERTOS"

with open(main_h_path, 'r+') as h_open:
    h_data = h_open.readlines()
    h_data.insert(32, add + '\n')
    h_open.seek(0)
    h_open.writelines(h_data)
    h_open.truncate()

print("FreeRTOS Update successful")

########## launch files ##########

source_folder = vpath / 'software/'
destination_folder = vpath / 'workspace/.metadata/.plugins/org.eclipse.debug.core/.launches'
files_to_move = ['Debug_FreeRTOS_Baremetal_FPGA.launch', 'DebugFreeRTOS.launch']

if os.path.exists(destination_folder):
    print("The .launches folder already exists")
else:
    destination_folder.mkdir(parents=True, exist_ok=True)

if not os.listdir(destination_folder):
    for file in files_to_move:
        # construct full file path
        source = source_folder / file
        destination = destination_folder / file
        # move file
        shutil.move(str(source), str(destination))
        print('Moved:', file)
else:
    print("The .launches folder is not empty")
