
################################################################
# This is a generated script based on design: zusys
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
set scripts_vivado_version 2022.2
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
# source zusys_script.tcl


# The design that will be created by this Tcl script contains the following 
# module references:
# iobufds_inst, iobufds_inst, iobufds_inst

# Please add the sources of those modules before sourcing this Tcl script.

set bCheckIPsPassed 1
##################################################################
# CHECK IPs
##################################################################
set bCheckIPs 1
if { $bCheckIPs == 1 } {
   set list_check_ips "\ 
UltraZohm:user:ADC_LTC2311:3.0\
xilinx.com:ip:xlconstant:1.1\
xilinx.com:ip:ila:6.2\
xilinx.com:ip:xlslice:1.0\
"

   set list_ips_missing ""
   common::send_gid_msg -ssname BD::TCL -id 2011 -severity "INFO" "Checking if the following IPs exist in the project's IP catalog: $list_check_ips ."

   foreach ip_vlnv $list_check_ips {
      set ip_obj [get_ipdefs -all $ip_vlnv]
      if { $ip_obj eq "" } {
         lappend list_ips_missing $ip_vlnv
      }
   }

   if { $list_ips_missing ne "" } {
      catch {common::send_gid_msg -ssname BD::TCL -id 2012 -severity "ERROR" "The following IPs are not found in the IP Catalog:\n  $list_ips_missing\n\nResolution: Please add the repository containing the IP(s) to the project." }
      set bCheckIPsPassed 0
   }

}

##################################################################
# CHECK Modules
##################################################################
set bCheckModules 1
if { $bCheckModules == 1 } {
   set list_check_mods "\ 
iobufds_inst\
iobufds_inst\
iobufds_inst\
"

   set list_mods_missing ""
   common::send_gid_msg -ssname BD::TCL -id 2020 -severity "INFO" "Checking if the following modules exist in the project's sources: $list_check_mods ."

   foreach mod_vlnv $list_check_mods {
      if { [can_resolve_reference $mod_vlnv] == 0 } {
         lappend list_mods_missing $mod_vlnv
      }
   }

   if { $list_mods_missing ne "" } {
      catch {common::send_gid_msg -ssname BD::TCL -id 2021 -severity "ERROR" "The following module(s) are not found in the project: $list_mods_missing" }
      common::send_gid_msg -ssname BD::TCL -id 2022 -severity "INFO" "Please add source files for the missing module(s) above."
      set bCheckIPsPassed 0
   }
}

if { $bCheckIPsPassed != 1 } {
  common::send_gid_msg -ssname BD::TCL -id 2023 -severity "WARNING" "Will not continue with creation of design due to the error(s) above."
  return 3
}

##################################################################
# DESIGN PROCs
##################################################################


