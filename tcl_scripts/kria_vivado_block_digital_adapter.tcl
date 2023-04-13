
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
# top_npc_state_machine

# Please add the sources of those modules before sourcing this Tcl script.

set bCheckIPsPassed 1
##################################################################
# CHECK IPs
##################################################################
set bCheckIPs 1
if { $bCheckIPs == 1 } {
   set list_check_ips "\ 
xilinx.com:ip:vio:3.0\
xilinx.com:ip:IncreEncoder_V24_ip:24.0\
xilinx.com:ip:ila:6.2\
xilinx.com:ip:PWM_and_SS_control_V4_ip:4.1\
xilinx.com:ip:util_vector_logic:2.0\
user.org:ip:uz_interlockDeadtime2L:1.0\
xilinx.com:ip:xlconcat:2.1\
xilinx.com:ip:xlconstant:1.1\
mwn.de:ip:PWM_SS_3L_ip:1.4\
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
top_npc_state_machine\
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


# Hierarchical cell: Gates_3L
proc create_hier_cell_Gates_3L { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_Gates_3L() - Empty argument(s)!"}
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
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite


  # Create pins
  create_bd_pin -dir I -type clk AXI4_Lite_ACLK
  create_bd_pin -dir I -type rst AXI4_Lite_ARESETN
  create_bd_pin -dir I -type rst Enable_Gates
  create_bd_pin -dir O -from 11 -to 0 Gate_Signals_3L
  create_bd_pin -dir O -from 0 -to 0 Interrupt_Center
  create_bd_pin -dir O -from 0 -to 0 Interrupt_Start
  create_bd_pin -dir O -from 0 -to 0 Interrupt_Start_Center

  # Create instance: Gates_Vector, and set properties
  set Gates_Vector [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 Gates_Vector ]
  set_property -dict [ list \
   CONFIG.NUM_PORTS {6} \
 ] $Gates_Vector

  # Create instance: Interrupt_Start_Center, and set properties
  set Interrupt_Start_Center [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 Interrupt_Start_Center ]
  set_property -dict [ list \
   CONFIG.C_OPERATION {or} \
   CONFIG.C_SIZE {1} \
 ] $Interrupt_Start_Center

  # Create instance: PWM_SS_3L_ip_0, and set properties
  set PWM_SS_3L_ip_0 [ create_bd_cell -type ip -vlnv mwn.de:ip:PWM_SS_3L_ip:1.4 PWM_SS_3L_ip_0 ]

  # Create instance: Set_Deadtime_3L, and set properties
  set Set_Deadtime_3L [ create_bd_cell -type ip -vlnv xilinx.com:ip:vio:3.0 Set_Deadtime_3L ]
  set_property -dict [ list \
   CONFIG.C_NUM_PROBE_IN {0} \
   CONFIG.C_PROBE_OUT0_INIT_VAL {0x0C8} \
   CONFIG.C_PROBE_OUT0_WIDTH {10} \
 ] $Set_Deadtime_3L

  # Create instance: ila_0, and set properties
  set ila_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:ila:6.2 ila_0 ]
  set_property -dict [ list \
   CONFIG.C_DATA_DEPTH {8192} \
   CONFIG.C_ENABLE_ILA_AXI_MON {false} \
   CONFIG.C_MONITOR_TYPE {Native} \
   CONFIG.C_NUM_OF_PROBES {23} \
 ] $ila_0

  # Create instance: top_npc_state_machine_0, and set properties
  set block_name top_npc_state_machine
  set block_cell_name top_npc_state_machine_0
  if { [catch {set top_npc_state_machine_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $top_npc_state_machine_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: vio_Gates_3L, and set properties
  set vio_Gates_3L [ create_bd_cell -type ip -vlnv xilinx.com:ip:vio:3.0 vio_Gates_3L ]
  set_property -dict [ list \
   CONFIG.C_NUM_PROBE_IN {0} \
   CONFIG.C_NUM_PROBE_OUT {9} \
   CONFIG.C_PROBE_OUT0_WIDTH {14} \
   CONFIG.C_PROBE_OUT1_WIDTH {14} \
   CONFIG.C_PROBE_OUT2_WIDTH {14} \
   CONFIG.C_PROBE_OUT6_WIDTH {1} \
   CONFIG.C_PROBE_OUT7_WIDTH {1} \
   CONFIG.C_PROBE_OUT8_WIDTH {1} \
 ] $vio_Gates_3L

  # Create instance: xlconcat_0, and set properties
  set xlconcat_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0 ]
  set_property -dict [ list \
   CONFIG.NUM_PORTS {12} \
 ] $xlconcat_0

  # Create interface connections
  connect_bd_intf_net -intf_net smartconnect_0_M12_AXI [get_bd_intf_pins AXI4_Lite] [get_bd_intf_pins PWM_SS_3L_ip_0/AXI4_Lite]

  # Create port connections
  connect_bd_net -net Enable_Gates_1 [get_bd_pins Enable_Gates] [get_bd_pins top_npc_state_machine_0/enable]
  connect_bd_net -net Gates_Vector_dout [get_bd_pins Gates_Vector/dout] [get_bd_pins ila_0/probe13] [get_bd_pins top_npc_state_machine_0/switching_signals]
  connect_bd_net -net Interrupt_Start_Center_Res [get_bd_pins Interrupt_Start_Center] [get_bd_pins Interrupt_Start_Center/Res] [get_bd_pins ila_0/probe12]
  connect_bd_net -net PWM_SS_3L_ip_0_Period_Center [get_bd_pins Interrupt_Center] [get_bd_pins Interrupt_Start_Center/Op1] [get_bd_pins PWM_SS_3L_ip_0/Period_Center] [get_bd_pins ila_0/probe20]
  connect_bd_net -net PWM_SS_3L_ip_0_Period_Start [get_bd_pins Interrupt_Start] [get_bd_pins Interrupt_Start_Center/Op2] [get_bd_pins PWM_SS_3L_ip_0/Period_Start] [get_bd_pins ila_0/probe21]
  connect_bd_net -net PWM_SS_3L_ip_0_SSa1_OUT [get_bd_pins Gates_Vector/In0] [get_bd_pins PWM_SS_3L_ip_0/SSa1_OUT] [get_bd_pins ila_0/probe14]
  connect_bd_net -net PWM_SS_3L_ip_0_SSa2_OUT [get_bd_pins Gates_Vector/In1] [get_bd_pins PWM_SS_3L_ip_0/SSa2_OUT] [get_bd_pins ila_0/probe15]
  connect_bd_net -net PWM_SS_3L_ip_0_SSb1_OUT [get_bd_pins Gates_Vector/In2] [get_bd_pins PWM_SS_3L_ip_0/SSb1_OUT] [get_bd_pins ila_0/probe16]
  connect_bd_net -net PWM_SS_3L_ip_0_SSb2_OUT [get_bd_pins Gates_Vector/In3] [get_bd_pins PWM_SS_3L_ip_0/SSb2_OUT] [get_bd_pins ila_0/probe17]
  connect_bd_net -net PWM_SS_3L_ip_0_SSc1_OUT [get_bd_pins Gates_Vector/In4] [get_bd_pins PWM_SS_3L_ip_0/SSc1_OUT] [get_bd_pins ila_0/probe18]
  connect_bd_net -net PWM_SS_3L_ip_0_SSc2_OUT [get_bd_pins Gates_Vector/In5] [get_bd_pins PWM_SS_3L_ip_0/SSc2_OUT] [get_bd_pins ila_0/probe19]
  connect_bd_net -net Set_Deadtime_3L_probe_out0 [get_bd_pins Set_Deadtime_3L/probe_out0] [get_bd_pins ila_0/probe22] [get_bd_pins top_npc_state_machine_0/deadtime]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins AXI4_Lite_ARESETN] [get_bd_pins PWM_SS_3L_ip_0/AXI4_Lite_ARESETN] [get_bd_pins PWM_SS_3L_ip_0/IPCORE_RESETN]
  connect_bd_net -net top_npc_state_machine_0_A_S1 [get_bd_pins ila_0/probe0] [get_bd_pins top_npc_state_machine_0/A_S1] [get_bd_pins xlconcat_0/In0]
  connect_bd_net -net top_npc_state_machine_0_A_S2 [get_bd_pins ila_0/probe1] [get_bd_pins top_npc_state_machine_0/A_S2] [get_bd_pins xlconcat_0/In1]
  connect_bd_net -net top_npc_state_machine_0_A_S3 [get_bd_pins ila_0/probe2] [get_bd_pins top_npc_state_machine_0/A_S3] [get_bd_pins xlconcat_0/In2]
  connect_bd_net -net top_npc_state_machine_0_A_S4 [get_bd_pins ila_0/probe3] [get_bd_pins top_npc_state_machine_0/A_S4] [get_bd_pins xlconcat_0/In3]
  connect_bd_net -net top_npc_state_machine_0_B_S1 [get_bd_pins ila_0/probe4] [get_bd_pins top_npc_state_machine_0/B_S1] [get_bd_pins xlconcat_0/In4]
  connect_bd_net -net top_npc_state_machine_0_B_S2 [get_bd_pins ila_0/probe5] [get_bd_pins top_npc_state_machine_0/B_S2] [get_bd_pins xlconcat_0/In5]
  connect_bd_net -net top_npc_state_machine_0_B_S3 [get_bd_pins ila_0/probe6] [get_bd_pins top_npc_state_machine_0/B_S3] [get_bd_pins xlconcat_0/In6]
  connect_bd_net -net top_npc_state_machine_0_B_S4 [get_bd_pins ila_0/probe7] [get_bd_pins top_npc_state_machine_0/B_S4] [get_bd_pins xlconcat_0/In7]
  connect_bd_net -net top_npc_state_machine_0_C_S1 [get_bd_pins ila_0/probe8] [get_bd_pins top_npc_state_machine_0/C_S1] [get_bd_pins xlconcat_0/In8]
  connect_bd_net -net top_npc_state_machine_0_C_S2 [get_bd_pins ila_0/probe9] [get_bd_pins top_npc_state_machine_0/C_S2] [get_bd_pins xlconcat_0/In9]
  connect_bd_net -net top_npc_state_machine_0_C_S3 [get_bd_pins ila_0/probe10] [get_bd_pins top_npc_state_machine_0/C_S3] [get_bd_pins xlconcat_0/In10]
  connect_bd_net -net top_npc_state_machine_0_C_S4 [get_bd_pins ila_0/probe11] [get_bd_pins top_npc_state_machine_0/C_S4] [get_bd_pins xlconcat_0/In11]
  connect_bd_net -net vio_Gates_3L_probe_out0 [get_bd_pins PWM_SS_3L_ip_0/m_u1_norm] [get_bd_pins vio_Gates_3L/probe_out0]
  connect_bd_net -net vio_Gates_3L_probe_out1 [get_bd_pins PWM_SS_3L_ip_0/m_u2_norm] [get_bd_pins vio_Gates_3L/probe_out1]
  connect_bd_net -net vio_Gates_3L_probe_out2 [get_bd_pins PWM_SS_3L_ip_0/m_u3_norm] [get_bd_pins vio_Gates_3L/probe_out2]
  connect_bd_net -net vio_Gates_3L_probe_out3 [get_bd_pins PWM_SS_3L_ip_0/SSa1_IN_External] [get_bd_pins vio_Gates_3L/probe_out3]
  connect_bd_net -net vio_Gates_3L_probe_out4 [get_bd_pins PWM_SS_3L_ip_0/SSa2_IN_External] [get_bd_pins vio_Gates_3L/probe_out4]
  connect_bd_net -net vio_Gates_3L_probe_out5 [get_bd_pins PWM_SS_3L_ip_0/SSb1_IN_External] [get_bd_pins vio_Gates_3L/probe_out5]
  connect_bd_net -net vio_Gates_3L_probe_out6 [get_bd_pins PWM_SS_3L_ip_0/SSb2_IN_External] [get_bd_pins vio_Gates_3L/probe_out6]
  connect_bd_net -net vio_Gates_3L_probe_out7 [get_bd_pins PWM_SS_3L_ip_0/SSc1_IN_External] [get_bd_pins vio_Gates_3L/probe_out7]
  connect_bd_net -net vio_Gates_3L_probe_out8 [get_bd_pins PWM_SS_3L_ip_0/SSc2_IN_External] [get_bd_pins vio_Gates_3L/probe_out8]
  connect_bd_net -net xlconcat_0_dout [get_bd_pins Gate_Signals_3L] [get_bd_pins xlconcat_0/dout]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins AXI4_Lite_ACLK] [get_bd_pins PWM_SS_3L_ip_0/AXI4_Lite_ACLK] [get_bd_pins PWM_SS_3L_ip_0/IPCORE_CLK] [get_bd_pins Set_Deadtime_3L/clk] [get_bd_pins ila_0/clk] [get_bd_pins top_npc_state_machine_0/clock] [get_bd_pins vio_Gates_3L/clk]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: Gates
proc create_hier_cell_Gates { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_Gates() - Empty argument(s)!"}
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
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_0

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_1

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_2

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_3

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_0

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_1

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_2

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_3


  # Create pins
  create_bd_pin -dir I -type clk CLK
  create_bd_pin -dir O -from 0 -to 0 Carrier_triangular_max
  create_bd_pin -dir O -from 0 -to 0 Carrier_triangular_max_min
  create_bd_pin -dir O -from 0 -to 0 Carrier_triangular_min
  create_bd_pin -dir O -from 23 -to 0 Gate_Signals_2L
  create_bd_pin -dir I -type rst RESETN

  # Create instance: PWM_and_SS_control_V_0, and set properties
  set PWM_and_SS_control_V_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:PWM_and_SS_control_V4_ip:4.1 PWM_and_SS_control_V_0 ]

  # Create instance: PWM_and_SS_control_V_1, and set properties
  set PWM_and_SS_control_V_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:PWM_and_SS_control_V4_ip:4.1 PWM_and_SS_control_V_1 ]

  # Create instance: PWM_and_SS_control_V_2, and set properties
  set PWM_and_SS_control_V_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:PWM_and_SS_control_V4_ip:4.1 PWM_and_SS_control_V_2 ]

  # Create instance: PWM_and_SS_control_V_3, and set properties
  set PWM_and_SS_control_V_3 [ create_bd_cell -type ip -vlnv xilinx.com:ip:PWM_and_SS_control_V4_ip:4.1 PWM_and_SS_control_V_3 ]

  # Create instance: util_vector_logic_0, and set properties
  set util_vector_logic_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 util_vector_logic_0 ]
  set_property -dict [ list \
   CONFIG.C_OPERATION {or} \
   CONFIG.C_SIZE {1} \
 ] $util_vector_logic_0

  # Create instance: uz_interlockDeadtime_0, and set properties
  set uz_interlockDeadtime_0 [ create_bd_cell -type ip -vlnv user.org:ip:uz_interlockDeadtime2L:1.0 uz_interlockDeadtime_0 ]

  # Create instance: uz_interlockDeadtime_1, and set properties
  set uz_interlockDeadtime_1 [ create_bd_cell -type ip -vlnv user.org:ip:uz_interlockDeadtime2L:1.0 uz_interlockDeadtime_1 ]

  # Create instance: uz_interlockDeadtime_2, and set properties
  set uz_interlockDeadtime_2 [ create_bd_cell -type ip -vlnv user.org:ip:uz_interlockDeadtime2L:1.0 uz_interlockDeadtime_2 ]

  # Create instance: uz_interlockDeadtime_3, and set properties
  set uz_interlockDeadtime_3 [ create_bd_cell -type ip -vlnv user.org:ip:uz_interlockDeadtime2L:1.0 uz_interlockDeadtime_3 ]

  # Create instance: vio_Gates_2L, and set properties
  set vio_Gates_2L [ create_bd_cell -type ip -vlnv xilinx.com:ip:vio:3.0 vio_Gates_2L ]
  set_property -dict [ list \
   CONFIG.C_NUM_PROBE_IN {0} \
   CONFIG.C_NUM_PROBE_OUT {6} \
 ] $vio_Gates_2L

  # Create instance: xlconcat_0, and set properties
  set xlconcat_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0 ]
  set_property -dict [ list \
   CONFIG.NUM_PORTS {24} \
 ] $xlconcat_0

  # Create instance: xlconstant_0, and set properties
  set xlconstant_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_0 ]
  set_property -dict [ list \
   CONFIG.CONST_VAL {2048} \
   CONFIG.CONST_WIDTH {14} \
 ] $xlconstant_0

  # Create interface connections
  connect_bd_intf_net -intf_net AXI4_Lite_PWM_0_1 [get_bd_intf_pins AXI4_Lite_PWM_0] [get_bd_intf_pins PWM_and_SS_control_V_0/AXI4_Lite]
  connect_bd_intf_net -intf_net AXI4_Lite_PWM_1_1 [get_bd_intf_pins AXI4_Lite_PWM_1] [get_bd_intf_pins PWM_and_SS_control_V_1/AXI4_Lite]
  connect_bd_intf_net -intf_net AXI4_Lite_PWM_2_1 [get_bd_intf_pins AXI4_Lite_PWM_2] [get_bd_intf_pins PWM_and_SS_control_V_2/AXI4_Lite]
  connect_bd_intf_net -intf_net AXI4_Lite_PWM_3_1 [get_bd_intf_pins AXI4_Lite_PWM_3] [get_bd_intf_pins PWM_and_SS_control_V_3/AXI4_Lite]
  connect_bd_intf_net -intf_net AXI4_interlock_1_1 [get_bd_intf_pins AXI4_interlock_1] [get_bd_intf_pins uz_interlockDeadtime_1/AXI4]
  connect_bd_intf_net -intf_net AXI4_interlock_2_1 [get_bd_intf_pins AXI4_interlock_2] [get_bd_intf_pins uz_interlockDeadtime_2/AXI4]
  connect_bd_intf_net -intf_net AXI4_interlock_3_1 [get_bd_intf_pins AXI4_interlock_3] [get_bd_intf_pins uz_interlockDeadtime_3/AXI4]
  connect_bd_intf_net -intf_net S00_AXI_1 [get_bd_intf_pins AXI4_interlock_0] [get_bd_intf_pins uz_interlockDeadtime_0/AXI4]

  # Create port connections
  connect_bd_net -net AXI4_Lite_ARESETN_1 [get_bd_pins RESETN] [get_bd_pins PWM_and_SS_control_V_0/AXI4_Lite_ARESETN] [get_bd_pins PWM_and_SS_control_V_0/IPCORE_RESETN] [get_bd_pins PWM_and_SS_control_V_1/AXI4_Lite_ARESETN] [get_bd_pins PWM_and_SS_control_V_1/IPCORE_RESETN] [get_bd_pins PWM_and_SS_control_V_2/AXI4_Lite_ARESETN] [get_bd_pins PWM_and_SS_control_V_2/IPCORE_RESETN] [get_bd_pins PWM_and_SS_control_V_3/AXI4_Lite_ARESETN] [get_bd_pins PWM_and_SS_control_V_3/IPCORE_RESETN] [get_bd_pins uz_interlockDeadtime_0/AXI4_ARESETN] [get_bd_pins uz_interlockDeadtime_0/IPCORE_RESETN] [get_bd_pins uz_interlockDeadtime_1/AXI4_ARESETN] [get_bd_pins uz_interlockDeadtime_1/IPCORE_RESETN] [get_bd_pins uz_interlockDeadtime_2/AXI4_ARESETN] [get_bd_pins uz_interlockDeadtime_2/IPCORE_RESETN] [get_bd_pins uz_interlockDeadtime_3/AXI4_ARESETN] [get_bd_pins uz_interlockDeadtime_3/IPCORE_RESETN]
  connect_bd_net -net InterLock_Module_0_S0_OUT [get_bd_pins uz_interlockDeadtime_0/s0_out] [get_bd_pins xlconcat_0/In0]
  connect_bd_net -net InterLock_Module_0_S1_OUT [get_bd_pins uz_interlockDeadtime_0/s1_out] [get_bd_pins xlconcat_0/In1]
  connect_bd_net -net InterLock_Module_0_S2_OUT [get_bd_pins uz_interlockDeadtime_0/s2_out] [get_bd_pins xlconcat_0/In2]
  connect_bd_net -net InterLock_Module_0_S3_OUT [get_bd_pins uz_interlockDeadtime_0/s3_out] [get_bd_pins xlconcat_0/In3]
  connect_bd_net -net InterLock_Module_0_S4_OUT [get_bd_pins uz_interlockDeadtime_0/s4_out] [get_bd_pins xlconcat_0/In4]
  connect_bd_net -net InterLock_Module_0_S5_OUT [get_bd_pins uz_interlockDeadtime_0/s5_out] [get_bd_pins xlconcat_0/In5]
  connect_bd_net -net PWM_and_SS_control_V_0_SS0_OUT [get_bd_pins PWM_and_SS_control_V_0/SS0_OUT] [get_bd_pins uz_interlockDeadtime_0/S0]
  connect_bd_net -net PWM_and_SS_control_V_0_SS1_OUT [get_bd_pins PWM_and_SS_control_V_0/SS1_OUT] [get_bd_pins uz_interlockDeadtime_0/S1]
  connect_bd_net -net PWM_and_SS_control_V_0_SS2_OUT [get_bd_pins PWM_and_SS_control_V_0/SS2_OUT] [get_bd_pins uz_interlockDeadtime_0/S2]
  connect_bd_net -net PWM_and_SS_control_V_0_SS3_OUT [get_bd_pins PWM_and_SS_control_V_0/SS3_OUT] [get_bd_pins uz_interlockDeadtime_0/S3]
  connect_bd_net -net PWM_and_SS_control_V_0_SS4_OUT [get_bd_pins PWM_and_SS_control_V_0/SS4_OUT] [get_bd_pins uz_interlockDeadtime_0/S4]
  connect_bd_net -net PWM_and_SS_control_V_0_SS5_OUT [get_bd_pins PWM_and_SS_control_V_0/SS5_OUT] [get_bd_pins uz_interlockDeadtime_0/S5]
  connect_bd_net -net PWM_and_SS_control_V_0_Triangular_Max [get_bd_pins Carrier_triangular_max] [get_bd_pins PWM_and_SS_control_V_0/Triangular_Max] [get_bd_pins util_vector_logic_0/Op1]
  connect_bd_net -net PWM_and_SS_control_V_0_Triangular_Min [get_bd_pins Carrier_triangular_min] [get_bd_pins PWM_and_SS_control_V_0/Triangular_Min] [get_bd_pins util_vector_logic_0/Op2]
  connect_bd_net -net PWM_and_SS_control_V_0_triangle_out [get_bd_pins PWM_and_SS_control_V_0/triangle_in] [get_bd_pins PWM_and_SS_control_V_0/triangle_out] [get_bd_pins PWM_and_SS_control_V_1/triangle_in] [get_bd_pins PWM_and_SS_control_V_2/triangle_in] [get_bd_pins PWM_and_SS_control_V_3/triangle_in]
  connect_bd_net -net PWM_and_SS_control_V_1_SS0_OUT [get_bd_pins PWM_and_SS_control_V_1/SS0_OUT] [get_bd_pins uz_interlockDeadtime_1/S0]
  connect_bd_net -net PWM_and_SS_control_V_1_SS1_OUT [get_bd_pins PWM_and_SS_control_V_1/SS1_OUT] [get_bd_pins uz_interlockDeadtime_1/S1]
  connect_bd_net -net PWM_and_SS_control_V_1_SS2_OUT [get_bd_pins PWM_and_SS_control_V_1/SS2_OUT] [get_bd_pins uz_interlockDeadtime_1/S2]
  connect_bd_net -net PWM_and_SS_control_V_1_SS3_OUT [get_bd_pins PWM_and_SS_control_V_1/SS3_OUT] [get_bd_pins uz_interlockDeadtime_1/S3]
  connect_bd_net -net PWM_and_SS_control_V_1_SS4_OUT [get_bd_pins PWM_and_SS_control_V_1/SS4_OUT] [get_bd_pins uz_interlockDeadtime_1/S4]
  connect_bd_net -net PWM_and_SS_control_V_1_SS5_OUT [get_bd_pins PWM_and_SS_control_V_1/SS5_OUT] [get_bd_pins uz_interlockDeadtime_1/S5]
  connect_bd_net -net PWM_and_SS_control_V_2_SS0_OUT [get_bd_pins PWM_and_SS_control_V_2/SS0_OUT] [get_bd_pins uz_interlockDeadtime_2/S0]
  connect_bd_net -net PWM_and_SS_control_V_2_SS1_OUT [get_bd_pins PWM_and_SS_control_V_2/SS1_OUT] [get_bd_pins uz_interlockDeadtime_2/S1]
  connect_bd_net -net PWM_and_SS_control_V_2_SS2_OUT [get_bd_pins PWM_and_SS_control_V_2/SS2_OUT] [get_bd_pins uz_interlockDeadtime_2/S2]
  connect_bd_net -net PWM_and_SS_control_V_2_SS3_OUT [get_bd_pins PWM_and_SS_control_V_2/SS3_OUT] [get_bd_pins uz_interlockDeadtime_2/S3]
  connect_bd_net -net PWM_and_SS_control_V_2_SS4_OUT [get_bd_pins PWM_and_SS_control_V_2/SS4_OUT] [get_bd_pins uz_interlockDeadtime_2/S4]
  connect_bd_net -net PWM_and_SS_control_V_2_SS5_OUT [get_bd_pins PWM_and_SS_control_V_2/SS5_OUT] [get_bd_pins uz_interlockDeadtime_2/S5]
  connect_bd_net -net PWM_and_SS_control_V_3_SS0_OUT [get_bd_pins PWM_and_SS_control_V_3/SS0_OUT] [get_bd_pins uz_interlockDeadtime_3/S0]
  connect_bd_net -net PWM_and_SS_control_V_3_SS1_OUT [get_bd_pins PWM_and_SS_control_V_3/SS1_OUT] [get_bd_pins uz_interlockDeadtime_3/S1]
  connect_bd_net -net PWM_and_SS_control_V_3_SS2_OUT [get_bd_pins PWM_and_SS_control_V_3/SS2_OUT] [get_bd_pins uz_interlockDeadtime_3/S2]
  connect_bd_net -net PWM_and_SS_control_V_3_SS3_OUT [get_bd_pins PWM_and_SS_control_V_3/SS3_OUT] [get_bd_pins uz_interlockDeadtime_3/S3]
  connect_bd_net -net PWM_and_SS_control_V_3_SS4_OUT [get_bd_pins PWM_and_SS_control_V_3/SS4_OUT] [get_bd_pins uz_interlockDeadtime_3/S4]
  connect_bd_net -net PWM_and_SS_control_V_3_SS5_OUT [get_bd_pins PWM_and_SS_control_V_3/SS5_OUT] [get_bd_pins uz_interlockDeadtime_3/S5]
  connect_bd_net -net util_vector_logic_0_Res [get_bd_pins Carrier_triangular_max_min] [get_bd_pins util_vector_logic_0/Res]
  connect_bd_net -net uz_interlockDeadtime_1_s0_out [get_bd_pins uz_interlockDeadtime_1/s0_out] [get_bd_pins xlconcat_0/In6]
  connect_bd_net -net uz_interlockDeadtime_1_s1_out [get_bd_pins uz_interlockDeadtime_1/s1_out] [get_bd_pins xlconcat_0/In7]
  connect_bd_net -net uz_interlockDeadtime_1_s2_out [get_bd_pins uz_interlockDeadtime_1/s2_out] [get_bd_pins xlconcat_0/In8]
  connect_bd_net -net uz_interlockDeadtime_1_s3_out [get_bd_pins uz_interlockDeadtime_1/s3_out] [get_bd_pins xlconcat_0/In9]
  connect_bd_net -net uz_interlockDeadtime_1_s4_out [get_bd_pins uz_interlockDeadtime_1/s4_out] [get_bd_pins xlconcat_0/In10]
  connect_bd_net -net uz_interlockDeadtime_1_s5_out [get_bd_pins uz_interlockDeadtime_1/s5_out] [get_bd_pins xlconcat_0/In11]
  connect_bd_net -net uz_interlockDeadtime_2_s0_out [get_bd_pins uz_interlockDeadtime_2/s0_out] [get_bd_pins xlconcat_0/In12]
  connect_bd_net -net uz_interlockDeadtime_2_s1_out [get_bd_pins uz_interlockDeadtime_2/s1_out] [get_bd_pins xlconcat_0/In13]
  connect_bd_net -net uz_interlockDeadtime_2_s2_out [get_bd_pins uz_interlockDeadtime_2/s2_out] [get_bd_pins xlconcat_0/In14]
  connect_bd_net -net uz_interlockDeadtime_2_s3_out [get_bd_pins uz_interlockDeadtime_2/s3_out] [get_bd_pins xlconcat_0/In15]
  connect_bd_net -net uz_interlockDeadtime_2_s4_out [get_bd_pins uz_interlockDeadtime_2/s4_out] [get_bd_pins xlconcat_0/In16]
  connect_bd_net -net uz_interlockDeadtime_2_s5_out [get_bd_pins uz_interlockDeadtime_2/s5_out] [get_bd_pins xlconcat_0/In17]
  connect_bd_net -net uz_interlockDeadtime_3_s0_out [get_bd_pins uz_interlockDeadtime_3/s0_out] [get_bd_pins xlconcat_0/In18]
  connect_bd_net -net uz_interlockDeadtime_3_s1_out [get_bd_pins uz_interlockDeadtime_3/s1_out] [get_bd_pins xlconcat_0/In19]
  connect_bd_net -net uz_interlockDeadtime_3_s2_out [get_bd_pins uz_interlockDeadtime_3/s2_out] [get_bd_pins xlconcat_0/In20]
  connect_bd_net -net uz_interlockDeadtime_3_s3_out [get_bd_pins uz_interlockDeadtime_3/s3_out] [get_bd_pins xlconcat_0/In21]
  connect_bd_net -net uz_interlockDeadtime_3_s4_out [get_bd_pins uz_interlockDeadtime_3/s4_out] [get_bd_pins xlconcat_0/In22]
  connect_bd_net -net uz_interlockDeadtime_3_s5_out [get_bd_pins uz_interlockDeadtime_3/s5_out] [get_bd_pins xlconcat_0/In23]
  connect_bd_net -net vio_Gates_2L_probe_out0 [get_bd_pins PWM_and_SS_control_V_0/SS0_IN_External] [get_bd_pins PWM_and_SS_control_V_1/SS0_IN_External] [get_bd_pins PWM_and_SS_control_V_2/SS0_IN_External] [get_bd_pins PWM_and_SS_control_V_3/SS0_IN_External] [get_bd_pins vio_Gates_2L/probe_out0]
  connect_bd_net -net vio_Gates_2L_probe_out1 [get_bd_pins PWM_and_SS_control_V_0/SS1_IN_External] [get_bd_pins PWM_and_SS_control_V_1/SS1_IN_External] [get_bd_pins PWM_and_SS_control_V_2/SS1_IN_External] [get_bd_pins PWM_and_SS_control_V_3/SS1_IN_External] [get_bd_pins vio_Gates_2L/probe_out1]
  connect_bd_net -net vio_Gates_2L_probe_out2 [get_bd_pins PWM_and_SS_control_V_0/SS2_IN_External] [get_bd_pins PWM_and_SS_control_V_1/SS2_IN_External] [get_bd_pins PWM_and_SS_control_V_2/SS2_IN_External] [get_bd_pins PWM_and_SS_control_V_3/SS2_IN_External] [get_bd_pins vio_Gates_2L/probe_out2]
  connect_bd_net -net vio_Gates_2L_probe_out3 [get_bd_pins PWM_and_SS_control_V_0/SS3_IN_External] [get_bd_pins PWM_and_SS_control_V_1/SS3_IN_External] [get_bd_pins PWM_and_SS_control_V_2/SS3_IN_External] [get_bd_pins PWM_and_SS_control_V_3/SS3_IN_External] [get_bd_pins vio_Gates_2L/probe_out3]
  connect_bd_net -net vio_Gates_2L_probe_out4 [get_bd_pins PWM_and_SS_control_V_0/SS4_IN_External] [get_bd_pins PWM_and_SS_control_V_1/SS4_IN_External] [get_bd_pins PWM_and_SS_control_V_2/SS4_IN_External] [get_bd_pins PWM_and_SS_control_V_3/SS4_IN_External] [get_bd_pins vio_Gates_2L/probe_out4]
  connect_bd_net -net vio_Gates_2L_probe_out5 [get_bd_pins PWM_and_SS_control_V_0/SS5_IN_External] [get_bd_pins PWM_and_SS_control_V_1/SS5_IN_External] [get_bd_pins PWM_and_SS_control_V_2/SS5_IN_External] [get_bd_pins PWM_and_SS_control_V_3/SS5_IN_External] [get_bd_pins vio_Gates_2L/probe_out5]
  connect_bd_net -net xlconcat_0_dout [get_bd_pins Gate_Signals_2L] [get_bd_pins xlconcat_0/dout]
  connect_bd_net -net xlconstant_0_dout [get_bd_pins PWM_and_SS_control_V_0/m_u1_norm] [get_bd_pins PWM_and_SS_control_V_0/m_u2_norm] [get_bd_pins PWM_and_SS_control_V_0/m_u3_norm] [get_bd_pins PWM_and_SS_control_V_1/m_u1_norm] [get_bd_pins PWM_and_SS_control_V_1/m_u2_norm] [get_bd_pins PWM_and_SS_control_V_1/m_u3_norm] [get_bd_pins PWM_and_SS_control_V_2/m_u1_norm] [get_bd_pins PWM_and_SS_control_V_2/m_u2_norm] [get_bd_pins PWM_and_SS_control_V_2/m_u3_norm] [get_bd_pins PWM_and_SS_control_V_3/m_u1_norm] [get_bd_pins PWM_and_SS_control_V_3/m_u2_norm] [get_bd_pins PWM_and_SS_control_V_3/m_u3_norm] [get_bd_pins xlconstant_0/dout]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins CLK] [get_bd_pins PWM_and_SS_control_V_0/AXI4_Lite_ACLK] [get_bd_pins PWM_and_SS_control_V_0/IPCORE_CLK] [get_bd_pins PWM_and_SS_control_V_1/AXI4_Lite_ACLK] [get_bd_pins PWM_and_SS_control_V_1/IPCORE_CLK] [get_bd_pins PWM_and_SS_control_V_2/AXI4_Lite_ACLK] [get_bd_pins PWM_and_SS_control_V_2/IPCORE_CLK] [get_bd_pins PWM_and_SS_control_V_3/AXI4_Lite_ACLK] [get_bd_pins PWM_and_SS_control_V_3/IPCORE_CLK] [get_bd_pins uz_interlockDeadtime_0/AXI4_ACLK] [get_bd_pins uz_interlockDeadtime_0/IPCORE_CLK] [get_bd_pins uz_interlockDeadtime_1/AXI4_ACLK] [get_bd_pins uz_interlockDeadtime_1/IPCORE_CLK] [get_bd_pins uz_interlockDeadtime_2/AXI4_ACLK] [get_bd_pins uz_interlockDeadtime_2/IPCORE_CLK] [get_bd_pins uz_interlockDeadtime_3/AXI4_ACLK] [get_bd_pins uz_interlockDeadtime_3/IPCORE_CLK] [get_bd_pins vio_Gates_2L/clk]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: D5_adapter
