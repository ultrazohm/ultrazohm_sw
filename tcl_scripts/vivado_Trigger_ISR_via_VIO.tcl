#******************************************************************************
# Copyright 2021 Robert Zipprich
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and limitations under the License.
#******************************************************************************

# Script to Trigger the ISR of the Ultrazohm once 

# Change to working-directory
# set work_directory [get_property DIRECTORY [current_project]] ; 
# cd $work_directory ; 

puts "Trigger ISR once";

#Set Interrupt-IO to high
set_property OUTPUT_VALUE 1 [get_hw_probes zusys_i/Interrupt/vio_0_probe_out0 -of_objects [get_hw_vios -of_objects [get_hw_devices xczu9_0] -filter {CELL_NAME=~"zusys_i/Interrupt/vio_interrupt"}]];
commit_hw_vio [get_hw_probes {zusys_i/Interrupt/vio_0_probe_out0} -of_objects [get_hw_vios -of_objects [get_hw_devices xczu9_0] -filter {CELL_NAME=~"zusys_i/Interrupt/vio_interrupt"}]];

#Set Interrupt-IO to low
set_property OUTPUT_VALUE 0 [get_hw_probes zusys_i/Interrupt/vio_0_probe_out0 -of_objects [get_hw_vios -of_objects [get_hw_devices xczu9_0] -filter {CELL_NAME=~"zusys_i/Interrupt/vio_interrupt"}]];
commit_hw_vio [get_hw_probes {zusys_i/Interrupt/vio_0_probe_out0} -of_objects [get_hw_vios -of_objects [get_hw_devices xczu9_0] -filter {CELL_NAME=~"zusys_i/Interrupt/vio_interrupt"}]];

puts "Trigger done!";