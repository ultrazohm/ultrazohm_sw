
################################################################
# This is a generated script based on design: k26sys
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
# source k26sys_script.tcl

set bCheckIPsPassed 1
##################################################################
# CHECK IPs
##################################################################
set bCheckIPs 1
if { $bCheckIPs == 1 } {
   set list_check_ips "\ 
xilinx.com:ip:smartconnect:1.0\
xilinx.com:ip:xlconstant:1.1\
xilinx.com:hls:uz_fixdt_to_float:1.0\
xilinx.com:ip:xlslice:1.0\
xilinx.com:ip:uz_inverter_3ph:1.0\
xilinx.com:ip:uz_pmsm_model_6ph_dq:1.0\
xilinx.com:ip:uz_rs_flip_flop:1.0\
xilinx.com:ip:uz_sixphase_VSD_transformation:1.0\
xilinx.com:hls:uz_float_to_sfixdt:1.0\
xilinx.com:hls:uz_FOC:1.0\
xilinx.com:hls:uz_Park:1.0\
xilinx.com:hls:uz_SPWM_3ph:1.0\
xilinx.com:hls:uz_VSD_6ph_asym:1.0\
xilinx.com:hls:uz_VSDinv_6ph_asym:1.0\
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

if { $bCheckIPsPassed != 1 } {
  common::send_gid_msg -ssname BD::TCL -id 2023 -severity "WARNING" "Will not continue with creation of design due to the error(s) above."
  return 3
}

##################################################################
# DESIGN PROCs
##################################################################


# Hierarchical cell: transformation_and_control
proc create_hier_cell_transformation_and_control { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_transformation_and_control() - Empty argument(s)!"}
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
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI_FOC

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi_control

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 s_axi_control1


  # Create pins
  create_bd_pin -dir I ap_clk
  create_bd_pin -dir O ap_done
  create_bd_pin -dir I ap_rst
  create_bd_pin -dir I ap_rst_n
  create_bd_pin -dir I ap_start
  create_bd_pin -dir I -from 31 -to 0 in_a1
  create_bd_pin -dir I -from 31 -to 0 in_a2
  create_bd_pin -dir I -from 31 -to 0 in_b1
  create_bd_pin -dir I -from 31 -to 0 in_b2
  create_bd_pin -dir I -from 31 -to 0 in_c1
  create_bd_pin -dir I -from 31 -to 0 in_c2
  create_bd_pin -dir I -from 31 -to 0 in_theta_el
  create_bd_pin -dir O -from 31 -to 0 out_dc_a1
  create_bd_pin -dir O -from 31 -to 0 out_dc_a2
  create_bd_pin -dir O -from 31 -to 0 out_dc_b1
  create_bd_pin -dir O -from 31 -to 0 out_dc_b2
  create_bd_pin -dir O -from 31 -to 0 out_dc_c1
  create_bd_pin -dir O -from 31 -to 0 out_dc_c2

  # Create instance: uz_FOC_0, and set properties
  set uz_FOC_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_FOC:1.0 uz_FOC_0 ]

  # Create instance: uz_Park_0, and set properties
  set uz_Park_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_Park:1.0 uz_Park_0 ]

  # Create instance: uz_SPWM_3ph_0, and set properties
  set uz_SPWM_3ph_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_SPWM_3ph:1.0 uz_SPWM_3ph_0 ]

  # Create instance: uz_SPWM_3ph_1, and set properties
  set uz_SPWM_3ph_1 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_SPWM_3ph:1.0 uz_SPWM_3ph_1 ]

  # Create instance: uz_VSD_6ph_asym_0, and set properties
  set uz_VSD_6ph_asym_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_VSD_6ph_asym:1.0 uz_VSD_6ph_asym_0 ]

  # Create instance: uz_VSDinv_6ph_asym_0, and set properties
  set uz_VSDinv_6ph_asym_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_VSDinv_6ph_asym:1.0 uz_VSDinv_6ph_asym_0 ]

  # Create instance: xlconstant_0, and set properties
  set xlconstant_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_0 ]
  set_property CONFIG.CONST_VAL {0} $xlconstant_0


  # Create interface connections
  connect_bd_intf_net -intf_net AXI_FOC_1 [get_bd_intf_pins AXI_FOC] [get_bd_intf_pins uz_FOC_0/s_axi_control]
  connect_bd_intf_net -intf_net Conn1 [get_bd_intf_pins s_axi_control1] [get_bd_intf_pins uz_SPWM_3ph_1/s_axi_control]
  connect_bd_intf_net -intf_net s_axi_control_1 [get_bd_intf_pins s_axi_control] [get_bd_intf_pins uz_SPWM_3ph_0/s_axi_control]

  # Create port connections
  connect_bd_net -net ap_clk_1 [get_bd_pins ap_clk] [get_bd_pins uz_FOC_0/ap_clk] [get_bd_pins uz_Park_0/ap_clk] [get_bd_pins uz_SPWM_3ph_0/ap_clk] [get_bd_pins uz_SPWM_3ph_1/ap_clk] [get_bd_pins uz_VSD_6ph_asym_0/ap_clk] [get_bd_pins uz_VSDinv_6ph_asym_0/ap_clk]
  connect_bd_net -net ap_rst_1 [get_bd_pins ap_rst] [get_bd_pins uz_Park_0/ap_rst] [get_bd_pins uz_VSD_6ph_asym_0/ap_rst] [get_bd_pins uz_VSDinv_6ph_asym_0/ap_rst]
  connect_bd_net -net ap_rst_n_1 [get_bd_pins ap_rst_n] [get_bd_pins uz_FOC_0/ap_rst_n] [get_bd_pins uz_SPWM_3ph_0/ap_rst_n] [get_bd_pins uz_SPWM_3ph_1/ap_rst_n]
  connect_bd_net -net ap_start_1 [get_bd_pins ap_start] [get_bd_pins uz_VSD_6ph_asym_0/ap_start]
  connect_bd_net -net in_a1_1 [get_bd_pins in_a1] [get_bd_pins uz_VSD_6ph_asym_0/in_a1]
  connect_bd_net -net in_a2_1 [get_bd_pins in_a2] [get_bd_pins uz_VSD_6ph_asym_0/in_a2]
  connect_bd_net -net in_b1_1 [get_bd_pins in_b1] [get_bd_pins uz_VSD_6ph_asym_0/in_b1]
  connect_bd_net -net in_b2_1 [get_bd_pins in_b2] [get_bd_pins uz_VSD_6ph_asym_0/in_b2]
  connect_bd_net -net in_c1_1 [get_bd_pins in_c1] [get_bd_pins uz_VSD_6ph_asym_0/in_c1]
  connect_bd_net -net in_c2_1 [get_bd_pins in_c2] [get_bd_pins uz_VSD_6ph_asym_0/in_c2]
  connect_bd_net -net in_theta_el_1 [get_bd_pins in_theta_el] [get_bd_pins uz_Park_0/theta_el]
  connect_bd_net -net uz_FOC_0_ap_done [get_bd_pins uz_FOC_0/ap_done] [get_bd_pins uz_VSDinv_6ph_asym_0/ap_start]
  connect_bd_net -net uz_FOC_0_ud_ref [get_bd_pins uz_FOC_0/ud_ref] [get_bd_pins uz_Park_0/in_inv_d]
  connect_bd_net -net uz_FOC_0_uq_ref [get_bd_pins uz_FOC_0/uq_ref] [get_bd_pins uz_Park_0/in_inv_q]
  connect_bd_net -net uz_Park_0_ap_done [get_bd_pins uz_FOC_0/ap_start] [get_bd_pins uz_Park_0/ap_done]
  connect_bd_net -net uz_Park_0_out_inv_alpha [get_bd_pins uz_Park_0/out_inv_alpha] [get_bd_pins uz_VSDinv_6ph_asym_0/in_alpha]
  connect_bd_net -net uz_Park_0_out_inv_beta [get_bd_pins uz_Park_0/out_inv_beta] [get_bd_pins uz_VSDinv_6ph_asym_0/in_beta]
  connect_bd_net -net uz_Park_0_out_trafo_d [get_bd_pins uz_FOC_0/id_actual] [get_bd_pins uz_Park_0/out_trafo_d]
  connect_bd_net -net uz_Park_0_out_trafo_q [get_bd_pins uz_FOC_0/iq_actual] [get_bd_pins uz_Park_0/out_trafo_q]
  connect_bd_net -net uz_SPWM_3ph_0_DC_a [get_bd_pins out_dc_a1] [get_bd_pins uz_SPWM_3ph_0/DC_a]
  connect_bd_net -net uz_SPWM_3ph_0_DC_b [get_bd_pins out_dc_b1] [get_bd_pins uz_SPWM_3ph_0/DC_b]
  connect_bd_net -net uz_SPWM_3ph_0_DC_c [get_bd_pins out_dc_c1] [get_bd_pins uz_SPWM_3ph_0/DC_c]
  connect_bd_net -net uz_SPWM_3ph_0_ap_done [get_bd_pins ap_done] [get_bd_pins uz_SPWM_3ph_0/ap_done]
  connect_bd_net -net uz_SPWM_3ph_1_DC_a [get_bd_pins out_dc_a2] [get_bd_pins uz_SPWM_3ph_1/DC_a]
  connect_bd_net -net uz_SPWM_3ph_1_DC_b [get_bd_pins out_dc_b2] [get_bd_pins uz_SPWM_3ph_1/DC_b]
  connect_bd_net -net uz_SPWM_3ph_1_DC_c [get_bd_pins out_dc_c2] [get_bd_pins uz_SPWM_3ph_1/DC_c]
  connect_bd_net -net uz_VSD_6ph_asym_0_ap_done [get_bd_pins uz_Park_0/ap_start] [get_bd_pins uz_VSD_6ph_asym_0/ap_done]
  connect_bd_net -net uz_VSD_6ph_asym_0_out_alpha [get_bd_pins uz_Park_0/in_trafo_alpha] [get_bd_pins uz_VSD_6ph_asym_0/out_alpha]
  connect_bd_net -net uz_VSD_6ph_asym_0_out_beta [get_bd_pins uz_Park_0/in_trafo_beta] [get_bd_pins uz_VSD_6ph_asym_0/out_beta]
  connect_bd_net -net uz_VSDinv_6ph_asym_0_ap_done [get_bd_pins uz_SPWM_3ph_0/ap_start] [get_bd_pins uz_SPWM_3ph_1/ap_start] [get_bd_pins uz_VSDinv_6ph_asym_0/ap_done]
  connect_bd_net -net uz_VSDinv_6ph_asym_0_out_a1 [get_bd_pins uz_SPWM_3ph_0/u_a] [get_bd_pins uz_VSDinv_6ph_asym_0/out_a1]
  connect_bd_net -net uz_VSDinv_6ph_asym_0_out_a2 [get_bd_pins uz_SPWM_3ph_1/u_a] [get_bd_pins uz_VSDinv_6ph_asym_0/out_a2]
  connect_bd_net -net uz_VSDinv_6ph_asym_0_out_b1 [get_bd_pins uz_SPWM_3ph_0/u_b] [get_bd_pins uz_VSDinv_6ph_asym_0/out_b1]
  connect_bd_net -net uz_VSDinv_6ph_asym_0_out_b2 [get_bd_pins uz_SPWM_3ph_1/u_b] [get_bd_pins uz_VSDinv_6ph_asym_0/out_b2]
  connect_bd_net -net uz_VSDinv_6ph_asym_0_out_c1 [get_bd_pins uz_SPWM_3ph_0/u_c] [get_bd_pins uz_VSDinv_6ph_asym_0/out_c1]
  connect_bd_net -net uz_VSDinv_6ph_asym_0_out_c2 [get_bd_pins uz_SPWM_3ph_1/u_c] [get_bd_pins uz_VSDinv_6ph_asym_0/out_c2]
  connect_bd_net -net xlconstant_0_dout [get_bd_pins uz_FOC_0/reset_PL] [get_bd_pins xlconstant_0/dout]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: float_to_fix_dutycycle
