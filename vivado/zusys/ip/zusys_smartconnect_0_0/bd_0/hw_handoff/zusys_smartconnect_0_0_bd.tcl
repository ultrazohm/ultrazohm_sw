
################################################################
# This is a generated script based on design: bd_2abc
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
# source bd_2abc_script.tcl

# If there is no project opened, this script will create a
# project, but make sure you do not have an existing project
# <./myproj/project_1.xpr> in the current working folder.

set list_projs [get_projects -quiet]
if { $list_projs eq "" } {
   create_project project_1 myproj -part xczu9eg-ffvc900-1-e
   set_property BOARD_PART trenz.biz:te0808_9eg_1e:part0:3.0 [current_project]
}


# CHANGE DESIGN NAME HERE
variable design_name
set design_name bd_2abc

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

   create_bd_design -bdsource SBD $design_name

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


# Hierarchical cell: switchboards
proc create_hier_cell_switchboards { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_switchboards() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M00_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M00_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M00_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M00_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M00_SC_W

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M01_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M01_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M01_SC_W

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M02_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M02_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M02_SC_W

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M03_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M03_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M03_SC_W

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M04_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M04_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M04_SC_W

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M05_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M05_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M05_SC_W

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M06_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M06_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M06_SC_W

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M07_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M07_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M07_SC_W

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M08_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M08_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M08_SC_W

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M09_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M09_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M09_SC_W

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M10_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M10_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M10_SC_W

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M11_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M11_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M11_SC_W

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M12_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M12_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M12_SC_W

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M13_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M13_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M13_SC_W

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M14_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M14_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M14_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S00_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S00_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S00_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S00_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S00_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S01_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S01_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S02_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S02_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S03_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S03_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S04_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S04_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S05_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S05_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S06_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S06_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S07_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S07_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S08_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S08_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S09_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S09_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S10_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S10_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S11_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S11_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S12_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S12_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S13_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S13_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S14_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S14_SC_R


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: ar_switchboard, and set properties
  set ar_switchboard [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_switchboard:1.0 ar_switchboard ]
  set_property -dict [ list \
   CONFIG.M00_S00_CONNECTIVITY {1} \
   CONFIG.M01_S00_CONNECTIVITY {1} \
   CONFIG.M02_S00_CONNECTIVITY {1} \
   CONFIG.M03_S00_CONNECTIVITY {1} \
   CONFIG.M04_S00_CONNECTIVITY {1} \
   CONFIG.M05_S00_CONNECTIVITY {1} \
   CONFIG.M06_S00_CONNECTIVITY {1} \
   CONFIG.M07_S00_CONNECTIVITY {1} \
   CONFIG.M08_S00_CONNECTIVITY {1} \
   CONFIG.M09_S00_CONNECTIVITY {1} \
   CONFIG.M10_S00_CONNECTIVITY {1} \
   CONFIG.M11_S00_CONNECTIVITY {1} \
   CONFIG.M12_S00_CONNECTIVITY {1} \
   CONFIG.M13_S00_CONNECTIVITY {1} \
   CONFIG.M14_S00_CONNECTIVITY {0} \
   CONFIG.M_PIPELINES {1} \
   CONFIG.NUM_MI {15} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S_LATENCY {0} \
   CONFIG.S_PIPELINES {0} \
 ] $ar_switchboard

  # Create instance: aw_switchboard, and set properties
  set aw_switchboard [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_switchboard:1.0 aw_switchboard ]
  set_property -dict [ list \
   CONFIG.M00_S00_CONNECTIVITY {1} \
   CONFIG.M01_S00_CONNECTIVITY {1} \
   CONFIG.M02_S00_CONNECTIVITY {1} \
   CONFIG.M03_S00_CONNECTIVITY {1} \
   CONFIG.M04_S00_CONNECTIVITY {1} \
   CONFIG.M05_S00_CONNECTIVITY {1} \
   CONFIG.M06_S00_CONNECTIVITY {1} \
   CONFIG.M07_S00_CONNECTIVITY {1} \
   CONFIG.M08_S00_CONNECTIVITY {1} \
   CONFIG.M09_S00_CONNECTIVITY {1} \
   CONFIG.M10_S00_CONNECTIVITY {1} \
   CONFIG.M11_S00_CONNECTIVITY {1} \
   CONFIG.M12_S00_CONNECTIVITY {1} \
   CONFIG.M13_S00_CONNECTIVITY {1} \
   CONFIG.M14_S00_CONNECTIVITY {0} \
   CONFIG.M_PIPELINES {1} \
   CONFIG.NUM_MI {15} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S_LATENCY {0} \
   CONFIG.S_PIPELINES {0} \
 ] $aw_switchboard

  # Create instance: b_switchboard, and set properties
  set b_switchboard [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_switchboard:1.0 b_switchboard ]
  set_property -dict [ list \
   CONFIG.M00_S00_CONNECTIVITY {1} \
   CONFIG.M00_S01_CONNECTIVITY {1} \
   CONFIG.M00_S02_CONNECTIVITY {1} \
   CONFIG.M00_S03_CONNECTIVITY {1} \
   CONFIG.M00_S04_CONNECTIVITY {1} \
   CONFIG.M00_S05_CONNECTIVITY {1} \
   CONFIG.M00_S06_CONNECTIVITY {1} \
   CONFIG.M00_S07_CONNECTIVITY {1} \
   CONFIG.M00_S08_CONNECTIVITY {1} \
   CONFIG.M00_S09_CONNECTIVITY {1} \
   CONFIG.M00_S10_CONNECTIVITY {1} \
   CONFIG.M00_S11_CONNECTIVITY {1} \
   CONFIG.M00_S12_CONNECTIVITY {1} \
   CONFIG.M00_S13_CONNECTIVITY {1} \
   CONFIG.M00_S14_CONNECTIVITY {0} \
   CONFIG.M_PIPELINES {1} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_SI {15} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S_LATENCY {0} \
   CONFIG.S_PIPELINES {0} \
 ] $b_switchboard

  # Create instance: r_switchboard, and set properties
  set r_switchboard [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_switchboard:1.0 r_switchboard ]
  set_property -dict [ list \
   CONFIG.M00_S00_CONNECTIVITY {1} \
   CONFIG.M00_S01_CONNECTIVITY {1} \
   CONFIG.M00_S02_CONNECTIVITY {1} \
   CONFIG.M00_S03_CONNECTIVITY {1} \
   CONFIG.M00_S04_CONNECTIVITY {1} \
   CONFIG.M00_S05_CONNECTIVITY {1} \
   CONFIG.M00_S06_CONNECTIVITY {1} \
   CONFIG.M00_S07_CONNECTIVITY {1} \
   CONFIG.M00_S08_CONNECTIVITY {1} \
   CONFIG.M00_S09_CONNECTIVITY {1} \
   CONFIG.M00_S10_CONNECTIVITY {1} \
   CONFIG.M00_S11_CONNECTIVITY {1} \
   CONFIG.M00_S12_CONNECTIVITY {1} \
   CONFIG.M00_S13_CONNECTIVITY {1} \
   CONFIG.M00_S14_CONNECTIVITY {0} \
   CONFIG.M_PIPELINES {1} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_SI {15} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S_LATENCY {0} \
   CONFIG.S_PIPELINES {0} \
 ] $r_switchboard

  # Create instance: w_switchboard, and set properties
  set w_switchboard [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_switchboard:1.0 w_switchboard ]
  set_property -dict [ list \
   CONFIG.M00_S00_CONNECTIVITY {1} \
   CONFIG.M01_S00_CONNECTIVITY {1} \
   CONFIG.M02_S00_CONNECTIVITY {1} \
   CONFIG.M03_S00_CONNECTIVITY {1} \
   CONFIG.M04_S00_CONNECTIVITY {1} \
   CONFIG.M05_S00_CONNECTIVITY {1} \
   CONFIG.M06_S00_CONNECTIVITY {1} \
   CONFIG.M07_S00_CONNECTIVITY {1} \
   CONFIG.M08_S00_CONNECTIVITY {1} \
   CONFIG.M09_S00_CONNECTIVITY {1} \
   CONFIG.M10_S00_CONNECTIVITY {1} \
   CONFIG.M11_S00_CONNECTIVITY {1} \
   CONFIG.M12_S00_CONNECTIVITY {1} \
   CONFIG.M13_S00_CONNECTIVITY {1} \
   CONFIG.M14_S00_CONNECTIVITY {0} \
   CONFIG.M_PIPELINES {1} \
   CONFIG.NUM_MI {15} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S_LATENCY {0} \
   CONFIG.S_PIPELINES {0} \
 ] $w_switchboard

  # Create interface connections
  connect_bd_intf_net -intf_net S00_SC_AR_1 [get_bd_intf_pins S00_SC_AR] [get_bd_intf_pins ar_switchboard/S00_SC]
  connect_bd_intf_net -intf_net S00_SC_AW_1 [get_bd_intf_pins S00_SC_AW] [get_bd_intf_pins aw_switchboard/S00_SC]
  connect_bd_intf_net -intf_net S00_SC_B_1 [get_bd_intf_pins S00_SC_B] [get_bd_intf_pins b_switchboard/S00_SC]
  connect_bd_intf_net -intf_net S00_SC_R_1 [get_bd_intf_pins S00_SC_R] [get_bd_intf_pins r_switchboard/S00_SC]
  connect_bd_intf_net -intf_net S00_SC_W_1 [get_bd_intf_pins S00_SC_W] [get_bd_intf_pins w_switchboard/S00_SC]
  connect_bd_intf_net -intf_net S01_SC_B_1 [get_bd_intf_pins S01_SC_B] [get_bd_intf_pins b_switchboard/S01_SC]
  connect_bd_intf_net -intf_net S01_SC_R_1 [get_bd_intf_pins S01_SC_R] [get_bd_intf_pins r_switchboard/S01_SC]
  connect_bd_intf_net -intf_net S02_SC_B_1 [get_bd_intf_pins S02_SC_B] [get_bd_intf_pins b_switchboard/S02_SC]
  connect_bd_intf_net -intf_net S02_SC_R_1 [get_bd_intf_pins S02_SC_R] [get_bd_intf_pins r_switchboard/S02_SC]
  connect_bd_intf_net -intf_net S03_SC_B_1 [get_bd_intf_pins S03_SC_B] [get_bd_intf_pins b_switchboard/S03_SC]
  connect_bd_intf_net -intf_net S03_SC_R_1 [get_bd_intf_pins S03_SC_R] [get_bd_intf_pins r_switchboard/S03_SC]
  connect_bd_intf_net -intf_net S04_SC_B_1 [get_bd_intf_pins S04_SC_B] [get_bd_intf_pins b_switchboard/S04_SC]
  connect_bd_intf_net -intf_net S04_SC_R_1 [get_bd_intf_pins S04_SC_R] [get_bd_intf_pins r_switchboard/S04_SC]
  connect_bd_intf_net -intf_net S05_SC_B_1 [get_bd_intf_pins S05_SC_B] [get_bd_intf_pins b_switchboard/S05_SC]
  connect_bd_intf_net -intf_net S05_SC_R_1 [get_bd_intf_pins S05_SC_R] [get_bd_intf_pins r_switchboard/S05_SC]
  connect_bd_intf_net -intf_net S06_SC_B_1 [get_bd_intf_pins S06_SC_B] [get_bd_intf_pins b_switchboard/S06_SC]
  connect_bd_intf_net -intf_net S06_SC_R_1 [get_bd_intf_pins S06_SC_R] [get_bd_intf_pins r_switchboard/S06_SC]
  connect_bd_intf_net -intf_net S07_SC_B_1 [get_bd_intf_pins S07_SC_B] [get_bd_intf_pins b_switchboard/S07_SC]
  connect_bd_intf_net -intf_net S07_SC_R_1 [get_bd_intf_pins S07_SC_R] [get_bd_intf_pins r_switchboard/S07_SC]
  connect_bd_intf_net -intf_net S08_SC_B_1 [get_bd_intf_pins S08_SC_B] [get_bd_intf_pins b_switchboard/S08_SC]
  connect_bd_intf_net -intf_net S08_SC_R_1 [get_bd_intf_pins S08_SC_R] [get_bd_intf_pins r_switchboard/S08_SC]
  connect_bd_intf_net -intf_net S09_SC_B_1 [get_bd_intf_pins S09_SC_B] [get_bd_intf_pins b_switchboard/S09_SC]
  connect_bd_intf_net -intf_net S09_SC_R_1 [get_bd_intf_pins S09_SC_R] [get_bd_intf_pins r_switchboard/S09_SC]
  connect_bd_intf_net -intf_net S10_SC_B_1 [get_bd_intf_pins S10_SC_B] [get_bd_intf_pins b_switchboard/S10_SC]
  connect_bd_intf_net -intf_net S10_SC_R_1 [get_bd_intf_pins S10_SC_R] [get_bd_intf_pins r_switchboard/S10_SC]
  connect_bd_intf_net -intf_net S11_SC_B_1 [get_bd_intf_pins S11_SC_B] [get_bd_intf_pins b_switchboard/S11_SC]
  connect_bd_intf_net -intf_net S11_SC_R_1 [get_bd_intf_pins S11_SC_R] [get_bd_intf_pins r_switchboard/S11_SC]
  connect_bd_intf_net -intf_net S12_SC_B_1 [get_bd_intf_pins S12_SC_B] [get_bd_intf_pins b_switchboard/S12_SC]
  connect_bd_intf_net -intf_net S12_SC_R_1 [get_bd_intf_pins S12_SC_R] [get_bd_intf_pins r_switchboard/S12_SC]
  connect_bd_intf_net -intf_net S13_SC_B_1 [get_bd_intf_pins S13_SC_B] [get_bd_intf_pins b_switchboard/S13_SC]
  connect_bd_intf_net -intf_net S13_SC_R_1 [get_bd_intf_pins S13_SC_R] [get_bd_intf_pins r_switchboard/S13_SC]
  connect_bd_intf_net -intf_net S14_SC_B_1 [get_bd_intf_pins S14_SC_B] [get_bd_intf_pins b_switchboard/S14_SC]
  connect_bd_intf_net -intf_net S14_SC_R_1 [get_bd_intf_pins S14_SC_R] [get_bd_intf_pins r_switchboard/S14_SC]
  connect_bd_intf_net -intf_net ar_switchboard_M00_SC [get_bd_intf_pins M00_SC_AR] [get_bd_intf_pins ar_switchboard/M00_SC]
  connect_bd_intf_net -intf_net ar_switchboard_M01_SC [get_bd_intf_pins M01_SC_AR] [get_bd_intf_pins ar_switchboard/M01_SC]
  connect_bd_intf_net -intf_net ar_switchboard_M02_SC [get_bd_intf_pins M02_SC_AR] [get_bd_intf_pins ar_switchboard/M02_SC]
  connect_bd_intf_net -intf_net ar_switchboard_M03_SC [get_bd_intf_pins M03_SC_AR] [get_bd_intf_pins ar_switchboard/M03_SC]
  connect_bd_intf_net -intf_net ar_switchboard_M04_SC [get_bd_intf_pins M04_SC_AR] [get_bd_intf_pins ar_switchboard/M04_SC]
  connect_bd_intf_net -intf_net ar_switchboard_M05_SC [get_bd_intf_pins M05_SC_AR] [get_bd_intf_pins ar_switchboard/M05_SC]
  connect_bd_intf_net -intf_net ar_switchboard_M06_SC [get_bd_intf_pins M06_SC_AR] [get_bd_intf_pins ar_switchboard/M06_SC]
  connect_bd_intf_net -intf_net ar_switchboard_M07_SC [get_bd_intf_pins M07_SC_AR] [get_bd_intf_pins ar_switchboard/M07_SC]
  connect_bd_intf_net -intf_net ar_switchboard_M08_SC [get_bd_intf_pins M08_SC_AR] [get_bd_intf_pins ar_switchboard/M08_SC]
  connect_bd_intf_net -intf_net ar_switchboard_M09_SC [get_bd_intf_pins M09_SC_AR] [get_bd_intf_pins ar_switchboard/M09_SC]
  connect_bd_intf_net -intf_net ar_switchboard_M10_SC [get_bd_intf_pins M10_SC_AR] [get_bd_intf_pins ar_switchboard/M10_SC]
  connect_bd_intf_net -intf_net ar_switchboard_M11_SC [get_bd_intf_pins M11_SC_AR] [get_bd_intf_pins ar_switchboard/M11_SC]
  connect_bd_intf_net -intf_net ar_switchboard_M12_SC [get_bd_intf_pins M12_SC_AR] [get_bd_intf_pins ar_switchboard/M12_SC]
  connect_bd_intf_net -intf_net ar_switchboard_M13_SC [get_bd_intf_pins M13_SC_AR] [get_bd_intf_pins ar_switchboard/M13_SC]
  connect_bd_intf_net -intf_net ar_switchboard_M14_SC [get_bd_intf_pins M14_SC_AR] [get_bd_intf_pins ar_switchboard/M14_SC]
  connect_bd_intf_net -intf_net aw_switchboard_M00_SC [get_bd_intf_pins M00_SC_AW] [get_bd_intf_pins aw_switchboard/M00_SC]
  connect_bd_intf_net -intf_net aw_switchboard_M01_SC [get_bd_intf_pins M01_SC_AW] [get_bd_intf_pins aw_switchboard/M01_SC]
  connect_bd_intf_net -intf_net aw_switchboard_M02_SC [get_bd_intf_pins M02_SC_AW] [get_bd_intf_pins aw_switchboard/M02_SC]
  connect_bd_intf_net -intf_net aw_switchboard_M03_SC [get_bd_intf_pins M03_SC_AW] [get_bd_intf_pins aw_switchboard/M03_SC]
  connect_bd_intf_net -intf_net aw_switchboard_M04_SC [get_bd_intf_pins M04_SC_AW] [get_bd_intf_pins aw_switchboard/M04_SC]
  connect_bd_intf_net -intf_net aw_switchboard_M05_SC [get_bd_intf_pins M05_SC_AW] [get_bd_intf_pins aw_switchboard/M05_SC]
  connect_bd_intf_net -intf_net aw_switchboard_M06_SC [get_bd_intf_pins M06_SC_AW] [get_bd_intf_pins aw_switchboard/M06_SC]
  connect_bd_intf_net -intf_net aw_switchboard_M07_SC [get_bd_intf_pins M07_SC_AW] [get_bd_intf_pins aw_switchboard/M07_SC]
  connect_bd_intf_net -intf_net aw_switchboard_M08_SC [get_bd_intf_pins M08_SC_AW] [get_bd_intf_pins aw_switchboard/M08_SC]
  connect_bd_intf_net -intf_net aw_switchboard_M09_SC [get_bd_intf_pins M09_SC_AW] [get_bd_intf_pins aw_switchboard/M09_SC]
  connect_bd_intf_net -intf_net aw_switchboard_M10_SC [get_bd_intf_pins M10_SC_AW] [get_bd_intf_pins aw_switchboard/M10_SC]
  connect_bd_intf_net -intf_net aw_switchboard_M11_SC [get_bd_intf_pins M11_SC_AW] [get_bd_intf_pins aw_switchboard/M11_SC]
  connect_bd_intf_net -intf_net aw_switchboard_M12_SC [get_bd_intf_pins M12_SC_AW] [get_bd_intf_pins aw_switchboard/M12_SC]
  connect_bd_intf_net -intf_net aw_switchboard_M13_SC [get_bd_intf_pins M13_SC_AW] [get_bd_intf_pins aw_switchboard/M13_SC]
  connect_bd_intf_net -intf_net aw_switchboard_M14_SC [get_bd_intf_pins M14_SC_AW] [get_bd_intf_pins aw_switchboard/M14_SC]
  connect_bd_intf_net -intf_net b_switchboard_M00_SC [get_bd_intf_pins M00_SC_B] [get_bd_intf_pins b_switchboard/M00_SC]
  connect_bd_intf_net -intf_net r_switchboard_M00_SC [get_bd_intf_pins M00_SC_R] [get_bd_intf_pins r_switchboard/M00_SC]
  connect_bd_intf_net -intf_net w_switchboard_M00_SC [get_bd_intf_pins M00_SC_W] [get_bd_intf_pins w_switchboard/M00_SC]
  connect_bd_intf_net -intf_net w_switchboard_M01_SC [get_bd_intf_pins M01_SC_W] [get_bd_intf_pins w_switchboard/M01_SC]
  connect_bd_intf_net -intf_net w_switchboard_M02_SC [get_bd_intf_pins M02_SC_W] [get_bd_intf_pins w_switchboard/M02_SC]
  connect_bd_intf_net -intf_net w_switchboard_M03_SC [get_bd_intf_pins M03_SC_W] [get_bd_intf_pins w_switchboard/M03_SC]
  connect_bd_intf_net -intf_net w_switchboard_M04_SC [get_bd_intf_pins M04_SC_W] [get_bd_intf_pins w_switchboard/M04_SC]
  connect_bd_intf_net -intf_net w_switchboard_M05_SC [get_bd_intf_pins M05_SC_W] [get_bd_intf_pins w_switchboard/M05_SC]
  connect_bd_intf_net -intf_net w_switchboard_M06_SC [get_bd_intf_pins M06_SC_W] [get_bd_intf_pins w_switchboard/M06_SC]
  connect_bd_intf_net -intf_net w_switchboard_M07_SC [get_bd_intf_pins M07_SC_W] [get_bd_intf_pins w_switchboard/M07_SC]
  connect_bd_intf_net -intf_net w_switchboard_M08_SC [get_bd_intf_pins M08_SC_W] [get_bd_intf_pins w_switchboard/M08_SC]
  connect_bd_intf_net -intf_net w_switchboard_M09_SC [get_bd_intf_pins M09_SC_W] [get_bd_intf_pins w_switchboard/M09_SC]
  connect_bd_intf_net -intf_net w_switchboard_M10_SC [get_bd_intf_pins M10_SC_W] [get_bd_intf_pins w_switchboard/M10_SC]
  connect_bd_intf_net -intf_net w_switchboard_M11_SC [get_bd_intf_pins M11_SC_W] [get_bd_intf_pins w_switchboard/M11_SC]
  connect_bd_intf_net -intf_net w_switchboard_M12_SC [get_bd_intf_pins M12_SC_W] [get_bd_intf_pins w_switchboard/M12_SC]
  connect_bd_intf_net -intf_net w_switchboard_M13_SC [get_bd_intf_pins M13_SC_W] [get_bd_intf_pins w_switchboard/M13_SC]
  connect_bd_intf_net -intf_net w_switchboard_M14_SC [get_bd_intf_pins M14_SC_W] [get_bd_intf_pins w_switchboard/M14_SC]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins ar_switchboard/aclk] [get_bd_pins aw_switchboard/aclk] [get_bd_pins b_switchboard/aclk] [get_bd_pins r_switchboard/aclk] [get_bd_pins w_switchboard/aclk]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: s00_nodes
