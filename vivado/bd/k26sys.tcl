
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


# The design that will be created by this Tcl script contains the following 
# module references:
# delay_trigger, top_npc_state_machine

# Please add the sources of those modules before sourcing this Tcl script.

# If there is no project opened, this script will create a
# project, but make sure you do not have an existing project
# <./myproj/project_1.xpr> in the current working folder.

set list_projs [get_projects -quiet]
if { $list_projs eq "" } {
   create_project project_1 myproj -part xck26-sfvc784-2LV-c
   set_property BOARD_PART xilinx.com:kr260_som:part0:1.1 [current_project]
}


# CHANGE DESIGN NAME HERE
variable design_name
set design_name k26sys

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

set bCheckIPsPassed 1
##################################################################
# CHECK IPs
##################################################################
set bCheckIPs 1
if { $bCheckIPs == 1 } {
   set list_check_ips "\ 
xilinx.com:ip:xlconstant:1.1\
xilinx.com:ip:zynq_ultra_ps_e:3.4\
xilinx.com:ip:axi_timebase_wdt:3.0\
xilinx.com:ip:smartconnect:1.0\
xilinx.com:ip:axi_timer:2.0\
user.org:ip:uz_axi_testIP:1.0\
UltraZohm:user:ADC_LTC2311:3.0\
xilinx.com:ip:vio:3.0\
xilinx.com:ip:IncreEncoder_V24_ip:24.0\
xilinx.com:ip:ila:6.2\
TUM:user:AXI2TCM:1.1\
xilinx.com:ip:util_vector_logic:2.0\
xilinx.com:ip:xlconcat:2.1\
xilinx.com:ip:mux_axi_ip:1.2\
xilinx.com:ip:clk_wiz:6.0\
xilinx.com:ip:proc_sys_reset:5.0\
xilinx.com:ip:axi_gpio:2.0\
xilinx.com:ip:xlslice:1.0\
xilinx.com:ip:PWM_and_SS_control_V4_ip:4.1\
user.org:ip:uz_interlockDeadtime2L:1.0\
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
delay_trigger\
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
  set_property CONFIG.NUM_PORTS {6} $Gates_Vector


  # Create instance: Interrupt_Start_Center, and set properties
  set Interrupt_Start_Center [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 Interrupt_Start_Center ]
  set_property -dict [list \
    CONFIG.C_OPERATION {or} \
    CONFIG.C_SIZE {1} \
  ] $Interrupt_Start_Center


  # Create instance: PWM_SS_3L_ip_0, and set properties
  set PWM_SS_3L_ip_0 [ create_bd_cell -type ip -vlnv mwn.de:ip:PWM_SS_3L_ip:1.4 PWM_SS_3L_ip_0 ]

  # Create instance: Set_Deadtime_3L, and set properties
  set Set_Deadtime_3L [ create_bd_cell -type ip -vlnv xilinx.com:ip:vio:3.0 Set_Deadtime_3L ]
  set_property -dict [list \
    CONFIG.C_NUM_PROBE_IN {0} \
    CONFIG.C_PROBE_OUT0_INIT_VAL {0x0C8} \
    CONFIG.C_PROBE_OUT0_WIDTH {10} \
  ] $Set_Deadtime_3L


  # Create instance: ila_0, and set properties
  set ila_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:ila:6.2 ila_0 ]
  set_property -dict [list \
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
  set_property -dict [list \
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
  set_property CONFIG.NUM_PORTS {12} $xlconcat_0


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
  set_property -dict [list \
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
  set_property -dict [list \
    CONFIG.C_NUM_PROBE_IN {0} \
    CONFIG.C_NUM_PROBE_OUT {6} \
  ] $vio_Gates_2L


  # Create instance: xlconcat_0, and set properties
  set xlconcat_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0 ]
  set_property CONFIG.NUM_PORTS {24} $xlconcat_0


  # Create instance: xlconstant_0, and set properties
  set xlconstant_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_0 ]
  set_property -dict [list \
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
  set_property -dict [list \
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
  set_property -dict [list \
    CONFIG.DIN_FROM {15} \
    CONFIG.DIN_WIDTH {128} \
    CONFIG.DOUT_WIDTH {16} \
  ] $xlslice_2


  # Create instance: xlslice_3, and set properties
  set xlslice_3 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_3 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {31} \
    CONFIG.DIN_TO {16} \
    CONFIG.DIN_WIDTH {128} \
    CONFIG.DOUT_WIDTH {16} \
  ] $xlslice_3


  # Create instance: xlslice_4, and set properties
  set xlslice_4 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_4 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {47} \
    CONFIG.DIN_TO {32} \
    CONFIG.DIN_WIDTH {128} \
    CONFIG.DOUT_WIDTH {16} \
  ] $xlslice_4


  # Create instance: xlslice_5, and set properties
  set xlslice_5 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_5 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {63} \
    CONFIG.DIN_TO {48} \
    CONFIG.DIN_WIDTH {128} \
    CONFIG.DOUT_WIDTH {16} \
  ] $xlslice_5


  # Create instance: xlslice_6, and set properties
  set xlslice_6 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_6 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {69} \
    CONFIG.DIN_TO {35} \
    CONFIG.DIN_WIDTH {280} \
    CONFIG.DOUT_WIDTH {35} \
  ] $xlslice_6


  # Create instance: xlslice_7, and set properties
  set xlslice_7 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_7 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {34} \
    CONFIG.DIN_WIDTH {280} \
    CONFIG.DOUT_WIDTH {35} \
  ] $xlslice_7


  # Create instance: xlslice_8, and set properties
  set xlslice_8 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_8 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {69} \
    CONFIG.DIN_TO {35} \
    CONFIG.DIN_WIDTH {280} \
    CONFIG.DOUT_WIDTH {35} \
  ] $xlslice_8


  # Create instance: xlslice_9, and set properties
  set xlslice_9 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_9 ]
  set_property -dict [list \
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

# Hierarchical cell: uz_enable
proc create_hier_cell_uz_enable { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_uz_enable() - Empty argument(s)!"}
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
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 S_AXI


  # Create pins
  create_bd_pin -dir O -from 0 -to 0 D1_OUT_26
  create_bd_pin -dir O -from 0 -to 0 D1_OUT_28
  create_bd_pin -dir O -from 0 -to 0 D4_OUT_29
  create_bd_pin -dir O -from 0 -to 0 Dout
  create_bd_pin -dir O -from 0 -to 0 Dout1
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type rst s_axi_aresetn

  # Create instance: Enable_Gates_CPLD_High, and set properties
  set Enable_Gates_CPLD_High [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 Enable_Gates_CPLD_High ]

  # Create instance: Enable_Gates_CPLD_Low, and set properties
  set Enable_Gates_CPLD_Low [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 Enable_Gates_CPLD_Low ]
  set_property CONFIG.CONST_VAL {0} $Enable_Gates_CPLD_Low


  # Create instance: axi_gpio_2, and set properties
  set axi_gpio_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_2 ]
  set_property CONFIG.C_GPIO_WIDTH {8} $axi_gpio_2


  # Create instance: xlslice_Enable_AXI2TCM_Bit4, and set properties
  set xlslice_Enable_AXI2TCM_Bit4 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_Enable_AXI2TCM_Bit4 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {4} \
    CONFIG.DIN_TO {4} \
    CONFIG.DIN_WIDTH {8} \
    CONFIG.DOUT_WIDTH {1} \
  ] $xlslice_Enable_AXI2TCM_Bit4


  # Create instance: xlslice_Enable_Gate_Bit1, and set properties
  set xlslice_Enable_Gate_Bit1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_Enable_Gate_Bit1 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {1} \
    CONFIG.DIN_TO {1} \
    CONFIG.DIN_WIDTH {8} \
    CONFIG.DOUT_WIDTH {1} \
  ] $xlslice_Enable_Gate_Bit1


  # Create instance: xlslice_Enable_Inverter_Bit0, and set properties
  set xlslice_Enable_Inverter_Bit0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_Enable_Inverter_Bit0 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {0} \
    CONFIG.DIN_TO {0} \
    CONFIG.DIN_WIDTH {8} \
  ] $xlslice_Enable_Inverter_Bit0


  # Create interface connections
  connect_bd_intf_net -intf_net smartconnect_0_M06_AXI [get_bd_intf_pins S_AXI] [get_bd_intf_pins axi_gpio_2/S_AXI]

  # Create port connections
  connect_bd_net -net Enable_Gates_CPLD_High_dout [get_bd_pins D1_OUT_28] [get_bd_pins Enable_Gates_CPLD_High/dout]
  connect_bd_net -net Enable_Gates_CPLD_Low_dout [get_bd_pins D1_OUT_26] [get_bd_pins Enable_Gates_CPLD_Low/dout]
  connect_bd_net -net axi_gpio_2_gpio_io_o [get_bd_pins axi_gpio_2/gpio_io_o] [get_bd_pins xlslice_Enable_AXI2TCM_Bit4/Din] [get_bd_pins xlslice_Enable_Gate_Bit1/Din] [get_bd_pins xlslice_Enable_Inverter_Bit0/Din]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins s_axi_aresetn] [get_bd_pins axi_gpio_2/s_axi_aresetn]
  connect_bd_net -net xlslice_Enable_AXI2TCM_Bit4_Dout [get_bd_pins Dout1] [get_bd_pins xlslice_Enable_AXI2TCM_Bit4/Dout]
  connect_bd_net -net xlslice_Enable_Gate_Dout [get_bd_pins D4_OUT_29] [get_bd_pins xlslice_Enable_Gate_Bit1/Dout]
  connect_bd_net -net xlslice_Enable_Inverter_Dout [get_bd_pins Dout] [get_bd_pins xlslice_Enable_Inverter_Bit0/Dout]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins s_axi_aclk] [get_bd_pins axi_gpio_2/s_axi_aclk]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: uz_clocks
proc create_hier_cell_uz_clocks { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_uz_clocks() - Empty argument(s)!"}
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
  create_bd_pin -dir O -type clk clk_50MHz
  create_bd_pin -dir I -type clk clk_in1
  create_bd_pin -dir O -from 0 -to 0 -type rst peripheral_aresetn
  create_bd_pin -dir O -from 0 -to 0 -type rst peripheral_aresetn1
  create_bd_pin -dir O -from 0 -to 0 -type rst peripheral_aresetn2
  create_bd_pin -dir I -type rst resetn
  create_bd_pin -dir O -type clk slowest_sync_clk

  # Create instance: clk_wiz_0, and set properties
  set clk_wiz_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:6.0 clk_wiz_0 ]
  set_property -dict [list \
    CONFIG.AUTO_PRIMITIVE {PLL} \
    CONFIG.CLKOUT1_DRIVES {Buffer} \
    CONFIG.CLKOUT1_JITTER {167.018} \
    CONFIG.CLKOUT1_PHASE_ERROR {114.213} \
    CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {50.000} \
    CONFIG.CLKOUT2_DRIVES {Buffer} \
    CONFIG.CLKOUT2_JITTER {229.364} \
    CONFIG.CLKOUT2_PHASE_ERROR {114.213} \
    CONFIG.CLKOUT2_REQUESTED_OUT_FREQ {10.000} \
    CONFIG.CLKOUT2_USED {true} \
    CONFIG.CLKOUT3_DRIVES {Buffer} \
    CONFIG.CLKOUT3_JITTER {191.697} \
    CONFIG.CLKOUT3_PHASE_ERROR {114.213} \
    CONFIG.CLKOUT3_REQUESTED_OUT_FREQ {25.000} \
    CONFIG.CLKOUT3_USED {true} \
    CONFIG.CLKOUT4_DRIVES {Buffer} \
    CONFIG.CLKOUT5_DRIVES {Buffer} \
    CONFIG.CLKOUT6_DRIVES {Buffer} \
    CONFIG.CLKOUT7_DRIVES {Buffer} \
    CONFIG.CLK_OUT1_PORT {clk_50MHz} \
    CONFIG.CLK_OUT2_PORT {clk_10MHz} \
    CONFIG.CLK_OUT3_PORT {clk_25MHz} \
    CONFIG.FEEDBACK_SOURCE {FDBK_AUTO} \
    CONFIG.MMCM_CLKFBOUT_MULT_F {8} \
    CONFIG.MMCM_CLKIN1_PERIOD {10.000} \
    CONFIG.MMCM_CLKIN2_PERIOD {10.000} \
    CONFIG.MMCM_CLKOUT0_DIVIDE_F {16} \
    CONFIG.MMCM_CLKOUT1_DIVIDE {80} \
    CONFIG.MMCM_CLKOUT2_DIVIDE {32} \
    CONFIG.MMCM_COMPENSATION {AUTO} \
    CONFIG.MMCM_DIVCLK_DIVIDE {1} \
    CONFIG.NUM_OUT_CLKS {3} \
    CONFIG.OVERRIDE_MMCM {false} \
    CONFIG.PRIMITIVE {Auto} \
    CONFIG.PRIM_SOURCE {Single_ended_clock_capable_pin} \
    CONFIG.RESET_PORT {resetn} \
    CONFIG.RESET_TYPE {ACTIVE_LOW} \
    CONFIG.SECONDARY_SOURCE {Single_ended_clock_capable_pin} \
    CONFIG.USE_LOCKED {false} \
    CONFIG.USE_PHASE_ALIGNMENT {false} \
    CONFIG.USE_RESET {true} \
  ] $clk_wiz_0


  # Create instance: proc_sys_reset_100MHz, and set properties
  set proc_sys_reset_100MHz [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 proc_sys_reset_100MHz ]

  # Create instance: proc_sys_reset_10MHz, and set properties
  set proc_sys_reset_10MHz [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 proc_sys_reset_10MHz ]

  # Create instance: proc_sys_reset_25MHz, and set properties
  set proc_sys_reset_25MHz [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 proc_sys_reset_25MHz ]

  # Create instance: proc_sys_reset_50MHz, and set properties
  set proc_sys_reset_50MHz [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 proc_sys_reset_50MHz ]

  # Create port connections
  connect_bd_net -net clk_wiz_0_clk_25MHz [get_bd_pins clk_wiz_0/clk_25MHz] [get_bd_pins proc_sys_reset_25MHz/slowest_sync_clk]
  connect_bd_net -net proc_sys_reset_10MHz_peripheral_aresetn [get_bd_pins peripheral_aresetn2] [get_bd_pins proc_sys_reset_10MHz/peripheral_aresetn]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins peripheral_aresetn] [get_bd_pins proc_sys_reset_100MHz/peripheral_aresetn]
  connect_bd_net -net proc_sys_reset_50MHz_peripheral_aresetn [get_bd_pins peripheral_aresetn1] [get_bd_pins proc_sys_reset_50MHz/peripheral_aresetn]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins clk_in1] [get_bd_pins clk_wiz_0/clk_in1] [get_bd_pins proc_sys_reset_100MHz/slowest_sync_clk]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk2 [get_bd_pins slowest_sync_clk] [get_bd_pins clk_wiz_0/clk_10MHz] [get_bd_pins proc_sys_reset_10MHz/slowest_sync_clk]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk3 [get_bd_pins clk_50MHz] [get_bd_pins clk_wiz_0/clk_50MHz] [get_bd_pins proc_sys_reset_50MHz/slowest_sync_clk]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_resetn0 [get_bd_pins resetn] [get_bd_pins clk_wiz_0/resetn] [get_bd_pins proc_sys_reset_100MHz/ext_reset_in] [get_bd_pins proc_sys_reset_10MHz/ext_reset_in] [get_bd_pins proc_sys_reset_25MHz/ext_reset_in] [get_bd_pins proc_sys_reset_50MHz/ext_reset_in]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: Interrupt
