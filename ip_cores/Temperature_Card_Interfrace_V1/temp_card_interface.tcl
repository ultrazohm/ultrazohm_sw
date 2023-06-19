
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

set bCheckIPsPassed 1
##################################################################
# CHECK IPs
##################################################################
set bCheckIPs 1
if { $bCheckIPs == 1 } {
   set list_check_ips "\ 
xilinx.com:user:Temperature_Card_Interface_v1_0:1.0\
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


# Hierarchical cell: temp_card_interface
proc create_hier_cell_temp_card_interface { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2092 -severity "ERROR" "create_hier_cell_temp_card_interface() - Empty argument(s)!"}
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
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 AXI


  # Create pins
  create_bd_pin -dir I LTC_Interrupt_1_Dig05
  create_bd_pin -dir I LTC_Interrupt_2_Dig17
  create_bd_pin -dir I LTC_Interrupt_3_Dig11
  create_bd_pin -dir O LTC_resetn_1_Dig19
  create_bd_pin -dir I SPI_MISO_1_Dig03
  create_bd_pin -dir I SPI_MISO_2_Dig15
  create_bd_pin -dir I SPI_MISO_3_Dig09
  create_bd_pin -dir O SPI_MOSI_1_Dig02
  create_bd_pin -dir O SPI_MOSI_2_Dig14
  create_bd_pin -dir O SPI_MOSI_3_Dig08
  create_bd_pin -dir O SPI_SCLK_1_Dig01
  create_bd_pin -dir O SPI_SCLK_2_Dig13
  create_bd_pin -dir O SPI_SCLK_3_Dig07
  create_bd_pin -dir O SPI_SS_1_Dig04
  create_bd_pin -dir O SPI_SS_2_Dig16
  create_bd_pin -dir O SPI_SS_3_Dig10
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -type rst aresetn

  # Create instance: Temperature_Card_Int_0, and set properties
  set Temperature_Card_Int_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:Temperature_Card_Interface_v1_0:1.0 Temperature_Card_Int_0 ]

  # Create interface connections
  connect_bd_intf_net -intf_net Conn1 [get_bd_intf_pins AXI] [get_bd_intf_pins Temperature_Card_Int_0/s00_axi]

  # Create port connections
  connect_bd_net -net LTC_Interrupt_1_1 [get_bd_pins LTC_Interrupt_1_Dig05] [get_bd_pins Temperature_Card_Int_0/LTC_Interrupt_1]
  connect_bd_net -net LTC_Interrupt_2_1 [get_bd_pins LTC_Interrupt_2_Dig17] [get_bd_pins Temperature_Card_Int_0/LTC_Interrupt_2]
  connect_bd_net -net LTC_Interrupt_3_1 [get_bd_pins LTC_Interrupt_3_Dig11] [get_bd_pins Temperature_Card_Int_0/LTC_Interrupt_3]
  connect_bd_net -net SPI_MISO_1_1 [get_bd_pins SPI_MISO_1_Dig03] [get_bd_pins Temperature_Card_Int_0/SPI_MISO_1]
  connect_bd_net -net SPI_MISO_2_1 [get_bd_pins SPI_MISO_2_Dig15] [get_bd_pins Temperature_Card_Int_0/SPI_MISO_2]
  connect_bd_net -net SPI_MISO_3_1 [get_bd_pins SPI_MISO_3_Dig09] [get_bd_pins Temperature_Card_Int_0/SPI_MISO_3]
  connect_bd_net -net Temperature_Card_Int_0_LTC_resetn_1 [get_bd_pins LTC_resetn_1_Dig19] [get_bd_pins Temperature_Card_Int_0/LTC_resetn_1]
  connect_bd_net -net Temperature_Card_Int_0_SPI_MOSI_1 [get_bd_pins SPI_MOSI_1_Dig02] [get_bd_pins Temperature_Card_Int_0/SPI_MOSI_1]
  connect_bd_net -net Temperature_Card_Int_0_SPI_MOSI_2 [get_bd_pins SPI_MOSI_2_Dig14] [get_bd_pins Temperature_Card_Int_0/SPI_MOSI_2]
  connect_bd_net -net Temperature_Card_Int_0_SPI_MOSI_3 [get_bd_pins SPI_MOSI_3_Dig08] [get_bd_pins Temperature_Card_Int_0/SPI_MOSI_3]
  connect_bd_net -net Temperature_Card_Int_0_SPI_SCLK_1 [get_bd_pins SPI_SCLK_1_Dig01] [get_bd_pins Temperature_Card_Int_0/SPI_SCLK_1]
  connect_bd_net -net Temperature_Card_Int_0_SPI_SCLK_2 [get_bd_pins SPI_SCLK_2_Dig13] [get_bd_pins Temperature_Card_Int_0/SPI_SCLK_2]
  connect_bd_net -net Temperature_Card_Int_0_SPI_SCLK_3 [get_bd_pins SPI_SCLK_3_Dig07] [get_bd_pins Temperature_Card_Int_0/SPI_SCLK_3]
  connect_bd_net -net Temperature_Card_Int_0_SPI_SS_1 [get_bd_pins SPI_SS_1_Dig04] [get_bd_pins Temperature_Card_Int_0/SPI_SS_1]
  connect_bd_net -net Temperature_Card_Int_0_SPI_SS_2 [get_bd_pins SPI_SS_2_Dig16] [get_bd_pins Temperature_Card_Int_0/SPI_SS_2]
  connect_bd_net -net Temperature_Card_Int_0_SPI_SS_3 [get_bd_pins SPI_SS_3_Dig10] [get_bd_pins Temperature_Card_Int_0/SPI_SS_3]
  connect_bd_net -net aclk_1 [get_bd_pins aclk] [get_bd_pins Temperature_Card_Int_0/s00_axi_aclk]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins Temperature_Card_Int_0/s00_axi_aresetn]

  # Restore current instance
  current_bd_instance $oldCurInst
}


proc available_tcl_procs { } {
   puts "##################################################################"
   puts "# Available Tcl procedures to recreate hierarchical blocks:"
   puts "#"
   puts "#    create_hier_cell_temp_card_interface parentCell nameHier"
   puts "#"
   puts "##################################################################"
}

available_tcl_procs