proc create_hier_cell_s00_nodes { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_s00_nodes() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_W


  # Create pins
  create_bd_pin -dir I -type clk m_sc_clk
  create_bd_pin -dir I -type rst m_sc_resetn
  create_bd_pin -dir I -type clk s_sc_clk
  create_bd_pin -dir I -type rst s_sc_resetn

  # Create instance: s00_ar_node, and set properties
  set s00_ar_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 s00_ar_node ]
  set_property -dict [ list \
   CONFIG.ACLKEN_CONVERSION {0} \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {2} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {15} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.USER_WIDTH {16} \
 ] $s00_ar_node

  # Create instance: s00_aw_node, and set properties
  set s00_aw_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 s00_aw_node ]
  set_property -dict [ list \
   CONFIG.ACLKEN_CONVERSION {0} \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {3} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {15} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.USER_WIDTH {16} \
 ] $s00_aw_node

  # Create instance: s00_b_node, and set properties
  set s00_b_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 s00_b_node ]
  set_property -dict [ list \
   CONFIG.ACLKEN_CONVERSION {0} \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {4} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {15} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {0} \
 ] $s00_b_node

  # Create instance: s00_r_node, and set properties
  set s00_r_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 s00_r_node ]
  set_property -dict [ list \
   CONFIG.ACLKEN_CONVERSION {0} \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {0} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {15} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
 ] $s00_r_node

  # Create instance: s00_w_node, and set properties
  set s00_w_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 s00_w_node ]
  set_property -dict [ list \
   CONFIG.ACLKEN_CONVERSION {0} \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {15} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.USER_BITS_PER_BYTE {0} \
 ] $s00_w_node

  # Create interface connections
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins S_SC_AR] [get_bd_intf_pins s00_ar_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins S_SC_AW] [get_bd_intf_pins s00_aw_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins S_SC_B] [get_bd_intf_pins s00_b_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins S_SC_R] [get_bd_intf_pins s00_r_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins S_SC_W] [get_bd_intf_pins s00_w_node/S_SC]
  connect_bd_intf_net -intf_net s00_ar_node_M_SC [get_bd_intf_pins M_SC_AR] [get_bd_intf_pins s00_ar_node/M_SC]
  connect_bd_intf_net -intf_net s00_aw_node_M_SC [get_bd_intf_pins M_SC_AW] [get_bd_intf_pins s00_aw_node/M_SC]
  connect_bd_intf_net -intf_net s00_b_node_M_SC [get_bd_intf_pins M_SC_B] [get_bd_intf_pins s00_b_node/M_SC]
  connect_bd_intf_net -intf_net s00_r_node_M_SC [get_bd_intf_pins M_SC_R] [get_bd_intf_pins s00_r_node/M_SC]
  connect_bd_intf_net -intf_net s00_w_node_M_SC [get_bd_intf_pins M_SC_W] [get_bd_intf_pins s00_w_node/M_SC]

  # Create port connections
  connect_bd_net -net m_sc_clk_1 [get_bd_pins m_sc_clk] [get_bd_pins s00_ar_node/m_sc_aclk] [get_bd_pins s00_aw_node/m_sc_aclk] [get_bd_pins s00_b_node/s_sc_aclk] [get_bd_pins s00_r_node/s_sc_aclk] [get_bd_pins s00_w_node/m_sc_aclk]
  connect_bd_net -net m_sc_resetn_1 [get_bd_pins m_sc_resetn] [get_bd_pins s00_ar_node/m_sc_aresetn] [get_bd_pins s00_aw_node/m_sc_aresetn] [get_bd_pins s00_b_node/s_sc_aresetn] [get_bd_pins s00_r_node/s_sc_aresetn] [get_bd_pins s00_w_node/m_sc_aresetn]
  connect_bd_net -net s_sc_clk_1 [get_bd_pins s_sc_clk] [get_bd_pins s00_ar_node/s_sc_aclk] [get_bd_pins s00_aw_node/s_sc_aclk] [get_bd_pins s00_b_node/m_sc_aclk] [get_bd_pins s00_r_node/m_sc_aclk] [get_bd_pins s00_w_node/s_sc_aclk]
  connect_bd_net -net s_sc_resetn_1 [get_bd_pins s_sc_resetn] [get_bd_pins s00_ar_node/s_sc_aresetn] [get_bd_pins s00_aw_node/s_sc_aresetn] [get_bd_pins s00_b_node/m_sc_aresetn] [get_bd_pins s00_r_node/m_sc_aresetn] [get_bd_pins s00_w_node/s_sc_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: s00_entry_pipeline
proc create_hier_cell_s00_entry_pipeline { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_s00_entry_pipeline() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 m_axi

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: s00_mmu, and set properties
  set s00_mmu [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_mmu:1.0 s00_mmu ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.ID_WIDTH {16} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MSC000_ROUTE {0b000000000000001} \
   CONFIG.MSC001_ROUTE {0b000000000000010} \
   CONFIG.MSC002_ROUTE {0b000000000000100} \
   CONFIG.MSC003_ROUTE {0b000000000001000} \
   CONFIG.MSC004_ROUTE {0b000000000010000} \
   CONFIG.MSC005_ROUTE {0b000000000100000} \
   CONFIG.MSC006_ROUTE {0b000000001000000} \
   CONFIG.MSC007_ROUTE {0b000000010000000} \
   CONFIG.MSC008_ROUTE {0b000000100000000} \
   CONFIG.MSC009_ROUTE {0b000001000000000} \
   CONFIG.MSC010_ROUTE {0b000010000000000} \
   CONFIG.MSC011_ROUTE {0b000100000000000} \
   CONFIG.MSC012_ROUTE {0b001000000000000} \
   CONFIG.MSC013_ROUTE {0b010000000000000} \
   CONFIG.MSC014_ROUTE {0b100000000000000} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_SEG {14} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RDATA_WIDTH {128} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SEG000_BASE_ADDR {0x0000000080000000} \
   CONFIG.SEG000_SECURE_READ {0} \
   CONFIG.SEG000_SECURE_WRITE {0} \
   CONFIG.SEG000_SEP_ROUTE {0b0000000000000000000000000000000000000000000000000000000000000000} \
   CONFIG.SEG000_SIZE {16} \
   CONFIG.SEG000_SUPPORTS_READ {1} \
   CONFIG.SEG000_SUPPORTS_WRITE {1} \
   CONFIG.SEG001_BASE_ADDR {0x0000000080010000} \
   CONFIG.SEG001_SECURE_READ {0} \
   CONFIG.SEG001_SECURE_WRITE {0} \
   CONFIG.SEG001_SEP_ROUTE {0b0000000000000000000000000000000000000000000000000000000000000001} \
   CONFIG.SEG001_SIZE {16} \
   CONFIG.SEG001_SUPPORTS_READ {1} \
   CONFIG.SEG001_SUPPORTS_WRITE {1} \
   CONFIG.SEG002_BASE_ADDR {0x0000000080020000} \
   CONFIG.SEG002_SECURE_READ {0} \
   CONFIG.SEG002_SECURE_WRITE {0} \
   CONFIG.SEG002_SEP_ROUTE {0b0000000000000000000000000000000000000000000000000000000000000010} \
   CONFIG.SEG002_SIZE {16} \
   CONFIG.SEG002_SUPPORTS_READ {1} \
   CONFIG.SEG002_SUPPORTS_WRITE {1} \
   CONFIG.SEG003_BASE_ADDR {0x0000000080030000} \
   CONFIG.SEG003_SECURE_READ {0} \
   CONFIG.SEG003_SECURE_WRITE {0} \
   CONFIG.SEG003_SEP_ROUTE {0b0000000000000000000000000000000000000000000000000000000000000011} \
   CONFIG.SEG003_SIZE {16} \
   CONFIG.SEG003_SUPPORTS_READ {1} \
   CONFIG.SEG003_SUPPORTS_WRITE {1} \
   CONFIG.SEG004_BASE_ADDR {0x0000000080040000} \
   CONFIG.SEG004_SECURE_READ {0} \
   CONFIG.SEG004_SECURE_WRITE {0} \
   CONFIG.SEG004_SEP_ROUTE {0b0000000000000000000000000000000000000000000000000000000000001000} \
   CONFIG.SEG004_SIZE {16} \
   CONFIG.SEG004_SUPPORTS_READ {1} \
   CONFIG.SEG004_SUPPORTS_WRITE {1} \
   CONFIG.SEG005_BASE_ADDR {0x0000000080050000} \
   CONFIG.SEG005_SECURE_READ {0} \
   CONFIG.SEG005_SECURE_WRITE {0} \
   CONFIG.SEG005_SEP_ROUTE {0b0000000000000000000000000000000000000000000000000000000000000111} \
   CONFIG.SEG005_SIZE {16} \
   CONFIG.SEG005_SUPPORTS_READ {1} \
   CONFIG.SEG005_SUPPORTS_WRITE {1} \
   CONFIG.SEG006_BASE_ADDR {0x0000000080060000} \
   CONFIG.SEG006_SECURE_READ {0} \
   CONFIG.SEG006_SECURE_WRITE {0} \
   CONFIG.SEG006_SEP_ROUTE {0b0000000000000000000000000000000000000000000000000000000000001100} \
   CONFIG.SEG006_SIZE {16} \
   CONFIG.SEG006_SUPPORTS_READ {1} \
   CONFIG.SEG006_SUPPORTS_WRITE {1} \
   CONFIG.SEG007_BASE_ADDR {0x0000000080070000} \
   CONFIG.SEG007_SECURE_READ {0} \
   CONFIG.SEG007_SECURE_WRITE {0} \
   CONFIG.SEG007_SEP_ROUTE {0b0000000000000000000000000000000000000000000000000000000000001001} \
   CONFIG.SEG007_SIZE {16} \
   CONFIG.SEG007_SUPPORTS_READ {1} \
   CONFIG.SEG007_SUPPORTS_WRITE {1} \
   CONFIG.SEG008_BASE_ADDR {0x0000000080080000} \
   CONFIG.SEG008_SECURE_READ {0} \
   CONFIG.SEG008_SECURE_WRITE {0} \
   CONFIG.SEG008_SEP_ROUTE {0b0000000000000000000000000000000000000000000000000000000000001011} \
   CONFIG.SEG008_SIZE {16} \
   CONFIG.SEG008_SUPPORTS_READ {1} \
   CONFIG.SEG008_SUPPORTS_WRITE {1} \
   CONFIG.SEG009_BASE_ADDR {0x0000000080090000} \
   CONFIG.SEG009_SECURE_READ {0} \
   CONFIG.SEG009_SECURE_WRITE {0} \
   CONFIG.SEG009_SEP_ROUTE {0b0000000000000000000000000000000000000000000000000000000000000100} \
   CONFIG.SEG009_SIZE {16} \
   CONFIG.SEG009_SUPPORTS_READ {1} \
   CONFIG.SEG009_SUPPORTS_WRITE {1} \
   CONFIG.SEG010_BASE_ADDR {0x00000000800A0000} \
   CONFIG.SEG010_SECURE_READ {0} \
   CONFIG.SEG010_SECURE_WRITE {0} \
   CONFIG.SEG010_SEP_ROUTE {0b0000000000000000000000000000000000000000000000000000000000000110} \
   CONFIG.SEG010_SIZE {16} \
   CONFIG.SEG010_SUPPORTS_READ {1} \
   CONFIG.SEG010_SUPPORTS_WRITE {1} \
   CONFIG.SEG011_BASE_ADDR {0x00000000800B0000} \
   CONFIG.SEG011_SECURE_READ {0} \
   CONFIG.SEG011_SECURE_WRITE {0} \
   CONFIG.SEG011_SEP_ROUTE {0b0000000000000000000000000000000000000000000000000000000000000101} \
   CONFIG.SEG011_SIZE {16} \
   CONFIG.SEG011_SUPPORTS_READ {1} \
   CONFIG.SEG011_SUPPORTS_WRITE {1} \
   CONFIG.SEG012_BASE_ADDR {0x00000000800C0000} \
   CONFIG.SEG012_SECURE_READ {0} \
   CONFIG.SEG012_SECURE_WRITE {0} \
   CONFIG.SEG012_SEP_ROUTE {0b0000000000000000000000000000000000000000000000000000000000001010} \
   CONFIG.SEG012_SIZE {16} \
   CONFIG.SEG012_SUPPORTS_READ {1} \
   CONFIG.SEG012_SUPPORTS_WRITE {1} \
   CONFIG.SEG013_BASE_ADDR {0x00000000800D0000} \
   CONFIG.SEG013_SECURE_READ {0} \
   CONFIG.SEG013_SECURE_WRITE {0} \
   CONFIG.SEG013_SEP_ROUTE {0b0000000000000000000000000000000000000000000000000000000000001101} \
   CONFIG.SEG013_SIZE {16} \
   CONFIG.SEG013_SUPPORTS_READ {1} \
   CONFIG.SEG013_SUPPORTS_WRITE {1} \
   CONFIG.SUPPORTS_NARROW {1} \
   CONFIG.S_ARUSER_WIDTH {16} \
   CONFIG.S_AWUSER_WIDTH {16} \
   CONFIG.S_BUSER_WIDTH {0} \
   CONFIG.S_PROTOCOL {AXI4} \
   CONFIG.S_RUSER_WIDTH {0} \
   CONFIG.S_WUSER_WIDTH {0} \
   CONFIG.WDATA_WIDTH {128} \
 ] $s00_mmu

  # Create instance: s00_si_converter, and set properties
  set s00_si_converter [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_si_converter:1.0 s00_si_converter ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.HAS_BURST {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MAX_RUSER_BITS_PER_BYTE {0} \
   CONFIG.MAX_WUSER_BITS_PER_BYTE {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.MSC000_RDATA_WIDTH {32} \
   CONFIG.MSC000_WDATA_WIDTH {32} \
   CONFIG.MSC001_RDATA_WIDTH {32} \
   CONFIG.MSC001_WDATA_WIDTH {32} \
   CONFIG.MSC002_RDATA_WIDTH {32} \
   CONFIG.MSC002_WDATA_WIDTH {32} \
   CONFIG.MSC003_RDATA_WIDTH {32} \
   CONFIG.MSC003_WDATA_WIDTH {32} \
   CONFIG.MSC004_RDATA_WIDTH {32} \
   CONFIG.MSC004_WDATA_WIDTH {32} \
   CONFIG.MSC005_RDATA_WIDTH {32} \
   CONFIG.MSC005_WDATA_WIDTH {32} \
   CONFIG.MSC006_RDATA_WIDTH {32} \
   CONFIG.MSC006_WDATA_WIDTH {32} \
   CONFIG.MSC007_RDATA_WIDTH {32} \
   CONFIG.MSC007_WDATA_WIDTH {32} \
   CONFIG.MSC008_RDATA_WIDTH {32} \
   CONFIG.MSC008_WDATA_WIDTH {32} \
   CONFIG.MSC009_RDATA_WIDTH {32} \
   CONFIG.MSC009_WDATA_WIDTH {32} \
   CONFIG.MSC010_RDATA_WIDTH {128} \
   CONFIG.MSC010_WDATA_WIDTH {128} \
   CONFIG.MSC011_RDATA_WIDTH {32} \
   CONFIG.MSC011_WDATA_WIDTH {32} \
   CONFIG.MSC012_RDATA_WIDTH {32} \
   CONFIG.MSC012_WDATA_WIDTH {32} \
   CONFIG.MSC013_RDATA_WIDTH {32} \
   CONFIG.MSC013_WDATA_WIDTH {32} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_READ_THREADS {4} \
   CONFIG.NUM_SEG {14} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_THREADS {4} \
   CONFIG.RDATA_WIDTH {128} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SEP000_PROTOCOL {AXI4LITE} \
   CONFIG.SEP000_RDATA_WIDTH {32} \
   CONFIG.SEP000_WDATA_WIDTH {32} \
   CONFIG.SEP001_PROTOCOL {AXI4LITE} \
   CONFIG.SEP001_RDATA_WIDTH {32} \
   CONFIG.SEP001_WDATA_WIDTH {32} \
   CONFIG.SEP002_PROTOCOL {AXI4LITE} \
   CONFIG.SEP002_RDATA_WIDTH {32} \
   CONFIG.SEP002_WDATA_WIDTH {32} \
   CONFIG.SEP003_PROTOCOL {AXI4LITE} \
   CONFIG.SEP003_RDATA_WIDTH {32} \
   CONFIG.SEP003_WDATA_WIDTH {32} \
   CONFIG.SEP004_PROTOCOL {AXI4LITE} \
   CONFIG.SEP004_RDATA_WIDTH {32} \
   CONFIG.SEP004_WDATA_WIDTH {32} \
   CONFIG.SEP005_PROTOCOL {AXI4} \
   CONFIG.SEP005_RDATA_WIDTH {32} \
   CONFIG.SEP005_WDATA_WIDTH {32} \
   CONFIG.SEP006_PROTOCOL {AXI4LITE} \
   CONFIG.SEP006_RDATA_WIDTH {32} \
   CONFIG.SEP006_WDATA_WIDTH {32} \
   CONFIG.SEP007_PROTOCOL {AXI4LITE} \
   CONFIG.SEP007_RDATA_WIDTH {32} \
   CONFIG.SEP007_WDATA_WIDTH {32} \
   CONFIG.SEP008_PROTOCOL {AXI4LITE} \
   CONFIG.SEP008_RDATA_WIDTH {32} \
   CONFIG.SEP008_WDATA_WIDTH {32} \
   CONFIG.SEP009_PROTOCOL {AXI4LITE} \
   CONFIG.SEP009_RDATA_WIDTH {32} \
   CONFIG.SEP009_WDATA_WIDTH {32} \
   CONFIG.SEP010_PROTOCOL {AXI4LITE} \
   CONFIG.SEP010_RDATA_WIDTH {32} \
   CONFIG.SEP010_WDATA_WIDTH {32} \
   CONFIG.SEP011_PROTOCOL {AXI4LITE} \
   CONFIG.SEP011_RDATA_WIDTH {32} \
   CONFIG.SEP011_WDATA_WIDTH {32} \
   CONFIG.SEP012_PROTOCOL {AXI4} \
   CONFIG.SEP012_RDATA_WIDTH {32} \
   CONFIG.SEP012_WDATA_WIDTH {32} \
   CONFIG.SEP013_PROTOCOL {AXI4LITE} \
   CONFIG.SEP013_RDATA_WIDTH {32} \
   CONFIG.SEP013_WDATA_WIDTH {32} \
   CONFIG.SUPPORTS_NARROW {1} \
   CONFIG.S_RUSER_BITS_PER_BYTE {0} \
   CONFIG.S_WUSER_BITS_PER_BYTE {0} \
   CONFIG.WDATA_WIDTH {128} \
 ] $s00_si_converter

  # Create instance: s00_transaction_regulator, and set properties
  set s00_transaction_regulator [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_transaction_regulator:1.0 s00_transaction_regulator ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MEP_IDENTIFIER {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_READ_THREADS {4} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_THREADS {4} \
   CONFIG.RDATA_WIDTH {128} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SEP_ROUTE_WIDTH {5} \
   CONFIG.SUPPORTS_READ_DEADLOCK {1} \
   CONFIG.SUPPORTS_WRITE_DEADLOCK {1} \
   CONFIG.S_ID_WIDTH {16} \
   CONFIG.WDATA_WIDTH {128} \
 ] $s00_transaction_regulator

  # Create interface connections
  connect_bd_intf_net -intf_net s00_mmu_M_AXI [get_bd_intf_pins s00_mmu/M_AXI] [get_bd_intf_pins s00_transaction_regulator/S_AXI]
  connect_bd_intf_net -intf_net s00_si_converter_M_AXI [get_bd_intf_pins m_axi] [get_bd_intf_pins s00_si_converter/M_AXI]
  connect_bd_intf_net -intf_net s00_transaction_regulator_M_AXI [get_bd_intf_pins s00_si_converter/S_AXI] [get_bd_intf_pins s00_transaction_regulator/M_AXI]
  connect_bd_intf_net -intf_net s_axi_1 [get_bd_intf_pins s_axi] [get_bd_intf_pins s00_mmu/S_AXI]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins s00_mmu/aclk] [get_bd_pins s00_si_converter/aclk] [get_bd_pins s00_transaction_regulator/aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins s00_mmu/aresetn] [get_bd_pins s00_si_converter/aresetn] [get_bd_pins s00_transaction_regulator/aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m13_nodes
proc create_hier_cell_m13_nodes { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m13_nodes() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_W


  # Create pins
  create_bd_pin -dir I -type clk m_axi_aclk
  create_bd_pin -dir I -type rst m_axi_aresetn
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type rst s_axi_aresetn

  # Create instance: m13_ar_node, and set properties
  set m13_ar_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m13_ar_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {2} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m13_ar_node

  # Create instance: m13_aw_node, and set properties
  set m13_aw_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m13_aw_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {3} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m13_aw_node

  # Create instance: m13_b_node, and set properties
  set m13_b_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m13_b_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {4} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_WIDTH {0} \
 ] $m13_b_node

  # Create instance: m13_r_node, and set properties
  set m13_r_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m13_r_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {0} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m13_r_node

  # Create instance: m13_w_node, and set properties
  set m13_w_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m13_w_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m13_w_node

  # Create interface connections
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins S_SC_AR] [get_bd_intf_pins m13_ar_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins S_SC_AW] [get_bd_intf_pins m13_aw_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins S_SC_B] [get_bd_intf_pins m13_b_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins S_SC_R] [get_bd_intf_pins m13_r_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins S_SC_W] [get_bd_intf_pins m13_w_node/S_SC]
  connect_bd_intf_net -intf_net m13_ar_node_M_SC [get_bd_intf_pins M_SC_AR] [get_bd_intf_pins m13_ar_node/M_SC]
  connect_bd_intf_net -intf_net m13_aw_node_M_SC [get_bd_intf_pins M_SC_AW] [get_bd_intf_pins m13_aw_node/M_SC]
  connect_bd_intf_net -intf_net m13_b_node_M_SC [get_bd_intf_pins M_SC_B] [get_bd_intf_pins m13_b_node/M_SC]
  connect_bd_intf_net -intf_net m13_r_node_M_SC [get_bd_intf_pins M_SC_R] [get_bd_intf_pins m13_r_node/M_SC]
  connect_bd_intf_net -intf_net m13_w_node_M_SC [get_bd_intf_pins M_SC_W] [get_bd_intf_pins m13_w_node/M_SC]

  # Create port connections
  connect_bd_net -net m_axi_aclk_1 [get_bd_pins m_axi_aclk] [get_bd_pins m13_ar_node/m_sc_aclk] [get_bd_pins m13_aw_node/m_sc_aclk] [get_bd_pins m13_b_node/s_sc_aclk] [get_bd_pins m13_r_node/s_sc_aclk] [get_bd_pins m13_w_node/m_sc_aclk]
  connect_bd_net -net m_axi_aresetn_1 [get_bd_pins m_axi_aresetn] [get_bd_pins m13_ar_node/m_sc_aresetn] [get_bd_pins m13_aw_node/m_sc_aresetn] [get_bd_pins m13_b_node/s_sc_aresetn] [get_bd_pins m13_r_node/s_sc_aresetn] [get_bd_pins m13_w_node/m_sc_aresetn]
  connect_bd_net -net s_axi_aclk_1 [get_bd_pins s_axi_aclk] [get_bd_pins m13_ar_node/s_sc_aclk] [get_bd_pins m13_aw_node/s_sc_aclk] [get_bd_pins m13_b_node/m_sc_aclk] [get_bd_pins m13_r_node/m_sc_aclk] [get_bd_pins m13_w_node/s_sc_aclk]
  connect_bd_net -net s_axi_aresetn_1 [get_bd_pins s_axi_aresetn] [get_bd_pins m13_ar_node/s_sc_aresetn] [get_bd_pins m13_aw_node/s_sc_aresetn] [get_bd_pins m13_b_node/m_sc_aresetn] [get_bd_pins m13_r_node/m_sc_aresetn] [get_bd_pins m13_w_node/s_sc_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m13_exit_pipeline
proc create_hier_cell_m13_exit_pipeline { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m13_exit_pipeline() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 m_axi

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: m13_exit, and set properties
  set m13_exit [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_exit:1.0 m13_exit ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {16} \
   CONFIG.HAS_BURST {0} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.M_ID_WIDTH {0} \
   CONFIG.M_MAX_BURST_LENGTH {1} \
   CONFIG.M_PROTOCOL {AXI4LITE} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RDATA_WIDTH {32} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SSC000_ROUTE {0b1} \
   CONFIG.SSC001_ROUTE {0b0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
   CONFIG.S_ID_WIDTH {3} \
   CONFIG.WDATA_WIDTH {32} \
 ] $m13_exit

  # Create interface connections
  connect_bd_intf_net -intf_net m13_exit_M_AXI [get_bd_intf_pins m_axi] [get_bd_intf_pins m13_exit/M_AXI]
  connect_bd_intf_net -intf_net s_axi_1 [get_bd_intf_pins s_axi] [get_bd_intf_pins m13_exit/S_AXI]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins m13_exit/aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins m13_exit/aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m12_nodes
proc create_hier_cell_m12_nodes { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m12_nodes() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_W


  # Create pins
  create_bd_pin -dir I -type clk m_axi_aclk
  create_bd_pin -dir I -type rst m_axi_aresetn
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type rst s_axi_aresetn

  # Create instance: m12_ar_node, and set properties
  set m12_ar_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m12_ar_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {2} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m12_ar_node

  # Create instance: m12_aw_node, and set properties
  set m12_aw_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m12_aw_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {3} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m12_aw_node

  # Create instance: m12_b_node, and set properties
  set m12_b_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m12_b_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {4} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_WIDTH {0} \
 ] $m12_b_node

  # Create instance: m12_r_node, and set properties
  set m12_r_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m12_r_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {0} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m12_r_node

  # Create instance: m12_w_node, and set properties
  set m12_w_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m12_w_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m12_w_node

  # Create interface connections
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins S_SC_AR] [get_bd_intf_pins m12_ar_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins S_SC_AW] [get_bd_intf_pins m12_aw_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins S_SC_B] [get_bd_intf_pins m12_b_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins S_SC_R] [get_bd_intf_pins m12_r_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins S_SC_W] [get_bd_intf_pins m12_w_node/S_SC]
  connect_bd_intf_net -intf_net m12_ar_node_M_SC [get_bd_intf_pins M_SC_AR] [get_bd_intf_pins m12_ar_node/M_SC]
  connect_bd_intf_net -intf_net m12_aw_node_M_SC [get_bd_intf_pins M_SC_AW] [get_bd_intf_pins m12_aw_node/M_SC]
  connect_bd_intf_net -intf_net m12_b_node_M_SC [get_bd_intf_pins M_SC_B] [get_bd_intf_pins m12_b_node/M_SC]
  connect_bd_intf_net -intf_net m12_r_node_M_SC [get_bd_intf_pins M_SC_R] [get_bd_intf_pins m12_r_node/M_SC]
  connect_bd_intf_net -intf_net m12_w_node_M_SC [get_bd_intf_pins M_SC_W] [get_bd_intf_pins m12_w_node/M_SC]

  # Create port connections
  connect_bd_net -net m_axi_aclk_1 [get_bd_pins m_axi_aclk] [get_bd_pins m12_ar_node/m_sc_aclk] [get_bd_pins m12_aw_node/m_sc_aclk] [get_bd_pins m12_b_node/s_sc_aclk] [get_bd_pins m12_r_node/s_sc_aclk] [get_bd_pins m12_w_node/m_sc_aclk]
  connect_bd_net -net m_axi_aresetn_1 [get_bd_pins m_axi_aresetn] [get_bd_pins m12_ar_node/m_sc_aresetn] [get_bd_pins m12_aw_node/m_sc_aresetn] [get_bd_pins m12_b_node/s_sc_aresetn] [get_bd_pins m12_r_node/s_sc_aresetn] [get_bd_pins m12_w_node/m_sc_aresetn]
  connect_bd_net -net s_axi_aclk_1 [get_bd_pins s_axi_aclk] [get_bd_pins m12_ar_node/s_sc_aclk] [get_bd_pins m12_aw_node/s_sc_aclk] [get_bd_pins m12_b_node/m_sc_aclk] [get_bd_pins m12_r_node/m_sc_aclk] [get_bd_pins m12_w_node/s_sc_aclk]
  connect_bd_net -net s_axi_aresetn_1 [get_bd_pins s_axi_aresetn] [get_bd_pins m12_ar_node/s_sc_aresetn] [get_bd_pins m12_aw_node/s_sc_aresetn] [get_bd_pins m12_b_node/m_sc_aresetn] [get_bd_pins m12_r_node/m_sc_aresetn] [get_bd_pins m12_w_node/s_sc_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m12_exit_pipeline
proc create_hier_cell_m12_exit_pipeline { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m12_exit_pipeline() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 m_axi

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: m12_exit, and set properties
  set m12_exit [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_exit:1.0 m12_exit ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {16} \
   CONFIG.HAS_BURST {0} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.M_ID_WIDTH {0} \
   CONFIG.M_MAX_BURST_LENGTH {1} \
   CONFIG.M_PROTOCOL {AXI4LITE} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RDATA_WIDTH {32} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SSC000_ROUTE {0b1} \
   CONFIG.SSC001_ROUTE {0b0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
   CONFIG.S_ID_WIDTH {3} \
   CONFIG.WDATA_WIDTH {32} \
 ] $m12_exit

  # Create interface connections
  connect_bd_intf_net -intf_net m12_exit_M_AXI [get_bd_intf_pins m_axi] [get_bd_intf_pins m12_exit/M_AXI]
  connect_bd_intf_net -intf_net s_axi_1 [get_bd_intf_pins s_axi] [get_bd_intf_pins m12_exit/S_AXI]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins m12_exit/aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins m12_exit/aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m11_nodes
proc create_hier_cell_m11_nodes { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m11_nodes() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_W


  # Create pins
  create_bd_pin -dir I -type clk m_axi_aclk
  create_bd_pin -dir I -type rst m_axi_aresetn
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type rst s_axi_aresetn

  # Create instance: m11_ar_node, and set properties
  set m11_ar_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m11_ar_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {2} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m11_ar_node

  # Create instance: m11_aw_node, and set properties
  set m11_aw_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m11_aw_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {3} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m11_aw_node

  # Create instance: m11_b_node, and set properties
  set m11_b_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m11_b_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {4} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_WIDTH {0} \
 ] $m11_b_node

  # Create instance: m11_r_node, and set properties
  set m11_r_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m11_r_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {0} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m11_r_node

  # Create instance: m11_w_node, and set properties
  set m11_w_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m11_w_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m11_w_node

  # Create interface connections
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins S_SC_AR] [get_bd_intf_pins m11_ar_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins S_SC_AW] [get_bd_intf_pins m11_aw_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins S_SC_B] [get_bd_intf_pins m11_b_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins S_SC_R] [get_bd_intf_pins m11_r_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins S_SC_W] [get_bd_intf_pins m11_w_node/S_SC]
  connect_bd_intf_net -intf_net m11_ar_node_M_SC [get_bd_intf_pins M_SC_AR] [get_bd_intf_pins m11_ar_node/M_SC]
  connect_bd_intf_net -intf_net m11_aw_node_M_SC [get_bd_intf_pins M_SC_AW] [get_bd_intf_pins m11_aw_node/M_SC]
  connect_bd_intf_net -intf_net m11_b_node_M_SC [get_bd_intf_pins M_SC_B] [get_bd_intf_pins m11_b_node/M_SC]
  connect_bd_intf_net -intf_net m11_r_node_M_SC [get_bd_intf_pins M_SC_R] [get_bd_intf_pins m11_r_node/M_SC]
  connect_bd_intf_net -intf_net m11_w_node_M_SC [get_bd_intf_pins M_SC_W] [get_bd_intf_pins m11_w_node/M_SC]

  # Create port connections
  connect_bd_net -net m_axi_aclk_1 [get_bd_pins m_axi_aclk] [get_bd_pins m11_ar_node/m_sc_aclk] [get_bd_pins m11_aw_node/m_sc_aclk] [get_bd_pins m11_b_node/s_sc_aclk] [get_bd_pins m11_r_node/s_sc_aclk] [get_bd_pins m11_w_node/m_sc_aclk]
  connect_bd_net -net m_axi_aresetn_1 [get_bd_pins m_axi_aresetn] [get_bd_pins m11_ar_node/m_sc_aresetn] [get_bd_pins m11_aw_node/m_sc_aresetn] [get_bd_pins m11_b_node/s_sc_aresetn] [get_bd_pins m11_r_node/s_sc_aresetn] [get_bd_pins m11_w_node/m_sc_aresetn]
  connect_bd_net -net s_axi_aclk_1 [get_bd_pins s_axi_aclk] [get_bd_pins m11_ar_node/s_sc_aclk] [get_bd_pins m11_aw_node/s_sc_aclk] [get_bd_pins m11_b_node/m_sc_aclk] [get_bd_pins m11_r_node/m_sc_aclk] [get_bd_pins m11_w_node/s_sc_aclk]
  connect_bd_net -net s_axi_aresetn_1 [get_bd_pins s_axi_aresetn] [get_bd_pins m11_ar_node/s_sc_aresetn] [get_bd_pins m11_aw_node/s_sc_aresetn] [get_bd_pins m11_b_node/m_sc_aresetn] [get_bd_pins m11_r_node/m_sc_aresetn] [get_bd_pins m11_w_node/s_sc_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m11_exit_pipeline
proc create_hier_cell_m11_exit_pipeline { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m11_exit_pipeline() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 m_axi

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: m11_exit, and set properties
  set m11_exit [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_exit:1.0 m11_exit ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {5} \
   CONFIG.HAS_BURST {0} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.M_ID_WIDTH {0} \
   CONFIG.M_MAX_BURST_LENGTH {1} \
   CONFIG.M_PROTOCOL {AXI4LITE} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RDATA_WIDTH {32} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SSC000_ROUTE {0b1} \
   CONFIG.SSC001_ROUTE {0b0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
   CONFIG.S_ID_WIDTH {3} \
   CONFIG.WDATA_WIDTH {32} \
 ] $m11_exit

  # Create interface connections
  connect_bd_intf_net -intf_net m11_exit_M_AXI [get_bd_intf_pins m_axi] [get_bd_intf_pins m11_exit/M_AXI]
  connect_bd_intf_net -intf_net s_axi_1 [get_bd_intf_pins s_axi] [get_bd_intf_pins m11_exit/S_AXI]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins m11_exit/aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins m11_exit/aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m10_nodes
proc create_hier_cell_m10_nodes { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m10_nodes() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_W


  # Create pins
  create_bd_pin -dir I -type clk m_axi_aclk
  create_bd_pin -dir I -type rst m_axi_aresetn
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type rst s_axi_aresetn

  # Create instance: m10_ar_node, and set properties
  set m10_ar_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m10_ar_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {2} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m10_ar_node

  # Create instance: m10_aw_node, and set properties
  set m10_aw_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m10_aw_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {3} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m10_aw_node

  # Create instance: m10_b_node, and set properties
  set m10_b_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m10_b_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {4} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_WIDTH {0} \
 ] $m10_b_node

  # Create instance: m10_r_node, and set properties
  set m10_r_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m10_r_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {0} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m10_r_node

  # Create instance: m10_w_node, and set properties
  set m10_w_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m10_w_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m10_w_node

  # Create interface connections
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins S_SC_AR] [get_bd_intf_pins m10_ar_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins S_SC_AW] [get_bd_intf_pins m10_aw_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins S_SC_B] [get_bd_intf_pins m10_b_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins S_SC_R] [get_bd_intf_pins m10_r_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins S_SC_W] [get_bd_intf_pins m10_w_node/S_SC]
  connect_bd_intf_net -intf_net m10_ar_node_M_SC [get_bd_intf_pins M_SC_AR] [get_bd_intf_pins m10_ar_node/M_SC]
  connect_bd_intf_net -intf_net m10_aw_node_M_SC [get_bd_intf_pins M_SC_AW] [get_bd_intf_pins m10_aw_node/M_SC]
  connect_bd_intf_net -intf_net m10_b_node_M_SC [get_bd_intf_pins M_SC_B] [get_bd_intf_pins m10_b_node/M_SC]
  connect_bd_intf_net -intf_net m10_r_node_M_SC [get_bd_intf_pins M_SC_R] [get_bd_intf_pins m10_r_node/M_SC]
  connect_bd_intf_net -intf_net m10_w_node_M_SC [get_bd_intf_pins M_SC_W] [get_bd_intf_pins m10_w_node/M_SC]

  # Create port connections
  connect_bd_net -net m_axi_aclk_1 [get_bd_pins m_axi_aclk] [get_bd_pins m10_ar_node/m_sc_aclk] [get_bd_pins m10_aw_node/m_sc_aclk] [get_bd_pins m10_b_node/s_sc_aclk] [get_bd_pins m10_r_node/s_sc_aclk] [get_bd_pins m10_w_node/m_sc_aclk]
  connect_bd_net -net m_axi_aresetn_1 [get_bd_pins m_axi_aresetn] [get_bd_pins m10_ar_node/m_sc_aresetn] [get_bd_pins m10_aw_node/m_sc_aresetn] [get_bd_pins m10_b_node/s_sc_aresetn] [get_bd_pins m10_r_node/s_sc_aresetn] [get_bd_pins m10_w_node/m_sc_aresetn]
  connect_bd_net -net s_axi_aclk_1 [get_bd_pins s_axi_aclk] [get_bd_pins m10_ar_node/s_sc_aclk] [get_bd_pins m10_aw_node/s_sc_aclk] [get_bd_pins m10_b_node/m_sc_aclk] [get_bd_pins m10_r_node/m_sc_aclk] [get_bd_pins m10_w_node/s_sc_aclk]
  connect_bd_net -net s_axi_aresetn_1 [get_bd_pins s_axi_aresetn] [get_bd_pins m10_ar_node/s_sc_aresetn] [get_bd_pins m10_aw_node/s_sc_aresetn] [get_bd_pins m10_b_node/m_sc_aresetn] [get_bd_pins m10_r_node/m_sc_aresetn] [get_bd_pins m10_w_node/s_sc_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m10_exit_pipeline
proc create_hier_cell_m10_exit_pipeline { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m10_exit_pipeline() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 m_axi

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: m10_exit, and set properties
  set m10_exit [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_exit:1.0 m10_exit ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.HAS_BURST {1} \
   CONFIG.IS_CASCADED {1} \
   CONFIG.MAX_RUSER_BITS_PER_BYTE {0} \
   CONFIG.MAX_WUSER_BITS_PER_BYTE {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.M_ARUSER_WIDTH {130} \
   CONFIG.M_AWUSER_WIDTH {130} \
   CONFIG.M_BUSER_WIDTH {114} \
   CONFIG.M_MAX_BURST_LENGTH {256} \
   CONFIG.M_RUSER_BITS_PER_BYTE {0} \
   CONFIG.M_RUSER_WIDTH {14} \
   CONFIG.M_WUSER_BITS_PER_BYTE {0} \
   CONFIG.M_WUSER_WIDTH {14} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RDATA_WIDTH {128} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SSC000_ROUTE {0b1} \
   CONFIG.SSC001_ROUTE {0b0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
   CONFIG.S_ID_WIDTH {3} \
   CONFIG.WDATA_WIDTH {128} \
 ] $m10_exit

  # Create interface connections
  connect_bd_intf_net -intf_net m10_exit_M_AXI [get_bd_intf_pins m_axi] [get_bd_intf_pins m10_exit/M_AXI]
  connect_bd_intf_net -intf_net s_axi_1 [get_bd_intf_pins s_axi] [get_bd_intf_pins m10_exit/S_AXI]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins m10_exit/aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins m10_exit/aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m09_nodes
proc create_hier_cell_m09_nodes { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m09_nodes() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_W


  # Create pins
  create_bd_pin -dir I -type clk m_axi_aclk
  create_bd_pin -dir I -type rst m_axi_aresetn
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type rst s_axi_aresetn

  # Create instance: m09_ar_node, and set properties
  set m09_ar_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m09_ar_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {0} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {2} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m09_ar_node

  # Create instance: m09_aw_node, and set properties
  set m09_aw_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m09_aw_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {0} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {3} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m09_aw_node

  # Create instance: m09_b_node, and set properties
  set m09_b_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m09_b_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {0} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {4} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_WIDTH {0} \
 ] $m09_b_node

  # Create instance: m09_r_node, and set properties
  set m09_r_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m09_r_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {0} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {0} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m09_r_node

  # Create instance: m09_w_node, and set properties
  set m09_w_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m09_w_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {0} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m09_w_node

  # Create interface connections
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins S_SC_AR] [get_bd_intf_pins m09_ar_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins S_SC_AW] [get_bd_intf_pins m09_aw_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins S_SC_B] [get_bd_intf_pins m09_b_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins S_SC_R] [get_bd_intf_pins m09_r_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins S_SC_W] [get_bd_intf_pins m09_w_node/S_SC]
  connect_bd_intf_net -intf_net m09_ar_node_M_SC [get_bd_intf_pins M_SC_AR] [get_bd_intf_pins m09_ar_node/M_SC]
  connect_bd_intf_net -intf_net m09_aw_node_M_SC [get_bd_intf_pins M_SC_AW] [get_bd_intf_pins m09_aw_node/M_SC]
  connect_bd_intf_net -intf_net m09_b_node_M_SC [get_bd_intf_pins M_SC_B] [get_bd_intf_pins m09_b_node/M_SC]
  connect_bd_intf_net -intf_net m09_r_node_M_SC [get_bd_intf_pins M_SC_R] [get_bd_intf_pins m09_r_node/M_SC]
  connect_bd_intf_net -intf_net m09_w_node_M_SC [get_bd_intf_pins M_SC_W] [get_bd_intf_pins m09_w_node/M_SC]

  # Create port connections
  connect_bd_net -net m_axi_aclk_1 [get_bd_pins m_axi_aclk] [get_bd_pins m09_ar_node/m_sc_aclk] [get_bd_pins m09_aw_node/m_sc_aclk] [get_bd_pins m09_b_node/s_sc_aclk] [get_bd_pins m09_r_node/s_sc_aclk] [get_bd_pins m09_w_node/m_sc_aclk]
  connect_bd_net -net m_axi_aresetn_1 [get_bd_pins m_axi_aresetn] [get_bd_pins m09_ar_node/m_sc_aresetn] [get_bd_pins m09_aw_node/m_sc_aresetn] [get_bd_pins m09_b_node/s_sc_aresetn] [get_bd_pins m09_r_node/s_sc_aresetn] [get_bd_pins m09_w_node/m_sc_aresetn]
  connect_bd_net -net s_axi_aclk_1 [get_bd_pins s_axi_aclk] [get_bd_pins m09_ar_node/s_sc_aclk] [get_bd_pins m09_aw_node/s_sc_aclk] [get_bd_pins m09_b_node/m_sc_aclk] [get_bd_pins m09_r_node/m_sc_aclk] [get_bd_pins m09_w_node/s_sc_aclk]
  connect_bd_net -net s_axi_aresetn_1 [get_bd_pins s_axi_aresetn] [get_bd_pins m09_ar_node/s_sc_aresetn] [get_bd_pins m09_aw_node/s_sc_aresetn] [get_bd_pins m09_b_node/m_sc_aresetn] [get_bd_pins m09_r_node/m_sc_aresetn] [get_bd_pins m09_w_node/s_sc_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m09_exit_pipeline
proc create_hier_cell_m09_exit_pipeline { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m09_exit_pipeline() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 m_axi

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: m09_exit, and set properties
  set m09_exit [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_exit:1.0 m09_exit ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {16} \
   CONFIG.HAS_BURST {0} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.M_ID_WIDTH {0} \
   CONFIG.M_MAX_BURST_LENGTH {1} \
   CONFIG.M_PROTOCOL {AXI4LITE} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RDATA_WIDTH {32} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SSC000_ROUTE {0b1} \
   CONFIG.SSC001_ROUTE {0b0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
   CONFIG.S_ID_WIDTH {3} \
   CONFIG.WDATA_WIDTH {32} \
 ] $m09_exit

  # Create interface connections
  connect_bd_intf_net -intf_net m09_exit_M_AXI [get_bd_intf_pins m_axi] [get_bd_intf_pins m09_exit/M_AXI]
  connect_bd_intf_net -intf_net s_axi_1 [get_bd_intf_pins s_axi] [get_bd_intf_pins m09_exit/S_AXI]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins m09_exit/aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins m09_exit/aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m08_nodes
proc create_hier_cell_m08_nodes { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m08_nodes() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_W


  # Create pins
  create_bd_pin -dir I -type clk m_axi_aclk
  create_bd_pin -dir I -type rst m_axi_aresetn
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type rst s_axi_aresetn

  # Create instance: m08_ar_node, and set properties
  set m08_ar_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m08_ar_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {2} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m08_ar_node

  # Create instance: m08_aw_node, and set properties
  set m08_aw_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m08_aw_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {3} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m08_aw_node

  # Create instance: m08_b_node, and set properties
  set m08_b_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m08_b_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {4} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_WIDTH {0} \
 ] $m08_b_node

  # Create instance: m08_r_node, and set properties
  set m08_r_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m08_r_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {0} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m08_r_node

  # Create instance: m08_w_node, and set properties
  set m08_w_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m08_w_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m08_w_node

  # Create interface connections
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins S_SC_AR] [get_bd_intf_pins m08_ar_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins S_SC_AW] [get_bd_intf_pins m08_aw_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins S_SC_B] [get_bd_intf_pins m08_b_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins S_SC_R] [get_bd_intf_pins m08_r_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins S_SC_W] [get_bd_intf_pins m08_w_node/S_SC]
  connect_bd_intf_net -intf_net m08_ar_node_M_SC [get_bd_intf_pins M_SC_AR] [get_bd_intf_pins m08_ar_node/M_SC]
  connect_bd_intf_net -intf_net m08_aw_node_M_SC [get_bd_intf_pins M_SC_AW] [get_bd_intf_pins m08_aw_node/M_SC]
  connect_bd_intf_net -intf_net m08_b_node_M_SC [get_bd_intf_pins M_SC_B] [get_bd_intf_pins m08_b_node/M_SC]
  connect_bd_intf_net -intf_net m08_r_node_M_SC [get_bd_intf_pins M_SC_R] [get_bd_intf_pins m08_r_node/M_SC]
  connect_bd_intf_net -intf_net m08_w_node_M_SC [get_bd_intf_pins M_SC_W] [get_bd_intf_pins m08_w_node/M_SC]

  # Create port connections
  connect_bd_net -net m_axi_aclk_1 [get_bd_pins m_axi_aclk] [get_bd_pins m08_ar_node/m_sc_aclk] [get_bd_pins m08_aw_node/m_sc_aclk] [get_bd_pins m08_b_node/s_sc_aclk] [get_bd_pins m08_r_node/s_sc_aclk] [get_bd_pins m08_w_node/m_sc_aclk]
  connect_bd_net -net m_axi_aresetn_1 [get_bd_pins m_axi_aresetn] [get_bd_pins m08_ar_node/m_sc_aresetn] [get_bd_pins m08_aw_node/m_sc_aresetn] [get_bd_pins m08_b_node/s_sc_aresetn] [get_bd_pins m08_r_node/s_sc_aresetn] [get_bd_pins m08_w_node/m_sc_aresetn]
  connect_bd_net -net s_axi_aclk_1 [get_bd_pins s_axi_aclk] [get_bd_pins m08_ar_node/s_sc_aclk] [get_bd_pins m08_aw_node/s_sc_aclk] [get_bd_pins m08_b_node/m_sc_aclk] [get_bd_pins m08_r_node/m_sc_aclk] [get_bd_pins m08_w_node/s_sc_aclk]
  connect_bd_net -net s_axi_aresetn_1 [get_bd_pins s_axi_aresetn] [get_bd_pins m08_ar_node/s_sc_aresetn] [get_bd_pins m08_aw_node/s_sc_aresetn] [get_bd_pins m08_b_node/m_sc_aresetn] [get_bd_pins m08_r_node/m_sc_aresetn] [get_bd_pins m08_w_node/s_sc_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m08_exit_pipeline
proc create_hier_cell_m08_exit_pipeline { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m08_exit_pipeline() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 m_axi

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: m08_exit, and set properties
  set m08_exit [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_exit:1.0 m08_exit ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {16} \
   CONFIG.HAS_BURST {0} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.M_ID_WIDTH {0} \
   CONFIG.M_MAX_BURST_LENGTH {1} \
   CONFIG.M_PROTOCOL {AXI4LITE} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RDATA_WIDTH {32} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SSC000_ROUTE {0b1} \
   CONFIG.SSC001_ROUTE {0b0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
   CONFIG.S_ID_WIDTH {3} \
   CONFIG.WDATA_WIDTH {32} \
 ] $m08_exit

  # Create interface connections
  connect_bd_intf_net -intf_net m08_exit_M_AXI [get_bd_intf_pins m_axi] [get_bd_intf_pins m08_exit/M_AXI]
  connect_bd_intf_net -intf_net s_axi_1 [get_bd_intf_pins s_axi] [get_bd_intf_pins m08_exit/S_AXI]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins m08_exit/aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins m08_exit/aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m07_nodes
proc create_hier_cell_m07_nodes { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m07_nodes() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_W


  # Create pins
  create_bd_pin -dir I -type clk m_axi_aclk
  create_bd_pin -dir I -type rst m_axi_aresetn
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type rst s_axi_aresetn

  # Create instance: m07_ar_node, and set properties
  set m07_ar_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m07_ar_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {2} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m07_ar_node

  # Create instance: m07_aw_node, and set properties
  set m07_aw_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m07_aw_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {3} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m07_aw_node

  # Create instance: m07_b_node, and set properties
  set m07_b_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m07_b_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {4} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_WIDTH {0} \
 ] $m07_b_node

  # Create instance: m07_r_node, and set properties
  set m07_r_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m07_r_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {0} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m07_r_node

  # Create instance: m07_w_node, and set properties
  set m07_w_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m07_w_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m07_w_node

  # Create interface connections
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins S_SC_AR] [get_bd_intf_pins m07_ar_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins S_SC_AW] [get_bd_intf_pins m07_aw_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins S_SC_B] [get_bd_intf_pins m07_b_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins S_SC_R] [get_bd_intf_pins m07_r_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins S_SC_W] [get_bd_intf_pins m07_w_node/S_SC]
  connect_bd_intf_net -intf_net m07_ar_node_M_SC [get_bd_intf_pins M_SC_AR] [get_bd_intf_pins m07_ar_node/M_SC]
  connect_bd_intf_net -intf_net m07_aw_node_M_SC [get_bd_intf_pins M_SC_AW] [get_bd_intf_pins m07_aw_node/M_SC]
  connect_bd_intf_net -intf_net m07_b_node_M_SC [get_bd_intf_pins M_SC_B] [get_bd_intf_pins m07_b_node/M_SC]
  connect_bd_intf_net -intf_net m07_r_node_M_SC [get_bd_intf_pins M_SC_R] [get_bd_intf_pins m07_r_node/M_SC]
  connect_bd_intf_net -intf_net m07_w_node_M_SC [get_bd_intf_pins M_SC_W] [get_bd_intf_pins m07_w_node/M_SC]

  # Create port connections
  connect_bd_net -net m_axi_aclk_1 [get_bd_pins m_axi_aclk] [get_bd_pins m07_ar_node/m_sc_aclk] [get_bd_pins m07_aw_node/m_sc_aclk] [get_bd_pins m07_b_node/s_sc_aclk] [get_bd_pins m07_r_node/s_sc_aclk] [get_bd_pins m07_w_node/m_sc_aclk]
  connect_bd_net -net m_axi_aresetn_1 [get_bd_pins m_axi_aresetn] [get_bd_pins m07_ar_node/m_sc_aresetn] [get_bd_pins m07_aw_node/m_sc_aresetn] [get_bd_pins m07_b_node/s_sc_aresetn] [get_bd_pins m07_r_node/s_sc_aresetn] [get_bd_pins m07_w_node/m_sc_aresetn]
  connect_bd_net -net s_axi_aclk_1 [get_bd_pins s_axi_aclk] [get_bd_pins m07_ar_node/s_sc_aclk] [get_bd_pins m07_aw_node/s_sc_aclk] [get_bd_pins m07_b_node/m_sc_aclk] [get_bd_pins m07_r_node/m_sc_aclk] [get_bd_pins m07_w_node/s_sc_aclk]
  connect_bd_net -net s_axi_aresetn_1 [get_bd_pins s_axi_aresetn] [get_bd_pins m07_ar_node/s_sc_aresetn] [get_bd_pins m07_aw_node/s_sc_aresetn] [get_bd_pins m07_b_node/m_sc_aresetn] [get_bd_pins m07_r_node/m_sc_aresetn] [get_bd_pins m07_w_node/s_sc_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m07_exit_pipeline
proc create_hier_cell_m07_exit_pipeline { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m07_exit_pipeline() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 m_axi

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: m07_exit, and set properties
  set m07_exit [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_exit:1.0 m07_exit ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {16} \
   CONFIG.HAS_BURST {1} \
   CONFIG.HAS_LOCK {0} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MAX_RUSER_BITS_PER_BYTE {0} \
   CONFIG.MAX_WUSER_BITS_PER_BYTE {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.M_ARUSER_WIDTH {16} \
   CONFIG.M_AWUSER_WIDTH {16} \
   CONFIG.M_BUSER_WIDTH {0} \
   CONFIG.M_ID_WIDTH {0} \
   CONFIG.M_MAX_BURST_LENGTH {256} \
   CONFIG.M_PROTOCOL {AXI4} \
   CONFIG.M_RUSER_BITS_PER_BYTE {0} \
   CONFIG.M_RUSER_WIDTH {0} \
   CONFIG.M_WUSER_BITS_PER_BYTE {0} \
   CONFIG.M_WUSER_WIDTH {0} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RDATA_WIDTH {32} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SSC000_ROUTE {0b1} \
   CONFIG.SSC001_ROUTE {0b0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
   CONFIG.S_ID_WIDTH {3} \
   CONFIG.WDATA_WIDTH {32} \
 ] $m07_exit

  # Create interface connections
  connect_bd_intf_net -intf_net m07_exit_M_AXI [get_bd_intf_pins m_axi] [get_bd_intf_pins m07_exit/M_AXI]
  connect_bd_intf_net -intf_net s_axi_1 [get_bd_intf_pins s_axi] [get_bd_intf_pins m07_exit/S_AXI]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins m07_exit/aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins m07_exit/aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m06_nodes
proc create_hier_cell_m06_nodes { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m06_nodes() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_W


  # Create pins
  create_bd_pin -dir I -type clk m_axi_aclk
  create_bd_pin -dir I -type rst m_axi_aresetn
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type rst s_axi_aresetn

  # Create instance: m06_ar_node, and set properties
  set m06_ar_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m06_ar_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {2} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m06_ar_node

  # Create instance: m06_aw_node, and set properties
  set m06_aw_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m06_aw_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {3} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m06_aw_node

  # Create instance: m06_b_node, and set properties
  set m06_b_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m06_b_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {4} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_WIDTH {0} \
 ] $m06_b_node

  # Create instance: m06_r_node, and set properties
  set m06_r_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m06_r_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {0} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m06_r_node

  # Create instance: m06_w_node, and set properties
  set m06_w_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m06_w_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m06_w_node

  # Create interface connections
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins S_SC_AR] [get_bd_intf_pins m06_ar_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins S_SC_AW] [get_bd_intf_pins m06_aw_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins S_SC_B] [get_bd_intf_pins m06_b_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins S_SC_R] [get_bd_intf_pins m06_r_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins S_SC_W] [get_bd_intf_pins m06_w_node/S_SC]
  connect_bd_intf_net -intf_net m06_ar_node_M_SC [get_bd_intf_pins M_SC_AR] [get_bd_intf_pins m06_ar_node/M_SC]
  connect_bd_intf_net -intf_net m06_aw_node_M_SC [get_bd_intf_pins M_SC_AW] [get_bd_intf_pins m06_aw_node/M_SC]
  connect_bd_intf_net -intf_net m06_b_node_M_SC [get_bd_intf_pins M_SC_B] [get_bd_intf_pins m06_b_node/M_SC]
  connect_bd_intf_net -intf_net m06_r_node_M_SC [get_bd_intf_pins M_SC_R] [get_bd_intf_pins m06_r_node/M_SC]
  connect_bd_intf_net -intf_net m06_w_node_M_SC [get_bd_intf_pins M_SC_W] [get_bd_intf_pins m06_w_node/M_SC]

  # Create port connections
  connect_bd_net -net m_axi_aclk_1 [get_bd_pins m_axi_aclk] [get_bd_pins m06_ar_node/m_sc_aclk] [get_bd_pins m06_aw_node/m_sc_aclk] [get_bd_pins m06_b_node/s_sc_aclk] [get_bd_pins m06_r_node/s_sc_aclk] [get_bd_pins m06_w_node/m_sc_aclk]
  connect_bd_net -net m_axi_aresetn_1 [get_bd_pins m_axi_aresetn] [get_bd_pins m06_ar_node/m_sc_aresetn] [get_bd_pins m06_aw_node/m_sc_aresetn] [get_bd_pins m06_b_node/s_sc_aresetn] [get_bd_pins m06_r_node/s_sc_aresetn] [get_bd_pins m06_w_node/m_sc_aresetn]
  connect_bd_net -net s_axi_aclk_1 [get_bd_pins s_axi_aclk] [get_bd_pins m06_ar_node/s_sc_aclk] [get_bd_pins m06_aw_node/s_sc_aclk] [get_bd_pins m06_b_node/m_sc_aclk] [get_bd_pins m06_r_node/m_sc_aclk] [get_bd_pins m06_w_node/s_sc_aclk]
  connect_bd_net -net s_axi_aresetn_1 [get_bd_pins s_axi_aresetn] [get_bd_pins m06_ar_node/s_sc_aresetn] [get_bd_pins m06_aw_node/s_sc_aresetn] [get_bd_pins m06_b_node/m_sc_aresetn] [get_bd_pins m06_r_node/m_sc_aresetn] [get_bd_pins m06_w_node/s_sc_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m06_exit_pipeline
proc create_hier_cell_m06_exit_pipeline { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m06_exit_pipeline() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 m_axi

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: m06_exit, and set properties
  set m06_exit [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_exit:1.0 m06_exit ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {9} \
   CONFIG.HAS_BURST {0} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.M_ID_WIDTH {0} \
   CONFIG.M_MAX_BURST_LENGTH {1} \
   CONFIG.M_PROTOCOL {AXI4LITE} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RDATA_WIDTH {32} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SSC000_ROUTE {0b1} \
   CONFIG.SSC001_ROUTE {0b0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
   CONFIG.S_ID_WIDTH {3} \
   CONFIG.WDATA_WIDTH {32} \
 ] $m06_exit

  # Create interface connections
  connect_bd_intf_net -intf_net m06_exit_M_AXI [get_bd_intf_pins m_axi] [get_bd_intf_pins m06_exit/M_AXI]
  connect_bd_intf_net -intf_net s_axi_1 [get_bd_intf_pins s_axi] [get_bd_intf_pins m06_exit/S_AXI]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins m06_exit/aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins m06_exit/aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m05_nodes
proc create_hier_cell_m05_nodes { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m05_nodes() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_W


  # Create pins
  create_bd_pin -dir I -type clk m_axi_aclk
  create_bd_pin -dir I -type rst m_axi_aresetn
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type rst s_axi_aresetn

  # Create instance: m05_ar_node, and set properties
  set m05_ar_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m05_ar_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {2} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m05_ar_node

  # Create instance: m05_aw_node, and set properties
  set m05_aw_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m05_aw_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {3} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m05_aw_node

  # Create instance: m05_b_node, and set properties
  set m05_b_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m05_b_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {4} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_WIDTH {0} \
 ] $m05_b_node

  # Create instance: m05_r_node, and set properties
  set m05_r_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m05_r_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {0} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m05_r_node

  # Create instance: m05_w_node, and set properties
  set m05_w_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m05_w_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m05_w_node

  # Create interface connections
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins S_SC_AR] [get_bd_intf_pins m05_ar_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins S_SC_AW] [get_bd_intf_pins m05_aw_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins S_SC_B] [get_bd_intf_pins m05_b_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins S_SC_R] [get_bd_intf_pins m05_r_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins S_SC_W] [get_bd_intf_pins m05_w_node/S_SC]
  connect_bd_intf_net -intf_net m05_ar_node_M_SC [get_bd_intf_pins M_SC_AR] [get_bd_intf_pins m05_ar_node/M_SC]
  connect_bd_intf_net -intf_net m05_aw_node_M_SC [get_bd_intf_pins M_SC_AW] [get_bd_intf_pins m05_aw_node/M_SC]
  connect_bd_intf_net -intf_net m05_b_node_M_SC [get_bd_intf_pins M_SC_B] [get_bd_intf_pins m05_b_node/M_SC]
  connect_bd_intf_net -intf_net m05_r_node_M_SC [get_bd_intf_pins M_SC_R] [get_bd_intf_pins m05_r_node/M_SC]
  connect_bd_intf_net -intf_net m05_w_node_M_SC [get_bd_intf_pins M_SC_W] [get_bd_intf_pins m05_w_node/M_SC]

  # Create port connections
  connect_bd_net -net m_axi_aclk_1 [get_bd_pins m_axi_aclk] [get_bd_pins m05_ar_node/m_sc_aclk] [get_bd_pins m05_aw_node/m_sc_aclk] [get_bd_pins m05_b_node/s_sc_aclk] [get_bd_pins m05_r_node/s_sc_aclk] [get_bd_pins m05_w_node/m_sc_aclk]
  connect_bd_net -net m_axi_aresetn_1 [get_bd_pins m_axi_aresetn] [get_bd_pins m05_ar_node/m_sc_aresetn] [get_bd_pins m05_aw_node/m_sc_aresetn] [get_bd_pins m05_b_node/s_sc_aresetn] [get_bd_pins m05_r_node/s_sc_aresetn] [get_bd_pins m05_w_node/m_sc_aresetn]
  connect_bd_net -net s_axi_aclk_1 [get_bd_pins s_axi_aclk] [get_bd_pins m05_ar_node/s_sc_aclk] [get_bd_pins m05_aw_node/s_sc_aclk] [get_bd_pins m05_b_node/m_sc_aclk] [get_bd_pins m05_r_node/m_sc_aclk] [get_bd_pins m05_w_node/s_sc_aclk]
  connect_bd_net -net s_axi_aresetn_1 [get_bd_pins s_axi_aresetn] [get_bd_pins m05_ar_node/s_sc_aresetn] [get_bd_pins m05_aw_node/s_sc_aresetn] [get_bd_pins m05_b_node/m_sc_aresetn] [get_bd_pins m05_r_node/m_sc_aresetn] [get_bd_pins m05_w_node/s_sc_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m05_exit_pipeline
proc create_hier_cell_m05_exit_pipeline { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m05_exit_pipeline() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 m_axi

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: m05_exit, and set properties
  set m05_exit [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_exit:1.0 m05_exit ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {5} \
   CONFIG.HAS_BURST {0} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.M_ID_WIDTH {0} \
   CONFIG.M_MAX_BURST_LENGTH {1} \
   CONFIG.M_PROTOCOL {AXI4LITE} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RDATA_WIDTH {32} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SSC000_ROUTE {0b1} \
   CONFIG.SSC001_ROUTE {0b0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
   CONFIG.S_ID_WIDTH {3} \
   CONFIG.WDATA_WIDTH {32} \
 ] $m05_exit

  # Create interface connections
  connect_bd_intf_net -intf_net m05_exit_M_AXI [get_bd_intf_pins m_axi] [get_bd_intf_pins m05_exit/M_AXI]
  connect_bd_intf_net -intf_net s_axi_1 [get_bd_intf_pins s_axi] [get_bd_intf_pins m05_exit/S_AXI]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins m05_exit/aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins m05_exit/aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m04_nodes
proc create_hier_cell_m04_nodes { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m04_nodes() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_W


  # Create pins
  create_bd_pin -dir I -type clk m_axi_aclk
  create_bd_pin -dir I -type rst m_axi_aresetn
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type rst s_axi_aresetn

  # Create instance: m04_ar_node, and set properties
  set m04_ar_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m04_ar_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {2} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m04_ar_node

  # Create instance: m04_aw_node, and set properties
  set m04_aw_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m04_aw_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {3} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m04_aw_node

  # Create instance: m04_b_node, and set properties
  set m04_b_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m04_b_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {4} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_WIDTH {0} \
 ] $m04_b_node

  # Create instance: m04_r_node, and set properties
  set m04_r_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m04_r_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {0} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m04_r_node

  # Create instance: m04_w_node, and set properties
  set m04_w_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m04_w_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m04_w_node

  # Create interface connections
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins S_SC_AR] [get_bd_intf_pins m04_ar_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins S_SC_AW] [get_bd_intf_pins m04_aw_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins S_SC_B] [get_bd_intf_pins m04_b_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins S_SC_R] [get_bd_intf_pins m04_r_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins S_SC_W] [get_bd_intf_pins m04_w_node/S_SC]
  connect_bd_intf_net -intf_net m04_ar_node_M_SC [get_bd_intf_pins M_SC_AR] [get_bd_intf_pins m04_ar_node/M_SC]
  connect_bd_intf_net -intf_net m04_aw_node_M_SC [get_bd_intf_pins M_SC_AW] [get_bd_intf_pins m04_aw_node/M_SC]
  connect_bd_intf_net -intf_net m04_b_node_M_SC [get_bd_intf_pins M_SC_B] [get_bd_intf_pins m04_b_node/M_SC]
  connect_bd_intf_net -intf_net m04_r_node_M_SC [get_bd_intf_pins M_SC_R] [get_bd_intf_pins m04_r_node/M_SC]
  connect_bd_intf_net -intf_net m04_w_node_M_SC [get_bd_intf_pins M_SC_W] [get_bd_intf_pins m04_w_node/M_SC]

  # Create port connections
  connect_bd_net -net m_axi_aclk_1 [get_bd_pins m_axi_aclk] [get_bd_pins m04_ar_node/m_sc_aclk] [get_bd_pins m04_aw_node/m_sc_aclk] [get_bd_pins m04_b_node/s_sc_aclk] [get_bd_pins m04_r_node/s_sc_aclk] [get_bd_pins m04_w_node/m_sc_aclk]
  connect_bd_net -net m_axi_aresetn_1 [get_bd_pins m_axi_aresetn] [get_bd_pins m04_ar_node/m_sc_aresetn] [get_bd_pins m04_aw_node/m_sc_aresetn] [get_bd_pins m04_b_node/s_sc_aresetn] [get_bd_pins m04_r_node/s_sc_aresetn] [get_bd_pins m04_w_node/m_sc_aresetn]
  connect_bd_net -net s_axi_aclk_1 [get_bd_pins s_axi_aclk] [get_bd_pins m04_ar_node/s_sc_aclk] [get_bd_pins m04_aw_node/s_sc_aclk] [get_bd_pins m04_b_node/m_sc_aclk] [get_bd_pins m04_r_node/m_sc_aclk] [get_bd_pins m04_w_node/s_sc_aclk]
  connect_bd_net -net s_axi_aresetn_1 [get_bd_pins s_axi_aresetn] [get_bd_pins m04_ar_node/s_sc_aresetn] [get_bd_pins m04_aw_node/s_sc_aresetn] [get_bd_pins m04_b_node/m_sc_aresetn] [get_bd_pins m04_r_node/m_sc_aresetn] [get_bd_pins m04_w_node/s_sc_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m04_exit_pipeline
proc create_hier_cell_m04_exit_pipeline { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m04_exit_pipeline() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 m_axi

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: m04_exit, and set properties
  set m04_exit [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_exit:1.0 m04_exit ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {16} \
   CONFIG.HAS_BURST {0} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.M_ID_WIDTH {0} \
   CONFIG.M_MAX_BURST_LENGTH {1} \
   CONFIG.M_PROTOCOL {AXI4LITE} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RDATA_WIDTH {32} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SSC000_ROUTE {0b1} \
   CONFIG.SSC001_ROUTE {0b0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
   CONFIG.S_ID_WIDTH {3} \
   CONFIG.WDATA_WIDTH {32} \
 ] $m04_exit

  # Create interface connections
  connect_bd_intf_net -intf_net m04_exit_M_AXI [get_bd_intf_pins m_axi] [get_bd_intf_pins m04_exit/M_AXI]
  connect_bd_intf_net -intf_net s_axi_1 [get_bd_intf_pins s_axi] [get_bd_intf_pins m04_exit/S_AXI]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins m04_exit/aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins m04_exit/aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m03_nodes
proc create_hier_cell_m03_nodes { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m03_nodes() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_W


  # Create pins
  create_bd_pin -dir I -type clk m_axi_aclk
  create_bd_pin -dir I -type rst m_axi_aresetn
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type rst s_axi_aresetn

  # Create instance: m03_ar_node, and set properties
  set m03_ar_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m03_ar_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {2} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m03_ar_node

  # Create instance: m03_aw_node, and set properties
  set m03_aw_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m03_aw_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {3} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m03_aw_node

  # Create instance: m03_b_node, and set properties
  set m03_b_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m03_b_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {4} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_WIDTH {0} \
 ] $m03_b_node

  # Create instance: m03_r_node, and set properties
  set m03_r_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m03_r_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {0} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m03_r_node

  # Create instance: m03_w_node, and set properties
  set m03_w_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m03_w_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m03_w_node

  # Create interface connections
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins S_SC_AR] [get_bd_intf_pins m03_ar_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins S_SC_AW] [get_bd_intf_pins m03_aw_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins S_SC_B] [get_bd_intf_pins m03_b_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins S_SC_R] [get_bd_intf_pins m03_r_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins S_SC_W] [get_bd_intf_pins m03_w_node/S_SC]
  connect_bd_intf_net -intf_net m03_ar_node_M_SC [get_bd_intf_pins M_SC_AR] [get_bd_intf_pins m03_ar_node/M_SC]
  connect_bd_intf_net -intf_net m03_aw_node_M_SC [get_bd_intf_pins M_SC_AW] [get_bd_intf_pins m03_aw_node/M_SC]
  connect_bd_intf_net -intf_net m03_b_node_M_SC [get_bd_intf_pins M_SC_B] [get_bd_intf_pins m03_b_node/M_SC]
  connect_bd_intf_net -intf_net m03_r_node_M_SC [get_bd_intf_pins M_SC_R] [get_bd_intf_pins m03_r_node/M_SC]
  connect_bd_intf_net -intf_net m03_w_node_M_SC [get_bd_intf_pins M_SC_W] [get_bd_intf_pins m03_w_node/M_SC]

  # Create port connections
  connect_bd_net -net m_axi_aclk_1 [get_bd_pins m_axi_aclk] [get_bd_pins m03_ar_node/m_sc_aclk] [get_bd_pins m03_aw_node/m_sc_aclk] [get_bd_pins m03_b_node/s_sc_aclk] [get_bd_pins m03_r_node/s_sc_aclk] [get_bd_pins m03_w_node/m_sc_aclk]
  connect_bd_net -net m_axi_aresetn_1 [get_bd_pins m_axi_aresetn] [get_bd_pins m03_ar_node/m_sc_aresetn] [get_bd_pins m03_aw_node/m_sc_aresetn] [get_bd_pins m03_b_node/s_sc_aresetn] [get_bd_pins m03_r_node/s_sc_aresetn] [get_bd_pins m03_w_node/m_sc_aresetn]
  connect_bd_net -net s_axi_aclk_1 [get_bd_pins s_axi_aclk] [get_bd_pins m03_ar_node/s_sc_aclk] [get_bd_pins m03_aw_node/s_sc_aclk] [get_bd_pins m03_b_node/m_sc_aclk] [get_bd_pins m03_r_node/m_sc_aclk] [get_bd_pins m03_w_node/s_sc_aclk]
  connect_bd_net -net s_axi_aresetn_1 [get_bd_pins s_axi_aresetn] [get_bd_pins m03_ar_node/s_sc_aresetn] [get_bd_pins m03_aw_node/s_sc_aresetn] [get_bd_pins m03_b_node/m_sc_aresetn] [get_bd_pins m03_r_node/m_sc_aresetn] [get_bd_pins m03_w_node/s_sc_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m03_exit_pipeline
proc create_hier_cell_m03_exit_pipeline { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m03_exit_pipeline() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 m_axi

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: m03_exit, and set properties
  set m03_exit [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_exit:1.0 m03_exit ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {16} \
   CONFIG.HAS_BURST {0} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.M_ID_WIDTH {0} \
   CONFIG.M_MAX_BURST_LENGTH {1} \
   CONFIG.M_PROTOCOL {AXI4LITE} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RDATA_WIDTH {32} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SSC000_ROUTE {0b1} \
   CONFIG.SSC001_ROUTE {0b0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
   CONFIG.S_ID_WIDTH {3} \
   CONFIG.WDATA_WIDTH {32} \
 ] $m03_exit

  # Create interface connections
  connect_bd_intf_net -intf_net m03_exit_M_AXI [get_bd_intf_pins m_axi] [get_bd_intf_pins m03_exit/M_AXI]
  connect_bd_intf_net -intf_net s_axi_1 [get_bd_intf_pins s_axi] [get_bd_intf_pins m03_exit/S_AXI]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins m03_exit/aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins m03_exit/aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m02_nodes
proc create_hier_cell_m02_nodes { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m02_nodes() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_W


  # Create pins
  create_bd_pin -dir I -type clk m_axi_aclk
  create_bd_pin -dir I -type rst m_axi_aresetn
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type rst s_axi_aresetn

  # Create instance: m02_ar_node, and set properties
  set m02_ar_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m02_ar_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {2} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m02_ar_node

  # Create instance: m02_aw_node, and set properties
  set m02_aw_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m02_aw_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {3} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m02_aw_node

  # Create instance: m02_b_node, and set properties
  set m02_b_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m02_b_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {4} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_WIDTH {0} \
 ] $m02_b_node

  # Create instance: m02_r_node, and set properties
  set m02_r_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m02_r_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {0} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m02_r_node

  # Create instance: m02_w_node, and set properties
  set m02_w_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m02_w_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m02_w_node

  # Create interface connections
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins S_SC_AR] [get_bd_intf_pins m02_ar_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins S_SC_AW] [get_bd_intf_pins m02_aw_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins S_SC_B] [get_bd_intf_pins m02_b_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins S_SC_R] [get_bd_intf_pins m02_r_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins S_SC_W] [get_bd_intf_pins m02_w_node/S_SC]
  connect_bd_intf_net -intf_net m02_ar_node_M_SC [get_bd_intf_pins M_SC_AR] [get_bd_intf_pins m02_ar_node/M_SC]
  connect_bd_intf_net -intf_net m02_aw_node_M_SC [get_bd_intf_pins M_SC_AW] [get_bd_intf_pins m02_aw_node/M_SC]
  connect_bd_intf_net -intf_net m02_b_node_M_SC [get_bd_intf_pins M_SC_B] [get_bd_intf_pins m02_b_node/M_SC]
  connect_bd_intf_net -intf_net m02_r_node_M_SC [get_bd_intf_pins M_SC_R] [get_bd_intf_pins m02_r_node/M_SC]
  connect_bd_intf_net -intf_net m02_w_node_M_SC [get_bd_intf_pins M_SC_W] [get_bd_intf_pins m02_w_node/M_SC]

  # Create port connections
  connect_bd_net -net m_axi_aclk_1 [get_bd_pins m_axi_aclk] [get_bd_pins m02_ar_node/m_sc_aclk] [get_bd_pins m02_aw_node/m_sc_aclk] [get_bd_pins m02_b_node/s_sc_aclk] [get_bd_pins m02_r_node/s_sc_aclk] [get_bd_pins m02_w_node/m_sc_aclk]
  connect_bd_net -net m_axi_aresetn_1 [get_bd_pins m_axi_aresetn] [get_bd_pins m02_ar_node/m_sc_aresetn] [get_bd_pins m02_aw_node/m_sc_aresetn] [get_bd_pins m02_b_node/s_sc_aresetn] [get_bd_pins m02_r_node/s_sc_aresetn] [get_bd_pins m02_w_node/m_sc_aresetn]
  connect_bd_net -net s_axi_aclk_1 [get_bd_pins s_axi_aclk] [get_bd_pins m02_ar_node/s_sc_aclk] [get_bd_pins m02_aw_node/s_sc_aclk] [get_bd_pins m02_b_node/m_sc_aclk] [get_bd_pins m02_r_node/m_sc_aclk] [get_bd_pins m02_w_node/s_sc_aclk]
  connect_bd_net -net s_axi_aresetn_1 [get_bd_pins s_axi_aresetn] [get_bd_pins m02_ar_node/s_sc_aresetn] [get_bd_pins m02_aw_node/s_sc_aresetn] [get_bd_pins m02_b_node/m_sc_aresetn] [get_bd_pins m02_r_node/m_sc_aresetn] [get_bd_pins m02_w_node/s_sc_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m02_exit_pipeline
proc create_hier_cell_m02_exit_pipeline { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m02_exit_pipeline() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 m_axi

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: m02_exit, and set properties
  set m02_exit [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_exit:1.0 m02_exit ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {6} \
   CONFIG.HAS_BURST {0} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.M_ID_WIDTH {0} \
   CONFIG.M_MAX_BURST_LENGTH {1} \
   CONFIG.M_PROTOCOL {AXI4LITE} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RDATA_WIDTH {32} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SSC000_ROUTE {0b1} \
   CONFIG.SSC001_ROUTE {0b0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
   CONFIG.S_ID_WIDTH {3} \
   CONFIG.WDATA_WIDTH {32} \
 ] $m02_exit

  # Create interface connections
  connect_bd_intf_net -intf_net m02_exit_M_AXI [get_bd_intf_pins m_axi] [get_bd_intf_pins m02_exit/M_AXI]
  connect_bd_intf_net -intf_net s_axi_1 [get_bd_intf_pins s_axi] [get_bd_intf_pins m02_exit/S_AXI]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins m02_exit/aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins m02_exit/aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m01_nodes
proc create_hier_cell_m01_nodes { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m01_nodes() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_W


  # Create pins
  create_bd_pin -dir I -type clk m_axi_aclk
  create_bd_pin -dir I -type rst m_axi_aresetn
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type rst s_axi_aresetn

  # Create instance: m01_ar_node, and set properties
  set m01_ar_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m01_ar_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {2} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m01_ar_node

  # Create instance: m01_aw_node, and set properties
  set m01_aw_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m01_aw_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {3} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m01_aw_node

  # Create instance: m01_b_node, and set properties
  set m01_b_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m01_b_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {4} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_WIDTH {0} \
 ] $m01_b_node

  # Create instance: m01_r_node, and set properties
  set m01_r_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m01_r_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {0} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m01_r_node

  # Create instance: m01_w_node, and set properties
  set m01_w_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m01_w_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m01_w_node

  # Create interface connections
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins S_SC_AR] [get_bd_intf_pins m01_ar_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins S_SC_AW] [get_bd_intf_pins m01_aw_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins S_SC_B] [get_bd_intf_pins m01_b_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins S_SC_R] [get_bd_intf_pins m01_r_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins S_SC_W] [get_bd_intf_pins m01_w_node/S_SC]
  connect_bd_intf_net -intf_net m01_ar_node_M_SC [get_bd_intf_pins M_SC_AR] [get_bd_intf_pins m01_ar_node/M_SC]
  connect_bd_intf_net -intf_net m01_aw_node_M_SC [get_bd_intf_pins M_SC_AW] [get_bd_intf_pins m01_aw_node/M_SC]
  connect_bd_intf_net -intf_net m01_b_node_M_SC [get_bd_intf_pins M_SC_B] [get_bd_intf_pins m01_b_node/M_SC]
  connect_bd_intf_net -intf_net m01_r_node_M_SC [get_bd_intf_pins M_SC_R] [get_bd_intf_pins m01_r_node/M_SC]
  connect_bd_intf_net -intf_net m01_w_node_M_SC [get_bd_intf_pins M_SC_W] [get_bd_intf_pins m01_w_node/M_SC]

  # Create port connections
  connect_bd_net -net m_axi_aclk_1 [get_bd_pins m_axi_aclk] [get_bd_pins m01_ar_node/m_sc_aclk] [get_bd_pins m01_aw_node/m_sc_aclk] [get_bd_pins m01_b_node/s_sc_aclk] [get_bd_pins m01_r_node/s_sc_aclk] [get_bd_pins m01_w_node/m_sc_aclk]
  connect_bd_net -net m_axi_aresetn_1 [get_bd_pins m_axi_aresetn] [get_bd_pins m01_ar_node/m_sc_aresetn] [get_bd_pins m01_aw_node/m_sc_aresetn] [get_bd_pins m01_b_node/s_sc_aresetn] [get_bd_pins m01_r_node/s_sc_aresetn] [get_bd_pins m01_w_node/m_sc_aresetn]
  connect_bd_net -net s_axi_aclk_1 [get_bd_pins s_axi_aclk] [get_bd_pins m01_ar_node/s_sc_aclk] [get_bd_pins m01_aw_node/s_sc_aclk] [get_bd_pins m01_b_node/m_sc_aclk] [get_bd_pins m01_r_node/m_sc_aclk] [get_bd_pins m01_w_node/s_sc_aclk]
  connect_bd_net -net s_axi_aresetn_1 [get_bd_pins s_axi_aresetn] [get_bd_pins m01_ar_node/s_sc_aresetn] [get_bd_pins m01_aw_node/s_sc_aresetn] [get_bd_pins m01_b_node/m_sc_aresetn] [get_bd_pins m01_r_node/m_sc_aresetn] [get_bd_pins m01_w_node/s_sc_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m01_exit_pipeline
proc create_hier_cell_m01_exit_pipeline { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m01_exit_pipeline() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 m_axi

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: m01_exit, and set properties
  set m01_exit [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_exit:1.0 m01_exit ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {6} \
   CONFIG.HAS_BURST {0} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.M_ID_WIDTH {0} \
   CONFIG.M_MAX_BURST_LENGTH {1} \
   CONFIG.M_PROTOCOL {AXI4LITE} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RDATA_WIDTH {32} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SSC000_ROUTE {0b1} \
   CONFIG.SSC001_ROUTE {0b0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
   CONFIG.S_ID_WIDTH {3} \
   CONFIG.WDATA_WIDTH {32} \
 ] $m01_exit

  # Create interface connections
  connect_bd_intf_net -intf_net m01_exit_M_AXI [get_bd_intf_pins m_axi] [get_bd_intf_pins m01_exit/M_AXI]
  connect_bd_intf_net -intf_net s_axi_1 [get_bd_intf_pins s_axi] [get_bd_intf_pins m01_exit/S_AXI]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins m01_exit/aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins m01_exit/aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m00_nodes
proc create_hier_cell_m00_nodes { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m00_nodes() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AR

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_AW

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_B

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_R

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:sc_rtl:1.0 M_SC_W

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AR

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_AW

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_B

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_R

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:sc_rtl:1.0 S_SC_W


  # Create pins
  create_bd_pin -dir I -type clk m_axi_aclk
  create_bd_pin -dir I -type rst m_axi_aresetn
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type rst s_axi_aresetn

  # Create instance: m00_ar_node, and set properties
  set m00_ar_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m00_ar_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {2} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m00_ar_node

  # Create instance: m00_aw_node, and set properties
  set m00_aw_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m00_aw_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {3} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {179} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_WIDTH {16} \
 ] $m00_aw_node

  # Create instance: m00_b_node, and set properties
  set m00_b_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m00_b_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {4} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {7} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_WIDTH {0} \
 ] $m00_b_node

  # Create instance: m00_r_node, and set properties
  set m00_r_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m00_r_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {0} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {16} \
   CONFIG.M01_NUM_BYTES {16} \
   CONFIG.M02_NUM_BYTES {16} \
   CONFIG.M03_NUM_BYTES {16} \
   CONFIG.M04_NUM_BYTES {16} \
   CONFIG.M05_NUM_BYTES {16} \
   CONFIG.M06_NUM_BYTES {16} \
   CONFIG.M07_NUM_BYTES {16} \
   CONFIG.M08_NUM_BYTES {16} \
   CONFIG.M09_NUM_BYTES {16} \
   CONFIG.M10_NUM_BYTES {16} \
   CONFIG.M11_NUM_BYTES {16} \
   CONFIG.M12_NUM_BYTES {16} \
   CONFIG.M13_NUM_BYTES {16} \
   CONFIG.M14_NUM_BYTES {16} \
   CONFIG.M15_NUM_BYTES {16} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {149} \
   CONFIG.S00_NUM_BYTES {4} \
   CONFIG.S01_NUM_BYTES {4} \
   CONFIG.S02_NUM_BYTES {4} \
   CONFIG.S03_NUM_BYTES {4} \
   CONFIG.S04_NUM_BYTES {4} \
   CONFIG.S05_NUM_BYTES {4} \
   CONFIG.S06_NUM_BYTES {4} \
   CONFIG.S07_NUM_BYTES {4} \
   CONFIG.S08_NUM_BYTES {4} \
   CONFIG.S09_NUM_BYTES {4} \
   CONFIG.S10_NUM_BYTES {4} \
   CONFIG.S11_NUM_BYTES {4} \
   CONFIG.S12_NUM_BYTES {4} \
   CONFIG.S13_NUM_BYTES {4} \
   CONFIG.S14_NUM_BYTES {4} \
   CONFIG.S15_NUM_BYTES {4} \
   CONFIG.SC_ROUTE_WIDTH {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m00_r_node

  # Create instance: m00_w_node, and set properties
  set m00_w_node [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_node:1.0 m00_w_node ]
  set_property -dict [ list \
   CONFIG.ACLK_RELATIONSHIP {1} \
   CONFIG.ADDR_WIDTH {40} \
   CONFIG.CHANNEL {1} \
   CONFIG.ID_WIDTH {3} \
   CONFIG.M00_NUM_BYTES {4} \
   CONFIG.M01_NUM_BYTES {4} \
   CONFIG.M02_NUM_BYTES {4} \
   CONFIG.M03_NUM_BYTES {4} \
   CONFIG.M04_NUM_BYTES {4} \
   CONFIG.M05_NUM_BYTES {4} \
   CONFIG.M06_NUM_BYTES {4} \
   CONFIG.M07_NUM_BYTES {4} \
   CONFIG.M08_NUM_BYTES {4} \
   CONFIG.M09_NUM_BYTES {4} \
   CONFIG.M10_NUM_BYTES {4} \
   CONFIG.M11_NUM_BYTES {4} \
   CONFIG.M12_NUM_BYTES {4} \
   CONFIG.M13_NUM_BYTES {4} \
   CONFIG.M14_NUM_BYTES {4} \
   CONFIG.M15_NUM_BYTES {4} \
   CONFIG.MAX_PAYLD_BYTES {16} \
   CONFIG.M_SEND_PIPELINE {0} \
   CONFIG.NUM_MI {1} \
   CONFIG.NUM_OUTSTANDING {8} \
   CONFIG.NUM_SI {1} \
   CONFIG.PAYLD_WIDTH {174} \
   CONFIG.S00_NUM_BYTES {16} \
   CONFIG.S01_NUM_BYTES {16} \
   CONFIG.S02_NUM_BYTES {16} \
   CONFIG.S03_NUM_BYTES {16} \
   CONFIG.S04_NUM_BYTES {16} \
   CONFIG.S05_NUM_BYTES {16} \
   CONFIG.S06_NUM_BYTES {16} \
   CONFIG.S07_NUM_BYTES {16} \
   CONFIG.S08_NUM_BYTES {16} \
   CONFIG.S09_NUM_BYTES {16} \
   CONFIG.S10_NUM_BYTES {16} \
   CONFIG.S11_NUM_BYTES {16} \
   CONFIG.S12_NUM_BYTES {16} \
   CONFIG.S13_NUM_BYTES {16} \
   CONFIG.S14_NUM_BYTES {16} \
   CONFIG.S15_NUM_BYTES {16} \
   CONFIG.SC_ROUTE_WIDTH {15} \
   CONFIG.S_LATENCY {1} \
   CONFIG.USER_BITS_PER_BYTE {0} \
   CONFIG.USER_WIDTH {0} \
 ] $m00_w_node

  # Create interface connections
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins S_SC_AR] [get_bd_intf_pins m00_ar_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins S_SC_AW] [get_bd_intf_pins m00_aw_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins S_SC_B] [get_bd_intf_pins m00_b_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins S_SC_R] [get_bd_intf_pins m00_r_node/S_SC]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins S_SC_W] [get_bd_intf_pins m00_w_node/S_SC]
  connect_bd_intf_net -intf_net m00_ar_node_M_SC [get_bd_intf_pins M_SC_AR] [get_bd_intf_pins m00_ar_node/M_SC]
  connect_bd_intf_net -intf_net m00_aw_node_M_SC [get_bd_intf_pins M_SC_AW] [get_bd_intf_pins m00_aw_node/M_SC]
  connect_bd_intf_net -intf_net m00_b_node_M_SC [get_bd_intf_pins M_SC_B] [get_bd_intf_pins m00_b_node/M_SC]
  connect_bd_intf_net -intf_net m00_r_node_M_SC [get_bd_intf_pins M_SC_R] [get_bd_intf_pins m00_r_node/M_SC]
  connect_bd_intf_net -intf_net m00_w_node_M_SC [get_bd_intf_pins M_SC_W] [get_bd_intf_pins m00_w_node/M_SC]

  # Create port connections
  connect_bd_net -net m_axi_aclk_1 [get_bd_pins m_axi_aclk] [get_bd_pins m00_ar_node/m_sc_aclk] [get_bd_pins m00_aw_node/m_sc_aclk] [get_bd_pins m00_b_node/s_sc_aclk] [get_bd_pins m00_r_node/s_sc_aclk] [get_bd_pins m00_w_node/m_sc_aclk]
  connect_bd_net -net m_axi_aresetn_1 [get_bd_pins m_axi_aresetn] [get_bd_pins m00_ar_node/m_sc_aresetn] [get_bd_pins m00_aw_node/m_sc_aresetn] [get_bd_pins m00_b_node/s_sc_aresetn] [get_bd_pins m00_r_node/s_sc_aresetn] [get_bd_pins m00_w_node/m_sc_aresetn]
  connect_bd_net -net s_axi_aclk_1 [get_bd_pins s_axi_aclk] [get_bd_pins m00_ar_node/s_sc_aclk] [get_bd_pins m00_aw_node/s_sc_aclk] [get_bd_pins m00_b_node/m_sc_aclk] [get_bd_pins m00_r_node/m_sc_aclk] [get_bd_pins m00_w_node/s_sc_aclk]
  connect_bd_net -net s_axi_aresetn_1 [get_bd_pins s_axi_aresetn] [get_bd_pins m00_ar_node/s_sc_aresetn] [get_bd_pins m00_aw_node/s_sc_aresetn] [get_bd_pins m00_b_node/m_sc_aresetn] [get_bd_pins m00_r_node/m_sc_aresetn] [get_bd_pins m00_w_node/s_sc_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: m00_exit_pipeline
proc create_hier_cell_m00_exit_pipeline { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_m00_exit_pipeline() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 m_axi

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi


  # Create pins
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: m00_exit, and set properties
  set m00_exit [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_exit:1.0 m00_exit ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {6} \
   CONFIG.HAS_BURST {0} \
   CONFIG.IS_CASCADED {0} \
   CONFIG.MEP_IDENTIFIER_WIDTH {1} \
   CONFIG.M_ID_WIDTH {0} \
   CONFIG.M_MAX_BURST_LENGTH {1} \
   CONFIG.M_PROTOCOL {AXI4LITE} \
   CONFIG.NUM_MSC {15} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RDATA_WIDTH {32} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SSC000_ROUTE {0b1} \
   CONFIG.SSC001_ROUTE {0b0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
   CONFIG.S_ID_WIDTH {3} \
   CONFIG.WDATA_WIDTH {32} \
 ] $m00_exit

  # Create interface connections
  connect_bd_intf_net -intf_net m00_exit_M_AXI [get_bd_intf_pins m_axi] [get_bd_intf_pins m00_exit/M_AXI]
  connect_bd_intf_net -intf_net s_axi_1 [get_bd_intf_pins s_axi] [get_bd_intf_pins m00_exit/S_AXI]

  # Create port connections
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins m00_exit/aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins m00_exit/aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: clk_map
proc create_hier_cell_clk_map { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_clk_map() - Empty argument(s)!"}
     return
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

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins

  # Create pins
  create_bd_pin -dir O -type clk M00_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst M00_ARESETN
  create_bd_pin -dir O -type clk M01_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst M01_ARESETN
  create_bd_pin -dir O -type clk M02_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst M02_ARESETN
  create_bd_pin -dir O -type clk M03_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst M03_ARESETN
  create_bd_pin -dir O -type clk M04_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst M04_ARESETN
  create_bd_pin -dir O -type clk M05_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst M05_ARESETN
  create_bd_pin -dir O -type clk M06_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst M06_ARESETN
  create_bd_pin -dir O -type clk M07_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst M07_ARESETN
  create_bd_pin -dir O -type clk M08_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst M08_ARESETN
  create_bd_pin -dir O -type clk M09_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst M09_ARESETN
  create_bd_pin -dir O -type clk M10_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst M10_ARESETN
  create_bd_pin -dir O -type clk M11_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst M11_ARESETN
  create_bd_pin -dir O -type clk M12_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst M12_ARESETN
  create_bd_pin -dir O -type clk M13_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst M13_ARESETN
  create_bd_pin -dir O -type clk M14_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst M14_ARESETN
  create_bd_pin -dir O -type clk S00_ACLK
  create_bd_pin -dir O -from 0 -to 0 -type rst S00_ARESETN
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type clk aclk1
  create_bd_pin -dir I -type clk aclk2
  create_bd_pin -dir I -type rst aresetn
  create_bd_pin -dir O -type rst aresetn_out
  create_bd_pin -dir O -type clk swbd_aclk
  create_bd_pin -dir O -from 0 -to 0 -type rst swbd_aresetn

  # Create instance: one, and set properties
  set one [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 one ]

  # Create instance: psr0, and set properties
  set psr0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 psr0 ]
  set_property -dict [ list \
   CONFIG.C_AUX_RESET_HIGH {0} \
   CONFIG.C_AUX_RST_WIDTH {1} \
 ] $psr0

  # Create instance: psr_aclk, and set properties
  set psr_aclk [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 psr_aclk ]
  set_property -dict [ list \
   CONFIG.C_AUX_RESET_HIGH {0} \
   CONFIG.C_AUX_RST_WIDTH {1} \
 ] $psr_aclk

  # Create instance: psr_aclk2, and set properties
  set psr_aclk2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 psr_aclk2 ]
  set_property -dict [ list \
   CONFIG.C_AUX_RESET_HIGH {0} \
   CONFIG.C_AUX_RST_WIDTH {1} \
 ] $psr_aclk2

  # Create port connections
  connect_bd_net -net clk_map_aclk2_net [get_bd_pins M09_ACLK] [get_bd_pins aclk2] [get_bd_pins psr0/slowest_sync_clk] [get_bd_pins psr_aclk2/slowest_sync_clk]
  connect_bd_net -net clk_map_aclk_net [get_bd_pins M00_ACLK] [get_bd_pins M01_ACLK] [get_bd_pins M02_ACLK] [get_bd_pins M03_ACLK] [get_bd_pins M04_ACLK] [get_bd_pins M05_ACLK] [get_bd_pins M06_ACLK] [get_bd_pins M07_ACLK] [get_bd_pins M08_ACLK] [get_bd_pins M10_ACLK] [get_bd_pins M11_ACLK] [get_bd_pins M12_ACLK] [get_bd_pins M13_ACLK] [get_bd_pins M14_ACLK] [get_bd_pins S00_ACLK] [get_bd_pins aclk] [get_bd_pins swbd_aclk] [get_bd_pins psr_aclk/slowest_sync_clk]
  connect_bd_net -net clk_map_aresetn_net [get_bd_pins aresetn] [get_bd_pins psr0/aux_reset_in] [get_bd_pins psr_aclk/aux_reset_in] [get_bd_pins psr_aclk2/aux_reset_in]
  connect_bd_net -net one_dout [get_bd_pins one/dout] [get_bd_pins psr0/ext_reset_in]
  connect_bd_net -net psr0_interconnect_aresetn [get_bd_pins psr0/interconnect_aresetn] [get_bd_pins psr_aclk/ext_reset_in] [get_bd_pins psr_aclk2/ext_reset_in]
  connect_bd_net -net psr_aclk2_interconnect_aresetn [get_bd_pins M09_ARESETN] [get_bd_pins psr_aclk2/interconnect_aresetn]
  connect_bd_net -net psr_aclk_interconnect_aresetn [get_bd_pins M00_ARESETN] [get_bd_pins M01_ARESETN] [get_bd_pins M02_ARESETN] [get_bd_pins M03_ARESETN] [get_bd_pins M04_ARESETN] [get_bd_pins M05_ARESETN] [get_bd_pins M06_ARESETN] [get_bd_pins M07_ARESETN] [get_bd_pins M08_ARESETN] [get_bd_pins M10_ARESETN] [get_bd_pins M11_ARESETN] [get_bd_pins M12_ARESETN] [get_bd_pins M13_ARESETN] [get_bd_pins M14_ARESETN] [get_bd_pins S00_ARESETN] [get_bd_pins swbd_aresetn] [get_bd_pins psr_aclk/interconnect_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}


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
  set M00_AXI [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M00_AXI ]
  set_property -dict [ list \
   CONFIG.MAX_BURST_LENGTH {1} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.SUPPORTS_NARROW_BURST {0} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   ] $M00_AXI

  set M01_AXI [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M01_AXI ]
  set_property -dict [ list \
   CONFIG.MAX_BURST_LENGTH {1} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.SUPPORTS_NARROW_BURST {0} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   ] $M01_AXI

  set M02_AXI [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M02_AXI ]
  set_property -dict [ list \
   CONFIG.MAX_BURST_LENGTH {1} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.SUPPORTS_NARROW_BURST {0} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   ] $M02_AXI

  set M03_AXI [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M03_AXI ]
  set_property -dict [ list \
   CONFIG.MAX_BURST_LENGTH {1} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.SUPPORTS_NARROW_BURST {0} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   ] $M03_AXI

  set M04_AXI [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M04_AXI ]
  set_property -dict [ list \
   CONFIG.MAX_BURST_LENGTH {1} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.SUPPORTS_NARROW_BURST {0} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   ] $M04_AXI

  set M05_AXI [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M05_AXI ]
  set_property -dict [ list \
   CONFIG.MAX_BURST_LENGTH {1} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.SUPPORTS_NARROW_BURST {0} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   ] $M05_AXI

  set M06_AXI [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M06_AXI ]
  set_property -dict [ list \
   CONFIG.MAX_BURST_LENGTH {1} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.SUPPORTS_NARROW_BURST {0} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   ] $M06_AXI

  set M07_AXI [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M07_AXI ]
  set_property -dict [ list \
   CONFIG.MAX_BURST_LENGTH {256} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.SUPPORTS_NARROW_BURST {0} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   ] $M07_AXI

  set M08_AXI [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M08_AXI ]
  set_property -dict [ list \
   CONFIG.MAX_BURST_LENGTH {1} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.SUPPORTS_NARROW_BURST {0} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   ] $M08_AXI

  set M09_AXI [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M09_AXI ]
  set_property -dict [ list \
   CONFIG.MAX_BURST_LENGTH {1} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.SUPPORTS_NARROW_BURST {0} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   ] $M09_AXI

  set M10_AXI [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M10_AXI ]
  set_property -dict [ list \
   CONFIG.MAX_BURST_LENGTH {256} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.SUPPORTS_NARROW_BURST {0} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   ] $M10_AXI

  set M11_AXI [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M11_AXI ]
  set_property -dict [ list \
   CONFIG.MAX_BURST_LENGTH {1} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.SUPPORTS_NARROW_BURST {0} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   ] $M11_AXI

  set M12_AXI [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M12_AXI ]
  set_property -dict [ list \
   CONFIG.MAX_BURST_LENGTH {1} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.SUPPORTS_NARROW_BURST {0} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   ] $M12_AXI

  set M13_AXI [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M13_AXI ]
  set_property -dict [ list \
   CONFIG.MAX_BURST_LENGTH {1} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.SUPPORTS_NARROW_BURST {0} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   ] $M13_AXI

  set M14_AXI [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M14_AXI ]
  set_property -dict [ list \
   CONFIG.MAX_BURST_LENGTH {1} \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.SUPPORTS_NARROW_BURST {0} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   ] $M14_AXI

  set S00_AXI [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 S00_AXI ]
  set_property -dict [ list \
   CONFIG.NUM_READ_OUTSTANDING {8} \
   CONFIG.NUM_WRITE_OUTSTANDING {8} \
   ] $S00_AXI


  # Create ports
  set aclk [ create_bd_port -dir I -type clk aclk ]
  set_property -dict [ list \
   CONFIG.ASSOCIATED_BUSIF {M00_AXI:M01_AXI:M02_AXI:M03_AXI:M04_AXI:M05_AXI:M06_AXI:M07_AXI:M08_AXI:M10_AXI:M11_AXI:M12_AXI:M13_AXI:M14_AXI:S00_AXI} \
 ] $aclk
  set aclk1 [ create_bd_port -dir I -type clk aclk1 ]
  set_property -dict [ list \
   CONFIG.ASSOCIATED_BUSIF {} \
 ] $aclk1
  set aclk2 [ create_bd_port -dir I -type clk aclk2 ]
  set_property -dict [ list \
   CONFIG.ASSOCIATED_BUSIF {M09_AXI} \
 ] $aclk2
  set aresetn [ create_bd_port -dir I -type rst aresetn ]
  set_property -dict [ list \
   CONFIG.POLARITY {ACTIVE_LOW} \
 ] $aresetn

  # Create instance: clk_map
  create_hier_cell_clk_map [current_bd_instance .] clk_map

  # Create instance: m00_exit_pipeline
  create_hier_cell_m00_exit_pipeline [current_bd_instance .] m00_exit_pipeline

  # Create instance: m00_nodes
  create_hier_cell_m00_nodes [current_bd_instance .] m00_nodes

  # Create instance: m00_sc2axi, and set properties
  set m00_sc2axi [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_sc2axi:1.0 m00_sc2axi ]
  set_property -dict [ list \
   CONFIG.AXI_ADDR_WIDTH {6} \
   CONFIG.AXI_ID_WIDTH {3} \
   CONFIG.AXI_RDATA_WIDTH {32} \
   CONFIG.AXI_WDATA_WIDTH {32} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SC_ADDR_WIDTH {40} \
   CONFIG.SC_ARUSER_WIDTH {16} \
   CONFIG.SC_AWUSER_WIDTH {16} \
   CONFIG.SC_BUSER_WIDTH {0} \
   CONFIG.SC_ID_WIDTH {3} \
   CONFIG.SC_RDATA_WIDTH {128} \
   CONFIG.SC_RUSER_BITS_PER_BYTE {0} \
   CONFIG.SC_WDATA_WIDTH {128} \
   CONFIG.SC_WUSER_BITS_PER_BYTE {0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
 ] $m00_sc2axi

  # Create instance: m01_exit_pipeline
  create_hier_cell_m01_exit_pipeline [current_bd_instance .] m01_exit_pipeline

  # Create instance: m01_nodes
  create_hier_cell_m01_nodes [current_bd_instance .] m01_nodes

  # Create instance: m01_sc2axi, and set properties
  set m01_sc2axi [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_sc2axi:1.0 m01_sc2axi ]
  set_property -dict [ list \
   CONFIG.AXI_ADDR_WIDTH {6} \
   CONFIG.AXI_ID_WIDTH {3} \
   CONFIG.AXI_RDATA_WIDTH {32} \
   CONFIG.AXI_WDATA_WIDTH {32} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SC_ADDR_WIDTH {40} \
   CONFIG.SC_ARUSER_WIDTH {16} \
   CONFIG.SC_AWUSER_WIDTH {16} \
   CONFIG.SC_BUSER_WIDTH {0} \
   CONFIG.SC_ID_WIDTH {3} \
   CONFIG.SC_RDATA_WIDTH {128} \
   CONFIG.SC_RUSER_BITS_PER_BYTE {0} \
   CONFIG.SC_WDATA_WIDTH {128} \
   CONFIG.SC_WUSER_BITS_PER_BYTE {0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
 ] $m01_sc2axi

  # Create instance: m02_exit_pipeline
  create_hier_cell_m02_exit_pipeline [current_bd_instance .] m02_exit_pipeline

  # Create instance: m02_nodes
  create_hier_cell_m02_nodes [current_bd_instance .] m02_nodes

  # Create instance: m02_sc2axi, and set properties
  set m02_sc2axi [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_sc2axi:1.0 m02_sc2axi ]
  set_property -dict [ list \
   CONFIG.AXI_ADDR_WIDTH {6} \
   CONFIG.AXI_ID_WIDTH {3} \
   CONFIG.AXI_RDATA_WIDTH {32} \
   CONFIG.AXI_WDATA_WIDTH {32} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SC_ADDR_WIDTH {40} \
   CONFIG.SC_ARUSER_WIDTH {16} \
   CONFIG.SC_AWUSER_WIDTH {16} \
   CONFIG.SC_BUSER_WIDTH {0} \
   CONFIG.SC_ID_WIDTH {3} \
   CONFIG.SC_RDATA_WIDTH {128} \
   CONFIG.SC_RUSER_BITS_PER_BYTE {0} \
   CONFIG.SC_WDATA_WIDTH {128} \
   CONFIG.SC_WUSER_BITS_PER_BYTE {0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
 ] $m02_sc2axi

  # Create instance: m03_exit_pipeline
  create_hier_cell_m03_exit_pipeline [current_bd_instance .] m03_exit_pipeline

  # Create instance: m03_nodes
  create_hier_cell_m03_nodes [current_bd_instance .] m03_nodes

  # Create instance: m03_sc2axi, and set properties
  set m03_sc2axi [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_sc2axi:1.0 m03_sc2axi ]
  set_property -dict [ list \
   CONFIG.AXI_ADDR_WIDTH {16} \
   CONFIG.AXI_ID_WIDTH {3} \
   CONFIG.AXI_RDATA_WIDTH {32} \
   CONFIG.AXI_WDATA_WIDTH {32} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SC_ADDR_WIDTH {40} \
   CONFIG.SC_ARUSER_WIDTH {16} \
   CONFIG.SC_AWUSER_WIDTH {16} \
   CONFIG.SC_BUSER_WIDTH {0} \
   CONFIG.SC_ID_WIDTH {3} \
   CONFIG.SC_RDATA_WIDTH {128} \
   CONFIG.SC_RUSER_BITS_PER_BYTE {0} \
   CONFIG.SC_WDATA_WIDTH {128} \
   CONFIG.SC_WUSER_BITS_PER_BYTE {0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
 ] $m03_sc2axi

  # Create instance: m04_exit_pipeline
  create_hier_cell_m04_exit_pipeline [current_bd_instance .] m04_exit_pipeline

  # Create instance: m04_nodes
  create_hier_cell_m04_nodes [current_bd_instance .] m04_nodes

  # Create instance: m04_sc2axi, and set properties
  set m04_sc2axi [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_sc2axi:1.0 m04_sc2axi ]
  set_property -dict [ list \
   CONFIG.AXI_ADDR_WIDTH {16} \
   CONFIG.AXI_ID_WIDTH {3} \
   CONFIG.AXI_RDATA_WIDTH {32} \
   CONFIG.AXI_WDATA_WIDTH {32} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SC_ADDR_WIDTH {40} \
   CONFIG.SC_ARUSER_WIDTH {16} \
   CONFIG.SC_AWUSER_WIDTH {16} \
   CONFIG.SC_BUSER_WIDTH {0} \
   CONFIG.SC_ID_WIDTH {3} \
   CONFIG.SC_RDATA_WIDTH {128} \
   CONFIG.SC_RUSER_BITS_PER_BYTE {0} \
   CONFIG.SC_WDATA_WIDTH {128} \
   CONFIG.SC_WUSER_BITS_PER_BYTE {0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
 ] $m04_sc2axi

  # Create instance: m05_exit_pipeline
  create_hier_cell_m05_exit_pipeline [current_bd_instance .] m05_exit_pipeline

  # Create instance: m05_nodes
  create_hier_cell_m05_nodes [current_bd_instance .] m05_nodes

  # Create instance: m05_sc2axi, and set properties
  set m05_sc2axi [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_sc2axi:1.0 m05_sc2axi ]
  set_property -dict [ list \
   CONFIG.AXI_ADDR_WIDTH {5} \
   CONFIG.AXI_ID_WIDTH {3} \
   CONFIG.AXI_RDATA_WIDTH {32} \
   CONFIG.AXI_WDATA_WIDTH {32} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SC_ADDR_WIDTH {40} \
   CONFIG.SC_ARUSER_WIDTH {16} \
   CONFIG.SC_AWUSER_WIDTH {16} \
   CONFIG.SC_BUSER_WIDTH {0} \
   CONFIG.SC_ID_WIDTH {3} \
   CONFIG.SC_RDATA_WIDTH {128} \
   CONFIG.SC_RUSER_BITS_PER_BYTE {0} \
   CONFIG.SC_WDATA_WIDTH {128} \
   CONFIG.SC_WUSER_BITS_PER_BYTE {0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
 ] $m05_sc2axi

  # Create instance: m06_exit_pipeline
  create_hier_cell_m06_exit_pipeline [current_bd_instance .] m06_exit_pipeline

  # Create instance: m06_nodes
  create_hier_cell_m06_nodes [current_bd_instance .] m06_nodes

  # Create instance: m06_sc2axi, and set properties
  set m06_sc2axi [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_sc2axi:1.0 m06_sc2axi ]
  set_property -dict [ list \
   CONFIG.AXI_ADDR_WIDTH {9} \
   CONFIG.AXI_ID_WIDTH {3} \
   CONFIG.AXI_RDATA_WIDTH {32} \
   CONFIG.AXI_WDATA_WIDTH {32} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SC_ADDR_WIDTH {40} \
   CONFIG.SC_ARUSER_WIDTH {16} \
   CONFIG.SC_AWUSER_WIDTH {16} \
   CONFIG.SC_BUSER_WIDTH {0} \
   CONFIG.SC_ID_WIDTH {3} \
   CONFIG.SC_RDATA_WIDTH {128} \
   CONFIG.SC_RUSER_BITS_PER_BYTE {0} \
   CONFIG.SC_WDATA_WIDTH {128} \
   CONFIG.SC_WUSER_BITS_PER_BYTE {0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
 ] $m06_sc2axi

  # Create instance: m07_exit_pipeline
  create_hier_cell_m07_exit_pipeline [current_bd_instance .] m07_exit_pipeline

  # Create instance: m07_nodes
  create_hier_cell_m07_nodes [current_bd_instance .] m07_nodes

  # Create instance: m07_sc2axi, and set properties
  set m07_sc2axi [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_sc2axi:1.0 m07_sc2axi ]
  set_property -dict [ list \
   CONFIG.AXI_ADDR_WIDTH {16} \
   CONFIG.AXI_ID_WIDTH {3} \
   CONFIG.AXI_RDATA_WIDTH {32} \
   CONFIG.AXI_WDATA_WIDTH {32} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SC_ADDR_WIDTH {40} \
   CONFIG.SC_ARUSER_WIDTH {16} \
   CONFIG.SC_AWUSER_WIDTH {16} \
   CONFIG.SC_BUSER_WIDTH {0} \
   CONFIG.SC_ID_WIDTH {3} \
   CONFIG.SC_RDATA_WIDTH {128} \
   CONFIG.SC_RUSER_BITS_PER_BYTE {0} \
   CONFIG.SC_WDATA_WIDTH {128} \
   CONFIG.SC_WUSER_BITS_PER_BYTE {0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
 ] $m07_sc2axi

  # Create instance: m08_exit_pipeline
  create_hier_cell_m08_exit_pipeline [current_bd_instance .] m08_exit_pipeline

  # Create instance: m08_nodes
  create_hier_cell_m08_nodes [current_bd_instance .] m08_nodes

  # Create instance: m08_sc2axi, and set properties
  set m08_sc2axi [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_sc2axi:1.0 m08_sc2axi ]
  set_property -dict [ list \
   CONFIG.AXI_ADDR_WIDTH {16} \
   CONFIG.AXI_ID_WIDTH {3} \
   CONFIG.AXI_RDATA_WIDTH {32} \
   CONFIG.AXI_WDATA_WIDTH {32} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SC_ADDR_WIDTH {40} \
   CONFIG.SC_ARUSER_WIDTH {16} \
   CONFIG.SC_AWUSER_WIDTH {16} \
   CONFIG.SC_BUSER_WIDTH {0} \
   CONFIG.SC_ID_WIDTH {3} \
   CONFIG.SC_RDATA_WIDTH {128} \
   CONFIG.SC_RUSER_BITS_PER_BYTE {0} \
   CONFIG.SC_WDATA_WIDTH {128} \
   CONFIG.SC_WUSER_BITS_PER_BYTE {0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
 ] $m08_sc2axi

  # Create instance: m09_exit_pipeline
  create_hier_cell_m09_exit_pipeline [current_bd_instance .] m09_exit_pipeline

  # Create instance: m09_nodes
  create_hier_cell_m09_nodes [current_bd_instance .] m09_nodes

  # Create instance: m09_sc2axi, and set properties
  set m09_sc2axi [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_sc2axi:1.0 m09_sc2axi ]
  set_property -dict [ list \
   CONFIG.AXI_ADDR_WIDTH {16} \
   CONFIG.AXI_ID_WIDTH {3} \
   CONFIG.AXI_RDATA_WIDTH {32} \
   CONFIG.AXI_WDATA_WIDTH {32} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SC_ADDR_WIDTH {40} \
   CONFIG.SC_ARUSER_WIDTH {16} \
   CONFIG.SC_AWUSER_WIDTH {16} \
   CONFIG.SC_BUSER_WIDTH {0} \
   CONFIG.SC_ID_WIDTH {3} \
   CONFIG.SC_RDATA_WIDTH {128} \
   CONFIG.SC_RUSER_BITS_PER_BYTE {0} \
   CONFIG.SC_WDATA_WIDTH {128} \
   CONFIG.SC_WUSER_BITS_PER_BYTE {0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
 ] $m09_sc2axi

  # Create instance: m10_exit_pipeline
  create_hier_cell_m10_exit_pipeline [current_bd_instance .] m10_exit_pipeline

  # Create instance: m10_nodes
  create_hier_cell_m10_nodes [current_bd_instance .] m10_nodes

  # Create instance: m10_sc2axi, and set properties
  set m10_sc2axi [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_sc2axi:1.0 m10_sc2axi ]
  set_property -dict [ list \
   CONFIG.AXI_ADDR_WIDTH {40} \
   CONFIG.AXI_ID_WIDTH {3} \
   CONFIG.AXI_RDATA_WIDTH {128} \
   CONFIG.AXI_WDATA_WIDTH {128} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SC_ADDR_WIDTH {40} \
   CONFIG.SC_ARUSER_WIDTH {16} \
   CONFIG.SC_AWUSER_WIDTH {16} \
   CONFIG.SC_BUSER_WIDTH {0} \
   CONFIG.SC_ID_WIDTH {3} \
   CONFIG.SC_RDATA_WIDTH {128} \
   CONFIG.SC_RUSER_BITS_PER_BYTE {0} \
   CONFIG.SC_WDATA_WIDTH {128} \
   CONFIG.SC_WUSER_BITS_PER_BYTE {0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
 ] $m10_sc2axi

  # Create instance: m11_exit_pipeline
  create_hier_cell_m11_exit_pipeline [current_bd_instance .] m11_exit_pipeline

  # Create instance: m11_nodes
  create_hier_cell_m11_nodes [current_bd_instance .] m11_nodes

  # Create instance: m11_sc2axi, and set properties
  set m11_sc2axi [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_sc2axi:1.0 m11_sc2axi ]
  set_property -dict [ list \
   CONFIG.AXI_ADDR_WIDTH {5} \
   CONFIG.AXI_ID_WIDTH {3} \
   CONFIG.AXI_RDATA_WIDTH {32} \
   CONFIG.AXI_WDATA_WIDTH {32} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SC_ADDR_WIDTH {40} \
   CONFIG.SC_ARUSER_WIDTH {16} \
   CONFIG.SC_AWUSER_WIDTH {16} \
   CONFIG.SC_BUSER_WIDTH {0} \
   CONFIG.SC_ID_WIDTH {3} \
   CONFIG.SC_RDATA_WIDTH {128} \
   CONFIG.SC_RUSER_BITS_PER_BYTE {0} \
   CONFIG.SC_WDATA_WIDTH {128} \
   CONFIG.SC_WUSER_BITS_PER_BYTE {0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
 ] $m11_sc2axi

  # Create instance: m12_exit_pipeline
  create_hier_cell_m12_exit_pipeline [current_bd_instance .] m12_exit_pipeline

  # Create instance: m12_nodes
  create_hier_cell_m12_nodes [current_bd_instance .] m12_nodes

  # Create instance: m12_sc2axi, and set properties
  set m12_sc2axi [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_sc2axi:1.0 m12_sc2axi ]
  set_property -dict [ list \
   CONFIG.AXI_ADDR_WIDTH {16} \
   CONFIG.AXI_ID_WIDTH {3} \
   CONFIG.AXI_RDATA_WIDTH {32} \
   CONFIG.AXI_WDATA_WIDTH {32} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SC_ADDR_WIDTH {40} \
   CONFIG.SC_ARUSER_WIDTH {16} \
   CONFIG.SC_AWUSER_WIDTH {16} \
   CONFIG.SC_BUSER_WIDTH {0} \
   CONFIG.SC_ID_WIDTH {3} \
   CONFIG.SC_RDATA_WIDTH {128} \
   CONFIG.SC_RUSER_BITS_PER_BYTE {0} \
   CONFIG.SC_WDATA_WIDTH {128} \
   CONFIG.SC_WUSER_BITS_PER_BYTE {0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
 ] $m12_sc2axi

  # Create instance: m13_exit_pipeline
  create_hier_cell_m13_exit_pipeline [current_bd_instance .] m13_exit_pipeline

  # Create instance: m13_nodes
  create_hier_cell_m13_nodes [current_bd_instance .] m13_nodes

  # Create instance: m13_sc2axi, and set properties
  set m13_sc2axi [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_sc2axi:1.0 m13_sc2axi ]
  set_property -dict [ list \
   CONFIG.AXI_ADDR_WIDTH {16} \
   CONFIG.AXI_ID_WIDTH {3} \
   CONFIG.AXI_RDATA_WIDTH {32} \
   CONFIG.AXI_WDATA_WIDTH {32} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SC_ADDR_WIDTH {40} \
   CONFIG.SC_ARUSER_WIDTH {16} \
   CONFIG.SC_AWUSER_WIDTH {16} \
   CONFIG.SC_BUSER_WIDTH {0} \
   CONFIG.SC_ID_WIDTH {3} \
   CONFIG.SC_RDATA_WIDTH {128} \
   CONFIG.SC_RUSER_BITS_PER_BYTE {0} \
   CONFIG.SC_WDATA_WIDTH {128} \
   CONFIG.SC_WUSER_BITS_PER_BYTE {0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
 ] $m13_sc2axi

  # Create instance: s00_axi2sc, and set properties
  set s00_axi2sc [ create_bd_cell -type ip -vlnv xilinx.com:ip:sc_axi2sc:1.0 s00_axi2sc ]
  set_property -dict [ list \
   CONFIG.AXI_ADDR_WIDTH {40} \
   CONFIG.AXI_ID_WIDTH {3} \
   CONFIG.AXI_RDATA_WIDTH {128} \
   CONFIG.AXI_WDATA_WIDTH {128} \
   CONFIG.MSC_ROUTE_WIDTH {15} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.SC_ADDR_WIDTH {40} \
   CONFIG.SC_ARUSER_WIDTH {16} \
   CONFIG.SC_AWUSER_WIDTH {16} \
   CONFIG.SC_BUSER_WIDTH {0} \
   CONFIG.SC_ID_WIDTH {3} \
   CONFIG.SC_RDATA_WIDTH {128} \
   CONFIG.SC_RUSER_BITS_PER_BYTE {0} \
   CONFIG.SC_WDATA_WIDTH {128} \
   CONFIG.SC_WUSER_BITS_PER_BYTE {0} \
   CONFIG.SSC_ROUTE_WIDTH {1} \
 ] $s00_axi2sc

  # Create instance: s00_entry_pipeline
  create_hier_cell_s00_entry_pipeline [current_bd_instance .] s00_entry_pipeline

  # Create instance: s00_nodes
  create_hier_cell_s00_nodes [current_bd_instance .] s00_nodes

  # Create instance: switchboards
  create_hier_cell_switchboards [current_bd_instance .] switchboards

  # Create interface connections
  connect_bd_intf_net -intf_net S00_AXI_1 [get_bd_intf_ports S00_AXI] [get_bd_intf_pins s00_entry_pipeline/s_axi]
  connect_bd_intf_net -intf_net S_SC_AR_1 [get_bd_intf_pins s00_axi2sc/M_SC_AR] [get_bd_intf_pins s00_nodes/S_SC_AR]
  connect_bd_intf_net -intf_net S_SC_AR_2 [get_bd_intf_pins m00_nodes/S_SC_AR] [get_bd_intf_pins switchboards/M00_SC_AR]
  connect_bd_intf_net -intf_net S_SC_AR_3 [get_bd_intf_pins m01_nodes/S_SC_AR] [get_bd_intf_pins switchboards/M01_SC_AR]
  connect_bd_intf_net -intf_net S_SC_AR_4 [get_bd_intf_pins m02_nodes/S_SC_AR] [get_bd_intf_pins switchboards/M02_SC_AR]
  connect_bd_intf_net -intf_net S_SC_AR_5 [get_bd_intf_pins m03_nodes/S_SC_AR] [get_bd_intf_pins switchboards/M03_SC_AR]
  connect_bd_intf_net -intf_net S_SC_AR_6 [get_bd_intf_pins m04_nodes/S_SC_AR] [get_bd_intf_pins switchboards/M04_SC_AR]
  connect_bd_intf_net -intf_net S_SC_AR_7 [get_bd_intf_pins m05_nodes/S_SC_AR] [get_bd_intf_pins switchboards/M05_SC_AR]
  connect_bd_intf_net -intf_net S_SC_AR_8 [get_bd_intf_pins m06_nodes/S_SC_AR] [get_bd_intf_pins switchboards/M06_SC_AR]
  connect_bd_intf_net -intf_net S_SC_AR_9 [get_bd_intf_pins m07_nodes/S_SC_AR] [get_bd_intf_pins switchboards/M07_SC_AR]
  connect_bd_intf_net -intf_net S_SC_AR_10 [get_bd_intf_pins m08_nodes/S_SC_AR] [get_bd_intf_pins switchboards/M08_SC_AR]
  connect_bd_intf_net -intf_net S_SC_AR_11 [get_bd_intf_pins m09_nodes/S_SC_AR] [get_bd_intf_pins switchboards/M09_SC_AR]
  connect_bd_intf_net -intf_net S_SC_AR_12 [get_bd_intf_pins m10_nodes/S_SC_AR] [get_bd_intf_pins switchboards/M10_SC_AR]
  connect_bd_intf_net -intf_net S_SC_AR_13 [get_bd_intf_pins m11_nodes/S_SC_AR] [get_bd_intf_pins switchboards/M11_SC_AR]
  connect_bd_intf_net -intf_net S_SC_AR_14 [get_bd_intf_pins m12_nodes/S_SC_AR] [get_bd_intf_pins switchboards/M12_SC_AR]
  connect_bd_intf_net -intf_net S_SC_AR_15 [get_bd_intf_pins m13_nodes/S_SC_AR] [get_bd_intf_pins switchboards/M13_SC_AR]
  connect_bd_intf_net -intf_net S_SC_AW_1 [get_bd_intf_pins s00_axi2sc/M_SC_AW] [get_bd_intf_pins s00_nodes/S_SC_AW]
  connect_bd_intf_net -intf_net S_SC_AW_2 [get_bd_intf_pins m00_nodes/S_SC_AW] [get_bd_intf_pins switchboards/M00_SC_AW]
  connect_bd_intf_net -intf_net S_SC_AW_3 [get_bd_intf_pins m01_nodes/S_SC_AW] [get_bd_intf_pins switchboards/M01_SC_AW]
  connect_bd_intf_net -intf_net S_SC_AW_4 [get_bd_intf_pins m02_nodes/S_SC_AW] [get_bd_intf_pins switchboards/M02_SC_AW]
  connect_bd_intf_net -intf_net S_SC_AW_5 [get_bd_intf_pins m03_nodes/S_SC_AW] [get_bd_intf_pins switchboards/M03_SC_AW]
  connect_bd_intf_net -intf_net S_SC_AW_6 [get_bd_intf_pins m04_nodes/S_SC_AW] [get_bd_intf_pins switchboards/M04_SC_AW]
  connect_bd_intf_net -intf_net S_SC_AW_7 [get_bd_intf_pins m05_nodes/S_SC_AW] [get_bd_intf_pins switchboards/M05_SC_AW]
  connect_bd_intf_net -intf_net S_SC_AW_8 [get_bd_intf_pins m06_nodes/S_SC_AW] [get_bd_intf_pins switchboards/M06_SC_AW]
  connect_bd_intf_net -intf_net S_SC_AW_9 [get_bd_intf_pins m07_nodes/S_SC_AW] [get_bd_intf_pins switchboards/M07_SC_AW]
  connect_bd_intf_net -intf_net S_SC_AW_10 [get_bd_intf_pins m08_nodes/S_SC_AW] [get_bd_intf_pins switchboards/M08_SC_AW]
  connect_bd_intf_net -intf_net S_SC_AW_11 [get_bd_intf_pins m09_nodes/S_SC_AW] [get_bd_intf_pins switchboards/M09_SC_AW]
  connect_bd_intf_net -intf_net S_SC_AW_12 [get_bd_intf_pins m10_nodes/S_SC_AW] [get_bd_intf_pins switchboards/M10_SC_AW]
  connect_bd_intf_net -intf_net S_SC_AW_13 [get_bd_intf_pins m11_nodes/S_SC_AW] [get_bd_intf_pins switchboards/M11_SC_AW]
  connect_bd_intf_net -intf_net S_SC_AW_14 [get_bd_intf_pins m12_nodes/S_SC_AW] [get_bd_intf_pins switchboards/M12_SC_AW]
  connect_bd_intf_net -intf_net S_SC_AW_15 [get_bd_intf_pins m13_nodes/S_SC_AW] [get_bd_intf_pins switchboards/M13_SC_AW]
  connect_bd_intf_net -intf_net S_SC_B_1 [get_bd_intf_pins s00_nodes/S_SC_B] [get_bd_intf_pins switchboards/M00_SC_B]
  connect_bd_intf_net -intf_net S_SC_B_2 [get_bd_intf_pins m00_nodes/S_SC_B] [get_bd_intf_pins m00_sc2axi/M_SC_B]
  connect_bd_intf_net -intf_net S_SC_B_3 [get_bd_intf_pins m01_nodes/S_SC_B] [get_bd_intf_pins m01_sc2axi/M_SC_B]
  connect_bd_intf_net -intf_net S_SC_B_4 [get_bd_intf_pins m02_nodes/S_SC_B] [get_bd_intf_pins m02_sc2axi/M_SC_B]
  connect_bd_intf_net -intf_net S_SC_B_5 [get_bd_intf_pins m03_nodes/S_SC_B] [get_bd_intf_pins m03_sc2axi/M_SC_B]
  connect_bd_intf_net -intf_net S_SC_B_6 [get_bd_intf_pins m04_nodes/S_SC_B] [get_bd_intf_pins m04_sc2axi/M_SC_B]
  connect_bd_intf_net -intf_net S_SC_B_7 [get_bd_intf_pins m05_nodes/S_SC_B] [get_bd_intf_pins m05_sc2axi/M_SC_B]
  connect_bd_intf_net -intf_net S_SC_B_8 [get_bd_intf_pins m06_nodes/S_SC_B] [get_bd_intf_pins m06_sc2axi/M_SC_B]
  connect_bd_intf_net -intf_net S_SC_B_9 [get_bd_intf_pins m07_nodes/S_SC_B] [get_bd_intf_pins m07_sc2axi/M_SC_B]
  connect_bd_intf_net -intf_net S_SC_B_10 [get_bd_intf_pins m08_nodes/S_SC_B] [get_bd_intf_pins m08_sc2axi/M_SC_B]
  connect_bd_intf_net -intf_net S_SC_B_11 [get_bd_intf_pins m09_nodes/S_SC_B] [get_bd_intf_pins m09_sc2axi/M_SC_B]
  connect_bd_intf_net -intf_net S_SC_B_12 [get_bd_intf_pins m10_nodes/S_SC_B] [get_bd_intf_pins m10_sc2axi/M_SC_B]
  connect_bd_intf_net -intf_net S_SC_B_13 [get_bd_intf_pins m11_nodes/S_SC_B] [get_bd_intf_pins m11_sc2axi/M_SC_B]
  connect_bd_intf_net -intf_net S_SC_B_14 [get_bd_intf_pins m12_nodes/S_SC_B] [get_bd_intf_pins m12_sc2axi/M_SC_B]
  connect_bd_intf_net -intf_net S_SC_B_15 [get_bd_intf_pins m13_nodes/S_SC_B] [get_bd_intf_pins m13_sc2axi/M_SC_B]
  connect_bd_intf_net -intf_net S_SC_R_1 [get_bd_intf_pins s00_nodes/S_SC_R] [get_bd_intf_pins switchboards/M00_SC_R]
  connect_bd_intf_net -intf_net S_SC_R_2 [get_bd_intf_pins m00_nodes/S_SC_R] [get_bd_intf_pins m00_sc2axi/M_SC_R]
  connect_bd_intf_net -intf_net S_SC_R_3 [get_bd_intf_pins m01_nodes/S_SC_R] [get_bd_intf_pins m01_sc2axi/M_SC_R]
  connect_bd_intf_net -intf_net S_SC_R_4 [get_bd_intf_pins m02_nodes/S_SC_R] [get_bd_intf_pins m02_sc2axi/M_SC_R]
  connect_bd_intf_net -intf_net S_SC_R_5 [get_bd_intf_pins m03_nodes/S_SC_R] [get_bd_intf_pins m03_sc2axi/M_SC_R]
  connect_bd_intf_net -intf_net S_SC_R_6 [get_bd_intf_pins m04_nodes/S_SC_R] [get_bd_intf_pins m04_sc2axi/M_SC_R]
  connect_bd_intf_net -intf_net S_SC_R_7 [get_bd_intf_pins m05_nodes/S_SC_R] [get_bd_intf_pins m05_sc2axi/M_SC_R]
  connect_bd_intf_net -intf_net S_SC_R_8 [get_bd_intf_pins m06_nodes/S_SC_R] [get_bd_intf_pins m06_sc2axi/M_SC_R]
  connect_bd_intf_net -intf_net S_SC_R_9 [get_bd_intf_pins m07_nodes/S_SC_R] [get_bd_intf_pins m07_sc2axi/M_SC_R]
  connect_bd_intf_net -intf_net S_SC_R_10 [get_bd_intf_pins m08_nodes/S_SC_R] [get_bd_intf_pins m08_sc2axi/M_SC_R]
  connect_bd_intf_net -intf_net S_SC_R_11 [get_bd_intf_pins m09_nodes/S_SC_R] [get_bd_intf_pins m09_sc2axi/M_SC_R]
  connect_bd_intf_net -intf_net S_SC_R_12 [get_bd_intf_pins m10_nodes/S_SC_R] [get_bd_intf_pins m10_sc2axi/M_SC_R]
  connect_bd_intf_net -intf_net S_SC_R_13 [get_bd_intf_pins m11_nodes/S_SC_R] [get_bd_intf_pins m11_sc2axi/M_SC_R]
  connect_bd_intf_net -intf_net S_SC_R_14 [get_bd_intf_pins m12_nodes/S_SC_R] [get_bd_intf_pins m12_sc2axi/M_SC_R]
  connect_bd_intf_net -intf_net S_SC_R_15 [get_bd_intf_pins m13_nodes/S_SC_R] [get_bd_intf_pins m13_sc2axi/M_SC_R]
  connect_bd_intf_net -intf_net S_SC_W_1 [get_bd_intf_pins s00_axi2sc/M_SC_W] [get_bd_intf_pins s00_nodes/S_SC_W]
  connect_bd_intf_net -intf_net S_SC_W_2 [get_bd_intf_pins m00_nodes/S_SC_W] [get_bd_intf_pins switchboards/M00_SC_W]
  connect_bd_intf_net -intf_net S_SC_W_3 [get_bd_intf_pins m01_nodes/S_SC_W] [get_bd_intf_pins switchboards/M01_SC_W]
  connect_bd_intf_net -intf_net S_SC_W_4 [get_bd_intf_pins m02_nodes/S_SC_W] [get_bd_intf_pins switchboards/M02_SC_W]
  connect_bd_intf_net -intf_net S_SC_W_5 [get_bd_intf_pins m03_nodes/S_SC_W] [get_bd_intf_pins switchboards/M03_SC_W]
  connect_bd_intf_net -intf_net S_SC_W_6 [get_bd_intf_pins m04_nodes/S_SC_W] [get_bd_intf_pins switchboards/M04_SC_W]
  connect_bd_intf_net -intf_net S_SC_W_7 [get_bd_intf_pins m05_nodes/S_SC_W] [get_bd_intf_pins switchboards/M05_SC_W]
  connect_bd_intf_net -intf_net S_SC_W_8 [get_bd_intf_pins m06_nodes/S_SC_W] [get_bd_intf_pins switchboards/M06_SC_W]
  connect_bd_intf_net -intf_net S_SC_W_9 [get_bd_intf_pins m07_nodes/S_SC_W] [get_bd_intf_pins switchboards/M07_SC_W]
  connect_bd_intf_net -intf_net S_SC_W_10 [get_bd_intf_pins m08_nodes/S_SC_W] [get_bd_intf_pins switchboards/M08_SC_W]
  connect_bd_intf_net -intf_net S_SC_W_11 [get_bd_intf_pins m09_nodes/S_SC_W] [get_bd_intf_pins switchboards/M09_SC_W]
  connect_bd_intf_net -intf_net S_SC_W_12 [get_bd_intf_pins m10_nodes/S_SC_W] [get_bd_intf_pins switchboards/M10_SC_W]
  connect_bd_intf_net -intf_net S_SC_W_13 [get_bd_intf_pins m11_nodes/S_SC_W] [get_bd_intf_pins switchboards/M11_SC_W]
  connect_bd_intf_net -intf_net S_SC_W_14 [get_bd_intf_pins m12_nodes/S_SC_W] [get_bd_intf_pins switchboards/M12_SC_W]
  connect_bd_intf_net -intf_net S_SC_W_15 [get_bd_intf_pins m13_nodes/S_SC_W] [get_bd_intf_pins switchboards/M13_SC_W]
  connect_bd_intf_net -intf_net m00_exit_pipeline_m_axi [get_bd_intf_ports M00_AXI] [get_bd_intf_pins m00_exit_pipeline/m_axi]
  connect_bd_intf_net -intf_net m00_nodes_M_SC_AR [get_bd_intf_pins m00_nodes/M_SC_AR] [get_bd_intf_pins m00_sc2axi/S_SC_AR]
  connect_bd_intf_net -intf_net m00_nodes_M_SC_AW [get_bd_intf_pins m00_nodes/M_SC_AW] [get_bd_intf_pins m00_sc2axi/S_SC_AW]
  connect_bd_intf_net -intf_net m00_nodes_M_SC_B [get_bd_intf_pins m00_nodes/M_SC_B] [get_bd_intf_pins switchboards/S00_SC_B]
  connect_bd_intf_net -intf_net m00_nodes_M_SC_R [get_bd_intf_pins m00_nodes/M_SC_R] [get_bd_intf_pins switchboards/S00_SC_R]
  connect_bd_intf_net -intf_net m00_nodes_M_SC_W [get_bd_intf_pins m00_nodes/M_SC_W] [get_bd_intf_pins m00_sc2axi/S_SC_W]
  connect_bd_intf_net -intf_net m00_sc2axi_M_AXI [get_bd_intf_pins m00_exit_pipeline/s_axi] [get_bd_intf_pins m00_sc2axi/M_AXI]
  connect_bd_intf_net -intf_net m01_exit_pipeline_m_axi [get_bd_intf_ports M01_AXI] [get_bd_intf_pins m01_exit_pipeline/m_axi]
  connect_bd_intf_net -intf_net m01_nodes_M_SC_AR [get_bd_intf_pins m01_nodes/M_SC_AR] [get_bd_intf_pins m01_sc2axi/S_SC_AR]
  connect_bd_intf_net -intf_net m01_nodes_M_SC_AW [get_bd_intf_pins m01_nodes/M_SC_AW] [get_bd_intf_pins m01_sc2axi/S_SC_AW]
  connect_bd_intf_net -intf_net m01_nodes_M_SC_B [get_bd_intf_pins m01_nodes/M_SC_B] [get_bd_intf_pins switchboards/S01_SC_B]
  connect_bd_intf_net -intf_net m01_nodes_M_SC_R [get_bd_intf_pins m01_nodes/M_SC_R] [get_bd_intf_pins switchboards/S01_SC_R]
  connect_bd_intf_net -intf_net m01_nodes_M_SC_W [get_bd_intf_pins m01_nodes/M_SC_W] [get_bd_intf_pins m01_sc2axi/S_SC_W]
  connect_bd_intf_net -intf_net m01_sc2axi_M_AXI [get_bd_intf_pins m01_exit_pipeline/s_axi] [get_bd_intf_pins m01_sc2axi/M_AXI]
  connect_bd_intf_net -intf_net m02_exit_pipeline_m_axi [get_bd_intf_ports M02_AXI] [get_bd_intf_pins m02_exit_pipeline/m_axi]
  connect_bd_intf_net -intf_net m02_nodes_M_SC_AR [get_bd_intf_pins m02_nodes/M_SC_AR] [get_bd_intf_pins m02_sc2axi/S_SC_AR]
  connect_bd_intf_net -intf_net m02_nodes_M_SC_AW [get_bd_intf_pins m02_nodes/M_SC_AW] [get_bd_intf_pins m02_sc2axi/S_SC_AW]
  connect_bd_intf_net -intf_net m02_nodes_M_SC_B [get_bd_intf_pins m02_nodes/M_SC_B] [get_bd_intf_pins switchboards/S02_SC_B]
  connect_bd_intf_net -intf_net m02_nodes_M_SC_R [get_bd_intf_pins m02_nodes/M_SC_R] [get_bd_intf_pins switchboards/S02_SC_R]
  connect_bd_intf_net -intf_net m02_nodes_M_SC_W [get_bd_intf_pins m02_nodes/M_SC_W] [get_bd_intf_pins m02_sc2axi/S_SC_W]
  connect_bd_intf_net -intf_net m02_sc2axi_M_AXI [get_bd_intf_pins m02_exit_pipeline/s_axi] [get_bd_intf_pins m02_sc2axi/M_AXI]
  connect_bd_intf_net -intf_net m03_exit_pipeline_m_axi [get_bd_intf_ports M03_AXI] [get_bd_intf_pins m03_exit_pipeline/m_axi]
  connect_bd_intf_net -intf_net m03_nodes_M_SC_AR [get_bd_intf_pins m03_nodes/M_SC_AR] [get_bd_intf_pins m03_sc2axi/S_SC_AR]
  connect_bd_intf_net -intf_net m03_nodes_M_SC_AW [get_bd_intf_pins m03_nodes/M_SC_AW] [get_bd_intf_pins m03_sc2axi/S_SC_AW]
  connect_bd_intf_net -intf_net m03_nodes_M_SC_B [get_bd_intf_pins m03_nodes/M_SC_B] [get_bd_intf_pins switchboards/S03_SC_B]
  connect_bd_intf_net -intf_net m03_nodes_M_SC_R [get_bd_intf_pins m03_nodes/M_SC_R] [get_bd_intf_pins switchboards/S03_SC_R]
  connect_bd_intf_net -intf_net m03_nodes_M_SC_W [get_bd_intf_pins m03_nodes/M_SC_W] [get_bd_intf_pins m03_sc2axi/S_SC_W]
  connect_bd_intf_net -intf_net m03_sc2axi_M_AXI [get_bd_intf_pins m03_exit_pipeline/s_axi] [get_bd_intf_pins m03_sc2axi/M_AXI]
  connect_bd_intf_net -intf_net m04_exit_pipeline_m_axi [get_bd_intf_ports M04_AXI] [get_bd_intf_pins m04_exit_pipeline/m_axi]
  connect_bd_intf_net -intf_net m04_nodes_M_SC_AR [get_bd_intf_pins m04_nodes/M_SC_AR] [get_bd_intf_pins m04_sc2axi/S_SC_AR]
  connect_bd_intf_net -intf_net m04_nodes_M_SC_AW [get_bd_intf_pins m04_nodes/M_SC_AW] [get_bd_intf_pins m04_sc2axi/S_SC_AW]
  connect_bd_intf_net -intf_net m04_nodes_M_SC_B [get_bd_intf_pins m04_nodes/M_SC_B] [get_bd_intf_pins switchboards/S04_SC_B]
  connect_bd_intf_net -intf_net m04_nodes_M_SC_R [get_bd_intf_pins m04_nodes/M_SC_R] [get_bd_intf_pins switchboards/S04_SC_R]
  connect_bd_intf_net -intf_net m04_nodes_M_SC_W [get_bd_intf_pins m04_nodes/M_SC_W] [get_bd_intf_pins m04_sc2axi/S_SC_W]
  connect_bd_intf_net -intf_net m04_sc2axi_M_AXI [get_bd_intf_pins m04_exit_pipeline/s_axi] [get_bd_intf_pins m04_sc2axi/M_AXI]
  connect_bd_intf_net -intf_net m05_exit_pipeline_m_axi [get_bd_intf_ports M05_AXI] [get_bd_intf_pins m05_exit_pipeline/m_axi]
  connect_bd_intf_net -intf_net m05_nodes_M_SC_AR [get_bd_intf_pins m05_nodes/M_SC_AR] [get_bd_intf_pins m05_sc2axi/S_SC_AR]
  connect_bd_intf_net -intf_net m05_nodes_M_SC_AW [get_bd_intf_pins m05_nodes/M_SC_AW] [get_bd_intf_pins m05_sc2axi/S_SC_AW]
  connect_bd_intf_net -intf_net m05_nodes_M_SC_B [get_bd_intf_pins m05_nodes/M_SC_B] [get_bd_intf_pins switchboards/S05_SC_B]
  connect_bd_intf_net -intf_net m05_nodes_M_SC_R [get_bd_intf_pins m05_nodes/M_SC_R] [get_bd_intf_pins switchboards/S05_SC_R]
  connect_bd_intf_net -intf_net m05_nodes_M_SC_W [get_bd_intf_pins m05_nodes/M_SC_W] [get_bd_intf_pins m05_sc2axi/S_SC_W]
  connect_bd_intf_net -intf_net m05_sc2axi_M_AXI [get_bd_intf_pins m05_exit_pipeline/s_axi] [get_bd_intf_pins m05_sc2axi/M_AXI]
  connect_bd_intf_net -intf_net m06_exit_pipeline_m_axi [get_bd_intf_ports M06_AXI] [get_bd_intf_pins m06_exit_pipeline/m_axi]
  connect_bd_intf_net -intf_net m06_nodes_M_SC_AR [get_bd_intf_pins m06_nodes/M_SC_AR] [get_bd_intf_pins m06_sc2axi/S_SC_AR]
  connect_bd_intf_net -intf_net m06_nodes_M_SC_AW [get_bd_intf_pins m06_nodes/M_SC_AW] [get_bd_intf_pins m06_sc2axi/S_SC_AW]
  connect_bd_intf_net -intf_net m06_nodes_M_SC_B [get_bd_intf_pins m06_nodes/M_SC_B] [get_bd_intf_pins switchboards/S06_SC_B]
  connect_bd_intf_net -intf_net m06_nodes_M_SC_R [get_bd_intf_pins m06_nodes/M_SC_R] [get_bd_intf_pins switchboards/S06_SC_R]
  connect_bd_intf_net -intf_net m06_nodes_M_SC_W [get_bd_intf_pins m06_nodes/M_SC_W] [get_bd_intf_pins m06_sc2axi/S_SC_W]
  connect_bd_intf_net -intf_net m06_sc2axi_M_AXI [get_bd_intf_pins m06_exit_pipeline/s_axi] [get_bd_intf_pins m06_sc2axi/M_AXI]
  connect_bd_intf_net -intf_net m07_exit_pipeline_m_axi [get_bd_intf_ports M07_AXI] [get_bd_intf_pins m07_exit_pipeline/m_axi]
  connect_bd_intf_net -intf_net m07_nodes_M_SC_AR [get_bd_intf_pins m07_nodes/M_SC_AR] [get_bd_intf_pins m07_sc2axi/S_SC_AR]
  connect_bd_intf_net -intf_net m07_nodes_M_SC_AW [get_bd_intf_pins m07_nodes/M_SC_AW] [get_bd_intf_pins m07_sc2axi/S_SC_AW]
  connect_bd_intf_net -intf_net m07_nodes_M_SC_B [get_bd_intf_pins m07_nodes/M_SC_B] [get_bd_intf_pins switchboards/S07_SC_B]
  connect_bd_intf_net -intf_net m07_nodes_M_SC_R [get_bd_intf_pins m07_nodes/M_SC_R] [get_bd_intf_pins switchboards/S07_SC_R]
  connect_bd_intf_net -intf_net m07_nodes_M_SC_W [get_bd_intf_pins m07_nodes/M_SC_W] [get_bd_intf_pins m07_sc2axi/S_SC_W]
  connect_bd_intf_net -intf_net m07_sc2axi_M_AXI [get_bd_intf_pins m07_exit_pipeline/s_axi] [get_bd_intf_pins m07_sc2axi/M_AXI]
  connect_bd_intf_net -intf_net m08_exit_pipeline_m_axi [get_bd_intf_ports M08_AXI] [get_bd_intf_pins m08_exit_pipeline/m_axi]
  connect_bd_intf_net -intf_net m08_nodes_M_SC_AR [get_bd_intf_pins m08_nodes/M_SC_AR] [get_bd_intf_pins m08_sc2axi/S_SC_AR]
  connect_bd_intf_net -intf_net m08_nodes_M_SC_AW [get_bd_intf_pins m08_nodes/M_SC_AW] [get_bd_intf_pins m08_sc2axi/S_SC_AW]
  connect_bd_intf_net -intf_net m08_nodes_M_SC_B [get_bd_intf_pins m08_nodes/M_SC_B] [get_bd_intf_pins switchboards/S08_SC_B]
  connect_bd_intf_net -intf_net m08_nodes_M_SC_R [get_bd_intf_pins m08_nodes/M_SC_R] [get_bd_intf_pins switchboards/S08_SC_R]
  connect_bd_intf_net -intf_net m08_nodes_M_SC_W [get_bd_intf_pins m08_nodes/M_SC_W] [get_bd_intf_pins m08_sc2axi/S_SC_W]
  connect_bd_intf_net -intf_net m08_sc2axi_M_AXI [get_bd_intf_pins m08_exit_pipeline/s_axi] [get_bd_intf_pins m08_sc2axi/M_AXI]
  connect_bd_intf_net -intf_net m09_exit_pipeline_m_axi [get_bd_intf_ports M09_AXI] [get_bd_intf_pins m09_exit_pipeline/m_axi]
  connect_bd_intf_net -intf_net m09_nodes_M_SC_AR [get_bd_intf_pins m09_nodes/M_SC_AR] [get_bd_intf_pins m09_sc2axi/S_SC_AR]
  connect_bd_intf_net -intf_net m09_nodes_M_SC_AW [get_bd_intf_pins m09_nodes/M_SC_AW] [get_bd_intf_pins m09_sc2axi/S_SC_AW]
  connect_bd_intf_net -intf_net m09_nodes_M_SC_B [get_bd_intf_pins m09_nodes/M_SC_B] [get_bd_intf_pins switchboards/S09_SC_B]
  connect_bd_intf_net -intf_net m09_nodes_M_SC_R [get_bd_intf_pins m09_nodes/M_SC_R] [get_bd_intf_pins switchboards/S09_SC_R]
  connect_bd_intf_net -intf_net m09_nodes_M_SC_W [get_bd_intf_pins m09_nodes/M_SC_W] [get_bd_intf_pins m09_sc2axi/S_SC_W]
  connect_bd_intf_net -intf_net m09_sc2axi_M_AXI [get_bd_intf_pins m09_exit_pipeline/s_axi] [get_bd_intf_pins m09_sc2axi/M_AXI]
  connect_bd_intf_net -intf_net m10_exit_pipeline_m_axi [get_bd_intf_ports M10_AXI] [get_bd_intf_pins m10_exit_pipeline/m_axi]
  connect_bd_intf_net -intf_net m10_nodes_M_SC_AR [get_bd_intf_pins m10_nodes/M_SC_AR] [get_bd_intf_pins m10_sc2axi/S_SC_AR]
  connect_bd_intf_net -intf_net m10_nodes_M_SC_AW [get_bd_intf_pins m10_nodes/M_SC_AW] [get_bd_intf_pins m10_sc2axi/S_SC_AW]
  connect_bd_intf_net -intf_net m10_nodes_M_SC_B [get_bd_intf_pins m10_nodes/M_SC_B] [get_bd_intf_pins switchboards/S10_SC_B]
  connect_bd_intf_net -intf_net m10_nodes_M_SC_R [get_bd_intf_pins m10_nodes/M_SC_R] [get_bd_intf_pins switchboards/S10_SC_R]
  connect_bd_intf_net -intf_net m10_nodes_M_SC_W [get_bd_intf_pins m10_nodes/M_SC_W] [get_bd_intf_pins m10_sc2axi/S_SC_W]
  connect_bd_intf_net -intf_net m10_sc2axi_M_AXI [get_bd_intf_pins m10_exit_pipeline/s_axi] [get_bd_intf_pins m10_sc2axi/M_AXI]
  connect_bd_intf_net -intf_net m11_exit_pipeline_m_axi [get_bd_intf_ports M11_AXI] [get_bd_intf_pins m11_exit_pipeline/m_axi]
  connect_bd_intf_net -intf_net m11_nodes_M_SC_AR [get_bd_intf_pins m11_nodes/M_SC_AR] [get_bd_intf_pins m11_sc2axi/S_SC_AR]
  connect_bd_intf_net -intf_net m11_nodes_M_SC_AW [get_bd_intf_pins m11_nodes/M_SC_AW] [get_bd_intf_pins m11_sc2axi/S_SC_AW]
  connect_bd_intf_net -intf_net m11_nodes_M_SC_B [get_bd_intf_pins m11_nodes/M_SC_B] [get_bd_intf_pins switchboards/S11_SC_B]
  connect_bd_intf_net -intf_net m11_nodes_M_SC_R [get_bd_intf_pins m11_nodes/M_SC_R] [get_bd_intf_pins switchboards/S11_SC_R]
  connect_bd_intf_net -intf_net m11_nodes_M_SC_W [get_bd_intf_pins m11_nodes/M_SC_W] [get_bd_intf_pins m11_sc2axi/S_SC_W]
  connect_bd_intf_net -intf_net m11_sc2axi_M_AXI [get_bd_intf_pins m11_exit_pipeline/s_axi] [get_bd_intf_pins m11_sc2axi/M_AXI]
  connect_bd_intf_net -intf_net m12_exit_pipeline_m_axi [get_bd_intf_ports M12_AXI] [get_bd_intf_pins m12_exit_pipeline/m_axi]
  connect_bd_intf_net -intf_net m12_nodes_M_SC_AR [get_bd_intf_pins m12_nodes/M_SC_AR] [get_bd_intf_pins m12_sc2axi/S_SC_AR]
  connect_bd_intf_net -intf_net m12_nodes_M_SC_AW [get_bd_intf_pins m12_nodes/M_SC_AW] [get_bd_intf_pins m12_sc2axi/S_SC_AW]
  connect_bd_intf_net -intf_net m12_nodes_M_SC_B [get_bd_intf_pins m12_nodes/M_SC_B] [get_bd_intf_pins switchboards/S12_SC_B]
  connect_bd_intf_net -intf_net m12_nodes_M_SC_R [get_bd_intf_pins m12_nodes/M_SC_R] [get_bd_intf_pins switchboards/S12_SC_R]
  connect_bd_intf_net -intf_net m12_nodes_M_SC_W [get_bd_intf_pins m12_nodes/M_SC_W] [get_bd_intf_pins m12_sc2axi/S_SC_W]
  connect_bd_intf_net -intf_net m12_sc2axi_M_AXI [get_bd_intf_pins m12_exit_pipeline/s_axi] [get_bd_intf_pins m12_sc2axi/M_AXI]
  connect_bd_intf_net -intf_net m13_exit_pipeline_m_axi [get_bd_intf_ports M13_AXI] [get_bd_intf_pins m13_exit_pipeline/m_axi]
  connect_bd_intf_net -intf_net m13_nodes_M_SC_AR [get_bd_intf_pins m13_nodes/M_SC_AR] [get_bd_intf_pins m13_sc2axi/S_SC_AR]
  connect_bd_intf_net -intf_net m13_nodes_M_SC_AW [get_bd_intf_pins m13_nodes/M_SC_AW] [get_bd_intf_pins m13_sc2axi/S_SC_AW]
  connect_bd_intf_net -intf_net m13_nodes_M_SC_B [get_bd_intf_pins m13_nodes/M_SC_B] [get_bd_intf_pins switchboards/S13_SC_B]
  connect_bd_intf_net -intf_net m13_nodes_M_SC_R [get_bd_intf_pins m13_nodes/M_SC_R] [get_bd_intf_pins switchboards/S13_SC_R]
  connect_bd_intf_net -intf_net m13_nodes_M_SC_W [get_bd_intf_pins m13_nodes/M_SC_W] [get_bd_intf_pins m13_sc2axi/S_SC_W]
  connect_bd_intf_net -intf_net m13_sc2axi_M_AXI [get_bd_intf_pins m13_exit_pipeline/s_axi] [get_bd_intf_pins m13_sc2axi/M_AXI]
  connect_bd_intf_net -intf_net s00_entry_pipeline_m_axi [get_bd_intf_pins s00_axi2sc/S_AXI] [get_bd_intf_pins s00_entry_pipeline/m_axi]
  connect_bd_intf_net -intf_net s00_nodes_M_SC_AR [get_bd_intf_pins s00_nodes/M_SC_AR] [get_bd_intf_pins switchboards/S00_SC_AR]
  connect_bd_intf_net -intf_net s00_nodes_M_SC_AW [get_bd_intf_pins s00_nodes/M_SC_AW] [get_bd_intf_pins switchboards/S00_SC_AW]
  connect_bd_intf_net -intf_net s00_nodes_M_SC_B [get_bd_intf_pins s00_axi2sc/S_SC_B] [get_bd_intf_pins s00_nodes/M_SC_B]
  connect_bd_intf_net -intf_net s00_nodes_M_SC_R [get_bd_intf_pins s00_axi2sc/S_SC_R] [get_bd_intf_pins s00_nodes/M_SC_R]
  connect_bd_intf_net -intf_net s00_nodes_M_SC_W [get_bd_intf_pins s00_nodes/M_SC_W] [get_bd_intf_pins switchboards/S00_SC_W]

  # Create port connections
  connect_bd_net -net aclk1_1 [get_bd_ports aclk1] [get_bd_pins clk_map/aclk1]
  connect_bd_net -net aclk2_1 [get_bd_ports aclk2] [get_bd_pins clk_map/aclk2]
  connect_bd_net -net aclk_1 [get_bd_pins clk_map/S00_ACLK] [get_bd_pins s00_axi2sc/aclk] [get_bd_pins s00_entry_pipeline/aclk] [get_bd_pins s00_nodes/s_sc_clk]
  connect_bd_net -net aclk_net [get_bd_ports aclk] [get_bd_pins clk_map/aclk]
  connect_bd_net -net aresetn_1 [get_bd_ports aresetn] [get_bd_pins clk_map/aresetn]
  connect_bd_net -net aresetn_2 [get_bd_pins clk_map/S00_ARESETN] [get_bd_pins s00_entry_pipeline/aresetn] [get_bd_pins s00_nodes/s_sc_resetn]
  connect_bd_net -net aresetn_net -boundary_type upper [get_bd_pins clk_map/aresetn_out]
  connect_bd_net -net clk_map_M00_ACLK [get_bd_pins clk_map/M00_ACLK] [get_bd_pins m00_exit_pipeline/aclk] [get_bd_pins m00_nodes/m_axi_aclk] [get_bd_pins m00_sc2axi/aclk]
  connect_bd_net -net clk_map_M01_ACLK [get_bd_pins clk_map/M01_ACLK] [get_bd_pins m01_exit_pipeline/aclk] [get_bd_pins m01_nodes/m_axi_aclk] [get_bd_pins m01_sc2axi/aclk]
  connect_bd_net -net clk_map_M02_ACLK [get_bd_pins clk_map/M02_ACLK] [get_bd_pins m02_exit_pipeline/aclk] [get_bd_pins m02_nodes/m_axi_aclk] [get_bd_pins m02_sc2axi/aclk]
  connect_bd_net -net clk_map_M03_ACLK [get_bd_pins clk_map/M03_ACLK] [get_bd_pins m03_exit_pipeline/aclk] [get_bd_pins m03_nodes/m_axi_aclk] [get_bd_pins m03_sc2axi/aclk]
  connect_bd_net -net clk_map_M04_ACLK [get_bd_pins clk_map/M04_ACLK] [get_bd_pins m04_exit_pipeline/aclk] [get_bd_pins m04_nodes/m_axi_aclk] [get_bd_pins m04_sc2axi/aclk]
  connect_bd_net -net clk_map_M05_ACLK [get_bd_pins clk_map/M05_ACLK] [get_bd_pins m05_exit_pipeline/aclk] [get_bd_pins m05_nodes/m_axi_aclk] [get_bd_pins m05_sc2axi/aclk]
  connect_bd_net -net clk_map_M06_ACLK [get_bd_pins clk_map/M06_ACLK] [get_bd_pins m06_exit_pipeline/aclk] [get_bd_pins m06_nodes/m_axi_aclk] [get_bd_pins m06_sc2axi/aclk]
  connect_bd_net -net clk_map_M07_ACLK [get_bd_pins clk_map/M07_ACLK] [get_bd_pins m07_exit_pipeline/aclk] [get_bd_pins m07_nodes/m_axi_aclk] [get_bd_pins m07_sc2axi/aclk]
  connect_bd_net -net clk_map_M08_ACLK [get_bd_pins clk_map/M08_ACLK] [get_bd_pins m08_exit_pipeline/aclk] [get_bd_pins m08_nodes/m_axi_aclk] [get_bd_pins m08_sc2axi/aclk]
  connect_bd_net -net clk_map_M09_ACLK [get_bd_pins clk_map/M09_ACLK] [get_bd_pins m09_exit_pipeline/aclk] [get_bd_pins m09_nodes/m_axi_aclk] [get_bd_pins m09_sc2axi/aclk]
  connect_bd_net -net clk_map_M10_ACLK [get_bd_pins clk_map/M10_ACLK] [get_bd_pins m10_exit_pipeline/aclk] [get_bd_pins m10_nodes/m_axi_aclk] [get_bd_pins m10_sc2axi/aclk]
  connect_bd_net -net clk_map_M11_ACLK [get_bd_pins clk_map/M11_ACLK] [get_bd_pins m11_exit_pipeline/aclk] [get_bd_pins m11_nodes/m_axi_aclk] [get_bd_pins m11_sc2axi/aclk]
  connect_bd_net -net clk_map_M12_ACLK [get_bd_pins clk_map/M12_ACLK] [get_bd_pins m12_exit_pipeline/aclk] [get_bd_pins m12_nodes/m_axi_aclk] [get_bd_pins m12_sc2axi/aclk]
  connect_bd_net -net clk_map_M13_ACLK [get_bd_pins clk_map/M13_ACLK] [get_bd_pins m13_exit_pipeline/aclk] [get_bd_pins m13_nodes/m_axi_aclk] [get_bd_pins m13_sc2axi/aclk]
  connect_bd_net -net m_axi_aresetn_1 [get_bd_pins clk_map/M00_ARESETN] [get_bd_pins m00_exit_pipeline/aresetn] [get_bd_pins m00_nodes/m_axi_aresetn]
  connect_bd_net -net m_axi_aresetn_2 [get_bd_pins clk_map/M01_ARESETN] [get_bd_pins m01_exit_pipeline/aresetn] [get_bd_pins m01_nodes/m_axi_aresetn]
  connect_bd_net -net m_axi_aresetn_3 [get_bd_pins clk_map/M02_ARESETN] [get_bd_pins m02_exit_pipeline/aresetn] [get_bd_pins m02_nodes/m_axi_aresetn]
  connect_bd_net -net m_axi_aresetn_4 [get_bd_pins clk_map/M03_ARESETN] [get_bd_pins m03_exit_pipeline/aresetn] [get_bd_pins m03_nodes/m_axi_aresetn]
  connect_bd_net -net m_axi_aresetn_5 [get_bd_pins clk_map/M04_ARESETN] [get_bd_pins m04_exit_pipeline/aresetn] [get_bd_pins m04_nodes/m_axi_aresetn]
  connect_bd_net -net m_axi_aresetn_6 [get_bd_pins clk_map/M05_ARESETN] [get_bd_pins m05_exit_pipeline/aresetn] [get_bd_pins m05_nodes/m_axi_aresetn]
  connect_bd_net -net m_axi_aresetn_7 [get_bd_pins clk_map/M06_ARESETN] [get_bd_pins m06_exit_pipeline/aresetn] [get_bd_pins m06_nodes/m_axi_aresetn]
  connect_bd_net -net m_axi_aresetn_8 [get_bd_pins clk_map/M07_ARESETN] [get_bd_pins m07_exit_pipeline/aresetn] [get_bd_pins m07_nodes/m_axi_aresetn]
  connect_bd_net -net m_axi_aresetn_9 [get_bd_pins clk_map/M08_ARESETN] [get_bd_pins m08_exit_pipeline/aresetn] [get_bd_pins m08_nodes/m_axi_aresetn]
  connect_bd_net -net m_axi_aresetn_10 [get_bd_pins clk_map/M09_ARESETN] [get_bd_pins m09_exit_pipeline/aresetn] [get_bd_pins m09_nodes/m_axi_aresetn]
  connect_bd_net -net m_axi_aresetn_11 [get_bd_pins clk_map/M10_ARESETN] [get_bd_pins m10_exit_pipeline/aresetn] [get_bd_pins m10_nodes/m_axi_aresetn]
  connect_bd_net -net m_axi_aresetn_12 [get_bd_pins clk_map/M11_ARESETN] [get_bd_pins m11_exit_pipeline/aresetn] [get_bd_pins m11_nodes/m_axi_aresetn]
  connect_bd_net -net m_axi_aresetn_13 [get_bd_pins clk_map/M12_ARESETN] [get_bd_pins m12_exit_pipeline/aresetn] [get_bd_pins m12_nodes/m_axi_aresetn]
  connect_bd_net -net m_axi_aresetn_14 [get_bd_pins clk_map/M13_ARESETN] [get_bd_pins m13_exit_pipeline/aresetn] [get_bd_pins m13_nodes/m_axi_aresetn]
  connect_bd_net -net swbd_aclk_net [get_bd_pins clk_map/swbd_aclk] [get_bd_pins m00_nodes/s_axi_aclk] [get_bd_pins m01_nodes/s_axi_aclk] [get_bd_pins m02_nodes/s_axi_aclk] [get_bd_pins m03_nodes/s_axi_aclk] [get_bd_pins m04_nodes/s_axi_aclk] [get_bd_pins m05_nodes/s_axi_aclk] [get_bd_pins m06_nodes/s_axi_aclk] [get_bd_pins m07_nodes/s_axi_aclk] [get_bd_pins m08_nodes/s_axi_aclk] [get_bd_pins m09_nodes/s_axi_aclk] [get_bd_pins m10_nodes/s_axi_aclk] [get_bd_pins m11_nodes/s_axi_aclk] [get_bd_pins m12_nodes/s_axi_aclk] [get_bd_pins m13_nodes/s_axi_aclk] [get_bd_pins s00_nodes/m_sc_clk] [get_bd_pins switchboards/aclk]
  connect_bd_net -net swbd_aresetn_net [get_bd_pins clk_map/swbd_aresetn] [get_bd_pins m00_nodes/s_axi_aresetn] [get_bd_pins m01_nodes/s_axi_aresetn] [get_bd_pins m02_nodes/s_axi_aresetn] [get_bd_pins m03_nodes/s_axi_aresetn] [get_bd_pins m04_nodes/s_axi_aresetn] [get_bd_pins m05_nodes/s_axi_aresetn] [get_bd_pins m06_nodes/s_axi_aresetn] [get_bd_pins m07_nodes/s_axi_aresetn] [get_bd_pins m08_nodes/s_axi_aresetn] [get_bd_pins m09_nodes/s_axi_aresetn] [get_bd_pins m10_nodes/s_axi_aresetn] [get_bd_pins m11_nodes/s_axi_aresetn] [get_bd_pins m12_nodes/s_axi_aresetn] [get_bd_pins m13_nodes/s_axi_aresetn] [get_bd_pins s00_nodes/m_sc_resetn] [get_bd_pins switchboards/aresetn]

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