proc create_hier_cell_D5_adapter { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_D5_adapter() - Empty argument(s)!"}
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
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite


  # Create pins
  create_bd_pin -dir I -type clk AXI4_Lite_ACLK
  create_bd_pin -dir I -type rst AXI4_Lite_ARESETN
  create_bd_pin -dir I -from 0 -to 0 Dig_11_Ch5
  create_bd_pin -dir I -from 0 -to 0 Dig_12_Ch5
  create_bd_pin -dir I -from 0 -to 0 Dig_13_Ch5
  create_bd_pin -dir I -type clk clk
  create_bd_pin -dir I -from 0 -to 0 probe5

  # Create instance: IncreEncoder_V24_ip_0, and set properties
  set IncreEncoder_V24_ip_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:IncreEncoder_V24_ip:24.0 IncreEncoder_V24_ip_0 ]

  # Create instance: ila_Encoder, and set properties
  set ila_Encoder [ create_bd_cell -type ip -vlnv xilinx.com:ip:ila:6.2 ila_Encoder ]
  set_property -dict [ list \
   CONFIG.C_DATA_DEPTH {2048} \
   CONFIG.C_ENABLE_ILA_AXI_MON {false} \
   CONFIG.C_MONITOR_TYPE {Native} \
   CONFIG.C_NUM_OF_PROBES {8} \
   CONFIG.C_PROBE3_WIDTH {24} \
   CONFIG.C_PROBE4_WIDTH {24} \
 ] $ila_Encoder

  # Create interface connections
  connect_bd_intf_net -intf_net smartconnect_0_M09_AXI [get_bd_intf_pins AXI4_Lite] [get_bd_intf_pins IncreEncoder_V24_ip_0/AXI4_Lite]

  # Create port connections
  connect_bd_net -net A_1 [get_bd_pins Dig_12_Ch5] [get_bd_pins IncreEncoder_V24_ip_0/A] [get_bd_pins ila_Encoder/probe0]
  connect_bd_net -net B_1 [get_bd_pins Dig_13_Ch5] [get_bd_pins IncreEncoder_V24_ip_0/B] [get_bd_pins ila_Encoder/probe1]
  connect_bd_net -net I_1 [get_bd_pins Dig_11_Ch5] [get_bd_pins IncreEncoder_V24_ip_0/I] [get_bd_pins ila_Encoder/probe2]
  connect_bd_net -net IncreEncoder_V24_ip_0_OverSamplFactor [get_bd_pins IncreEncoder_V24_ip_0/OverSamplFactor] [get_bd_pins ila_Encoder/probe7]
  connect_bd_net -net IncreEncoder_V24_ip_0_omega [get_bd_pins IncreEncoder_V24_ip_0/omega] [get_bd_pins ila_Encoder/probe3]
  connect_bd_net -net IncreEncoder_V24_ip_0_position [get_bd_pins IncreEncoder_V24_ip_0/position] [get_bd_pins ila_Encoder/probe6]
  connect_bd_net -net IncreEncoder_ip_0_theta_el [get_bd_pins IncreEncoder_V24_ip_0/theta_el] [get_bd_pins ila_Encoder/probe4]
  connect_bd_net -net Interrupt_muxed [get_bd_pins probe5] [get_bd_pins IncreEncoder_V24_ip_0/PeriodEnd] [get_bd_pins ila_Encoder/probe5]
  connect_bd_net -net proc_sys_reset_50MHz_peripheral_aresetn [get_bd_pins AXI4_Lite_ARESETN] [get_bd_pins IncreEncoder_V24_ip_0/AXI4_Lite_ARESETN] [get_bd_pins IncreEncoder_V24_ip_0/IPCORE_RESETN]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins clk] [get_bd_pins ila_Encoder/clk]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk3 [get_bd_pins AXI4_Lite_ACLK] [get_bd_pins IncreEncoder_V24_ip_0/AXI4_Lite_ACLK] [get_bd_pins IncreEncoder_V24_ip_0/IPCORE_CLK]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: D3_adapter