proc create_hier_cell_Interrupt { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_Interrupt() - Empty argument(s)!"}
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

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 S_AXI


  # Create pins
  create_bd_pin -dir I -type rst IPCORE_RESETN
  create_bd_pin -dir I -from 0 -to 0 Interrupt0
  create_bd_pin -dir I -from 0 -to 0 Interrupt1
  create_bd_pin -dir I -from 0 -to 0 Interrupt2
  create_bd_pin -dir I -from 0 -to 0 Interrupt3
  create_bd_pin -dir I -from 0 -to 0 Interrupt4
  create_bd_pin -dir I -from 0 -to 0 Interrupt5
  create_bd_pin -dir O -from 7 -to 0 Interrupt_vector
  create_bd_pin -dir I -type clk clk
  create_bd_pin -dir O trigger_converesions

  # Create instance: Concat_interrupts, and set properties
  set Concat_interrupts [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 Concat_interrupts ]
  set_property CONFIG.NUM_PORTS {8} $Concat_interrupts


  # Create instance: Trigger_f_cc, and set properties
  set Trigger_f_cc [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_timer:2.0 Trigger_f_cc ]
  set_property CONFIG.enable_timer2 {0} $Trigger_f_cc


  # Create instance: adc_delay, and set properties
  set adc_delay [ create_bd_cell -type ip -vlnv xilinx.com:ip:vio:3.0 adc_delay ]
  set_property -dict [list \
    CONFIG.C_NUM_PROBE_IN {0} \
    CONFIG.C_PROBE_OUT0_WIDTH {11} \
  ] $adc_delay


  # Create instance: delay_trigger_0, and set properties
  set block_name delay_trigger
  set block_cell_name delay_trigger_0
  if { [catch {set delay_trigger_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $delay_trigger_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: ila_0, and set properties
  set ila_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:ila:6.2 ila_0 ]
  set_property -dict [list \
    CONFIG.C_DATA_DEPTH {16384} \
    CONFIG.C_ENABLE_ILA_AXI_MON {false} \
    CONFIG.C_MONITOR_TYPE {Native} \
    CONFIG.C_NUM_OF_PROBES {10} \
  ] $ila_0


  # Create instance: mux_axi_ip_1, and set properties
  set mux_axi_ip_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:mux_axi_ip:1.2 mux_axi_ip_1 ]

  # Create instance: vio_interrupt, and set properties
  set vio_interrupt [ create_bd_cell -type ip -vlnv xilinx.com:ip:vio:3.0 vio_interrupt ]
  set_property CONFIG.C_NUM_PROBE_IN {0} $vio_interrupt


  # Create interface connections
  connect_bd_intf_net -intf_net AXI4_Lite_1 [get_bd_intf_pins AXI4_Lite] [get_bd_intf_pins mux_axi_ip_1/AXI4_Lite]
  connect_bd_intf_net -intf_net smartconnect_0_M11_AXI [get_bd_intf_pins S_AXI] [get_bd_intf_pins Trigger_f_cc/S_AXI]

  # Create port connections
  connect_bd_net -net Concat_interrupts_dout [get_bd_pins Concat_interrupts/dout] [get_bd_pins mux_axi_ip_1/interrupts_in]
  connect_bd_net -net Gates_3L_Interrupt_Center [get_bd_pins Interrupt5] [get_bd_pins Concat_interrupts/In5] [get_bd_pins ila_0/probe5]
  connect_bd_net -net Gates_3L_Interrupt_Start [get_bd_pins Interrupt4] [get_bd_pins Concat_interrupts/In4] [get_bd_pins ila_0/probe4]
  connect_bd_net -net Gates_3L_Interrupt_Start_Center [get_bd_pins Interrupt3] [get_bd_pins Concat_interrupts/In3] [get_bd_pins ila_0/probe3]
  connect_bd_net -net Gates_Carrier_triangular_max1 [get_bd_pins Interrupt2] [get_bd_pins Concat_interrupts/In2] [get_bd_pins ila_0/probe2]
  connect_bd_net -net Gates_Carrier_triangular_max_min [get_bd_pins Interrupt0] [get_bd_pins Concat_interrupts/In0] [get_bd_pins ila_0/probe0]
  connect_bd_net -net Gates_Carrier_triangular_min1 [get_bd_pins Interrupt1] [get_bd_pins Concat_interrupts/In1] [get_bd_pins ila_0/probe1]
  connect_bd_net -net Trigger_f_cc_interrupt [get_bd_pins Concat_interrupts/In6] [get_bd_pins Trigger_f_cc/interrupt] [get_bd_pins ila_0/probe6]
  connect_bd_net -net adc_delay_probe_out0 [get_bd_pins adc_delay/probe_out0] [get_bd_pins delay_trigger_0/delay_cycles]
  connect_bd_net -net delay_trigger_0_a_out [get_bd_pins trigger_converesions] [get_bd_pins delay_trigger_0/a_out] [get_bd_pins ila_0/probe9]
  connect_bd_net -net mux_axi_ip_1_interrupt_out_adc [get_bd_pins delay_trigger_0/a_in] [get_bd_pins ila_0/probe7] [get_bd_pins mux_axi_ip_1/interrupt_out_adc]
  connect_bd_net -net mux_axi_ip_1_interrupt_out_isr [get_bd_pins Interrupt_vector] [get_bd_pins mux_axi_ip_1/interrupt_out_isr]
  connect_bd_net -net mux_axi_ip_1_select_out [get_bd_pins ila_0/probe8] [get_bd_pins mux_axi_ip_1/select_out]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins IPCORE_RESETN] [get_bd_pins Trigger_f_cc/s_axi_aresetn] [get_bd_pins mux_axi_ip_1/AXI4_Lite_ARESETN] [get_bd_pins mux_axi_ip_1/IPCORE_RESETN]
  connect_bd_net -net vio_0_probe_out0 [get_bd_pins Concat_interrupts/In7] [get_bd_pins vio_interrupt/probe_out0]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins clk] [get_bd_pins Trigger_f_cc/s_axi_aclk] [get_bd_pins adc_delay/clk] [get_bd_pins delay_trigger_0/clk] [get_bd_pins ila_0/clk] [get_bd_pins mux_axi_ip_1/AXI4_Lite_ACLK] [get_bd_pins mux_axi_ip_1/IPCORE_CLK] [get_bd_pins vio_interrupt/clk]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: DataMover