# Hierarchical cell: adc_debug
proc create_hier_cell_adc_debug { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_adc_debug() - Empty argument(s)!"}
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
  create_bd_pin -dir I -from 127 -to 0 Din
  create_bd_pin -dir I -from 279 -to 0 Din1
  create_bd_pin -dir I -type clk clk
  create_bd_pin -dir I -from 0 -to 0 probe4
  create_bd_pin -dir I -from 0 -to 0 probe5
  create_bd_pin -dir I -from 31 -to 0 probe6
  create_bd_pin -dir I -from 0 -to 0 probe7

  # Create instance: ila_0, and set properties
  set ila_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:ila:6.2 ila_0 ]
  set_property -dict [ list \
   CONFIG.C_DATA_DEPTH {8192} \
   CONFIG.C_ENABLE_ILA_AXI_MON {false} \
   CONFIG.C_INPUT_PIPE_STAGES {2} \
   CONFIG.C_MONITOR_TYPE {Native} \
   CONFIG.C_NUM_OF_PROBES {12} \
   CONFIG.C_PROBE0_WIDTH {16} \
   CONFIG.C_PROBE10_WIDTH {35} \
   CONFIG.C_PROBE11_WIDTH {35} \
   CONFIG.C_PROBE1_WIDTH {16} \
   CONFIG.C_PROBE2_WIDTH {16} \
   CONFIG.C_PROBE3_WIDTH {16} \
   CONFIG.C_PROBE6_WIDTH {32} \
   CONFIG.C_PROBE8_WIDTH {35} \
   CONFIG.C_PROBE9_WIDTH {35} \
 ] $ila_0

  # Create instance: xlslice_2, and set properties
  set xlslice_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_2 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {15} \
   CONFIG.DIN_WIDTH {128} \
   CONFIG.DOUT_WIDTH {16} \
 ] $xlslice_2

  # Create instance: xlslice_3, and set properties
  set xlslice_3 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_3 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {31} \
   CONFIG.DIN_TO {16} \
   CONFIG.DIN_WIDTH {128} \
   CONFIG.DOUT_WIDTH {16} \
 ] $xlslice_3

  # Create instance: xlslice_4, and set properties
  set xlslice_4 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_4 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {47} \
   CONFIG.DIN_TO {32} \
   CONFIG.DIN_WIDTH {128} \
   CONFIG.DOUT_WIDTH {16} \
 ] $xlslice_4

  # Create instance: xlslice_5, and set properties
  set xlslice_5 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_5 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {63} \
   CONFIG.DIN_TO {48} \
   CONFIG.DIN_WIDTH {128} \
   CONFIG.DOUT_WIDTH {16} \
 ] $xlslice_5

  # Create instance: xlslice_6, and set properties
  set xlslice_6 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_6 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {69} \
   CONFIG.DIN_TO {35} \
   CONFIG.DIN_WIDTH {280} \
   CONFIG.DOUT_WIDTH {35} \
 ] $xlslice_6

  # Create instance: xlslice_7, and set properties
  set xlslice_7 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_7 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {34} \
   CONFIG.DIN_WIDTH {280} \
   CONFIG.DOUT_WIDTH {35} \
 ] $xlslice_7

  # Create instance: xlslice_8, and set properties
  set xlslice_8 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_8 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {69} \
   CONFIG.DIN_TO {35} \
   CONFIG.DIN_WIDTH {280} \
   CONFIG.DOUT_WIDTH {35} \
 ] $xlslice_8

  # Create instance: xlslice_9, and set properties
  set xlslice_9 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_9 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {104} \
   CONFIG.DIN_TO {70} \
   CONFIG.DIN_WIDTH {280} \
   CONFIG.DOUT_WIDTH {35} \
 ] $xlslice_9

  # Create port connections
  connect_bd_net -net A1_ADC_LTC2311_SAMPLE_COUNTER [get_bd_pins probe6] [get_bd_pins ila_0/probe6]
  connect_bd_net -net A1_ADC_LTC2311_SI_VALID [get_bd_pins probe7] [get_bd_pins ila_0/probe7]
  connect_bd_net -net A1_ADC_LTC2311_SI_VALUE [get_bd_pins Din1] [get_bd_pins xlslice_6/Din] [get_bd_pins xlslice_7/Din] [get_bd_pins xlslice_8/Din] [get_bd_pins xlslice_9/Din]
  connect_bd_net -net ADC_LTC2311_1_RAW_VALUE [get_bd_pins Din] [get_bd_pins xlslice_2/Din] [get_bd_pins xlslice_3/Din] [get_bd_pins xlslice_4/Din] [get_bd_pins xlslice_5/Din]
  connect_bd_net -net Current_Valid_0_Dout [get_bd_pins probe4] [get_bd_pins ila_0/probe4]
  connect_bd_net -net Interrupt_muxed [get_bd_pins probe5] [get_bd_pins ila_0/probe5]
  connect_bd_net -net xlslice_2_Dout [get_bd_pins ila_0/probe0] [get_bd_pins xlslice_2/Dout]
  connect_bd_net -net xlslice_3_Dout [get_bd_pins ila_0/probe1] [get_bd_pins xlslice_3/Dout]
  connect_bd_net -net xlslice_4_Dout [get_bd_pins ila_0/probe2] [get_bd_pins xlslice_4/Dout]
  connect_bd_net -net xlslice_5_Dout [get_bd_pins ila_0/probe3] [get_bd_pins xlslice_5/Dout]
  connect_bd_net -net xlslice_6_Dout [get_bd_pins ila_0/probe9] [get_bd_pins xlslice_6/Dout]
  connect_bd_net -net xlslice_7_Dout [get_bd_pins ila_0/probe8] [get_bd_pins xlslice_7/Dout]
  connect_bd_net -net xlslice_8_Dout [get_bd_pins ila_0/probe10] [get_bd_pins xlslice_8/Dout]
  connect_bd_net -net xlslice_9_Dout [get_bd_pins ila_0/probe11] [get_bd_pins xlslice_9/Dout]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins clk] [get_bd_pins ila_0/clk]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: A3_adapter