proc create_hier_cell_float_to_fix_dutycycle { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_float_to_fix_dutycycle() - Empty argument(s)!"}
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
  create_bd_pin -dir I clk
  create_bd_pin -dir I -from 31 -to 0 in_0
  create_bd_pin -dir I -from 31 -to 0 in_1
  create_bd_pin -dir I -from 31 -to 0 in_2
  create_bd_pin -dir I -from 31 -to 0 in_3
  create_bd_pin -dir I -from 31 -to 0 in_4
  create_bd_pin -dir I -from 31 -to 0 in_5
  create_bd_pin -dir O -from 31 -to 0 out_0
  create_bd_pin -dir O -from 31 -to 0 out_1
  create_bd_pin -dir O -from 31 -to 0 out_2
  create_bd_pin -dir O -from 31 -to 0 out_3
  create_bd_pin -dir O -from 31 -to 0 out_4
  create_bd_pin -dir O -from 31 -to 0 out_5
  create_bd_pin -dir I rst
  create_bd_pin -dir I sp_start

  # Create instance: dutycycle_fraction, and set properties
  set dutycycle_fraction [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 dutycycle_fraction ]
  set_property -dict [list \
    CONFIG.CONST_VAL {12} \
    CONFIG.CONST_WIDTH {8} \
  ] $dutycycle_fraction


  # Create instance: uz_float_to_sfixdt_0, and set properties
  set uz_float_to_sfixdt_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_float_to_sfixdt:1.0 uz_float_to_sfixdt_0 ]

  # Create instance: uz_float_to_sfixdt_1, and set properties
  set uz_float_to_sfixdt_1 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_float_to_sfixdt:1.0 uz_float_to_sfixdt_1 ]

  # Create instance: uz_float_to_sfixdt_2, and set properties
  set uz_float_to_sfixdt_2 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_float_to_sfixdt:1.0 uz_float_to_sfixdt_2 ]

  # Create instance: uz_float_to_sfixdt_3, and set properties
  set uz_float_to_sfixdt_3 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_float_to_sfixdt:1.0 uz_float_to_sfixdt_3 ]

  # Create instance: uz_float_to_sfixdt_4, and set properties
  set uz_float_to_sfixdt_4 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_float_to_sfixdt:1.0 uz_float_to_sfixdt_4 ]

  # Create instance: uz_float_to_sfixdt_5, and set properties
  set uz_float_to_sfixdt_5 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_float_to_sfixdt:1.0 uz_float_to_sfixdt_5 ]

  # Create port connections
  connect_bd_net -net Net [get_bd_pins clk] [get_bd_pins uz_float_to_sfixdt_0/ap_clk] [get_bd_pins uz_float_to_sfixdt_1/ap_clk] [get_bd_pins uz_float_to_sfixdt_2/ap_clk] [get_bd_pins uz_float_to_sfixdt_3/ap_clk] [get_bd_pins uz_float_to_sfixdt_4/ap_clk] [get_bd_pins uz_float_to_sfixdt_5/ap_clk]
  connect_bd_net -net Net1 [get_bd_pins rst] [get_bd_pins uz_float_to_sfixdt_0/ap_rst] [get_bd_pins uz_float_to_sfixdt_1/ap_rst] [get_bd_pins uz_float_to_sfixdt_2/ap_rst] [get_bd_pins uz_float_to_sfixdt_3/ap_rst] [get_bd_pins uz_float_to_sfixdt_4/ap_rst] [get_bd_pins uz_float_to_sfixdt_5/ap_rst]
  connect_bd_net -net Net2 [get_bd_pins sp_start] [get_bd_pins uz_float_to_sfixdt_0/ap_start] [get_bd_pins uz_float_to_sfixdt_1/ap_start] [get_bd_pins uz_float_to_sfixdt_2/ap_start] [get_bd_pins uz_float_to_sfixdt_3/ap_start] [get_bd_pins uz_float_to_sfixdt_4/ap_start] [get_bd_pins uz_float_to_sfixdt_5/ap_start]
  connect_bd_net -net dutycycle_fraction_dout [get_bd_pins dutycycle_fraction/dout] [get_bd_pins uz_float_to_sfixdt_0/fraction] [get_bd_pins uz_float_to_sfixdt_1/fraction] [get_bd_pins uz_float_to_sfixdt_2/fraction] [get_bd_pins uz_float_to_sfixdt_3/fraction] [get_bd_pins uz_float_to_sfixdt_4/fraction] [get_bd_pins uz_float_to_sfixdt_5/fraction]
  connect_bd_net -net in_0_1 [get_bd_pins in_0] [get_bd_pins uz_float_to_sfixdt_0/in_float]
  connect_bd_net -net in_1_1 [get_bd_pins in_1] [get_bd_pins uz_float_to_sfixdt_1/in_float]
  connect_bd_net -net in_2_1 [get_bd_pins in_2] [get_bd_pins uz_float_to_sfixdt_2/in_float]
  connect_bd_net -net in_3_1 [get_bd_pins in_3] [get_bd_pins uz_float_to_sfixdt_3/in_float]
  connect_bd_net -net in_4_1 [get_bd_pins in_4] [get_bd_pins uz_float_to_sfixdt_4/in_float]
  connect_bd_net -net in_5_1 [get_bd_pins in_5] [get_bd_pins uz_float_to_sfixdt_5/in_float]
  connect_bd_net -net uz_float_to_sfixdt_0_out_sfix [get_bd_pins out_0] [get_bd_pins uz_float_to_sfixdt_0/out_sfix]
  connect_bd_net -net uz_float_to_sfixdt_1_out_sfix [get_bd_pins out_1] [get_bd_pins uz_float_to_sfixdt_1/out_sfix]
  connect_bd_net -net uz_float_to_sfixdt_2_out_sfix [get_bd_pins out_2] [get_bd_pins uz_float_to_sfixdt_2/out_sfix]
  connect_bd_net -net uz_float_to_sfixdt_3_out_sfix [get_bd_pins out_3] [get_bd_pins uz_float_to_sfixdt_3/out_sfix]
  connect_bd_net -net uz_float_to_sfixdt_4_out_sfix [get_bd_pins out_4] [get_bd_pins uz_float_to_sfixdt_4/out_sfix]
  connect_bd_net -net uz_float_to_sfixdt_5_out_sfix [get_bd_pins out_5] [get_bd_pins uz_float_to_sfixdt_5/out_sfix]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: fix_to_float_current