proc create_hier_cell_DataMover { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_DataMover() - Empty argument(s)!"}
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
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M00_AXI


  # Create pins
  create_bd_pin -dir I -from 127 -to 0 ADC_A1
  create_bd_pin -dir I -from 127 -to 0 ADC_A2
  create_bd_pin -dir I -from 127 -to 0 ADC_A3
  create_bd_pin -dir I -from 0 -to 0 Op2
  create_bd_pin -dir I -from 0 -to 0 Trigger_AXI2TCM
  create_bd_pin -dir I -type clk m00_axi_aclk
  create_bd_pin -dir I -type rst m00_axi_aresetn

  # Create instance: AXI2TCM_0, and set properties
  set AXI2TCM_0 [ create_bd_cell -type ip -vlnv TUM:user:AXI2TCM:1.1 AXI2TCM_0 ]
  set_property CONFIG.C_M00_NUMBER_of_ADCs {24} $AXI2TCM_0


  # Create instance: ila_0, and set properties
  set ila_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:ila:6.2 ila_0 ]
  set_property -dict [list \
    CONFIG.C_ENABLE_ILA_AXI_MON {false} \
    CONFIG.C_MONITOR_TYPE {Native} \
    CONFIG.C_NUM_OF_PROBES {5} \
  ] $ila_0


  # Create instance: util_vector_logic_0, and set properties
  set util_vector_logic_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 util_vector_logic_0 ]
  set_property CONFIG.C_SIZE {1} $util_vector_logic_0


  # Create instance: xlconcat_0, and set properties
  set xlconcat_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0 ]
  set_property CONFIG.NUM_PORTS {3} $xlconcat_0


  # Create interface connections
  connect_bd_intf_net -intf_net AXI2TCM_0_M00_AXI [get_bd_intf_pins M00_AXI] [get_bd_intf_pins AXI2TCM_0/M00_AXI]

  # Create port connections
  connect_bd_net -net ADC_A1_1 [get_bd_pins ADC_A1] [get_bd_pins xlconcat_0/In0]
  connect_bd_net -net ADC_A2_1 [get_bd_pins ADC_A2] [get_bd_pins xlconcat_0/In1]
  connect_bd_net -net ADC_A3_1 [get_bd_pins ADC_A3] [get_bd_pins xlconcat_0/In2]
  connect_bd_net -net ADCs_ADC_values_raw [get_bd_pins AXI2TCM_0/DATA_IN] [get_bd_pins ila_0/probe0] [get_bd_pins xlconcat_0/dout]
  connect_bd_net -net AXI2TCM_0_axi_error [get_bd_pins AXI2TCM_0/axi_error] [get_bd_pins ila_0/probe3]
  connect_bd_net -net AXI2TCM_0_write_done [get_bd_pins AXI2TCM_0/write_done] [get_bd_pins ila_0/probe2]
  connect_bd_net -net DATA_IN1_1 [get_bd_pins Trigger_AXI2TCM] [get_bd_pins ila_0/probe4] [get_bd_pins util_vector_logic_0/Op1]
  connect_bd_net -net Op2_1 [get_bd_pins Op2] [get_bd_pins util_vector_logic_0/Op2]
  connect_bd_net -net init_axi2tcm [get_bd_pins AXI2TCM_0/init_axi_txn] [get_bd_pins ila_0/probe1] [get_bd_pins util_vector_logic_0/Res]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins m00_axi_aresetn] [get_bd_pins AXI2TCM_0/m00_axi_aresetn]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins m00_axi_aclk] [get_bd_pins AXI2TCM_0/m00_axi_aclk] [get_bd_pins ila_0/clk]

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
  set_property -dict [list \
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
  set_property -dict [list \
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
  create_bd_pin -dir O -from 0 -to 0 A3_OUT_CNV_1
  create_bd_pin -dir O -from 127 -to 0 RAW_VALUE
  create_bd_pin -dir I -from 0 -to 0 TRIGGER_CNV
  create_bd_pin -dir I -type clk s00_axi_aclk
  create_bd_pin -dir I -type rst s00_axi_aresetn

  # Create instance: A3_ADC_LTC2311, and set properties
  set A3_ADC_LTC2311 [ create_bd_cell -type ip -vlnv UltraZohm:user:ADC_LTC2311:3.0 A3_ADC_LTC2311 ]
  set_property -dict [list \
    CONFIG.DIFFERENTIAL {false} \
    CONFIG.RES_LSB {0} \
    CONFIG.RES_MSB {34} \
  ] $A3_ADC_LTC2311


  # Create interface connections
  connect_bd_intf_net -intf_net smartconnect_0_M02_AXI [get_bd_intf_pins S00_AXI] [get_bd_intf_pins A3_ADC_LTC2311/S00_AXI]

  # Create port connections
  connect_bd_net -net ADC_LTC2311_2_RAW_VALUE [get_bd_pins RAW_VALUE] [get_bd_pins A3_ADC_LTC2311/RAW_VALUE]
  connect_bd_net -net ADC_LTC2311_2_SS_N [get_bd_pins A3_OUT_CNV_1] [get_bd_pins A3_ADC_LTC2311/SS_N]
  connect_bd_net -net Interrupt_muxed [get_bd_pins TRIGGER_CNV] [get_bd_pins A3_ADC_LTC2311/TRIGGER_CNV]
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
  create_bd_pin -dir O -from 0 -to 0 A2_OUT_CNV_1
  create_bd_pin -dir O -from 127 -to 0 RAW_VALUE
  create_bd_pin -dir I -from 0 -to 0 TRIGGER_CNV
  create_bd_pin -dir I -type clk s00_axi_aclk
  create_bd_pin -dir I -type rst s00_axi_aresetn

  # Create instance: A2_ADC_LTC2311, and set properties
  set A2_ADC_LTC2311 [ create_bd_cell -type ip -vlnv UltraZohm:user:ADC_LTC2311:3.0 A2_ADC_LTC2311 ]
  set_property -dict [list \
    CONFIG.DIFFERENTIAL {false} \
    CONFIG.RES_LSB {0} \
    CONFIG.RES_MSB {34} \
  ] $A2_ADC_LTC2311


  # Create interface connections
  connect_bd_intf_net -intf_net smartconnect_0_M01_AXI [get_bd_intf_pins S00_AXI] [get_bd_intf_pins A2_ADC_LTC2311/S00_AXI]

  # Create port connections
  connect_bd_net -net ADC_LTC2311_0_RAW_VALUE [get_bd_pins RAW_VALUE] [get_bd_pins A2_ADC_LTC2311/RAW_VALUE]
  connect_bd_net -net ADC_LTC2311_0_SS_N [get_bd_pins A2_OUT_CNV_1] [get_bd_pins A2_ADC_LTC2311/SS_N]
  connect_bd_net -net Interrupt_muxed [get_bd_pins TRIGGER_CNV] [get_bd_pins A2_ADC_LTC2311/TRIGGER_CNV]
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
  create_bd_pin -dir O -from 0 -to 0 A1_OUT_CNV_1
  create_bd_pin -dir O -from 127 -to 0 Din
  create_bd_pin -dir I -type clk clk
  create_bd_pin -dir O -from 0 -to 0 probe4
  create_bd_pin -dir I -from 0 -to 0 probe5
  create_bd_pin -dir I -type rst s00_axi_aresetn

  # Create instance: A1_ADC_LTC2311, and set properties
  set A1_ADC_LTC2311 [ create_bd_cell -type ip -vlnv UltraZohm:user:ADC_LTC2311:3.0 A1_ADC_LTC2311 ]
  set_property -dict [list \
    CONFIG.DIFFERENTIAL {false} \
    CONFIG.RES_LSB {0} \
    CONFIG.RES_MSB {34} \
    CONFIG.SPI_MASTER {1} \
  ] $A1_ADC_LTC2311


  # Create instance: adc_debug
  create_hier_cell_adc_debug $hier_obj adc_debug

  # Create interface connections
  connect_bd_intf_net -intf_net smartconnect_0_M00_AXI [get_bd_intf_pins S00_AXI] [get_bd_intf_pins A1_ADC_LTC2311/S00_AXI]

  # Create port connections
  connect_bd_net -net A1_ADC_LTC2311_SAMPLE_COUNTER [get_bd_pins A1_ADC_LTC2311/SAMPLE_COUNTER] [get_bd_pins adc_debug/probe6]
  connect_bd_net -net A1_ADC_LTC2311_SI_VALID [get_bd_pins A1_ADC_LTC2311/SI_VALID] [get_bd_pins adc_debug/probe7]
  connect_bd_net -net A1_ADC_LTC2311_SI_VALUE [get_bd_pins A1_ADC_LTC2311/SI_VALUE] [get_bd_pins adc_debug/Din1]
  connect_bd_net -net ADC_LTC2311_1_RAW_VALUE [get_bd_pins Din] [get_bd_pins A1_ADC_LTC2311/RAW_VALUE] [get_bd_pins adc_debug/Din]
  connect_bd_net -net ADC_LTC2311_1_SS_N [get_bd_pins A1_OUT_CNV_1] [get_bd_pins A1_ADC_LTC2311/SS_N]
  connect_bd_net -net Current_Valid_0_Dout [get_bd_pins probe4] [get_bd_pins A1_ADC_LTC2311/RAW_VALID] [get_bd_pins adc_debug/probe4]
  connect_bd_net -net Interrupt_muxed [get_bd_pins probe5] [get_bd_pins A1_ADC_LTC2311/TRIGGER_CNV] [get_bd_pins adc_debug/probe5]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins s00_axi_aresetn] [get_bd_pins A1_ADC_LTC2311/s00_axi_aresetn]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins clk] [get_bd_pins A1_ADC_LTC2311/s00_axi_aclk] [get_bd_pins adc_debug/clk]

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

  # Create instance: smartconnect_1, and set properties
  set smartconnect_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:smartconnect:1.0 smartconnect_1 ]
  set_property -dict [list \
    CONFIG.NUM_MI {1} \
    CONFIG.NUM_SI {1} \
  ] $smartconnect_1


  # Create instance: uz_axi_testIP_0, and set properties
  set uz_axi_testIP_0 [ create_bd_cell -type ip -vlnv user.org:ip:uz_axi_testIP:1.0 uz_axi_testIP_0 ]

  # Create interface connections
  connect_bd_intf_net -intf_net smartconnect_0_M10_AXI [get_bd_intf_pins S00_AXI] [get_bd_intf_pins smartconnect_1/S00_AXI]
  connect_bd_intf_net -intf_net smartconnect_1_M00_AXI [get_bd_intf_pins smartconnect_1/M00_AXI] [get_bd_intf_pins uz_axi_testIP_0/AXI4]

  # Create port connections
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins aresetn] [get_bd_pins smartconnect_1/aresetn] [get_bd_pins uz_axi_testIP_0/AXI4_ARESETN] [get_bd_pins uz_axi_testIP_0/IPCORE_RESETN]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins aclk] [get_bd_pins smartconnect_1/aclk] [get_bd_pins uz_axi_testIP_0/AXI4_ACLK] [get_bd_pins uz_axi_testIP_0/IPCORE_CLK]

  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: uz_system
