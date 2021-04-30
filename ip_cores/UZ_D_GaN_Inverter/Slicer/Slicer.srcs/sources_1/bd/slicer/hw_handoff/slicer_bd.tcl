
################################################################
# This is a generated script based on design: slicer
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

namespace eval _tcl {
proc get_script_folder {} {
   set script_path [file normalize [info script]]
   set script_folder [file dirname $script_path]
   return $script_folder
}
}
variable script_folder
set script_folder [_tcl::get_script_folder]

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2020.1
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   catch {common::send_gid_msg -ssname BD::TCL -id 2041 -severity "ERROR" "This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."}

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source slicer_script.tcl

# If there is no project opened, this script will create a
# project, but make sure you do not have an existing project
# <./myproj/project_1.xpr> in the current working folder.

set list_projs [get_projects -quiet]
if { $list_projs eq "" } {
   create_project project_1 myproj -part xczu9eg-ffvc900-1-i
}


# CHANGE DESIGN NAME HERE
variable design_name
set design_name slicer

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
   # USE CASES:
   #    1) Design_name not set

   set errMsg "Please set the variable <design_name> to a non-empty value."
   set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
   # USE CASES:
   #    2): Current design opened AND is empty AND names same.
   #    3): Current design opened AND is empty AND names diff; design_name NOT in project.
   #    4): Current design opened AND is empty AND names diff; design_name exists in project.

   if { $cur_design ne $design_name } {
      common::send_gid_msg -ssname BD::TCL -id 2001 -severity "INFO" "Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   common::send_gid_msg -ssname BD::TCL -id 2002 -severity "INFO" "Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
   # USE CASES:
   #    5) Current design opened AND has components AND same names.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
   # USE CASES: 
   #    6) Current opened design, has components, but diff names, design_name exists in project.
   #    7) No opened design, design_name exists in project.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 2

} else {
   # USE CASES:
   #    8) No opened design, design_name not in project.
   #    9) Current opened design, has components, but diff names, design_name not in project.

   common::send_gid_msg -ssname BD::TCL -id 2003 -severity "INFO" "Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design $design_name

   common::send_gid_msg -ssname BD::TCL -id 2004 -severity "INFO" "Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

common::send_gid_msg -ssname BD::TCL -id 2005 -severity "INFO" "Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   catch {common::send_gid_msg -ssname BD::TCL -id 2006 -severity "ERROR" $errMsg}
   return $nRet
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  variable script_folder
  variable design_name

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2090 -severity "ERROR" "Unable to find parent cell <$parentCell>!"}
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2091 -severity "ERROR" "Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."}
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports

  # Create ports
  set GaN_FAULT [ create_bd_port -dir I -from 5 -to 0 GaN_FAULT ]
  set GaN_H1_FAULT [ create_bd_port -dir O -from 0 -to 0 GaN_H1_FAULT ]
  set GaN_H1_OC [ create_bd_port -dir O -from 0 -to 0 GaN_H1_OC ]
  set GaN_H1_Temp [ create_bd_port -dir O -from 0 -to 0 GaN_H1_Temp ]
  set GaN_H2_FAULT [ create_bd_port -dir O -from 0 -to 0 GaN_H2_FAULT ]
  set GaN_H2_OC [ create_bd_port -dir O -from 0 -to 0 GaN_H2_OC ]
  set GaN_H2_Temp [ create_bd_port -dir O -from 0 -to 0 GaN_H2_Temp ]
  set GaN_H3_FAULT [ create_bd_port -dir O -from 0 -to 0 GaN_H3_FAULT ]
  set GaN_H3_OC [ create_bd_port -dir O -from 0 -to 0 GaN_H3_OC ]
  set GaN_H3_Temp [ create_bd_port -dir O -from 0 -to 0 GaN_H3_Temp ]
  set GaN_L1_FAULT [ create_bd_port -dir O -from 0 -to 0 GaN_L1_FAULT ]
  set GaN_L1_OC [ create_bd_port -dir O -from 0 -to 0 GaN_L1_OC ]
  set GaN_L1_Temp [ create_bd_port -dir O -from 0 -to 0 GaN_L1_Temp ]
  set GaN_L2_FAULT [ create_bd_port -dir O -from 0 -to 0 GaN_L2_FAULT ]
  set GaN_L2_OC [ create_bd_port -dir O -from 0 -to 0 GaN_L2_OC ]
  set GaN_L2_Temp [ create_bd_port -dir O -from 0 -to 0 GaN_L2_Temp ]
  set GaN_L3_FAULT [ create_bd_port -dir O -from 0 -to 0 GaN_L3_FAULT ]
  set GaN_L3_OC [ create_bd_port -dir O -from 0 -to 0 GaN_L3_OC ]
  set GaN_L3_Temp [ create_bd_port -dir O -from 0 -to 0 GaN_L3_Temp ]
  set GaN_OC [ create_bd_port -dir I -from 5 -to 0 GaN_OC ]
  set GaN_Temp [ create_bd_port -dir I -from 5 -to 0 GaN_Temp ]
  set I1_DIAG [ create_bd_port -dir O -from 0 -to 0 I1_DIAG ]
  set I2_DIAG [ create_bd_port -dir O -from 0 -to 0 I2_DIAG ]
  set I3_DIAG [ create_bd_port -dir O -from 0 -to 0 I3_DIAG ]
  set I_DIAG [ create_bd_port -dir O -from 0 -to 0 I_DIAG ]
  set I_SENSE_DIAG [ create_bd_port -dir I -from 3 -to 0 I_SENSE_DIAG ]

  # Create instance: xlslice_0, and set properties
  set xlslice_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_0 ]
  set_property -dict [ list \
   CONFIG.DIN_WIDTH {6} \
 ] $xlslice_0

  # Create instance: xlslice_1, and set properties
  set xlslice_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_1 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {1} \
   CONFIG.DIN_TO {1} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_1

  # Create instance: xlslice_2, and set properties
  set xlslice_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_2 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {2} \
   CONFIG.DIN_TO {2} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_2

  # Create instance: xlslice_3, and set properties
  set xlslice_3 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_3 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {3} \
   CONFIG.DIN_TO {3} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_3

  # Create instance: xlslice_4, and set properties
  set xlslice_4 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_4 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {4} \
   CONFIG.DIN_TO {4} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_4

  # Create instance: xlslice_5, and set properties
  set xlslice_5 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_5 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {5} \
   CONFIG.DIN_TO {5} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_5

  # Create instance: xlslice_6, and set properties
  set xlslice_6 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_6 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {5} \
   CONFIG.DIN_TO {5} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_6

  # Create instance: xlslice_7, and set properties
  set xlslice_7 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_7 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {0} \
   CONFIG.DIN_TO {0} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_7

  # Create instance: xlslice_8, and set properties
  set xlslice_8 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_8 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {1} \
   CONFIG.DIN_TO {1} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_8

  # Create instance: xlslice_9, and set properties
  set xlslice_9 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_9 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {2} \
   CONFIG.DIN_TO {2} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_9

  # Create instance: xlslice_10, and set properties
  set xlslice_10 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_10 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {4} \
   CONFIG.DIN_TO {4} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_10

  # Create instance: xlslice_11, and set properties
  set xlslice_11 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_11 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {3} \
   CONFIG.DIN_TO {3} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_11

  # Create instance: xlslice_12, and set properties
  set xlslice_12 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_12 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {5} \
   CONFIG.DIN_TO {5} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_12

  # Create instance: xlslice_13, and set properties
  set xlslice_13 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_13 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {4} \
   CONFIG.DIN_TO {4} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_13

  # Create instance: xlslice_14, and set properties
  set xlslice_14 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_14 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {3} \
   CONFIG.DIN_TO {3} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_14

  # Create instance: xlslice_15, and set properties
  set xlslice_15 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_15 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {0} \
   CONFIG.DIN_TO {0} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_15

  # Create instance: xlslice_16, and set properties
  set xlslice_16 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_16 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {1} \
   CONFIG.DIN_TO {1} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_16

  # Create instance: xlslice_17, and set properties
  set xlslice_17 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_17 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {2} \
   CONFIG.DIN_TO {2} \
   CONFIG.DIN_WIDTH {6} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_17

  # Create instance: xlslice_18, and set properties
  set xlslice_18 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_18 ]
  set_property -dict [ list \
   CONFIG.DIN_WIDTH {4} \
 ] $xlslice_18

  # Create instance: xlslice_19, and set properties
  set xlslice_19 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_19 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {1} \
   CONFIG.DIN_TO {1} \
   CONFIG.DIN_WIDTH {4} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_19

  # Create instance: xlslice_20, and set properties
  set xlslice_20 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_20 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {2} \
   CONFIG.DIN_TO {2} \
   CONFIG.DIN_WIDTH {4} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_20

  # Create instance: xlslice_21, and set properties
  set xlslice_21 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_21 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {3} \
   CONFIG.DIN_TO {3} \
   CONFIG.DIN_WIDTH {4} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_21

  # Create port connections
  connect_bd_net -net GaN_FAULT_1 [get_bd_ports GaN_FAULT] [get_bd_pins xlslice_12/Din] [get_bd_pins xlslice_13/Din] [get_bd_pins xlslice_14/Din] [get_bd_pins xlslice_15/Din] [get_bd_pins xlslice_16/Din] [get_bd_pins xlslice_17/Din]
  connect_bd_net -net GaN_OC_1 [get_bd_ports GaN_OC] [get_bd_pins xlslice_10/Din] [get_bd_pins xlslice_11/Din] [get_bd_pins xlslice_6/Din] [get_bd_pins xlslice_7/Din] [get_bd_pins xlslice_8/Din] [get_bd_pins xlslice_9/Din]
  connect_bd_net -net GaN_Temp_1 [get_bd_ports GaN_Temp] [get_bd_pins xlslice_0/Din] [get_bd_pins xlslice_1/Din] [get_bd_pins xlslice_2/Din] [get_bd_pins xlslice_3/Din] [get_bd_pins xlslice_4/Din] [get_bd_pins xlslice_5/Din]
  connect_bd_net -net I_DIAG_1 [get_bd_ports I_SENSE_DIAG] [get_bd_pins xlslice_18/Din] [get_bd_pins xlslice_19/Din] [get_bd_pins xlslice_20/Din] [get_bd_pins xlslice_21/Din]
  connect_bd_net -net xlslice_0_Dout [get_bd_ports GaN_H1_Temp] [get_bd_pins xlslice_0/Dout]
  connect_bd_net -net xlslice_10_Dout [get_bd_ports GaN_H3_OC] [get_bd_pins xlslice_10/Dout]
  connect_bd_net -net xlslice_11_Dout [get_bd_ports GaN_L2_OC] [get_bd_pins xlslice_11/Dout]
  connect_bd_net -net xlslice_12_Dout [get_bd_ports GaN_L3_FAULT] [get_bd_pins xlslice_12/Dout]
  connect_bd_net -net xlslice_13_Dout [get_bd_ports GaN_H3_FAULT] [get_bd_pins xlslice_13/Dout]
  connect_bd_net -net xlslice_14_Dout [get_bd_ports GaN_L2_FAULT] [get_bd_pins xlslice_14/Dout]
  connect_bd_net -net xlslice_15_Dout [get_bd_ports GaN_H1_FAULT] [get_bd_pins xlslice_15/Dout]
  connect_bd_net -net xlslice_16_Dout [get_bd_ports GaN_L1_FAULT] [get_bd_pins xlslice_16/Dout]
  connect_bd_net -net xlslice_17_Dout [get_bd_ports GaN_H2_FAULT] [get_bd_pins xlslice_17/Dout]
  connect_bd_net -net xlslice_18_Dout [get_bd_ports I_DIAG] [get_bd_pins xlslice_18/Dout]
  connect_bd_net -net xlslice_19_Dout [get_bd_ports I1_DIAG] [get_bd_pins xlslice_19/Dout]
  connect_bd_net -net xlslice_1_Dout [get_bd_ports GaN_L1_Temp] [get_bd_pins xlslice_1/Dout]
  connect_bd_net -net xlslice_20_Dout [get_bd_ports I2_DIAG] [get_bd_pins xlslice_20/Dout]
  connect_bd_net -net xlslice_21_Dout [get_bd_ports I3_DIAG] [get_bd_pins xlslice_21/Dout]
  connect_bd_net -net xlslice_2_Dout [get_bd_ports GaN_H2_Temp] [get_bd_pins xlslice_2/Dout]
  connect_bd_net -net xlslice_3_Dout [get_bd_ports GaN_L2_Temp] [get_bd_pins xlslice_3/Dout]
  connect_bd_net -net xlslice_4_Dout [get_bd_ports GaN_H3_Temp] [get_bd_pins xlslice_4/Dout]
  connect_bd_net -net xlslice_5_Dout [get_bd_ports GaN_L3_Temp] [get_bd_pins xlslice_5/Dout]
  connect_bd_net -net xlslice_6_Dout [get_bd_ports GaN_L3_OC] [get_bd_pins xlslice_6/Dout]
  connect_bd_net -net xlslice_7_Dout [get_bd_ports GaN_H1_OC] [get_bd_pins xlslice_7/Dout]
  connect_bd_net -net xlslice_8_Dout [get_bd_ports GaN_L1_OC] [get_bd_pins xlslice_8/Dout]
  connect_bd_net -net xlslice_9_Dout [get_bd_ports GaN_H2_OC] [get_bd_pins xlslice_9/Dout]

  # Create address segments


  # Restore current instance
  current_bd_instance $oldCurInst

  validate_bd_design
  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