proc create_hier_cell_D3_adapter { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_D3_adapter() - Empty argument(s)!"}
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
  create_bd_pin -dir O -from 25 -to 0 D3_OUT
  create_bd_pin -dir I -type clk clk

  # Create instance: vio_D3_test, and set properties
  set vio_D3_test [ create_bd_cell -type ip -vlnv xilinx.com:ip:vio:3.0 vio_D3_test ]
  set_property -dict [ list \
   CONFIG.C_NUM_PROBE_IN {0} \
   CONFIG.C_NUM_PROBE_OUT {1} \
   CONFIG.C_PROBE_OUT0_WIDTH {26} \
 ] $vio_D3_test

  # Create port connections
  connect_bd_net -net vio_D2_test_probe_out0 [get_bd_pins D3_OUT] [get_bd_pins vio_D3_test/probe_out0]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins clk] [get_bd_pins vio_D3_test/clk]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: D2_adapter
proc create_hier_cell_D2_adapter { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_D2_adapter() - Empty argument(s)!"}
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
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite


  # Create pins
  create_bd_pin -dir I -type clk AXI4_Lite_ACLK
  create_bd_pin -dir I -type rst AXI4_Lite_ARESETN
  create_bd_pin -dir O -from 11 -to 0 D2_OUT
  create_bd_pin -dir I -type rst Enable_Gates
  create_bd_pin -dir O -from 0 -to 0 Interrupt_Center
  create_bd_pin -dir O -from 0 -to 0 Interrupt_Start
  create_bd_pin -dir O -from 0 -to 0 Interrupt_Start_Center

  # Create instance: Gates_3L
  create_hier_cell_Gates_3L $hier_obj Gates_3L

  # Create interface connections
  connect_bd_intf_net -intf_net smartconnect_0_M12_AXI [get_bd_intf_pins AXI4_Lite] [get_bd_intf_pins Gates_3L/AXI4_Lite]

  # Create port connections
  connect_bd_net -net Gates_3L_Gate_Signals_3L [get_bd_pins D2_OUT] [get_bd_pins Gates_3L/Gate_Signals_3L]
  connect_bd_net -net Gates_3L_Interrupt_Center [get_bd_pins Interrupt_Center] [get_bd_pins Gates_3L/Interrupt_Center]
  connect_bd_net -net Gates_3L_Interrupt_Start [get_bd_pins Interrupt_Start] [get_bd_pins Gates_3L/Interrupt_Start]
  connect_bd_net -net Gates_3L_Interrupt_Start_Center [get_bd_pins Interrupt_Start_Center] [get_bd_pins Gates_3L/Interrupt_Start_Center]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins AXI4_Lite_ARESETN] [get_bd_pins Gates_3L/AXI4_Lite_ARESETN]
  connect_bd_net -net xlslice_Enable_Inverter_Dout [get_bd_pins Enable_Gates] [get_bd_pins Gates_3L/Enable_Gates]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins AXI4_Lite_ACLK] [get_bd_pins Gates_3L/AXI4_Lite_ACLK]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: D1_adapter