proc create_hier_cell_uz_system { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_uz_system() - Empty argument(s)!"}
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
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_0

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_1

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_2

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_Lite_PWM_3

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_0

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_1

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_2

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI4_interlock_3

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M00_AXI

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M00_AXI1

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M01_AXI

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M02_AXI

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M09_AXI

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M10_AXI

  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M12_AXI

  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 S00_AXI


  # Create pins
  create_bd_pin -dir I -from 127 -to 0 ADC_A1
  create_bd_pin -dir I -from 127 -to 0 ADC_A2
  create_bd_pin -dir I -from 127 -to 0 ADC_A3
  create_bd_pin -dir O -from 0 -to 0 D1_OUT_26
  create_bd_pin -dir O -from 0 -to 0 D1_OUT_28
  create_bd_pin -dir O -from 0 -to 0 D1_OUT_29
  create_bd_pin -dir O -from 7 -to 0 D4_OUT
  create_bd_pin -dir O -from 0 -to 0 Dout
  create_bd_pin -dir I -from 0 -to 0 Interrupt0
  create_bd_pin -dir I -from 0 -to 0 Interrupt1
  create_bd_pin -dir I -from 0 -to 0 Interrupt2
  create_bd_pin -dir I -from 0 -to 0 Interrupt3
  create_bd_pin -dir I -from 0 -to 0 Interrupt4
  create_bd_pin -dir I -from 0 -to 0 Interrupt5
  create_bd_pin -dir I -from 0 -to 0 Trigger_AXI2TCM
  create_bd_pin -dir I -type clk clk
  create_bd_pin -dir O -type clk clk_50MHz
  create_bd_pin -dir O -from 0 -to 0 -type rst peripheral_aresetn
  create_bd_pin -dir O -from 0 -to 0 -type rst peripheral_aresetn1
  create_bd_pin -dir O -from 0 -to 0 -type rst peripheral_aresetn2
  create_bd_pin -dir I -type rst resetn
  create_bd_pin -dir O -type clk slowest_sync_clk
  create_bd_pin -dir O trigger_converesions
  create_bd_pin -dir O -type intr wdt_interrupt

  # Create instance: DataMover
  create_hier_cell_DataMover $hier_obj DataMover

  # Create instance: Interrupt
  create_hier_cell_Interrupt $hier_obj Interrupt

  # Create instance: axi_timebase_wdt_0, and set properties
  set axi_timebase_wdt_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_timebase_wdt:3.0 axi_timebase_wdt_0 ]
  set_property -dict [list \
    CONFIG.ENABLE_WINDOW_WDT {1} \
    CONFIG.SST_COUNT_WIDTH {30} \
  ] $axi_timebase_wdt_0


  # Create instance: smartconnect_0, and set properties
  set smartconnect_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:smartconnect:1.0 smartconnect_0 ]
  set_property -dict [list \
    CONFIG.NUM_CLKS {3} \
    CONFIG.NUM_MI {15} \
    CONFIG.NUM_SI {1} \
  ] $smartconnect_0


  # Create instance: smartconnect_1, and set properties
  set smartconnect_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:smartconnect:1.0 smartconnect_1 ]
  set_property -dict [list \
    CONFIG.NUM_MI {5} \
    CONFIG.NUM_SI {1} \
  ] $smartconnect_1


  # Create instance: timer_uptime_64bit, and set properties
  set timer_uptime_64bit [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_timer:2.0 timer_uptime_64bit ]
  set_property CONFIG.mode_64bit {1} $timer_uptime_64bit


  # Create instance: uz_clocks
  create_hier_cell_uz_clocks $hier_obj uz_clocks

  # Create instance: uz_enable
  create_hier_cell_uz_enable $hier_obj uz_enable

  # Create interface connections
  connect_bd_intf_net -intf_net AXI4_Lite_1 [get_bd_intf_pins Interrupt/AXI4_Lite] [get_bd_intf_pins smartconnect_0/M04_AXI]
  connect_bd_intf_net -intf_net Conn1 [get_bd_intf_pins M00_AXI] [get_bd_intf_pins DataMover/M00_AXI]
  connect_bd_intf_net -intf_net Conn2 [get_bd_intf_pins M10_AXI] [get_bd_intf_pins smartconnect_0/M10_AXI]
  connect_bd_intf_net -intf_net Conn3 [get_bd_intf_pins S00_AXI] [get_bd_intf_pins smartconnect_0/S00_AXI]
  connect_bd_intf_net -intf_net Conn4 [get_bd_intf_pins M00_AXI1] [get_bd_intf_pins smartconnect_0/M00_AXI]
  connect_bd_intf_net -intf_net Conn5 [get_bd_intf_pins M02_AXI] [get_bd_intf_pins smartconnect_0/M02_AXI]
  connect_bd_intf_net -intf_net Conn6 [get_bd_intf_pins M01_AXI] [get_bd_intf_pins smartconnect_0/M01_AXI]
  connect_bd_intf_net -intf_net Conn7 [get_bd_intf_pins AXI4_Lite_PWM_0] [get_bd_intf_pins smartconnect_0/M08_AXI]
  connect_bd_intf_net -intf_net Conn8 [get_bd_intf_pins M09_AXI] [get_bd_intf_pins smartconnect_0/M09_AXI]
  connect_bd_intf_net -intf_net Conn10 [get_bd_intf_pins AXI4_interlock_0] [get_bd_intf_pins smartconnect_0/M07_AXI]
  connect_bd_intf_net -intf_net Conn11 [get_bd_intf_pins AXI4_Lite_PWM_1] [get_bd_intf_pins smartconnect_0/M03_AXI]
  connect_bd_intf_net -intf_net Conn12 [get_bd_intf_pins M12_AXI] [get_bd_intf_pins smartconnect_0/M12_AXI]
  connect_bd_intf_net -intf_net S_AXI_1 [get_bd_intf_pins Interrupt/S_AXI] [get_bd_intf_pins smartconnect_0/M11_AXI]
  connect_bd_intf_net -intf_net smartconnect_0_M05_AXI [get_bd_intf_pins smartconnect_0/M05_AXI] [get_bd_intf_pins timer_uptime_64bit/S_AXI]
  connect_bd_intf_net -intf_net smartconnect_0_M06_AXI [get_bd_intf_pins smartconnect_0/M06_AXI] [get_bd_intf_pins uz_enable/S_AXI]
  connect_bd_intf_net -intf_net smartconnect_0_M13_AXI [get_bd_intf_pins axi_timebase_wdt_0/S_AXI] [get_bd_intf_pins smartconnect_0/M13_AXI]
  connect_bd_intf_net -intf_net smartconnect_0_M14_AXI [get_bd_intf_pins smartconnect_0/M14_AXI] [get_bd_intf_pins smartconnect_1/S00_AXI]
  connect_bd_intf_net -intf_net smartconnect_1_M00_AXI [get_bd_intf_pins AXI4_Lite_PWM_2] [get_bd_intf_pins smartconnect_1/M00_AXI]
  connect_bd_intf_net -intf_net smartconnect_1_M01_AXI [get_bd_intf_pins AXI4_Lite_PWM_3] [get_bd_intf_pins smartconnect_1/M01_AXI]
  connect_bd_intf_net -intf_net smartconnect_1_M02_AXI [get_bd_intf_pins AXI4_interlock_1] [get_bd_intf_pins smartconnect_1/M02_AXI]
  connect_bd_intf_net -intf_net smartconnect_1_M03_AXI [get_bd_intf_pins AXI4_interlock_2] [get_bd_intf_pins smartconnect_1/M03_AXI]
  connect_bd_intf_net -intf_net smartconnect_1_M04_AXI [get_bd_intf_pins AXI4_interlock_3] [get_bd_intf_pins smartconnect_1/M04_AXI]

  # Create port connections
  connect_bd_net -net ADC_A1_1 [get_bd_pins ADC_A1] [get_bd_pins DataMover/ADC_A1]
  connect_bd_net -net ADC_A2_1 [get_bd_pins ADC_A2] [get_bd_pins DataMover/ADC_A2]
  connect_bd_net -net ADC_A3_1 [get_bd_pins ADC_A3] [get_bd_pins DataMover/ADC_A3]
  connect_bd_net -net Gates_3L_Interrupt_Center [get_bd_pins Interrupt5] [get_bd_pins Interrupt/Interrupt5]
  connect_bd_net -net Gates_3L_Interrupt_Start [get_bd_pins Interrupt4] [get_bd_pins Interrupt/Interrupt4]
  connect_bd_net -net Gates_3L_Interrupt_Start_Center [get_bd_pins Interrupt3] [get_bd_pins Interrupt/Interrupt3]
  connect_bd_net -net Gates_Carrier_triangular_max1 [get_bd_pins Interrupt2] [get_bd_pins Interrupt/Interrupt2]
  connect_bd_net -net Gates_Carrier_triangular_max_min [get_bd_pins Interrupt0] [get_bd_pins Interrupt/Interrupt0]
  connect_bd_net -net Gates_Carrier_triangular_min1 [get_bd_pins Interrupt1] [get_bd_pins Interrupt/Interrupt1]
  connect_bd_net -net Interrupt_muxed [get_bd_pins trigger_converesions] [get_bd_pins Interrupt/trigger_converesions]
  connect_bd_net -net Op2_1 [get_bd_pins DataMover/Op2] [get_bd_pins uz_enable/Dout1]
  connect_bd_net -net Trigger_AXI2TCM_1 [get_bd_pins Trigger_AXI2TCM] [get_bd_pins DataMover/Trigger_AXI2TCM]
  connect_bd_net -net axi_timebase_wdt_0_wdt_interrupt [get_bd_pins wdt_interrupt] [get_bd_pins axi_timebase_wdt_0/wdt_interrupt]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins peripheral_aresetn] [get_bd_pins DataMover/m00_axi_aresetn] [get_bd_pins Interrupt/IPCORE_RESETN] [get_bd_pins axi_timebase_wdt_0/s_axi_aresetn] [get_bd_pins smartconnect_0/aresetn] [get_bd_pins smartconnect_1/aresetn] [get_bd_pins timer_uptime_64bit/s_axi_aresetn] [get_bd_pins uz_clocks/peripheral_aresetn] [get_bd_pins uz_enable/s_axi_aresetn]
  connect_bd_net -net resetn_1 [get_bd_pins resetn] [get_bd_pins uz_clocks/resetn]
  connect_bd_net -net uz_clocks_clk_50MHz [get_bd_pins clk_50MHz] [get_bd_pins smartconnect_0/aclk2] [get_bd_pins uz_clocks/clk_50MHz]
  connect_bd_net -net uz_clocks_peripheral_aresetn1 [get_bd_pins peripheral_aresetn1] [get_bd_pins uz_clocks/peripheral_aresetn1]
  connect_bd_net -net uz_clocks_peripheral_aresetn2 [get_bd_pins peripheral_aresetn2] [get_bd_pins uz_clocks/peripheral_aresetn2]
  connect_bd_net -net uz_clocks_slowest_sync_clk [get_bd_pins slowest_sync_clk] [get_bd_pins smartconnect_0/aclk1] [get_bd_pins uz_clocks/slowest_sync_clk]
  connect_bd_net -net uz_enable_D1_OUT_26 [get_bd_pins D1_OUT_26] [get_bd_pins uz_enable/D1_OUT_26]
  connect_bd_net -net uz_enable_D1_OUT_28 [get_bd_pins D1_OUT_28] [get_bd_pins uz_enable/D1_OUT_28]
  connect_bd_net -net uz_enable_D4_OUT_29 [get_bd_pins D1_OUT_29] [get_bd_pins uz_enable/D4_OUT_29]
  connect_bd_net -net uz_enable_Dout [get_bd_pins Dout] [get_bd_pins uz_enable/Dout]
  connect_bd_net -net xlconcat_0_dout [get_bd_pins D4_OUT] [get_bd_pins Interrupt/Interrupt_vector]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins clk] [get_bd_pins DataMover/m00_axi_aclk] [get_bd_pins Interrupt/clk] [get_bd_pins axi_timebase_wdt_0/s_axi_aclk] [get_bd_pins smartconnect_0/aclk] [get_bd_pins smartconnect_1/aclk] [get_bd_pins timer_uptime_64bit/s_axi_aclk] [get_bd_pins uz_clocks/clk_in1] [get_bd_pins uz_enable/s_axi_aclk]

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
  create_bd_pin -dir O -from 0 -to 0 A1_OUT_CNV_1
  create_bd_pin -dir O -from 0 -to 0 A2_OUT_CNV_1
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
  connect_bd_net -net A1_adapter_Din [get_bd_pins Din] [get_bd_pins A1_adapter/Din]
  connect_bd_net -net A1_adapter_probe4 [get_bd_pins probe4] [get_bd_pins A1_adapter/probe4]
  connect_bd_net -net A2_adapter_RAW_VALUE [get_bd_pins RAW_VALUE1] [get_bd_pins A2_adapter/RAW_VALUE]
  connect_bd_net -net A3_adapter_RAW_VALUE [get_bd_pins RAW_VALUE] [get_bd_pins A3_adapter/RAW_VALUE]
  connect_bd_net -net ADC_LTC2311_0_SS_N [get_bd_pins A2_OUT_CNV_1] [get_bd_pins A2_adapter/A2_OUT_CNV_1]
  connect_bd_net -net ADC_LTC2311_1_SS_N [get_bd_pins A1_OUT_CNV_1] [get_bd_pins A1_adapter/A1_OUT_CNV_1]
  connect_bd_net -net ADC_LTC2311_2_SS_N [get_bd_pins A3_OUT_CNV_1] [get_bd_pins A3_adapter/A3_OUT_CNV_1]
  connect_bd_net -net Interrupt_muxed [get_bd_pins TRIGGER_CNV] [get_bd_pins A1_adapter/probe5] [get_bd_pins A2_adapter/TRIGGER_CNV] [get_bd_pins A3_adapter/TRIGGER_CNV]
  connect_bd_net -net proc_sys_reset_1_peripheral_aresetn [get_bd_pins s00_axi_aresetn] [get_bd_pins A1_adapter/s00_axi_aresetn] [get_bd_pins A2_adapter/s00_axi_aresetn] [get_bd_pins A3_adapter/s00_axi_aresetn]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk1 [get_bd_pins s00_axi_aclk] [get_bd_pins A1_adapter/clk] [get_bd_pins A2_adapter/s00_axi_aclk] [get_bd_pins A3_adapter/s00_axi_aclk]

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

  # Create ports

  # Create instance: uz_analog_adapter
  create_hier_cell_uz_analog_adapter [current_bd_instance .] uz_analog_adapter

  # Create instance: uz_digital_adapter
  create_hier_cell_uz_digital_adapter [current_bd_instance .] uz_digital_adapter

  # Create instance: uz_system
  create_hier_cell_uz_system [current_bd_instance .] uz_system

  # Create instance: uz_user
  create_hier_cell_uz_user [current_bd_instance .] uz_user

  # Create instance: xlconstant_0, and set properties
  set xlconstant_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_0 ]

  # Create instance: zynq_ultra_ps_e_0, and set properties
  set zynq_ultra_ps_e_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:zynq_ultra_ps_e:3.4 zynq_ultra_ps_e_0 ]
  set_property -dict [list \
    CONFIG.PSU_BANK_0_IO_STANDARD {LVCMOS18} \
    CONFIG.PSU_BANK_1_IO_STANDARD {LVCMOS18} \
    CONFIG.PSU_BANK_2_IO_STANDARD {LVCMOS18} \
    CONFIG.PSU_BANK_3_IO_STANDARD {LVCMOS18} \
    CONFIG.PSU_DDR_RAM_HIGHADDR {0xFFFFFFFF} \
    CONFIG.PSU_DDR_RAM_HIGHADDR_OFFSET {0x800000000} \
    CONFIG.PSU_DDR_RAM_LOWADDR_OFFSET {0x80000000} \
    CONFIG.PSU_MIO_0_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_0_SLEW {slow} \
    CONFIG.PSU_MIO_10_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_10_SLEW {slow} \
    CONFIG.PSU_MIO_11_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_11_SLEW {slow} \
    CONFIG.PSU_MIO_12_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_12_POLARITY {Default} \
    CONFIG.PSU_MIO_12_SLEW {slow} \
    CONFIG.PSU_MIO_13_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_13_POLARITY {Default} \
    CONFIG.PSU_MIO_13_SLEW {slow} \
    CONFIG.PSU_MIO_14_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_14_POLARITY {Default} \
    CONFIG.PSU_MIO_14_SLEW {slow} \
    CONFIG.PSU_MIO_15_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_15_POLARITY {Default} \
    CONFIG.PSU_MIO_15_SLEW {slow} \
    CONFIG.PSU_MIO_16_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_16_POLARITY {Default} \
    CONFIG.PSU_MIO_16_SLEW {slow} \
    CONFIG.PSU_MIO_17_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_17_POLARITY {Default} \
    CONFIG.PSU_MIO_17_SLEW {slow} \
    CONFIG.PSU_MIO_18_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_18_POLARITY {Default} \
    CONFIG.PSU_MIO_18_SLEW {slow} \
    CONFIG.PSU_MIO_19_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_19_POLARITY {Default} \
    CONFIG.PSU_MIO_19_SLEW {slow} \
    CONFIG.PSU_MIO_1_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_1_SLEW {slow} \
    CONFIG.PSU_MIO_20_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_20_POLARITY {Default} \
    CONFIG.PSU_MIO_20_SLEW {slow} \
    CONFIG.PSU_MIO_21_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_21_POLARITY {Default} \
    CONFIG.PSU_MIO_21_SLEW {slow} \
    CONFIG.PSU_MIO_22_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_22_INPUT_TYPE {cmos} \
    CONFIG.PSU_MIO_22_POLARITY {Default} \
    CONFIG.PSU_MIO_22_SLEW {slow} \
    CONFIG.PSU_MIO_23_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_23_POLARITY {Default} \
    CONFIG.PSU_MIO_23_SLEW {slow} \
    CONFIG.PSU_MIO_24_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_24_SLEW {slow} \
    CONFIG.PSU_MIO_25_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_25_SLEW {slow} \
    CONFIG.PSU_MIO_27_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_27_SLEW {slow} \
    CONFIG.PSU_MIO_29_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_29_SLEW {slow} \
    CONFIG.PSU_MIO_2_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_2_SLEW {slow} \
    CONFIG.PSU_MIO_32_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_32_INPUT_TYPE {cmos} \
    CONFIG.PSU_MIO_32_POLARITY {Default} \
    CONFIG.PSU_MIO_32_SLEW {slow} \
    CONFIG.PSU_MIO_33_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_33_INPUT_TYPE {cmos} \
    CONFIG.PSU_MIO_33_POLARITY {Default} \
    CONFIG.PSU_MIO_33_SLEW {slow} \
    CONFIG.PSU_MIO_34_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_34_INPUT_TYPE {cmos} \
    CONFIG.PSU_MIO_34_POLARITY {Default} \
    CONFIG.PSU_MIO_34_SLEW {slow} \
    CONFIG.PSU_MIO_35_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_35_SLEW {slow} \
    CONFIG.PSU_MIO_36_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_36_SLEW {slow} \
    CONFIG.PSU_MIO_37_INPUT_TYPE {schmitt} \
    CONFIG.PSU_MIO_38_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_38_SLEW {slow} \
    CONFIG.PSU_MIO_39_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_39_SLEW {slow} \
    CONFIG.PSU_MIO_3_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_3_SLEW {slow} \
    CONFIG.PSU_MIO_40_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_40_SLEW {slow} \
    CONFIG.PSU_MIO_41_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_41_SLEW {slow} \
    CONFIG.PSU_MIO_42_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_42_SLEW {slow} \
    CONFIG.PSU_MIO_43_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_43_SLEW {slow} \
    CONFIG.PSU_MIO_4_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_4_SLEW {slow} \
    CONFIG.PSU_MIO_50_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_50_SLEW {slow} \
    CONFIG.PSU_MIO_51_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_51_INPUT_TYPE {cmos} \
    CONFIG.PSU_MIO_51_SLEW {slow} \
    CONFIG.PSU_MIO_52_DIRECTION {in} \
    CONFIG.PSU_MIO_52_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_52_SLEW {fast} \
    CONFIG.PSU_MIO_53_DIRECTION {in} \
    CONFIG.PSU_MIO_53_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_53_SLEW {fast} \
    CONFIG.PSU_MIO_54_DIRECTION {inout} \
    CONFIG.PSU_MIO_54_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_54_SLEW {slow} \
    CONFIG.PSU_MIO_55_DIRECTION {in} \
    CONFIG.PSU_MIO_55_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_55_SLEW {fast} \
    CONFIG.PSU_MIO_56_DIRECTION {inout} \
    CONFIG.PSU_MIO_56_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_56_SLEW {slow} \
    CONFIG.PSU_MIO_57_DIRECTION {inout} \
    CONFIG.PSU_MIO_57_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_57_SLEW {slow} \
    CONFIG.PSU_MIO_58_DIRECTION {out} \
    CONFIG.PSU_MIO_58_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_58_INPUT_TYPE {cmos} \
    CONFIG.PSU_MIO_58_SLEW {slow} \
    CONFIG.PSU_MIO_59_DIRECTION {inout} \
    CONFIG.PSU_MIO_59_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_59_SLEW {slow} \
    CONFIG.PSU_MIO_5_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_5_SLEW {slow} \
    CONFIG.PSU_MIO_60_DIRECTION {inout} \
    CONFIG.PSU_MIO_60_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_60_SLEW {slow} \
    CONFIG.PSU_MIO_61_DIRECTION {inout} \
    CONFIG.PSU_MIO_61_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_61_SLEW {slow} \
    CONFIG.PSU_MIO_62_DIRECTION {inout} \
    CONFIG.PSU_MIO_62_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_62_SLEW {slow} \
    CONFIG.PSU_MIO_63_DIRECTION {inout} \
    CONFIG.PSU_MIO_63_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_63_SLEW {slow} \
    CONFIG.PSU_MIO_64_DIRECTION {in} \
    CONFIG.PSU_MIO_64_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_64_INPUT_TYPE {cmos} \
    CONFIG.PSU_MIO_64_SLEW {fast} \
    CONFIG.PSU_MIO_65_DIRECTION {in} \
    CONFIG.PSU_MIO_65_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_65_INPUT_TYPE {cmos} \
    CONFIG.PSU_MIO_65_SLEW {fast} \
    CONFIG.PSU_MIO_66_DIRECTION {inout} \
    CONFIG.PSU_MIO_66_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_66_INPUT_TYPE {cmos} \
    CONFIG.PSU_MIO_66_SLEW {slow} \
    CONFIG.PSU_MIO_67_DIRECTION {in} \
    CONFIG.PSU_MIO_67_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_67_INPUT_TYPE {cmos} \
    CONFIG.PSU_MIO_67_SLEW {fast} \
    CONFIG.PSU_MIO_68_DIRECTION {inout} \
    CONFIG.PSU_MIO_68_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_68_INPUT_TYPE {cmos} \
    CONFIG.PSU_MIO_68_SLEW {slow} \
    CONFIG.PSU_MIO_69_DIRECTION {inout} \
    CONFIG.PSU_MIO_69_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_69_INPUT_TYPE {cmos} \
    CONFIG.PSU_MIO_69_SLEW {slow} \
    CONFIG.PSU_MIO_6_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_6_SLEW {slow} \
    CONFIG.PSU_MIO_70_DIRECTION {out} \
    CONFIG.PSU_MIO_70_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_70_INPUT_TYPE {cmos} \
    CONFIG.PSU_MIO_70_SLEW {fast} \
    CONFIG.PSU_MIO_71_DIRECTION {inout} \
    CONFIG.PSU_MIO_71_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_71_INPUT_TYPE {schmitt} \
    CONFIG.PSU_MIO_71_SLEW {fast} \
    CONFIG.PSU_MIO_72_DIRECTION {inout} \
    CONFIG.PSU_MIO_72_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_72_INPUT_TYPE {schmitt} \
    CONFIG.PSU_MIO_72_SLEW {fast} \
    CONFIG.PSU_MIO_73_DIRECTION {inout} \
    CONFIG.PSU_MIO_73_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_73_INPUT_TYPE {schmitt} \
    CONFIG.PSU_MIO_73_SLEW {fast} \
    CONFIG.PSU_MIO_74_DIRECTION {inout} \
    CONFIG.PSU_MIO_74_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_74_INPUT_TYPE {schmitt} \
    CONFIG.PSU_MIO_74_SLEW {fast} \
    CONFIG.PSU_MIO_75_DIRECTION {inout} \
    CONFIG.PSU_MIO_75_DRIVE_STRENGTH {12} \
    CONFIG.PSU_MIO_75_INPUT_TYPE {schmitt} \
    CONFIG.PSU_MIO_75_SLEW {fast} \
    CONFIG.PSU_MIO_76_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_76_SLEW {slow} \
    CONFIG.PSU_MIO_77_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_77_SLEW {slow} \
    CONFIG.PSU_MIO_7_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_7_INPUT_TYPE {cmos} \
    CONFIG.PSU_MIO_7_POLARITY {Default} \
    CONFIG.PSU_MIO_7_SLEW {slow} \
    CONFIG.PSU_MIO_8_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_8_POLARITY {Default} \
    CONFIG.PSU_MIO_8_SLEW {slow} \
    CONFIG.PSU_MIO_9_DRIVE_STRENGTH {4} \
    CONFIG.PSU_MIO_9_SLEW {slow} \
    CONFIG.PSU_MIO_TREE_PERIPHERALS {Quad SPI Flash#Quad SPI Flash#Quad SPI Flash#Quad SPI Flash#Quad SPI Flash#Quad SPI Flash#SPI 1#GPIO0 MIO#GPIO0 MIO#SPI 1#SPI 1#SPI 1#GPIO0 MIO#GPIO0 MIO#GPIO0 MIO#GPIO0\
MIO#GPIO0 MIO#GPIO0 MIO#GPIO0 MIO#GPIO0 MIO#GPIO0 MIO#GPIO0 MIO#GPIO0 MIO#GPIO0 MIO#I2C 1#I2C 1#PMU GPI 0#DPAUX#DPAUX#DPAUX#DPAUX#PMU GPI 5#GPIO1 MIO#GPIO1 MIO#GPIO1 MIO#PMU GPO 3#UART 1#UART 1#Gem 1#Gem\
1#Gem 1#Gem 1#Gem 1#Gem 1#Gem 1#Gem 1#Gem 1#Gem 1#Gem 1#Gem 1#MDIO 1#MDIO 1#########################USB0 Reset#USB1 Reset} \
    CONFIG.PSU_MIO_TREE_SIGNALS {sclk_out#miso_mo1#mo2#mo3#mosi_mi0#n_ss_out#sclk_out#gpio0[7]#gpio0[8]#n_ss_out[0]#miso#mosi#gpio0[12]#gpio0[13]#gpio0[14]#gpio0[15]#gpio0[16]#gpio0[17]#gpio0[18]#gpio0[19]#gpio0[20]#gpio0[21]#gpio0[22]#gpio0[23]#scl_out#sda_out#gpi[0]#dp_aux_data_out#dp_hot_plug_detect#dp_aux_data_oe#dp_aux_data_in#gpi[5]#gpio1[32]#gpio1[33]#gpio1[34]#gpo[3]#txd#rxd#rgmii_tx_clk#rgmii_txd[0]#rgmii_txd[1]#rgmii_txd[2]#rgmii_txd[3]#rgmii_tx_ctl#rgmii_rx_clk#rgmii_rxd[0]#rgmii_rxd[1]#rgmii_rxd[2]#rgmii_rxd[3]#rgmii_rx_ctl#gem1_mdc#gem1_mdio_out#########################reset#reset}\
\
    CONFIG.PSU_USB3__DUAL_CLOCK_ENABLE {0} \
    CONFIG.PSU__ACT_DDR_FREQ_MHZ {1066.656006} \
    CONFIG.PSU__CRF_APB__ACPU_CTRL__ACT_FREQMHZ {1333.333008} \
    CONFIG.PSU__CRF_APB__ACPU_CTRL__FREQMHZ {1333.333} \
    CONFIG.PSU__CRF_APB__ACPU_CTRL__SRCSEL {APLL} \
    CONFIG.PSU__CRF_APB__ACPU__FRAC_ENABLED {1} \
    CONFIG.PSU__CRF_APB__APLL_CTRL__FRACFREQ {1333.333} \
    CONFIG.PSU__CRF_APB__APLL_CTRL__SRCSEL {PSS_REF_CLK} \
    CONFIG.PSU__CRF_APB__APLL_FRAC_CFG__ENABLED {1} \
    CONFIG.PSU__CRF_APB__DBG_FPD_CTRL__ACT_FREQMHZ {249.997498} \
    CONFIG.PSU__CRF_APB__DBG_FPD_CTRL__FREQMHZ {250} \
    CONFIG.PSU__CRF_APB__DBG_FPD_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRF_APB__DBG_TRACE_CTRL__FREQMHZ {250} \
    CONFIG.PSU__CRF_APB__DBG_TRACE_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRF_APB__DBG_TSTMP_CTRL__ACT_FREQMHZ {249.997498} \
    CONFIG.PSU__CRF_APB__DBG_TSTMP_CTRL__FREQMHZ {250} \
    CONFIG.PSU__CRF_APB__DBG_TSTMP_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRF_APB__DDR_CTRL__ACT_FREQMHZ {533.328003} \
    CONFIG.PSU__CRF_APB__DDR_CTRL__FREQMHZ {1200} \
    CONFIG.PSU__CRF_APB__DDR_CTRL__SRCSEL {DPLL} \
    CONFIG.PSU__CRF_APB__DPDMA_REF_CTRL__ACT_FREQMHZ {444.444336} \
    CONFIG.PSU__CRF_APB__DPDMA_REF_CTRL__FREQMHZ {600} \
    CONFIG.PSU__CRF_APB__DPDMA_REF_CTRL__SRCSEL {APLL} \
    CONFIG.PSU__CRF_APB__DPLL_CTRL__SRCSEL {PSS_REF_CLK} \
    CONFIG.PSU__CRF_APB__DP_AUDIO_REF_CTRL__ACT_FREQMHZ {24.242182} \
    CONFIG.PSU__CRF_APB__DP_AUDIO_REF_CTRL__FREQMHZ {25} \
    CONFIG.PSU__CRF_APB__DP_AUDIO_REF_CTRL__SRCSEL {RPLL} \
    CONFIG.PSU__CRF_APB__DP_AUDIO__FRAC_ENABLED {0} \
    CONFIG.PSU__CRF_APB__DP_STC_REF_CTRL__ACT_FREQMHZ {26.666401} \
    CONFIG.PSU__CRF_APB__DP_STC_REF_CTRL__FREQMHZ {27} \
    CONFIG.PSU__CRF_APB__DP_STC_REF_CTRL__SRCSEL {RPLL} \
    CONFIG.PSU__CRF_APB__DP_VIDEO_REF_CTRL__ACT_FREQMHZ {299.997009} \
    CONFIG.PSU__CRF_APB__DP_VIDEO_REF_CTRL__FREQMHZ {300} \
    CONFIG.PSU__CRF_APB__DP_VIDEO_REF_CTRL__SRCSEL {VPLL} \
    CONFIG.PSU__CRF_APB__DP_VIDEO__FRAC_ENABLED {0} \
    CONFIG.PSU__CRF_APB__GDMA_REF_CTRL__ACT_FREQMHZ {533.328003} \
    CONFIG.PSU__CRF_APB__GDMA_REF_CTRL__FREQMHZ {600} \
    CONFIG.PSU__CRF_APB__GDMA_REF_CTRL__SRCSEL {DPLL} \
    CONFIG.PSU__CRF_APB__GPU_REF_CTRL__ACT_FREQMHZ {499.994995} \
    CONFIG.PSU__CRF_APB__GPU_REF_CTRL__FREQMHZ {600} \
    CONFIG.PSU__CRF_APB__GPU_REF_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRF_APB__PCIE_REF_CTRL__ACT_FREQMHZ {249.997498} \
    CONFIG.PSU__CRF_APB__TOPSW_LSBUS_CTRL__ACT_FREQMHZ {99.999001} \
    CONFIG.PSU__CRF_APB__TOPSW_LSBUS_CTRL__FREQMHZ {100} \
    CONFIG.PSU__CRF_APB__TOPSW_LSBUS_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRF_APB__TOPSW_MAIN_CTRL__ACT_FREQMHZ {533.328003} \
    CONFIG.PSU__CRF_APB__TOPSW_MAIN_CTRL__FREQMHZ {533.33} \
    CONFIG.PSU__CRF_APB__TOPSW_MAIN_CTRL__SRCSEL {DPLL} \
    CONFIG.PSU__CRF_APB__VPLL_CTRL__SRCSEL {PSS_REF_CLK} \
    CONFIG.PSU__CRL_APB__ADMA_REF_CTRL__ACT_FREQMHZ {499.994995} \
    CONFIG.PSU__CRL_APB__ADMA_REF_CTRL__FREQMHZ {500} \
    CONFIG.PSU__CRL_APB__ADMA_REF_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRL_APB__AMS_REF_CTRL__ACT_FREQMHZ {49.999500} \
    CONFIG.PSU__CRL_APB__CPU_R5_CTRL__ACT_FREQMHZ {533.328003} \
    CONFIG.PSU__CRL_APB__CPU_R5_CTRL__FREQMHZ {533.333} \
    CONFIG.PSU__CRL_APB__CPU_R5_CTRL__SRCSEL {RPLL} \
    CONFIG.PSU__CRL_APB__DBG_LPD_CTRL__ACT_FREQMHZ {249.997498} \
    CONFIG.PSU__CRL_APB__DBG_LPD_CTRL__FREQMHZ {250} \
    CONFIG.PSU__CRL_APB__DBG_LPD_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRL_APB__DLL_REF_CTRL__ACT_FREQMHZ {999.989990} \
    CONFIG.PSU__CRL_APB__GEM0_REF_CTRL__ACT_FREQMHZ {124.998749} \
    CONFIG.PSU__CRL_APB__GEM1_REF_CTRL__ACT_FREQMHZ {124.998749} \
    CONFIG.PSU__CRL_APB__GEM3_REF_CTRL__ACT_FREQMHZ {124.998749} \
    CONFIG.PSU__CRL_APB__GEM_TSU_REF_CTRL__ACT_FREQMHZ {249.997498} \
    CONFIG.PSU__CRL_APB__GEM_TSU_REF_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRL_APB__I2C1_REF_CTRL__ACT_FREQMHZ {99.999001} \
    CONFIG.PSU__CRL_APB__IOPLL_CTRL__SRCSEL {PSS_REF_CLK} \
    CONFIG.PSU__CRL_APB__IOU_SWITCH_CTRL__ACT_FREQMHZ {249.997498} \
    CONFIG.PSU__CRL_APB__IOU_SWITCH_CTRL__FREQMHZ {250} \
    CONFIG.PSU__CRL_APB__IOU_SWITCH_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRL_APB__LPD_LSBUS_CTRL__ACT_FREQMHZ {99.999001} \
    CONFIG.PSU__CRL_APB__LPD_LSBUS_CTRL__FREQMHZ {100} \
    CONFIG.PSU__CRL_APB__LPD_LSBUS_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRL_APB__LPD_SWITCH_CTRL__ACT_FREQMHZ {499.994995} \
    CONFIG.PSU__CRL_APB__LPD_SWITCH_CTRL__FREQMHZ {500} \
    CONFIG.PSU__CRL_APB__LPD_SWITCH_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRL_APB__PCAP_CTRL__ACT_FREQMHZ {199.998001} \
    CONFIG.PSU__CRL_APB__PCAP_CTRL__FREQMHZ {200} \
    CONFIG.PSU__CRL_APB__PCAP_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRL_APB__PL0_REF_CTRL__ACT_FREQMHZ {99.999001} \
    CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {100} \
    CONFIG.PSU__CRL_APB__PL0_REF_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRL_APB__PL1_REF_CTRL__ACT_FREQMHZ {99.999001} \
    CONFIG.PSU__CRL_APB__QSPI_REF_CTRL__ACT_FREQMHZ {124.998749} \
    CONFIG.PSU__CRL_APB__QSPI_REF_CTRL__FREQMHZ {125} \
    CONFIG.PSU__CRL_APB__QSPI_REF_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRL_APB__RPLL_CTRL__SRCSEL {PSS_REF_CLK} \
    CONFIG.PSU__CRL_APB__SPI1_REF_CTRL__ACT_FREQMHZ {199.998001} \
    CONFIG.PSU__CRL_APB__SPI1_REF_CTRL__FREQMHZ {200} \
    CONFIG.PSU__CRL_APB__SPI1_REF_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRL_APB__TIMESTAMP_REF_CTRL__ACT_FREQMHZ {99.999001} \
    CONFIG.PSU__CRL_APB__TIMESTAMP_REF_CTRL__FREQMHZ {100} \
    CONFIG.PSU__CRL_APB__TIMESTAMP_REF_CTRL__SRCSEL {IOPLL} \
    CONFIG.PSU__CRL_APB__UART0_REF_CTRL__ACT_FREQMHZ {99.999001} \
    CONFIG.PSU__CRL_APB__UART1_REF_CTRL__ACT_FREQMHZ {99.999001} \
    CONFIG.PSU__CRL_APB__USB0_BUS_REF_CTRL__ACT_FREQMHZ {249.997498} \
    CONFIG.PSU__CRL_APB__USB1_BUS_REF_CTRL__ACT_FREQMHZ {249.997498} \
    CONFIG.PSU__CRL_APB__USB3_DUAL_REF_CTRL__ACT_FREQMHZ {19.999800} \
    CONFIG.PSU__CRL_APB__USB3__ENABLE {0} \
    CONFIG.PSU__CSUPMU__PERIPHERAL__VALID {1} \
    CONFIG.PSU__DDRC__BG_ADDR_COUNT {1} \
    CONFIG.PSU__DDRC__BRC_MAPPING {ROW_BANK_COL} \
    CONFIG.PSU__DDRC__BUS_WIDTH {64 Bit} \
    CONFIG.PSU__DDRC__CL {16} \
    CONFIG.PSU__DDRC__CLOCK_STOP_EN {0} \
    CONFIG.PSU__DDRC__COMPONENTS {Components} \
    CONFIG.PSU__DDRC__CWL {14} \
    CONFIG.PSU__DDRC__DDR4_ADDR_MAPPING {0} \
    CONFIG.PSU__DDRC__DDR4_CAL_MODE_ENABLE {0} \
    CONFIG.PSU__DDRC__DDR4_CRC_CONTROL {0} \
    CONFIG.PSU__DDRC__DDR4_T_REF_MODE {0} \
    CONFIG.PSU__DDRC__DDR4_T_REF_RANGE {Normal (0-85)} \
    CONFIG.PSU__DDRC__DEVICE_CAPACITY {8192 MBits} \
    CONFIG.PSU__DDRC__DM_DBI {DM_NO_DBI} \
    CONFIG.PSU__DDRC__DRAM_WIDTH {16 Bits} \
    CONFIG.PSU__DDRC__ECC {Disabled} \
    CONFIG.PSU__DDRC__FGRM {1X} \
    CONFIG.PSU__DDRC__LP_ASR {manual normal} \
    CONFIG.PSU__DDRC__MEMORY_TYPE {DDR 4} \
    CONFIG.PSU__DDRC__PARITY_ENABLE {0} \
    CONFIG.PSU__DDRC__PER_BANK_REFRESH {0} \
    CONFIG.PSU__DDRC__PHY_DBI_MODE {0} \
    CONFIG.PSU__DDRC__RANK_ADDR_COUNT {0} \
    CONFIG.PSU__DDRC__ROW_ADDR_COUNT {16} \
    CONFIG.PSU__DDRC__SELF_REF_ABORT {0} \
    CONFIG.PSU__DDRC__SPEED_BIN {DDR4_2400R} \
    CONFIG.PSU__DDRC__STATIC_RD_MODE {0} \
    CONFIG.PSU__DDRC__TRAIN_DATA_EYE {1} \
    CONFIG.PSU__DDRC__TRAIN_READ_GATE {1} \
    CONFIG.PSU__DDRC__TRAIN_WRITE_LEVEL {1} \
    CONFIG.PSU__DDRC__T_FAW {30.0} \
    CONFIG.PSU__DDRC__T_RAS_MIN {33} \
    CONFIG.PSU__DDRC__T_RC {47.06} \
    CONFIG.PSU__DDRC__T_RCD {16} \
    CONFIG.PSU__DDRC__T_RP {16} \
    CONFIG.PSU__DDRC__VREF {1} \
    CONFIG.PSU__DDR_HIGH_ADDRESS_GUI_ENABLE {1} \
    CONFIG.PSU__DDR__INTERFACE__FREQMHZ {600.000} \
    CONFIG.PSU__DISPLAYPORT__LANE0__ENABLE {1} \
    CONFIG.PSU__DISPLAYPORT__LANE0__IO {GT Lane1} \
    CONFIG.PSU__DISPLAYPORT__LANE1__ENABLE {0} \
    CONFIG.PSU__DISPLAYPORT__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__DPAUX__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__DPAUX__PERIPHERAL__IO {MIO 27 .. 30} \
    CONFIG.PSU__DP__LANE_SEL {None} \
    CONFIG.PSU__ENET0__PERIPHERAL__ENABLE {0} \
    CONFIG.PSU__ENET1__FIFO__ENABLE {0} \
    CONFIG.PSU__ENET1__GRP_MDIO__ENABLE {1} \
    CONFIG.PSU__ENET1__GRP_MDIO__IO {MIO 50 .. 51} \
    CONFIG.PSU__ENET1__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__ENET1__PERIPHERAL__IO {MIO 38 .. 49} \
    CONFIG.PSU__ENET1__PTP__ENABLE {0} \
    CONFIG.PSU__ENET1__TSU__ENABLE {0} \
    CONFIG.PSU__ENET3__PERIPHERAL__ENABLE {0} \
    CONFIG.PSU__FPD_SLCR__WDT1__ACT_FREQMHZ {99.999001} \
    CONFIG.PSU__FPGA_PL0_ENABLE {1} \
    CONFIG.PSU__FPGA_PL1_ENABLE {0} \
    CONFIG.PSU__GEM1_COHERENCY {0} \
    CONFIG.PSU__GEM1_ROUTE_THROUGH_FPD {0} \
    CONFIG.PSU__GEM__TSU__ENABLE {0} \
    CONFIG.PSU__GPIO0_MIO__IO {MIO 0 .. 25} \
    CONFIG.PSU__GPIO0_MIO__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__GPIO1_MIO__IO {MIO 26 .. 51} \
    CONFIG.PSU__GPIO1_MIO__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__GPIO2_MIO__PERIPHERAL__ENABLE {0} \
    CONFIG.PSU__GPIO_EMIO_WIDTH {1} \
    CONFIG.PSU__GPIO_EMIO__PERIPHERAL__ENABLE {0} \
    CONFIG.PSU__GPIO_EMIO__WIDTH {[91:0]} \
    CONFIG.PSU__GT__LINK_SPEED {HBR} \
    CONFIG.PSU__GT__PRE_EMPH_LVL_4 {0} \
    CONFIG.PSU__GT__VLT_SWNG_LVL_4 {0} \
    CONFIG.PSU__I2C1__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__I2C1__PERIPHERAL__IO {MIO 24 .. 25} \
    CONFIG.PSU__IOU_SLCR__IOU_TTC_APB_CLK__TTC0_SEL {APB} \
    CONFIG.PSU__IOU_SLCR__IOU_TTC_APB_CLK__TTC1_SEL {APB} \
    CONFIG.PSU__IOU_SLCR__IOU_TTC_APB_CLK__TTC2_SEL {APB} \
    CONFIG.PSU__IOU_SLCR__IOU_TTC_APB_CLK__TTC3_SEL {APB} \
    CONFIG.PSU__IOU_SLCR__TTC0__ACT_FREQMHZ {100.000000} \
    CONFIG.PSU__IOU_SLCR__TTC1__ACT_FREQMHZ {100.000000} \
    CONFIG.PSU__IOU_SLCR__TTC2__ACT_FREQMHZ {100.000000} \
    CONFIG.PSU__IOU_SLCR__TTC3__ACT_FREQMHZ {100.000000} \
    CONFIG.PSU__IOU_SLCR__WDT0__ACT_FREQMHZ {99.999001} \
    CONFIG.PSU__LPD_SLCR__CSUPMU__ACT_FREQMHZ {100.000000} \
    CONFIG.PSU__MAXIGP2__DATA_WIDTH {128} \
    CONFIG.PSU__NUM_FABRIC_RESETS {4} \
    CONFIG.PSU__OVERRIDE__BASIC_CLOCK {0} \
    CONFIG.PSU__PCIE__CLASS_CODE_BASE {} \
    CONFIG.PSU__PCIE__CLASS_CODE_INTERFACE {} \
    CONFIG.PSU__PCIE__CLASS_CODE_SUB {} \
    CONFIG.PSU__PCIE__DEVICE_ID {} \
    CONFIG.PSU__PCIE__INTX_GENERATION {0} \
    CONFIG.PSU__PCIE__PERIPHERAL__ENABLE {0} \
    CONFIG.PSU__PCIE__PERIPHERAL__ENDPOINT_ENABLE {1} \
    CONFIG.PSU__PCIE__PERIPHERAL__ROOTPORT_ENABLE {0} \
    CONFIG.PSU__PCIE__RESET__POLARITY {Active Low} \
    CONFIG.PSU__PCIE__REVISION_ID {} \
    CONFIG.PSU__PCIE__SUBSYSTEM_ID {} \
    CONFIG.PSU__PCIE__SUBSYSTEM_VENDOR_ID {} \
    CONFIG.PSU__PCIE__VENDOR_ID {} \
    CONFIG.PSU__PL_CLK0_BUF {TRUE} \
    CONFIG.PSU__PMU_COHERENCY {0} \
    CONFIG.PSU__PMU__AIBACK__ENABLE {0} \
    CONFIG.PSU__PMU__EMIO_GPI__ENABLE {0} \
    CONFIG.PSU__PMU__EMIO_GPO__ENABLE {0} \
    CONFIG.PSU__PMU__GPI0__ENABLE {1} \
    CONFIG.PSU__PMU__GPI0__IO {MIO 26} \
    CONFIG.PSU__PMU__GPI1__ENABLE {0} \
    CONFIG.PSU__PMU__GPI2__ENABLE {0} \
    CONFIG.PSU__PMU__GPI3__ENABLE {0} \
    CONFIG.PSU__PMU__GPI4__ENABLE {0} \
    CONFIG.PSU__PMU__GPI5__ENABLE {1} \
    CONFIG.PSU__PMU__GPI5__IO {MIO 31} \
    CONFIG.PSU__PMU__GPO0__ENABLE {0} \
    CONFIG.PSU__PMU__GPO1__ENABLE {0} \
    CONFIG.PSU__PMU__GPO2__ENABLE {0} \
    CONFIG.PSU__PMU__GPO3__ENABLE {1} \
    CONFIG.PSU__PMU__GPO3__IO {MIO 35} \
    CONFIG.PSU__PMU__GPO3__POLARITY {low} \
    CONFIG.PSU__PMU__GPO4__ENABLE {0} \
    CONFIG.PSU__PMU__GPO5__ENABLE {0} \
    CONFIG.PSU__PMU__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__PMU__PLERROR__ENABLE {0} \
    CONFIG.PSU__PRESET_APPLIED {1} \
    CONFIG.PSU__PROTECTION__MASTERS {USB1:NonSecure;0|USB0:NonSecure;0|S_AXI_LPD:NA;1|S_AXI_HPC1_FPD:NA;0|S_AXI_HPC0_FPD:NA;0|S_AXI_HP3_FPD:NA;0|S_AXI_HP2_FPD:NA;0|S_AXI_HP1_FPD:NA;0|S_AXI_HP0_FPD:NA;0|S_AXI_ACP:NA;0|S_AXI_ACE:NA;0|SD1:NonSecure;0|SD0:NonSecure;0|SATA1:NonSecure;0|SATA0:NonSecure;0|RPU1:Secure;1|RPU0:Secure;1|QSPI:NonSecure;1|PMU:NA;1|PCIe:NonSecure;0|NAND:NonSecure;0|LDMA:NonSecure;1|GPU:NonSecure;1|GEM3:NonSecure;0|GEM2:NonSecure;0|GEM1:NonSecure;1|GEM0:NonSecure;0|FDMA:NonSecure;1|DP:NonSecure;1|DAP:NA;1|Coresight:NA;1|CSU:NA;1|APU:NA;1}\
\
    CONFIG.PSU__PROTECTION__SLAVES {LPD;USB3_1_XHCI;FE300000;FE3FFFFF;0|LPD;USB3_1;FF9E0000;FF9EFFFF;0|LPD;USB3_0_XHCI;FE200000;FE2FFFFF;0|LPD;USB3_0;FF9D0000;FF9DFFFF;0|LPD;UART1;FF010000;FF01FFFF;1|LPD;UART0;FF000000;FF00FFFF;0|LPD;TTC3;FF140000;FF14FFFF;0|LPD;TTC2;FF130000;FF13FFFF;0|LPD;TTC1;FF120000;FF12FFFF;0|LPD;TTC0;FF110000;FF11FFFF;0|FPD;SWDT1;FD4D0000;FD4DFFFF;1|LPD;SWDT0;FF150000;FF15FFFF;1|LPD;SPI1;FF050000;FF05FFFF;1|LPD;SPI0;FF040000;FF04FFFF;0|FPD;SMMU_REG;FD5F0000;FD5FFFFF;1|FPD;SMMU;FD800000;FDFFFFFF;1|FPD;SIOU;FD3D0000;FD3DFFFF;1|FPD;SERDES;FD400000;FD47FFFF;1|LPD;SD1;FF170000;FF17FFFF;0|LPD;SD0;FF160000;FF16FFFF;0|FPD;SATA;FD0C0000;FD0CFFFF;0|LPD;RTC;FFA60000;FFA6FFFF;1|LPD;RSA_CORE;FFCE0000;FFCEFFFF;1|LPD;RPU;FF9A0000;FF9AFFFF;1|LPD;R5_TCM_RAM_GLOBAL;FFE00000;FFE3FFFF;1|LPD;R5_1_Instruction_Cache;FFEC0000;FFECFFFF;1|LPD;R5_1_Data_Cache;FFED0000;FFEDFFFF;1|LPD;R5_1_BTCM_GLOBAL;FFEB0000;FFEBFFFF;1|LPD;R5_1_ATCM_GLOBAL;FFE90000;FFE9FFFF;1|LPD;R5_0_Instruction_Cache;FFE40000;FFE4FFFF;1|LPD;R5_0_Data_Cache;FFE50000;FFE5FFFF;1|LPD;R5_0_BTCM_GLOBAL;FFE20000;FFE2FFFF;1|LPD;R5_0_ATCM_GLOBAL;FFE00000;FFE0FFFF;1|LPD;QSPI_Linear_Address;C0000000;DFFFFFFF;1|LPD;QSPI;FF0F0000;FF0FFFFF;1|LPD;PMU_RAM;FFDC0000;FFDDFFFF;1|LPD;PMU_GLOBAL;FFD80000;FFDBFFFF;1|FPD;PCIE_MAIN;FD0E0000;FD0EFFFF;0|FPD;PCIE_LOW;E0000000;EFFFFFFF;0|FPD;PCIE_HIGH2;8000000000;BFFFFFFFFF;0|FPD;PCIE_HIGH1;600000000;7FFFFFFFF;0|FPD;PCIE_DMA;FD0F0000;FD0FFFFF;0|FPD;PCIE_ATTRIB;FD480000;FD48FFFF;0|LPD;OCM_XMPU_CFG;FFA70000;FFA7FFFF;1|LPD;OCM_SLCR;FF960000;FF96FFFF;1|OCM;OCM;FFFC0000;FFFFFFFF;1|LPD;NAND;FF100000;FF10FFFF;0|LPD;MBISTJTAG;FFCF0000;FFCFFFFF;1|LPD;LPD_XPPU_SINK;FF9C0000;FF9CFFFF;1|LPD;LPD_XPPU;FF980000;FF98FFFF;1|LPD;LPD_SLCR_SECURE;FF4B0000;FF4DFFFF;1|LPD;LPD_SLCR;FF410000;FF4AFFFF;1|LPD;LPD_GPV;FE100000;FE1FFFFF;1|LPD;LPD_DMA_7;FFAF0000;FFAFFFFF;1|LPD;LPD_DMA_6;FFAE0000;FFAEFFFF;1|LPD;LPD_DMA_5;FFAD0000;FFADFFFF;1|LPD;LPD_DMA_4;FFAC0000;FFACFFFF;1|LPD;LPD_DMA_3;FFAB0000;FFABFFFF;1|LPD;LPD_DMA_2;FFAA0000;FFAAFFFF;1|LPD;LPD_DMA_1;FFA90000;FFA9FFFF;1|LPD;LPD_DMA_0;FFA80000;FFA8FFFF;1|LPD;IPI_CTRL;FF380000;FF3FFFFF;1|LPD;IOU_SLCR;FF180000;FF23FFFF;1|LPD;IOU_SECURE_SLCR;FF240000;FF24FFFF;1|LPD;IOU_SCNTRS;FF260000;FF26FFFF;1|LPD;IOU_SCNTR;FF250000;FF25FFFF;1|LPD;IOU_GPV;FE000000;FE0FFFFF;1|LPD;I2C1;FF030000;FF03FFFF;1|LPD;I2C0;FF020000;FF02FFFF;0|FPD;GPU;FD4B0000;FD4BFFFF;1|LPD;GPIO;FF0A0000;FF0AFFFF;1|LPD;GEM3;FF0E0000;FF0EFFFF;0|LPD;GEM2;FF0D0000;FF0DFFFF;0|LPD;GEM1;FF0C0000;FF0CFFFF;1|LPD;GEM0;FF0B0000;FF0BFFFF;0|FPD;FPD_XMPU_SINK;FD4F0000;FD4FFFFF;1|FPD;FPD_XMPU_CFG;FD5D0000;FD5DFFFF;1|FPD;FPD_SLCR_SECURE;FD690000;FD6CFFFF;1|FPD;FPD_SLCR;FD610000;FD68FFFF;1|FPD;FPD_DMA_CH7;FD570000;FD57FFFF;1|FPD;FPD_DMA_CH6;FD560000;FD56FFFF;1|FPD;FPD_DMA_CH5;FD550000;FD55FFFF;1|FPD;FPD_DMA_CH4;FD540000;FD54FFFF;1|FPD;FPD_DMA_CH3;FD530000;FD53FFFF;1|FPD;FPD_DMA_CH2;FD520000;FD52FFFF;1|FPD;FPD_DMA_CH1;FD510000;FD51FFFF;1|FPD;FPD_DMA_CH0;FD500000;FD50FFFF;1|LPD;EFUSE;FFCC0000;FFCCFFFF;1|FPD;Display\
Port;FD4A0000;FD4AFFFF;1|FPD;DPDMA;FD4C0000;FD4CFFFF;1|FPD;DDR_XMPU5_CFG;FD050000;FD05FFFF;1|FPD;DDR_XMPU4_CFG;FD040000;FD04FFFF;1|FPD;DDR_XMPU3_CFG;FD030000;FD03FFFF;1|FPD;DDR_XMPU2_CFG;FD020000;FD02FFFF;1|FPD;DDR_XMPU1_CFG;FD010000;FD01FFFF;1|FPD;DDR_XMPU0_CFG;FD000000;FD00FFFF;1|FPD;DDR_QOS_CTRL;FD090000;FD09FFFF;1|FPD;DDR_PHY;FD080000;FD08FFFF;1|DDR;DDR_LOW;0;7FFFFFFF;1|DDR;DDR_HIGH;800000000;87FFFFFFF;1|FPD;DDDR_CTRL;FD070000;FD070FFF;1|LPD;Coresight;FE800000;FEFFFFFF;1|LPD;CSU_DMA;FFC80000;FFC9FFFF;1|LPD;CSU;FFCA0000;FFCAFFFF;1|LPD;CRL_APB;FF5E0000;FF85FFFF;1|FPD;CRF_APB;FD1A0000;FD2DFFFF;1|FPD;CCI_REG;FD5E0000;FD5EFFFF;1|LPD;CAN1;FF070000;FF07FFFF;0|LPD;CAN0;FF060000;FF06FFFF;0|FPD;APU;FD5C0000;FD5CFFFF;1|LPD;APM_INTC_IOU;FFA20000;FFA2FFFF;1|LPD;APM_FPD_LPD;FFA30000;FFA3FFFF;1|FPD;APM_5;FD490000;FD49FFFF;1|FPD;APM_0;FD0B0000;FD0BFFFF;1|LPD;APM2;FFA10000;FFA1FFFF;1|LPD;APM1;FFA00000;FFA0FFFF;1|LPD;AMS;FFA50000;FFA5FFFF;1|FPD;AFI_5;FD3B0000;FD3BFFFF;1|FPD;AFI_4;FD3A0000;FD3AFFFF;1|FPD;AFI_3;FD390000;FD39FFFF;1|FPD;AFI_2;FD380000;FD38FFFF;1|FPD;AFI_1;FD370000;FD37FFFF;1|FPD;AFI_0;FD360000;FD36FFFF;1|LPD;AFIFM6;FF9B0000;FF9BFFFF;1|FPD;ACPU_GIC;F9010000;F907FFFF;1}\
\
    CONFIG.PSU__PSS_REF_CLK__FREQMHZ {33.333} \
    CONFIG.PSU__QSPI_COHERENCY {0} \
    CONFIG.PSU__QSPI_ROUTE_THROUGH_FPD {0} \
    CONFIG.PSU__QSPI__GRP_FBCLK__ENABLE {0} \
    CONFIG.PSU__QSPI__PERIPHERAL__DATA_MODE {x4} \
    CONFIG.PSU__QSPI__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__QSPI__PERIPHERAL__IO {MIO 0 .. 5} \
    CONFIG.PSU__QSPI__PERIPHERAL__MODE {Single} \
    CONFIG.PSU__SAXIGP6__DATA_WIDTH {32} \
    CONFIG.PSU__SPI1__GRP_SS0__IO {MIO 9} \
    CONFIG.PSU__SPI1__GRP_SS1__ENABLE {0} \
    CONFIG.PSU__SPI1__GRP_SS2__ENABLE {0} \
    CONFIG.PSU__SPI1__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__SPI1__PERIPHERAL__IO {MIO 6 .. 11} \
    CONFIG.PSU__SWDT0__CLOCK__ENABLE {0} \
    CONFIG.PSU__SWDT0__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__SWDT0__RESET__ENABLE {0} \
    CONFIG.PSU__SWDT1__CLOCK__ENABLE {0} \
    CONFIG.PSU__SWDT1__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__SWDT1__RESET__ENABLE {0} \
    CONFIG.PSU__TSU__BUFG_PORT_PAIR {0} \
    CONFIG.PSU__TTC0__PERIPHERAL__ENABLE {0} \
    CONFIG.PSU__TTC1__PERIPHERAL__ENABLE {0} \
    CONFIG.PSU__TTC2__PERIPHERAL__ENABLE {0} \
    CONFIG.PSU__TTC3__PERIPHERAL__ENABLE {0} \
    CONFIG.PSU__UART0__PERIPHERAL__ENABLE {0} \
    CONFIG.PSU__UART1__BAUD_RATE {115200} \
    CONFIG.PSU__UART1__MODEM__ENABLE {0} \
    CONFIG.PSU__UART1__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__UART1__PERIPHERAL__IO {MIO 36 .. 37} \
    CONFIG.PSU__USB0__PERIPHERAL__ENABLE {0} \
    CONFIG.PSU__USB0__RESET__ENABLE {1} \
    CONFIG.PSU__USB0__RESET__IO {MIO 76} \
    CONFIG.PSU__USB1__PERIPHERAL__ENABLE {0} \
    CONFIG.PSU__USB1__RESET__ENABLE {1} \
    CONFIG.PSU__USB1__RESET__IO {MIO 77} \
    CONFIG.PSU__USE__IRQ0 {1} \
    CONFIG.PSU__USE__IRQ1 {1} \
    CONFIG.PSU__USE__M_AXI_GP0 {0} \
    CONFIG.PSU__USE__M_AXI_GP1 {0} \
    CONFIG.PSU__USE__M_AXI_GP2 {1} \
    CONFIG.PSU__USE__S_AXI_GP6 {1} \
  ] $zynq_ultra_ps_e_0


  # Create interface connections
  connect_bd_intf_net -intf_net S00_AXI_1 [get_bd_intf_pins uz_system/S00_AXI] [get_bd_intf_pins zynq_ultra_ps_e_0/M_AXI_HPM0_LPD]
  connect_bd_intf_net -intf_net uz_system_AXI4_Lite_PWM_0 [get_bd_intf_pins uz_digital_adapter/AXI4_Lite_PWM_0] [get_bd_intf_pins uz_system/AXI4_Lite_PWM_0]
  connect_bd_intf_net -intf_net uz_system_AXI4_Lite_PWM_1 [get_bd_intf_pins uz_digital_adapter/AXI4_Lite_PWM_1] [get_bd_intf_pins uz_system/AXI4_Lite_PWM_1]
  connect_bd_intf_net -intf_net uz_system_AXI4_Lite_PWM_2 [get_bd_intf_pins uz_digital_adapter/AXI4_Lite_PWM_2] [get_bd_intf_pins uz_system/AXI4_Lite_PWM_2]
  connect_bd_intf_net -intf_net uz_system_AXI4_Lite_PWM_3 [get_bd_intf_pins uz_digital_adapter/AXI4_Lite_PWM_3] [get_bd_intf_pins uz_system/AXI4_Lite_PWM_3]
  connect_bd_intf_net -intf_net uz_system_AXI4_interlock_0 [get_bd_intf_pins uz_digital_adapter/AXI4_interlock_0] [get_bd_intf_pins uz_system/AXI4_interlock_0]
  connect_bd_intf_net -intf_net uz_system_AXI4_interlock_1 [get_bd_intf_pins uz_digital_adapter/AXI4_interlock_1] [get_bd_intf_pins uz_system/AXI4_interlock_1]
  connect_bd_intf_net -intf_net uz_system_AXI4_interlock_2 [get_bd_intf_pins uz_digital_adapter/AXI4_interlock_2] [get_bd_intf_pins uz_system/AXI4_interlock_2]
  connect_bd_intf_net -intf_net uz_system_AXI4_interlock_3 [get_bd_intf_pins uz_digital_adapter/AXI4_interlock_3] [get_bd_intf_pins uz_system/AXI4_interlock_3]
  connect_bd_intf_net -intf_net uz_system_M00_AXI [get_bd_intf_pins uz_system/M00_AXI] [get_bd_intf_pins zynq_ultra_ps_e_0/S_AXI_LPD]
  connect_bd_intf_net -intf_net uz_system_M00_AXI1 [get_bd_intf_pins uz_analog_adapter/S00_AXI1] [get_bd_intf_pins uz_system/M00_AXI1]
  connect_bd_intf_net -intf_net uz_system_M01_AXI [get_bd_intf_pins uz_analog_adapter/S00_AXI2] [get_bd_intf_pins uz_system/M01_AXI]
  connect_bd_intf_net -intf_net uz_system_M02_AXI [get_bd_intf_pins uz_analog_adapter/S00_AXI] [get_bd_intf_pins uz_system/M02_AXI]
  connect_bd_intf_net -intf_net uz_system_M09_AXI [get_bd_intf_pins uz_digital_adapter/AXI4_Lite3] [get_bd_intf_pins uz_system/M09_AXI]
  connect_bd_intf_net -intf_net uz_system_M10_AXI [get_bd_intf_pins uz_system/M10_AXI] [get_bd_intf_pins uz_user/S00_AXI]
  connect_bd_intf_net -intf_net uz_system_M12_AXI [get_bd_intf_pins uz_digital_adapter/AXI4_Lite] [get_bd_intf_pins uz_system/M12_AXI]

  # Create port connections
  connect_bd_net -net ADC_A1_1 [get_bd_pins uz_analog_adapter/Din] [get_bd_pins uz_system/ADC_A1]
  connect_bd_net -net ADC_A2_1 [get_bd_pins uz_analog_adapter/RAW_VALUE1] [get_bd_pins uz_system/ADC_A2]
  connect_bd_net -net ADC_A3_1 [get_bd_pins uz_analog_adapter/RAW_VALUE] [get_bd_pins uz_system/ADC_A3]
  connect_bd_net -net Interrupt0_1 [get_bd_pins uz_digital_adapter/Carrier_triangular_max_min] [get_bd_pins uz_system/Interrupt0]
  connect_bd_net -net Interrupt1_1 [get_bd_pins uz_digital_adapter/Carrier_triangular_min] [get_bd_pins uz_system/Interrupt1]
  connect_bd_net -net Interrupt2_1 [get_bd_pins uz_digital_adapter/Carrier_triangular_max] [get_bd_pins uz_system/Interrupt2]
  connect_bd_net -net Interrupt3_1 [get_bd_pins uz_digital_adapter/Interrupt_Start_Center] [get_bd_pins uz_system/Interrupt3]
  connect_bd_net -net Interrupt4_1 [get_bd_pins uz_digital_adapter/Interrupt_Start] [get_bd_pins uz_system/Interrupt4]
  connect_bd_net -net Interrupt5_1 [get_bd_pins uz_digital_adapter/Interrupt_Center] [get_bd_pins uz_system/Interrupt5]
  connect_bd_net -net Trigger_AXI2TCM_1 [get_bd_pins uz_analog_adapter/probe4] [get_bd_pins uz_system/Trigger_AXI2TCM]
  connect_bd_net -net resetn_1 [get_bd_pins uz_system/resetn] [get_bd_pins zynq_ultra_ps_e_0/pl_resetn0]
  connect_bd_net -net uz_system_D4_OUT [get_bd_pins uz_system/D4_OUT] [get_bd_pins zynq_ultra_ps_e_0/pl_ps_irq0]
  connect_bd_net -net uz_system_Dout [get_bd_pins uz_digital_adapter/Enable_Gate] [get_bd_pins uz_system/Dout]
  connect_bd_net -net uz_system_clk_50MHz [get_bd_pins uz_digital_adapter/AXI4_Lite_ACLK] [get_bd_pins uz_system/clk_50MHz]
  connect_bd_net -net uz_system_peripheral_aresetn [get_bd_pins uz_analog_adapter/s00_axi_aresetn] [get_bd_pins uz_digital_adapter/RESETN] [get_bd_pins uz_system/peripheral_aresetn] [get_bd_pins uz_user/aresetn]
  connect_bd_net -net uz_system_peripheral_aresetn1 [get_bd_pins uz_digital_adapter/AXI4_Lite_ARESETN1] [get_bd_pins uz_system/peripheral_aresetn1]
  connect_bd_net -net uz_system_trigger_converesions [get_bd_pins uz_analog_adapter/TRIGGER_CNV] [get_bd_pins uz_digital_adapter/probe5] [get_bd_pins uz_system/trigger_converesions]
  connect_bd_net -net uz_system_wdt_interrupt [get_bd_pins uz_system/wdt_interrupt] [get_bd_pins zynq_ultra_ps_e_0/pl_ps_irq1]
  connect_bd_net -net xlconstant_0_dout [get_bd_pins uz_digital_adapter/Dig_11_Ch5] [get_bd_pins uz_digital_adapter/Dig_12_Ch5] [get_bd_pins uz_digital_adapter/Dig_13_Ch5] [get_bd_pins xlconstant_0/dout]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk0 [get_bd_pins uz_analog_adapter/s00_axi_aclk] [get_bd_pins uz_digital_adapter/clk] [get_bd_pins uz_system/clk] [get_bd_pins uz_user/aclk] [get_bd_pins zynq_ultra_ps_e_0/maxihpm0_lpd_aclk] [get_bd_pins zynq_ultra_ps_e_0/pl_clk0] [get_bd_pins zynq_ultra_ps_e_0/saxi_lpd_aclk]

  # Create address segments
  assign_bd_address -offset 0x80000000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_analog_adapter/A1_adapter/A1_ADC_LTC2311/S00_AXI/S00_AXI_reg] -force
  assign_bd_address -offset 0x80010000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_analog_adapter/A2_adapter/A2_ADC_LTC2311/S00_AXI/S00_AXI_reg] -force
  assign_bd_address -offset 0x80020000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_analog_adapter/A3_adapter/A3_ADC_LTC2311/S00_AXI/S00_AXI_reg] -force
  assign_bd_address -offset 0x80120000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_digital_adapter/D5_adapter/IncreEncoder_V24_ip_0/AXI4_Lite/reg0] -force
  assign_bd_address -offset 0x800B0000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_digital_adapter/D2_adapter/Gates_3L/PWM_SS_3L_ip_0/AXI4_Lite/reg0] -force
  assign_bd_address -offset 0x80030000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_digital_adapter/D1_adapter/Gates/PWM_and_SS_control_V_0/AXI4_Lite/reg0] -force
  assign_bd_address -offset 0x80040000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_digital_adapter/D1_adapter/Gates/PWM_and_SS_control_V_1/AXI4_Lite/reg0] -force
  assign_bd_address -offset 0x80050000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_digital_adapter/D1_adapter/Gates/PWM_and_SS_control_V_2/AXI4_Lite/reg0] -force
  assign_bd_address -offset 0x80060000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_digital_adapter/D1_adapter/Gates/PWM_and_SS_control_V_3/AXI4_Lite/reg0] -force
  assign_bd_address -offset 0x800C0000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_system/Interrupt/Trigger_f_cc/S_AXI/Reg] -force
  assign_bd_address -offset 0x80100000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_system/uz_enable/axi_gpio_2/S_AXI/Reg] -force
  assign_bd_address -offset 0x800E0000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_system/axi_timebase_wdt_0/S_AXI/Reg] -force
  assign_bd_address -offset 0x800D0000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_system/Interrupt/mux_axi_ip_1/AXI4_Lite/reg0] -force
  assign_bd_address -offset 0x800F0000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_system/timer_uptime_64bit/S_AXI/Reg] -force
  assign_bd_address -offset 0x80110000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_user/uz_axi_testIP_0/AXI4/reg0] -force
  assign_bd_address -offset 0x80070000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_digital_adapter/D1_adapter/Gates/uz_interlockDeadtime_0/AXI4/reg0] -force
  assign_bd_address -offset 0x80080000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_digital_adapter/D1_adapter/Gates/uz_interlockDeadtime_1/AXI4/reg0] -force
  assign_bd_address -offset 0x80090000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_digital_adapter/D1_adapter/Gates/uz_interlockDeadtime_2/AXI4/reg0] -force
  assign_bd_address -offset 0x800A0000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs uz_digital_adapter/D1_adapter/Gates/uz_interlockDeadtime_3/AXI4/reg0] -force
  assign_bd_address -offset 0x00000000 -range 0x80000000 -target_address_space [get_bd_addr_spaces uz_system/DataMover/AXI2TCM_0/M00_AXI] [get_bd_addr_segs zynq_ultra_ps_e_0/SAXIGP6/LPD_DDR_LOW] -force
  assign_bd_address -offset 0xFF000000 -range 0x01000000 -target_address_space [get_bd_addr_spaces uz_system/DataMover/AXI2TCM_0/M00_AXI] [get_bd_addr_segs zynq_ultra_ps_e_0/SAXIGP6/LPD_LPS_OCM] -force
  assign_bd_address -offset 0xC0000000 -range 0x20000000 -target_address_space [get_bd_addr_spaces uz_system/DataMover/AXI2TCM_0/M00_AXI] [get_bd_addr_segs zynq_ultra_ps_e_0/SAXIGP6/LPD_QSPI] -force

  # Exclude Address Segments
  exclude_bd_addr_seg -offset 0x000800000000 -range 0x000100000000 -target_address_space [get_bd_addr_spaces uz_system/DataMover/AXI2TCM_0/M00_AXI] [get_bd_addr_segs zynq_ultra_ps_e_0/SAXIGP6/LPD_DDR_HIGH]


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