proc create_hier_cell_fix_to_float_current { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_fix_to_float_current() - Empty argument(s)!"}
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
  create_bd_pin -dir O ap_done
  create_bd_pin -dir I clk
  create_bd_pin -dir I -from 26 -to 0 in_0
  create_bd_pin -dir I -from 26 -to 0 in_1
  create_bd_pin -dir I -from 26 -to 0 in_2
  create_bd_pin -dir I -from 26 -to 0 in_3
  create_bd_pin -dir I -from 26 -to 0 in_4
  create_bd_pin -dir I -from 26 -to 0 in_5
  create_bd_pin -dir O -from 31 -to 0 out_0
  create_bd_pin -dir O -from 31 -to 0 out_1
  create_bd_pin -dir O -from 31 -to 0 out_2
  create_bd_pin -dir O -from 31 -to 0 out_3
  create_bd_pin -dir O -from 31 -to 0 out_4
  create_bd_pin -dir O -from 31 -to 0 out_5
  create_bd_pin -dir I rst
  create_bd_pin -dir I sp_start

  # Create instance: current_fraction, and set properties
  set current_fraction [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 current_fraction ]
  set_property -dict [list \
    CONFIG.CONST_VAL {18} \
    CONFIG.CONST_WIDTH {8} \
  ] $current_fraction


  # Create instance: current_sign, and set properties
  set current_sign [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 current_sign ]

  # Create instance: current_word, and set properties
  set current_word [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 current_word ]
  set_property -dict [list \
    CONFIG.CONST_VAL {27} \
    CONFIG.CONST_WIDTH {8} \
  ] $current_word


  # Create instance: uz_fixdt_to_float_0, and set properties
  set uz_fixdt_to_float_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_fixdt_to_float:1.0 uz_fixdt_to_float_0 ]

  # Create instance: uz_fixdt_to_float_1, and set properties
  set uz_fixdt_to_float_1 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_fixdt_to_float:1.0 uz_fixdt_to_float_1 ]

  # Create instance: uz_fixdt_to_float_2, and set properties
  set uz_fixdt_to_float_2 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_fixdt_to_float:1.0 uz_fixdt_to_float_2 ]

  # Create instance: uz_fixdt_to_float_3, and set properties
  set uz_fixdt_to_float_3 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_fixdt_to_float:1.0 uz_fixdt_to_float_3 ]

  # Create instance: uz_fixdt_to_float_4, and set properties
  set uz_fixdt_to_float_4 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_fixdt_to_float:1.0 uz_fixdt_to_float_4 ]

  # Create instance: uz_fixdt_to_float_5, and set properties
  set uz_fixdt_to_float_5 [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_fixdt_to_float:1.0 uz_fixdt_to_float_5 ]

  # Create port connections
  connect_bd_net -net Net [get_bd_pins clk] [get_bd_pins uz_fixdt_to_float_0/ap_clk] [get_bd_pins uz_fixdt_to_float_1/ap_clk] [get_bd_pins uz_fixdt_to_float_2/ap_clk] [get_bd_pins uz_fixdt_to_float_3/ap_clk] [get_bd_pins uz_fixdt_to_float_4/ap_clk] [get_bd_pins uz_fixdt_to_float_5/ap_clk]
  connect_bd_net -net Net1 [get_bd_pins rst] [get_bd_pins uz_fixdt_to_float_0/ap_rst] [get_bd_pins uz_fixdt_to_float_1/ap_rst] [get_bd_pins uz_fixdt_to_float_2/ap_rst] [get_bd_pins uz_fixdt_to_float_3/ap_rst] [get_bd_pins uz_fixdt_to_float_4/ap_rst] [get_bd_pins uz_fixdt_to_float_5/ap_rst]
  connect_bd_net -net Net2 [get_bd_pins sp_start] [get_bd_pins uz_fixdt_to_float_0/ap_start] [get_bd_pins uz_fixdt_to_float_1/ap_start] [get_bd_pins uz_fixdt_to_float_2/ap_start] [get_bd_pins uz_fixdt_to_float_3/ap_start] [get_bd_pins uz_fixdt_to_float_4/ap_start] [get_bd_pins uz_fixdt_to_float_5/ap_start]
  connect_bd_net -net current_fraction_dout [get_bd_pins current_fraction/dout] [get_bd_pins uz_fixdt_to_float_0/fraction] [get_bd_pins uz_fixdt_to_float_1/fraction] [get_bd_pins uz_fixdt_to_float_2/fraction] [get_bd_pins uz_fixdt_to_float_3/fraction] [get_bd_pins uz_fixdt_to_float_4/fraction] [get_bd_pins uz_fixdt_to_float_5/fraction]
  connect_bd_net -net current_sign_dout [get_bd_pins current_sign/dout] [get_bd_pins uz_fixdt_to_float_0/sign] [get_bd_pins uz_fixdt_to_float_1/sign] [get_bd_pins uz_fixdt_to_float_2/sign] [get_bd_pins uz_fixdt_to_float_3/sign] [get_bd_pins uz_fixdt_to_float_4/sign] [get_bd_pins uz_fixdt_to_float_5/sign]
  connect_bd_net -net current_word_dout [get_bd_pins current_word/dout] [get_bd_pins uz_fixdt_to_float_0/word] [get_bd_pins uz_fixdt_to_float_1/word] [get_bd_pins uz_fixdt_to_float_2/word] [get_bd_pins uz_fixdt_to_float_3/word] [get_bd_pins uz_fixdt_to_float_4/word] [get_bd_pins uz_fixdt_to_float_5/word]
  connect_bd_net -net in_0_1 [get_bd_pins in_0] [get_bd_pins uz_fixdt_to_float_0/in_fixed]
  connect_bd_net -net in_1_1 [get_bd_pins in_1] [get_bd_pins uz_fixdt_to_float_1/in_fixed]
  connect_bd_net -net in_2_1 [get_bd_pins in_2] [get_bd_pins uz_fixdt_to_float_2/in_fixed]
  connect_bd_net -net in_3_1 [get_bd_pins in_3] [get_bd_pins uz_fixdt_to_float_3/in_fixed]
  connect_bd_net -net in_4_1 [get_bd_pins in_4] [get_bd_pins uz_fixdt_to_float_4/in_fixed]
  connect_bd_net -net in_5_1 [get_bd_pins in_5] [get_bd_pins uz_fixdt_to_float_5/in_fixed]
  connect_bd_net -net uz_fixdt_to_float_0_ap_done [get_bd_pins ap_done] [get_bd_pins uz_fixdt_to_float_0/ap_done]
  connect_bd_net -net uz_fixdt_to_float_0_out_float [get_bd_pins out_0] [get_bd_pins uz_fixdt_to_float_0/out_float]
  connect_bd_net -net uz_fixdt_to_float_1_out_float [get_bd_pins out_1] [get_bd_pins uz_fixdt_to_float_1/out_float]
  connect_bd_net -net uz_fixdt_to_float_2_out_float [get_bd_pins out_2] [get_bd_pins uz_fixdt_to_float_2/out_float]
  connect_bd_net -net uz_fixdt_to_float_3_out_float [get_bd_pins out_3] [get_bd_pins uz_fixdt_to_float_3/out_float]
  connect_bd_net -net uz_fixdt_to_float_4_out_float [get_bd_pins out_4] [get_bd_pins uz_fixdt_to_float_4/out_float]
  connect_bd_net -net uz_fixdt_to_float_5_out_float [get_bd_pins out_5] [get_bd_pins uz_fixdt_to_float_5/out_float]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: CIL