proc create_hier_cell_D1_adapter { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_D1_adapter() - Empty argument(s)!"}
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
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_0

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_1

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_2

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_3

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_0

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_1

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_2

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_3


  # Create pins
  create_bd_pin -dir I -type clk CLK
  create_bd_pin -dir O -from 0 -to 0 Carrier_triangular_max
  create_bd_pin -dir O -from 0 -to 0 Carrier_triangular_max_min
  create_bd_pin -dir O -from 0 -to 0 Carrier_triangular_min
  create_bd_pin -dir O -from 23 -to 0 D1_OUT
  create_bd_pin -dir I -type rst RESETN

  # Create instance: Gates
  create_hier_cell_Gates $hier_obj Gates

  # Create interface connections
  connect_bd_intf_net -intf_net AXI4_Lite1_1 [get_bd_intf_pins AXI4_Lite_PWM_1] [get_bd_intf_pins Gates/AXI4_Lite_PWM_1]
  connect_bd_intf_net -intf_net AXI4_Lite_PWM_2_1 [get_bd_intf_pins AXI4_Lite_PWM_2] [get_bd_intf_pins Gates/AXI4_Lite_PWM_2]
  connect_bd_intf_net -intf_net AXI4_Lite_PWM_3_1 [get_bd_intf_pins AXI4_Lite_PWM_3] [get_bd_intf_pins Gates/AXI4_Lite_PWM_3]
  connect_bd_intf_net -intf_net AXI_interlock_1_1 [get_bd_intf_pins AXI4_interlock_1] [get_bd_intf_pins Gates/AXI4_interlock_1]
  connect_bd_intf_net -intf_net AXI_interlock_2_1 [get_bd_intf_pins AXI4_interlock_2] [get_bd_intf_pins Gates/AXI4_interlock_2]
  connect_bd_intf_net -intf_net AXI_interlock_3_1 [get_bd_intf_pins AXI4_interlock_3] [get_bd_intf_pins Gates/AXI4_interlock_3]
  connect_bd_intf_net -intf_net smartconnect_0_M07_AXI [get_bd_intf_pins AXI4_interlock_0] [get_bd_intf_pins Gates/AXI4_interlock_0]
  connect_bd_intf_net -intf_net smartconnect_0_M08_AXI [get_bd_intf_pins AXI4_Lite_PWM_0] [get_bd_intf_pins Gates/AXI4_Lite_PWM_0]

  # Create port connections
  connect_bd_net -net Gates_Carrier_triangular_max1 [get_bd_pins Carrier_triangular_max] [get_bd_pins Gates/Carrier_triangular_max]
  connect_bd_net -net Gates_Carrier_triangular_max_min [get_bd_pins Carrier_triangular_max_min] [get_bd_pins Gates/Carrier_triangular_max_min]
  connect_bd_net -net Gates_Carrier_triangular_min1 [get_bd_pins Carrier_triangular_min] [get_bd_pins Gates/Carrier_triangular_min]
  connect_bd_net -net Gates_dout_0 [get_bd_pins D1_OUT] [get_bd_pins Gates/Gate_Signals_2L]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins RESETN] [get_bd_pins Gates/RESETN]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins CLK] [get_bd_pins Gates/CLK]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: uz_digital_adapter
