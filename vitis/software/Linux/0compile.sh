#!/bin/bash

. /tools/Xilinx/Vitis/2022.2/settings64.sh

set -ex

aarch64-linux-gnu-gcc -Wall -o eeprom eeprom.c
