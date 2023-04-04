
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
# delay_trigger

# Please add the sources of those modules before sourcing this Tcl script.

set bCheckIPsPassed 1
##################################################################
# CHECK IPs
##################################################################
set bCheckIPs 1
if { $bCheckIPs == 1 } {
   set list_check_ips "\ 
xilinx.com:ip:axi_timebase_wdt:3.0\
xilinx.com:ip:smartconnect:1.0\
xilinx.com:ip:axi_timer:2.0\
TUM:user:AXI2TCM:1.1\
xilinx.com:ip:ila:6.2\
xilinx.com:ip:util_vector_logic:2.0\
xilinx.com:ip:xlconcat:2.1\
xilinx.com:ip:vio:3.0\
xilinx.com:ip:mux_axi_ip:1.2\
xilinx.com:ip:clk_wiz:6.0\
xilinx.com:ip:proc_sys_reset:5.0\
xilinx.com:ip:xlconstant:1.1\
xilinx.com:ip:axi_gpio:2.0\
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
delay_trigger\
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
  set_property -dict [ list \
   CONFIG.CONST_VAL {0} \
 ] $Enable_Gates_CPLD_Low

  # Create instance: axi_gpio_2, and set properties
  set axi_gpio_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_2 ]
  set_property -dict [ list \
   CONFIG.C_GPIO_WIDTH {8} \
 ] $axi_gpio_2

  # Create instance: xlslice_Enable_AXI2TCM_Bit4, and set properties
  set xlslice_Enable_AXI2TCM_Bit4 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_Enable_AXI2TCM_Bit4 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {4} \
   CONFIG.DIN_TO {4} \
   CONFIG.DIN_WIDTH {8} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_Enable_AXI2TCM_Bit4

  # Create instance: xlslice_Enable_Gate_Bit1, and set properties
  set xlslice_Enable_Gate_Bit1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_Enable_Gate_Bit1 ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {1} \
   CONFIG.DIN_TO {1} \
   CONFIG.DIN_WIDTH {8} \
   CONFIG.DOUT_WIDTH {1} \
 ] $xlslice_Enable_Gate_Bit1

  # Create instance: xlslice_Enable_Inverter_Bit0, and set properties
  set xlslice_Enable_Inverter_Bit0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_Enable_Inverter_Bit0 ]
  set_property -dict [ list \
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
  set_property -dict [ list \
   CONFIG.AUTO_PRIMITIVE {PLL} \
   CONFIG.CLKOUT1_DRIVES {Buffer} \
   CONFIG.CLKOUT1_JITTER {167.017} \
   CONFIG.CLKOUT1_PHASE_ERROR {114.212} \
   CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {50.000} \
   CONFIG.CLKOUT2_DRIVES {Buffer} \
   CONFIG.CLKOUT2_JITTER {229.362} \
   CONFIG.CLKOUT2_PHASE_ERROR {114.212} \
   CONFIG.CLKOUT2_REQUESTED_OUT_FREQ {10.000} \
   CONFIG.CLKOUT2_USED {true} \
   CONFIG.CLKOUT3_DRIVES {Buffer} \
   CONFIG.CLKOUT3_JITTER {191.696} \
   CONFIG.CLKOUT3_PHASE_ERROR {114.212} \
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
  set_property -dict [ list \
   CONFIG.NUM_PORTS {8} \
 ] $Concat_interrupts

  # Create instance: Trigger_f_cc, and set properties
  set Trigger_f_cc [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_timer:2.0 Trigger_f_cc ]
  set_property -dict [ list \
   CONFIG.enable_timer2 {0} \
 ] $Trigger_f_cc

  # Create instance: adc_delay, and set properties
  set adc_delay [ create_bd_cell -type ip -vlnv xilinx.com:ip:vio:3.0 adc_delay ]
  set_property -dict [ list \
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
  set_property -dict [ list \
   CONFIG.C_DATA_DEPTH {16384} \
   CONFIG.C_ENABLE_ILA_AXI_MON {false} \
   CONFIG.C_MONITOR_TYPE {Native} \
   CONFIG.C_NUM_OF_PROBES {10} \
 ] $ila_0

  # Create instance: mux_axi_ip_1, and set properties
  set mux_axi_ip_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:mux_axi_ip:1.2 mux_axi_ip_1 ]

  # Create instance: vio_interrupt, and set properties
  set vio_interrupt [ create_bd_cell -type ip -vlnv xilinx.com:ip:vio:3.0 vio_interrupt ]
  set_property -dict [ list \
   CONFIG.C_NUM_PROBE_IN {0} \
 ] $vio_interrupt

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
  set_property -dict [ list \
   CONFIG.C_M00_NUMBER_of_ADCs {24} \
 ] $AXI2TCM_0

  # Create instance: ila_0, and set properties
  set ila_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:ila:6.2 ila_0 ]
  set_property -dict [ list \
   CONFIG.C_ENABLE_ILA_AXI_MON {false} \
   CONFIG.C_MONITOR_TYPE {Native} \
   CONFIG.C_NUM_OF_PROBES {5} \
 ] $ila_0

  # Create instance: util_vector_logic_0, and set properties
  set util_vector_logic_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 util_vector_logic_0 ]
  set_property -dict [ list \
   CONFIG.C_SIZE {1} \
 ] $util_vector_logic_0

  # Create instance: xlconcat_0, and set properties
  set xlconcat_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0 ]
  set_property -dict [ list \
   CONFIG.NUM_PORTS {3} \
 ] $xlconcat_0

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
  set_property -dict [ list \
   CONFIG.ENABLE_WINDOW_WDT {1} \
   CONFIG.SST_COUNT_WIDTH {30} \
 ] $axi_timebase_wdt_0

  # Create instance: smartconnect_0, and set properties
  set smartconnect_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:smartconnect:1.0 smartconnect_0 ]
  set_property -dict [ list \
   CONFIG.NUM_CLKS {3} \
   CONFIG.NUM_MI {15} \
   CONFIG.NUM_SI {1} \
 ] $smartconnect_0

  # Create instance: smartconnect_1, and set properties
  set smartconnect_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:smartconnect:1.0 smartconnect_1 ]
  set_property -dict [ list \
   CONFIG.NUM_MI {5} \
   CONFIG.NUM_SI {1} \
 ] $smartconnect_1

  # Create instance: timer_uptime_64bit, and set properties
  set timer_uptime_64bit [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_timer:2.0 timer_uptime_64bit ]
  set_property -dict [ list \
   CONFIG.mode_64bit {1} \
 ] $timer_uptime_64bit

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


proc available_tcl_procs { } {
   puts "##################################################################"
   puts "# Available Tcl procedures to recreate hierarchical blocks:"
   puts "#"
   puts "#    create_hier_cell_uz_system parentCell nameHier"
   puts "#    create_hier_cell_DataMover parentCell nameHier"
   puts "#    create_hier_cell_Interrupt parentCell nameHier"
   puts "#    create_hier_cell_uz_clocks parentCell nameHier"
   puts "#    create_hier_cell_uz_enable parentCell nameHier"
   puts "#"
   puts "##################################################################"
}

available_tcl_procs