proc create_hier_cell_uz_digital_adapter { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_uz_digital_adapter() - Empty argument(s)!"}
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
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite3

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_0

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_1

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_2

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_3

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_0

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_1

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_2

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_3


  # Create pins
  create_bd_pin -dir I -type clk AXI4_Lite_ACLK
  create_bd_pin -dir I -type rst AXI4_Lite_ARESETN1
  create_bd_pin -dir O -from 0 -to 0 Carrier_triangular_max
  create_bd_pin -dir O -from 0 -to 0 Carrier_triangular_max_min
  create_bd_pin -dir O -from 0 -to 0 Carrier_triangular_min
  create_bd_pin -dir O -from 23 -to 0 D1_OUT
  create_bd_pin -dir O -from 11 -to 0 D2_OUT
  create_bd_pin -dir O -from 25 -to 0 D3_OUT
  create_bd_pin -dir I -from 0 -to 0 Dig_11_Ch5
  create_bd_pin -dir I -from 0 -to 0 Dig_12_Ch5
  create_bd_pin -dir I -from 0 -to 0 Dig_13_Ch5
  create_bd_pin -dir I -from 0 -to 0 Enable_Gate
  create_bd_pin -dir O -from 0 -to 0 Interrupt_Center
  create_bd_pin -dir O -from 0 -to 0 Interrupt_Start
  create_bd_pin -dir O -from 0 -to 0 Interrupt_Start_Center
  create_bd_pin -dir I -type rst RESETN
  create_bd_pin -dir I -type clk clk
  create_bd_pin -dir I -from 0 -to 0 probe5

  # Create instance: D1_adapter
  create_hier_cell_D1_adapter $hier_obj D1_adapter

  # Create instance: D2_adapter
  create_hier_cell_D2_adapter $hier_obj D2_adapter

  # Create instance: D3_adapter
  create_hier_cell_D3_adapter $hier_obj D3_adapter

  # Create instance: D5_adapter
  create_hier_cell_D5_adapter $hier_obj D5_adapter

  # Create interface connections
  connect_bd_intf_net -intf_net AXI4_Lite1_1 [get_bd_intf_pins AXI4_Lite_PWM_1] [get_bd_intf_pins D1_adapter/AXI4_Lite_PWM_1]
  connect_bd_intf_net -intf_net AXI4_Lite_1 [get_bd_intf_pins AXI4_Lite_PWM_0] [get_bd_intf_pins D1_adapter/AXI4_Lite_PWM_0]
  connect_bd_intf_net -intf_net AXI4_Lite_2 [get_bd_intf_pins AXI4_Lite3] [get_bd_intf_pins D5_adapter/AXI4_Lite]
  connect_bd_intf_net -intf_net AXI4_Lite_3 [get_bd_intf_pins AXI4_Lite] [get_bd_intf_pins D2_adapter/AXI4_Lite]
  connect_bd_intf_net -intf_net AXI4_Lite_PWM_2_1 [get_bd_intf_pins AXI4_Lite_PWM_2] [get_bd_intf_pins D1_adapter/AXI4_Lite_PWM_2]
  connect_bd_intf_net -intf_net AXI4_Lite_PWM_3_1 [get_bd_intf_pins AXI4_Lite_PWM_3] [get_bd_intf_pins D1_adapter/AXI4_Lite_PWM_3]
  connect_bd_intf_net -intf_net AXI_interlock_1_1 [get_bd_intf_pins AXI4_interlock_1] [get_bd_intf_pins D1_adapter/AXI4_interlock_1]
  connect_bd_intf_net -intf_net AXI_interlock_2_1 [get_bd_intf_pins AXI4_interlock_2] [get_bd_intf_pins D1_adapter/AXI4_interlock_2]
  connect_bd_intf_net -intf_net AXI_interlock_3_1 [get_bd_intf_pins AXI4_interlock_3] [get_bd_intf_pins D1_adapter/AXI4_interlock_3]
  connect_bd_intf_net -intf_net S00_AXI_5 [get_bd_intf_pins AXI4_interlock_0] [get_bd_intf_pins D1_adapter/AXI4_interlock_0]

  # Create port connections
  connect_bd_net -net A_1 [get_bd_pins Dig_12_Ch5] [get_bd_pins D5_adapter/Dig_12_Ch5]
  connect_bd_net -net B_1 [get_bd_pins Dig_13_Ch5] [get_bd_pins D5_adapter/Dig_13_Ch5]
  connect_bd_net -net Gates_3L_Gate_Signals_3L [get_bd_pins D2_OUT] [get_bd_pins D2_adapter/D2_OUT]
  connect_bd_net -net Gates_3L_Interrupt_Center [get_bd_pins Interrupt_Center] [get_bd_pins D2_adapter/Interrupt_Center]
  connect_bd_net -net Gates_3L_Interrupt_Start [get_bd_pins Interrupt_Start] [get_bd_pins D2_adapter/Interrupt_Start]
  connect_bd_net -net Gates_3L_Interrupt_Start_Center [get_bd_pins Interrupt_Start_Center] [get_bd_pins D2_adapter/Interrupt_Start_Center]
  connect_bd_net -net Gates_Carrier_triangular_max1 [get_bd_pins Carrier_triangular_max] [get_bd_pins D1_adapter/Carrier_triangular_max]
  connect_bd_net -net Gates_Carrier_triangular_max_min [get_bd_pins Carrier_triangular_max_min] [get_bd_pins D1_adapter/Carrier_triangular_max_min]
  connect_bd_net -net Gates_Carrier_triangular_min1 [get_bd_pins Carrier_triangular_min] [get_bd_pins D1_adapter/Carrier_triangular_min]
  connect_bd_net -net Gates_dout_0 [get_bd_pins D1_OUT] [get_bd_pins D1_adapter/D1_OUT]
  connect_bd_net -net I_1 [get_bd_pins Dig_11_Ch5] [get_bd_pins D5_adapter/Dig_11_Ch5]
  connect_bd_net -net Interrupt_muxed [get_bd_pins probe5] [get_bd_pins D5_adapter/probe5]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins RESETN] [get_bd_pins D1_adapter/RESETN] [get_bd_pins D2_adapter/AXI4_Lite_ARESETN]
  connect_bd_net -net proc_sys_reset_50MHz_peripheral_aresetn [get_bd_pins AXI4_Lite_ARESETN1] [get_bd_pins D5_adapter/AXI4_Lite_ARESETN]
  connect_bd_net -net vio_D2_test_probe_out0 [get_bd_pins D3_OUT] [get_bd_pins D3_adapter/D3_OUT]
  connect_bd_net -net xlslice_Enable_Inverter_Dout [get_bd_pins Enable_Gate] [get_bd_pins D2_adapter/Enable_Gates]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins clk] [get_bd_pins D1_adapter/CLK] [get_bd_pins D2_adapter/AXI4_Lite_ACLK] [get_bd_pins D3_adapter/clk] [get_bd_pins D5_adapter/clk]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk3 [get_bd_pins AXI4_Lite_ACLK] [get_bd_pins D5_adapter/AXI4_Lite_ACLK]

  # Restore current instance
  current_bd_instance $oldCurInst
}


proc available_tcl_procs { } {
   puts "##################################################################"
   puts "# Available Tcl procedures to recreate hierarchical blocks:"
   puts "#"
   puts "#    create_hier_cell_uz_digital_adapter parentCell nameHier"
   puts "#    create_hier_cell_D1_adapter parentCell nameHier"
   puts "#    create_hier_cell_D2_adapter parentCell nameHier"
   puts "#    create_hier_cell_D3_adapter parentCell nameHier"
   puts "#    create_hier_cell_D5_adapter parentCell nameHier"
   puts "#    create_hier_cell_Gates parentCell nameHier"
   puts "#    create_hier_cell_Gates_3L parentCell nameHier"
   puts "#"
   puts "##################################################################"
}

available_tcl_procs