proc create_hier_cell_CIL { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_CIL() - Empty argument(s)!"}
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
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn
  create_bd_pin -dir I ff_set
  create_bd_pin -dir I -from 5 -to 0 gate_pl_0
  create_bd_pin -dir I -from 5 -to 0 gate_pl_1
  create_bd_pin -dir O -from 80 -to 0 i_abc_pl_0
  create_bd_pin -dir O -from 17 -to 0 theta_el
  create_bd_pin -dir O -from 80 -to 0 x_abc_2_0

  # Create instance: smartconnect_0, and set properties
  set smartconnect_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:smartconnect:1.0 smartconnect_0 ]
  set_property -dict [list \
    CONFIG.NUM_MI {4} \
    CONFIG.NUM_SI {1} \
  ] $smartconnect_0


  # Create instance: uz_inverter_3ph_0, and set properties
  set uz_inverter_3ph_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:uz_inverter_3ph:1.0 uz_inverter_3ph_0 ]

  # Create instance: uz_inverter_3ph_1, and set properties
  set uz_inverter_3ph_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:uz_inverter_3ph:1.0 uz_inverter_3ph_1 ]

  # Create instance: uz_pmsm_model_6ph_dq_0, and set properties
  set uz_pmsm_model_6ph_dq_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:uz_pmsm_model_6ph_dq:1.0 uz_pmsm_model_6ph_dq_0 ]

  # Create instance: uz_rs_flip_flop_0, and set properties
  set uz_rs_flip_flop_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:uz_rs_flip_flop:1.0 uz_rs_flip_flop_0 ]

  # Create instance: uz_sixphase_VSD_tran_0, and set properties
  set uz_sixphase_VSD_tran_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:uz_sixphase_VSD_transformation:1.0 uz_sixphase_VSD_tran_0 ]

  # Create interface connections
  connect_bd_intf_net -intf_net Conn1 [get_bd_intf_pins S00_AXI] [get_bd_intf_pins smartconnect_0/S00_AXI]
  connect_bd_intf_net -intf_net smartconnect_0_M00_AXI [get_bd_intf_pins smartconnect_0/M00_AXI] [get_bd_intf_pins uz_pmsm_model_6ph_dq_0/AXI4]
  connect_bd_intf_net -intf_net smartconnect_0_M01_AXI [get_bd_intf_pins smartconnect_0/M01_AXI] [get_bd_intf_pins uz_sixphase_VSD_tran_0/AXI4]
  connect_bd_intf_net -intf_net smartconnect_0_M02_AXI [get_bd_intf_pins smartconnect_0/M02_AXI] [get_bd_intf_pins uz_inverter_3ph_0/AXI4]
  connect_bd_intf_net -intf_net smartconnect_0_M03_AXI [get_bd_intf_pins smartconnect_0/M03_AXI] [get_bd_intf_pins uz_inverter_3ph_1/AXI4]

  # Create port connections
  connect_bd_net -net ff_set_1 [get_bd_pins ff_set] [get_bd_pins uz_rs_flip_flop_0/ff_set]
  connect_bd_net -net gate_pl_0_1 [get_bd_pins gate_pl_0] [get_bd_pins uz_inverter_3ph_0/gate_pl_0]
  connect_bd_net -net gate_pl_1_1 [get_bd_pins gate_pl_1] [get_bd_pins uz_inverter_3ph_1/gate_pl_0]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins aresetn] [get_bd_pins smartconnect_0/aresetn] [get_bd_pins uz_inverter_3ph_0/AXI4_ARESETN] [get_bd_pins uz_inverter_3ph_0/IPCORE_RESETN] [get_bd_pins uz_inverter_3ph_1/AXI4_ARESETN] [get_bd_pins uz_inverter_3ph_1/IPCORE_RESETN] [get_bd_pins uz_pmsm_model_6ph_dq_0/AXI4_ARESETN] [get_bd_pins uz_pmsm_model_6ph_dq_0/IPCORE_RESETN] [get_bd_pins uz_rs_flip_flop_0/IPCORE_RESETN] [get_bd_pins uz_sixphase_VSD_tran_0/AXI4_ARESETN] [get_bd_pins uz_sixphase_VSD_tran_0/IPCORE_RESETN]
  connect_bd_net -net uz_inverter_3ph_0_u_abc_pl_0 [get_bd_pins uz_inverter_3ph_0/u_abc_pl_0] [get_bd_pins uz_sixphase_VSD_tran_0/x_abc1_ll_pl_0]
  connect_bd_net -net uz_inverter_3ph_1_u_abc_pl_0 [get_bd_pins uz_inverter_3ph_1/u_abc_pl_0] [get_bd_pins uz_sixphase_VSD_tran_0/x_abc2_ll_pl_0]
  connect_bd_net -net uz_pmsm_model_6ph_dq_0_currents_dq_out_0 [get_bd_pins uz_pmsm_model_6ph_dq_0/currents_dq_out_0] [get_bd_pins uz_sixphase_VSD_tran_0/x_in_dq_0]
  connect_bd_net -net uz_pmsm_model_6ph_dq_0_theta_el_out [get_bd_pins theta_el] [get_bd_pins uz_pmsm_model_6ph_dq_0/theta_el_out] [get_bd_pins uz_sixphase_VSD_tran_0/theta_el]
  connect_bd_net -net uz_rs_flip_flop_0_ff_out [get_bd_pins uz_rs_flip_flop_0/ff_out] [get_bd_pins uz_sixphase_VSD_tran_0/trigger_new_values]
  connect_bd_net -net uz_sixphase_VSD_tran_0_refresh_values [get_bd_pins uz_rs_flip_flop_0/ff_reset] [get_bd_pins uz_sixphase_VSD_tran_0/refresh_values]
  connect_bd_net -net uz_sixphase_VSD_tran_0_x_abc_1_0 [get_bd_pins i_abc_pl_0] [get_bd_pins uz_inverter_3ph_0/i_abc_pl_0] [get_bd_pins uz_sixphase_VSD_tran_0/x_abc_1_0]
  connect_bd_net -net uz_sixphase_VSD_tran_0_x_abc_2_0 [get_bd_pins x_abc_2_0] [get_bd_pins uz_inverter_3ph_1/i_abc_pl_0] [get_bd_pins uz_sixphase_VSD_tran_0/x_abc_2_0]
  connect_bd_net -net uz_sixphase_VSD_tran_0_x_out_dq_0 [get_bd_pins uz_pmsm_model_6ph_dq_0/voltage_input_dq_0] [get_bd_pins uz_sixphase_VSD_tran_0/x_out_dq_0]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins aclk] [get_bd_pins smartconnect_0/aclk] [get_bd_pins uz_inverter_3ph_0/AXI4_ACLK] [get_bd_pins uz_inverter_3ph_0/IPCORE_CLK] [get_bd_pins uz_inverter_3ph_1/AXI4_ACLK] [get_bd_pins uz_inverter_3ph_1/IPCORE_CLK] [get_bd_pins uz_pmsm_model_6ph_dq_0/AXI4_ACLK] [get_bd_pins uz_pmsm_model_6ph_dq_0/IPCORE_CLK] [get_bd_pins uz_rs_flip_flop_0/IPCORE_CLK] [get_bd_pins uz_sixphase_VSD_tran_0/AXI4_ACLK] [get_bd_pins uz_sixphase_VSD_tran_0/IPCORE_CLK]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: uz_user