proc create_hier_cell_A3_adapter { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_A3_adapter() - Empty argument(s)!"}
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
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 S00_AXI


  # Create pins
  create_bd_pin -dir I -from 15 -to 0 A3_IN
  create_bd_pin -dir O -from 1 -to 0 A3_OUT_CLK
  create_bd_pin -dir O -from 0 -to 0 A3_OUT_CNV_1
  create_bd_pin -dir O -from 127 -to 0 RAW_VALUE
  create_bd_pin -dir I -from 0 -to 0 TRIGGER_CNV
  create_bd_pin -dir I -type clk s00_axi_aclk
  create_bd_pin -dir I -type rst s00_axi_aresetn

  # Create instance: A3_ADC_LTC2311, and set properties
  set A3_ADC_LTC2311 [ create_bd_cell -type ip -vlnv UltraZohm:user:ADC_LTC2311:3.0 A3_ADC_LTC2311 ]
  set_property -dict [ list \
   CONFIG.DIFFERENTIAL {false} \
   CONFIG.RES_LSB {0} \
   CONFIG.RES_MSB {34} \
 ] $A3_ADC_LTC2311

  # Create instance: A3_inv_input, and set properties
  set A3_inv_input [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 A3_inv_input ]
  set_property -dict [ list \
   CONFIG.CONST_VAL {0x00} \
   CONFIG.CONST_WIDTH {8} \
 ] $A3_inv_input

  # Create instance: iobufds_inst_2, and set properties
  set block_name iobufds_inst
  set block_cell_name iobufds_inst_2
  if { [catch {set iobufds_inst_2 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $iobufds_inst_2 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create interface connections
  connect_bd_intf_net -intf_net smartconnect_0_M02_AXI [get_bd_intf_pins S00_AXI] [get_bd_intf_pins A3_ADC_LTC2311/S00_AXI]

  # Create port connections
  connect_bd_net -net A2_inv_input1_dout [get_bd_pins A3_inv_input/dout] [get_bd_pins iobufds_inst_2/INVERT_OUTPUT]
  connect_bd_net -net A3_ADC_LTC2311_SCLK [get_bd_pins A3_ADC_LTC2311/SCLK] [get_bd_pins iobufds_inst_2/SCLK_IN]
  connect_bd_net -net A3_IN_1 [get_bd_pins A3_IN] [get_bd_pins iobufds_inst_2/MISO_IN]
  connect_bd_net -net ADC_LTC2311_2_RAW_VALUE [get_bd_pins RAW_VALUE] [get_bd_pins A3_ADC_LTC2311/RAW_VALUE]
  connect_bd_net -net ADC_LTC2311_2_SS_N [get_bd_pins A3_OUT_CNV_1] [get_bd_pins A3_ADC_LTC2311/SS_N]
  connect_bd_net -net Interrupt_muxed [get_bd_pins TRIGGER_CNV] [get_bd_pins A3_ADC_LTC2311/TRIGGER_CNV]
  connect_bd_net -net iobufds_inst_2_MISO_OUT [get_bd_pins A3_ADC_LTC2311/MISO] [get_bd_pins iobufds_inst_2/MISO_OUT]
  connect_bd_net -net iobufds_inst_2_SCLK_OUT [get_bd_pins A3_OUT_CLK] [get_bd_pins iobufds_inst_2/SCLK_OUT]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins s00_axi_aresetn] [get_bd_pins A3_ADC_LTC2311/s00_axi_aresetn]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins s00_axi_aclk] [get_bd_pins A3_ADC_LTC2311/s00_axi_aclk]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: A2_adapter
proc create_hier_cell_A2_adapter { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_A2_adapter() - Empty argument(s)!"}
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
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 S00_AXI


  # Create pins
  create_bd_pin -dir I -from 15 -to 0 A2_IN
  create_bd_pin -dir O -from 1 -to 0 A2_OUT_CLK
  create_bd_pin -dir O -from 0 -to 0 A2_OUT_CNV_1
  create_bd_pin -dir O -from 127 -to 0 RAW_VALUE
  create_bd_pin -dir I -from 0 -to 0 TRIGGER_CNV
  create_bd_pin -dir I -type clk s00_axi_aclk
  create_bd_pin -dir I -type rst s00_axi_aresetn

  # Create instance: A2_ADC_LTC2311, and set properties
  set A2_ADC_LTC2311 [ create_bd_cell -type ip -vlnv UltraZohm:user:ADC_LTC2311:3.0 A2_ADC_LTC2311 ]
  set_property -dict [ list \
   CONFIG.DIFFERENTIAL {false} \
   CONFIG.RES_LSB {0} \
   CONFIG.RES_MSB {34} \
 ] $A2_ADC_LTC2311

  # Create instance: A2_inv_input, and set properties
  set A2_inv_input [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 A2_inv_input ]
  set_property -dict [ list \
   CONFIG.CONST_VAL {0x00} \
   CONFIG.CONST_WIDTH {8} \
 ] $A2_inv_input

  # Create instance: A2_iobufds_inst, and set properties
  set block_name iobufds_inst
  set block_cell_name A2_iobufds_inst
  if { [catch {set A2_iobufds_inst [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $A2_iobufds_inst eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create interface connections
  connect_bd_intf_net -intf_net smartconnect_0_M01_AXI [get_bd_intf_pins S00_AXI] [get_bd_intf_pins A2_ADC_LTC2311/S00_AXI]

  # Create port connections
  connect_bd_net -net A2_ADC_LTC2311_SCLK [get_bd_pins A2_ADC_LTC2311/SCLK] [get_bd_pins A2_iobufds_inst/SCLK_IN]
  connect_bd_net -net A2_IN_1 [get_bd_pins A2_IN] [get_bd_pins A2_iobufds_inst/MISO_IN]
  connect_bd_net -net A2_inv_input_dout [get_bd_pins A2_inv_input/dout] [get_bd_pins A2_iobufds_inst/INVERT_OUTPUT]
  connect_bd_net -net ADC_LTC2311_0_RAW_VALUE [get_bd_pins RAW_VALUE] [get_bd_pins A2_ADC_LTC2311/RAW_VALUE]
  connect_bd_net -net ADC_LTC2311_0_SS_N [get_bd_pins A2_OUT_CNV_1] [get_bd_pins A2_ADC_LTC2311/SS_N]
  connect_bd_net -net Interrupt_muxed [get_bd_pins TRIGGER_CNV] [get_bd_pins A2_ADC_LTC2311/TRIGGER_CNV]
  connect_bd_net -net iobufds_inst_1_MISO_OUT [get_bd_pins A2_ADC_LTC2311/MISO] [get_bd_pins A2_iobufds_inst/MISO_OUT]
  connect_bd_net -net iobufds_inst_1_SCLK_OUT [get_bd_pins A2_OUT_CLK] [get_bd_pins A2_iobufds_inst/SCLK_OUT]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins s00_axi_aresetn] [get_bd_pins A2_ADC_LTC2311/s00_axi_aresetn]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins s00_axi_aclk] [get_bd_pins A2_ADC_LTC2311/s00_axi_aclk]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: A1_adapter
proc create_hier_cell_A1_adapter { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_A1_adapter() - Empty argument(s)!"}
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
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 S00_AXI


  # Create pins
  create_bd_pin -dir I -from 15 -to 0 A1_IN
  create_bd_pin -dir O -from 1 -to 0 A1_OUT_CLK
  create_bd_pin -dir O -from 0 -to 0 A1_OUT_CNV_1
  create_bd_pin -dir O -from 127 -to 0 Din
  create_bd_pin -dir I -type clk clk
  create_bd_pin -dir O -from 0 -to 0 probe4
  create_bd_pin -dir I -from 0 -to 0 probe5
  create_bd_pin -dir I -type rst s00_axi_aresetn

  # Create instance: A1_ADC_LTC2311, and set properties
  set A1_ADC_LTC2311 [ create_bd_cell -type ip -vlnv UltraZohm:user:ADC_LTC2311:3.0 A1_ADC_LTC2311 ]
  set_property -dict [ list \
   CONFIG.DIFFERENTIAL {false} \
   CONFIG.RES_LSB {0} \
   CONFIG.RES_MSB {34} \
   CONFIG.SPI_MASTER {1} \
 ] $A1_ADC_LTC2311

  # Create instance: A1_inv_input, and set properties
  set A1_inv_input [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 A1_inv_input ]
  set_property -dict [ list \
   CONFIG.CONST_VAL {0x00} \
   CONFIG.CONST_WIDTH {8} \
 ] $A1_inv_input

  # Create instance: A1_iobufds_inst, and set properties
  set block_name iobufds_inst
  set block_cell_name A1_iobufds_inst
  if { [catch {set A1_iobufds_inst [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $A1_iobufds_inst eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: adc_debug
  create_hier_cell_adc_debug $hier_obj adc_debug

  # Create interface connections
  connect_bd_intf_net -intf_net smartconnect_0_M00_AXI [get_bd_intf_pins S00_AXI] [get_bd_intf_pins A1_ADC_LTC2311/S00_AXI]

  # Create port connections
  connect_bd_net -net A1_ADC_LTC2311_SAMPLE_COUNTER [get_bd_pins A1_ADC_LTC2311/SAMPLE_COUNTER] [get_bd_pins adc_debug/probe6]
  connect_bd_net -net A1_ADC_LTC2311_SCLK [get_bd_pins A1_ADC_LTC2311/SCLK] [get_bd_pins A1_iobufds_inst/SCLK_IN]
  connect_bd_net -net A1_ADC_LTC2311_SI_VALID [get_bd_pins A1_ADC_LTC2311/SI_VALID] [get_bd_pins adc_debug/probe7]
  connect_bd_net -net A1_ADC_LTC2311_SI_VALUE [get_bd_pins A1_ADC_LTC2311/SI_VALUE] [get_bd_pins adc_debug/Din1]
  connect_bd_net -net A1_IN_1 [get_bd_pins A1_IN] [get_bd_pins A1_iobufds_inst/MISO_IN]
  connect_bd_net -net ADC_LTC2311_1_RAW_VALUE [get_bd_pins Din] [get_bd_pins A1_ADC_LTC2311/RAW_VALUE] [get_bd_pins adc_debug/Din]
  connect_bd_net -net ADC_LTC2311_1_SS_N [get_bd_pins A1_OUT_CNV_1] [get_bd_pins A1_ADC_LTC2311/SS_N]
  connect_bd_net -net Current_Valid_0_Dout [get_bd_pins probe4] [get_bd_pins A1_ADC_LTC2311/RAW_VALID] [get_bd_pins adc_debug/probe4]
  connect_bd_net -net Interrupt_muxed [get_bd_pins probe5] [get_bd_pins A1_ADC_LTC2311/TRIGGER_CNV] [get_bd_pins adc_debug/probe5]
  connect_bd_net -net iobufds_inst_0_MISO_OUT [get_bd_pins A1_ADC_LTC2311/MISO] [get_bd_pins A1_iobufds_inst/MISO_OUT]
  connect_bd_net -net iobufds_inst_0_SCLK_OUT [get_bd_pins A1_OUT_CLK] [get_bd_pins A1_iobufds_inst/SCLK_OUT]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins s00_axi_aresetn] [get_bd_pins A1_ADC_LTC2311/s00_axi_aresetn]
  connect_bd_net -net xlconstant_0_dout [get_bd_pins A1_inv_input/dout] [get_bd_pins A1_iobufds_inst/INVERT_OUTPUT]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins clk] [get_bd_pins A1_ADC_LTC2311/s00_axi_aclk] [get_bd_pins adc_debug/clk]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: uz_analog_adapter
proc create_hier_cell_uz_analog_adapter { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_uz_analog_adapter() - Empty argument(s)!"}
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
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 S00_AXI

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 S00_AXI1

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 S00_AXI2


  # Create pins
  create_bd_pin -dir I -from 15 -to 0 A1_IN
  create_bd_pin -dir O -from 1 -to 0 A1_OUT_CLK
  create_bd_pin -dir O -from 0 -to 0 A1_OUT_CNV_1
  create_bd_pin -dir I -from 15 -to 0 A2_IN
  create_bd_pin -dir O -from 1 -to 0 A2_OUT_CLK
  create_bd_pin -dir O -from 0 -to 0 A2_OUT_CNV_1
  create_bd_pin -dir I -from 15 -to 0 A3_IN
  create_bd_pin -dir O -from 1 -to 0 A3_OUT_CLK
  create_bd_pin -dir O -from 0 -to 0 A3_OUT_CNV_1
  create_bd_pin -dir O -from 127 -to 0 Din
  create_bd_pin -dir O -from 127 -to 0 RAW_VALUE
  create_bd_pin -dir O -from 127 -to 0 RAW_VALUE1
  create_bd_pin -dir I -from 0 -to 0 TRIGGER_CNV
  create_bd_pin -dir O -from 0 -to 0 probe4
  create_bd_pin -dir I -type clk s00_axi_aclk
  create_bd_pin -dir I -type rst s00_axi_aresetn

  # Create instance: A1_adapter
  create_hier_cell_A1_adapter $hier_obj A1_adapter

  # Create instance: A2_adapter
  create_hier_cell_A2_adapter $hier_obj A2_adapter

  # Create instance: A3_adapter
  create_hier_cell_A3_adapter $hier_obj A3_adapter

  # Create interface connections
  connect_bd_intf_net -intf_net S00_AXI_2 [get_bd_intf_pins S00_AXI1] [get_bd_intf_pins A1_adapter/S00_AXI]
  connect_bd_intf_net -intf_net S00_AXI_3 [get_bd_intf_pins S00_AXI] [get_bd_intf_pins A3_adapter/S00_AXI]
  connect_bd_intf_net -intf_net S00_AXI_4 [get_bd_intf_pins S00_AXI2] [get_bd_intf_pins A2_adapter/S00_AXI]

  # Create port connections
  connect_bd_net -net A1_IN_1 [get_bd_pins A1_IN] [get_bd_pins A1_adapter/A1_IN]
  connect_bd_net -net A1_adapter_Din [get_bd_pins Din] [get_bd_pins A1_adapter/Din]
  connect_bd_net -net A1_adapter_probe4 [get_bd_pins probe4] [get_bd_pins A1_adapter/probe4]
  connect_bd_net -net A2_IN_1 [get_bd_pins A2_IN] [get_bd_pins A2_adapter/A2_IN]
  connect_bd_net -net A2_adapter_RAW_VALUE [get_bd_pins RAW_VALUE1] [get_bd_pins A2_adapter/RAW_VALUE]
  connect_bd_net -net A3_IN_1 [get_bd_pins A3_IN] [get_bd_pins A3_adapter/A3_IN]
  connect_bd_net -net A3_adapter_RAW_VALUE [get_bd_pins RAW_VALUE] [get_bd_pins A3_adapter/RAW_VALUE]
  connect_bd_net -net ADC_LTC2311_0_SS_N [get_bd_pins A2_OUT_CNV_1] [get_bd_pins A2_adapter/A2_OUT_CNV_1]
  connect_bd_net -net ADC_LTC2311_1_SS_N [get_bd_pins A1_OUT_CNV_1] [get_bd_pins A1_adapter/A1_OUT_CNV_1]
  connect_bd_net -net ADC_LTC2311_2_SS_N [get_bd_pins A3_OUT_CNV_1] [get_bd_pins A3_adapter/A3_OUT_CNV_1]
  connect_bd_net -net Interrupt_muxed [get_bd_pins TRIGGER_CNV] [get_bd_pins A1_adapter/probe5] [get_bd_pins A2_adapter/TRIGGER_CNV] [get_bd_pins A3_adapter/TRIGGER_CNV]
  connect_bd_net -net iobufds_inst_0_SCLK_OUT [get_bd_pins A1_OUT_CLK] [get_bd_pins A1_adapter/A1_OUT_CLK]
  connect_bd_net -net iobufds_inst_1_SCLK_OUT [get_bd_pins A2_OUT_CLK] [get_bd_pins A2_adapter/A2_OUT_CLK]
  connect_bd_net -net iobufds_inst_2_SCLK_OUT [get_bd_pins A3_OUT_CLK] [get_bd_pins A3_adapter/A3_OUT_CLK]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins s00_axi_aresetn] [get_bd_pins A1_adapter/s00_axi_aresetn] [get_bd_pins A2_adapter/s00_axi_aresetn] [get_bd_pins A3_adapter/s00_axi_aresetn]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins s00_axi_aclk] [get_bd_pins A1_adapter/clk] [get_bd_pins A2_adapter/s00_axi_aclk] [get_bd_pins A3_adapter/s00_axi_aclk]

  # Restore current instance
  current_bd_instance $oldCurInst
}


proc available_tcl_procs { } {
   puts "##################################################################"
   puts "# Available Tcl procedures to recreate hierarchical blocks:"
   puts "#"
   puts "#    create_hier_cell_uz_analog_adapter parentCell nameHier"
   puts "#    create_hier_cell_A1_adapter parentCell nameHier"
   puts "#    create_hier_cell_A2_adapter parentCell nameHier"
   puts "#    create_hier_cell_A3_adapter parentCell nameHier"
   puts "#    create_hier_cell_adc_debug parentCell nameHier"
   puts "#"
   puts "##################################################################"
}

available_tcl_procs