proc create_hier_cell_uz_user { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_uz_user() - Empty argument(s)!"}
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
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn
  create_bd_pin -dir I ff_set
  create_bd_pin -dir I -from 5 -to 0 gate_pl_0
  create_bd_pin -dir I -from 5 -to 0 gate_pl_1
  create_bd_pin -dir O -from 31 -to 0 out_0
  create_bd_pin -dir O -from 31 -to 0 out_1
  create_bd_pin -dir O -from 31 -to 0 out_2
  create_bd_pin -dir O -from 31 -to 0 out_3
  create_bd_pin -dir O -from 31 -to 0 out_4
  create_bd_pin -dir O -from 31 -to 0 out_5

  # Create instance: CIL
  create_hier_cell_CIL $hier_obj CIL

  # Create instance: fix_to_float_current
  create_hier_cell_fix_to_float_current $hier_obj fix_to_float_current

  # Create instance: float_to_fix_dutycycle
  create_hier_cell_float_to_fix_dutycycle $hier_obj float_to_fix_dutycycle

  # Create instance: smartconnect_1, and set properties
  set smartconnect_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:smartconnect:1.0 smartconnect_1 ]
  set_property -dict [list \
    CONFIG.NUM_MI {4} \
    CONFIG.NUM_SI {1} \
  ] $smartconnect_1


  # Create instance: theta_fraction, and set properties
  set theta_fraction [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 theta_fraction ]
  set_property -dict [list \
    CONFIG.CONST_VAL {14} \
    CONFIG.CONST_WIDTH {8} \
  ] $theta_fraction


  # Create instance: theta_sign, and set properties
  set theta_sign [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 theta_sign ]

  # Create instance: theta_word, and set properties
  set theta_word [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 theta_word ]
  set_property -dict [list \
    CONFIG.CONST_VAL {18} \
    CONFIG.CONST_WIDTH {8} \
  ] $theta_word


  # Create instance: transformation_and_control
  create_hier_cell_transformation_and_control $hier_obj transformation_and_control

  # Create instance: uz_fixdt_to_float_theta, and set properties
  set uz_fixdt_to_float_theta [ create_bd_cell -type ip -vlnv xilinx.com:hls:uz_fixdt_to_float:1.0 uz_fixdt_to_float_theta ]

  # Create instance: xlconstant_0, and set properties
  set xlconstant_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_0 ]
  set_property CONFIG.CONST_VAL {0} $xlconstant_0


  # Create instance: xlslice_0, and set properties
  set xlslice_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_0 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {26} \
    CONFIG.DIN_WIDTH {81} \
  ] $xlslice_0


  # Create instance: xlslice_1, and set properties
  set xlslice_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_1 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {53} \
    CONFIG.DIN_TO {27} \
    CONFIG.DIN_WIDTH {81} \
  ] $xlslice_1


  # Create instance: xlslice_2, and set properties
  set xlslice_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_2 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {80} \
    CONFIG.DIN_TO {54} \
    CONFIG.DIN_WIDTH {81} \
  ] $xlslice_2


  # Create instance: xlslice_3, and set properties
  set xlslice_3 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_3 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {26} \
    CONFIG.DIN_WIDTH {81} \
  ] $xlslice_3


  # Create instance: xlslice_4, and set properties
  set xlslice_4 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_4 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {53} \
    CONFIG.DIN_TO {27} \
    CONFIG.DIN_WIDTH {81} \
  ] $xlslice_4


  # Create instance: xlslice_5, and set properties
  set xlslice_5 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_5 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {80} \
    CONFIG.DIN_TO {54} \
    CONFIG.DIN_WIDTH {81} \
  ] $xlslice_5


  # Create interface connections
  connect_bd_intf_net -intf_net AXI_FOC_1 [get_bd_intf_pins smartconnect_1/M01_AXI] [get_bd_intf_pins transformation_and_control/AXI_FOC]
  connect_bd_intf_net -intf_net smartconnect_0_M10_AXI [get_bd_intf_pins S00_AXI] [get_bd_intf_pins smartconnect_1/S00_AXI]
  connect_bd_intf_net -intf_net smartconnect_1_M00_AXI [get_bd_intf_pins CIL/S00_AXI] [get_bd_intf_pins smartconnect_1/M00_AXI]
  connect_bd_intf_net -intf_net smartconnect_1_M02_AXI [get_bd_intf_pins smartconnect_1/M02_AXI] [get_bd_intf_pins transformation_and_control/s_axi_control]
  connect_bd_intf_net -intf_net smartconnect_1_M03_AXI [get_bd_intf_pins smartconnect_1/M03_AXI] [get_bd_intf_pins transformation_and_control/s_axi_control1]

  # Create port connections
  connect_bd_net -net ff_set_1 [get_bd_pins ff_set] [get_bd_pins CIL/ff_set] [get_bd_pins fix_to_float_current/sp_start] [get_bd_pins uz_fixdt_to_float_theta/ap_start]
  connect_bd_net -net fix_to_float_current_ap_done [get_bd_pins fix_to_float_current/ap_done] [get_bd_pins transformation_and_control/ap_start]
  connect_bd_net -net fix_to_float_current_out_0 [get_bd_pins fix_to_float_current/out_0] [get_bd_pins transformation_and_control/in_a1]
  connect_bd_net -net fix_to_float_current_out_1 [get_bd_pins fix_to_float_current/out_1] [get_bd_pins transformation_and_control/in_b1]
  connect_bd_net -net fix_to_float_current_out_2 [get_bd_pins fix_to_float_current/out_2] [get_bd_pins transformation_and_control/in_c1]
  connect_bd_net -net fix_to_float_current_out_3 [get_bd_pins fix_to_float_current/out_3] [get_bd_pins transformation_and_control/in_a2]
  connect_bd_net -net fix_to_float_current_out_4 [get_bd_pins fix_to_float_current/out_4] [get_bd_pins transformation_and_control/in_b2]
  connect_bd_net -net fix_to_float_current_out_5 [get_bd_pins fix_to_float_current/out_5] [get_bd_pins transformation_and_control/in_c2]
  connect_bd_net -net float_to_fix_dutycycle_out_0 [get_bd_pins out_0] [get_bd_pins float_to_fix_dutycycle/out_0]
  connect_bd_net -net float_to_fix_dutycycle_out_1 [get_bd_pins out_1] [get_bd_pins float_to_fix_dutycycle/out_1]
  connect_bd_net -net float_to_fix_dutycycle_out_2 [get_bd_pins out_2] [get_bd_pins float_to_fix_dutycycle/out_2]
  connect_bd_net -net float_to_fix_dutycycle_out_3 [get_bd_pins out_3] [get_bd_pins float_to_fix_dutycycle/out_3]
  connect_bd_net -net float_to_fix_dutycycle_out_4 [get_bd_pins out_4] [get_bd_pins float_to_fix_dutycycle/out_4]
  connect_bd_net -net float_to_fix_dutycycle_out_5 [get_bd_pins out_5] [get_bd_pins float_to_fix_dutycycle/out_5]
  connect_bd_net -net gate_pl_0_1 [get_bd_pins gate_pl_0] [get_bd_pins CIL/gate_pl_0]
  connect_bd_net -net gate_pl_1_1 [get_bd_pins gate_pl_1] [get_bd_pins CIL/gate_pl_1]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins aresetn] [get_bd_pins CIL/aresetn] [get_bd_pins smartconnect_1/aresetn] [get_bd_pins transformation_and_control/ap_rst_n]
  connect_bd_net -net rst_1 [get_bd_pins fix_to_float_current/rst] [get_bd_pins float_to_fix_dutycycle/rst] [get_bd_pins transformation_and_control/ap_rst] [get_bd_pins uz_fixdt_to_float_theta/ap_rst] [get_bd_pins xlconstant_0/dout]
  connect_bd_net -net theta_fraction_dout [get_bd_pins theta_fraction/dout] [get_bd_pins uz_fixdt_to_float_theta/fraction]
  connect_bd_net -net theta_sign_dout [get_bd_pins theta_sign/dout] [get_bd_pins uz_fixdt_to_float_theta/sign]
  connect_bd_net -net theta_word_dout [get_bd_pins theta_word/dout] [get_bd_pins uz_fixdt_to_float_theta/word]
  connect_bd_net -net transformation_and_control_ap_done [get_bd_pins float_to_fix_dutycycle/sp_start] [get_bd_pins transformation_and_control/ap_done]
  connect_bd_net -net transformation_and_control_out_dc_a1 [get_bd_pins float_to_fix_dutycycle/in_0] [get_bd_pins transformation_and_control/out_dc_a1]
  connect_bd_net -net transformation_and_control_out_dc_a2 [get_bd_pins float_to_fix_dutycycle/in_3] [get_bd_pins transformation_and_control/out_dc_a2]
  connect_bd_net -net transformation_and_control_out_dc_b1 [get_bd_pins float_to_fix_dutycycle/in_1] [get_bd_pins transformation_and_control/out_dc_b1]
  connect_bd_net -net transformation_and_control_out_dc_b2 [get_bd_pins float_to_fix_dutycycle/in_4] [get_bd_pins transformation_and_control/out_dc_b2]
  connect_bd_net -net transformation_and_control_out_dc_c1 [get_bd_pins float_to_fix_dutycycle/in_2] [get_bd_pins transformation_and_control/out_dc_c1]
  connect_bd_net -net transformation_and_control_out_dc_c2 [get_bd_pins float_to_fix_dutycycle/in_5] [get_bd_pins transformation_and_control/out_dc_c2]
  connect_bd_net -net uz_fixdt_to_float_theta_out_float [get_bd_pins transformation_and_control/in_theta_el] [get_bd_pins uz_fixdt_to_float_theta/out_float]
  connect_bd_net -net uz_pmsm_model_6ph_dq_0_theta_el_out [get_bd_pins CIL/theta_el] [get_bd_pins uz_fixdt_to_float_theta/in_fixed]
  connect_bd_net -net uz_sixphase_VSD_tran_0_x_abc_1_0 [get_bd_pins CIL/i_abc_pl_0] [get_bd_pins xlslice_0/Din] [get_bd_pins xlslice_1/Din] [get_bd_pins xlslice_2/Din]
  connect_bd_net -net uz_sixphase_VSD_tran_0_x_abc_2_0 [get_bd_pins CIL/x_abc_2_0] [get_bd_pins xlslice_3/Din] [get_bd_pins xlslice_4/Din] [get_bd_pins xlslice_5/Din]
  connect_bd_net -net xlslice_0_Dout [get_bd_pins fix_to_float_current/in_0] [get_bd_pins xlslice_0/Dout]
  connect_bd_net -net xlslice_1_Dout [get_bd_pins fix_to_float_current/in_1] [get_bd_pins xlslice_1/Dout]
  connect_bd_net -net xlslice_2_Dout [get_bd_pins fix_to_float_current/in_2] [get_bd_pins xlslice_2/Dout]
  connect_bd_net -net xlslice_3_Dout [get_bd_pins fix_to_float_current/in_3] [get_bd_pins xlslice_3/Dout]
  connect_bd_net -net xlslice_4_Dout [get_bd_pins fix_to_float_current/in_4] [get_bd_pins xlslice_4/Dout]
  connect_bd_net -net xlslice_5_Dout [get_bd_pins fix_to_float_current/in_5] [get_bd_pins xlslice_5/Dout]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins aclk] [get_bd_pins CIL/aclk] [get_bd_pins fix_to_float_current/clk] [get_bd_pins float_to_fix_dutycycle/clk] [get_bd_pins smartconnect_1/aclk] [get_bd_pins transformation_and_control/ap_clk] [get_bd_pins uz_fixdt_to_float_theta/ap_clk]

  # Restore current instance
  current_bd_instance $oldCurInst
}


proc available_tcl_procs { } {
   puts "##################################################################"
   puts "# Available Tcl procedures to recreate hierarchical blocks:"
   puts "#"
   puts "#    create_hier_cell_uz_user parentCell nameHier"
   puts "#    create_hier_cell_CIL parentCell nameHier"
   puts "#    create_hier_cell_fix_to_float_current parentCell nameHier"
   puts "#    create_hier_cell_float_to_fix_dutycycle parentCell nameHier"
   puts "#    create_hier_cell_transformation_and_control parentCell nameHier"
   puts "#"
   puts "##################################################################"
}

available_tcl_procs
