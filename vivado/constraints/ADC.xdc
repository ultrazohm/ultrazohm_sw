###Output ADC Pins
# Author: Sebastian Wendel
# Date: 27.06.2017
# All ADC-Pins are 2,5 Volt on Bank13 (Remove R36 from TE0729 Modul)



############ ADC1 -> Strom Phase 1
##ADC_I_U_Clk1 -
#set_property PACKAGE_PIN W12 [get_ports B13_L4_N] 
##ADC_I_U_Clk1 +  
#set_property PACKAGE_PIN V12 [get_ports B13_L4_P]
##ADC_I_U_Rx1 +   
#set_property PACKAGE_PIN Y11 [get_ports B13_L10_P] 
##ADC_I_U_Rx1 - 
#set_property PACKAGE_PIN Y10 [get_ports B13_L10_N] 
##ADC_I_U_Conv1 
#set_property PACKAGE_PIN V5 [get_ports B13_L21_P]  

############ ADC2 -> Strom Phase 2
##ADC_I_U_Clk2 +
#set_property PACKAGE_PIN AA12 [get_ports B13_L7_P] 
##ADC_I_U_Clk2 - 
#set_property PACKAGE_PIN AB12 [get_ports B13_L7_N]  
##ADC_I_U_Rx2 +
#set_property PACKAGE_PIN AA11 [get_ports B13_L8_P] 
##ADC_I_U_Rx2 - 
#set_property PACKAGE_PIN AB11 [get_ports B13_L8_N]
##ADC_I_U_Conv2  
#set_property PACKAGE_PIN V4 [get_ports B13_L21_N] 

############ ADC3 -> Strom Phase 3
##ADC_I_U_Clk3 +
#set_property PACKAGE_PIN W11 [get_ports B13_L3_P] 
##ADC_I_U_Clk3 -  
#set_property PACKAGE_PIN W10 [get_ports B13_L3_N]
##ADC_I_U_Rx3 +   
#set_property PACKAGE_PIN Y9 [get_ports B13_L12_P]  
##ADC_I_U_Rx3 -
#set_property PACKAGE_PIN Y8 [get_ports B13_L12_N]
##ADC_I_U_Conv3  
#set_property PACKAGE_PIN U5 [get_ports B13_L22_N]  

############ ADC4 -> MUX (DC- and Phase-Voltage, Analog-Hall)
##ADC_I_U_Clk4 +
#set_property PACKAGE_PIN AB10 [get_ports B13_L9_P]  
##ADC_I_U_Clk4 -
#set_property PACKAGE_PIN AB9 [get_ports B13_L9_N] 
##ADC_I_U_Rx4 +  
#set_property PACKAGE_PIN AA9 [get_ports B13_L11_P]  
##ADC_I_U_Rx4 -
#set_property PACKAGE_PIN AA8 [get_ports B13_L11_N]  
##ADC_I_U_Conv4
#set_property PACKAGE_PIN U6 [get_ports B13_L22_P]   

############ MUX-Pins (DC- and Phase-Voltage, Analog-Hall)
###ADC_Rest_MUX1
##set_property PACKAGE_PIN B16 [get_ports B35_IO8]  
###ADC_Rest_MUX2
##set_property PACKAGE_PIN A16 [get_ports B35_IO9] 
###ADC_Rest_MUX3  
##set_property PACKAGE_PIN B15 [get_ports B35_IO10]  

#######################################################################################################################################
##################Set voltage level for ADC1 Pins -> Strom Phase 1
##Set Pin in LVDS Mode for differential Signal
#set_property IOSTANDARD LVDS_25 [get_ports B13_L4_N]   
#set_property IOSTANDARD LVDS_25 [get_ports B13_L4_P]    
#set_property IOSTANDARD LVDS_25 [get_ports B13_L10_P]   
#set_property IOSTANDARD LVDS_25 [get_ports B13_L10_N]
##Set Pin in CMOS Mode for non differential Signal (normal/single Signal)   
#set_property IOSTANDARD LVCMOS25 [get_ports B13_L21_P] 

##################Set voltage level for ADC2 Pins -> Strom Phase 2
##Set Pin in LVDS Mode for differential Signal
#set_property IOSTANDARD LVDS_25 [get_ports B13_L7_P]    
#set_property IOSTANDARD LVDS_25 [get_ports B13_L7_N]    
#set_property IOSTANDARD LVDS_25 [get_ports B13_L8_P]   
#set_property IOSTANDARD LVDS_25 [get_ports B13_L8_N]    
##Set Pin in CMOS Mode for non differential Signal (normal/single Signal)
#set_property IOSTANDARD LVCMOS25 [get_ports B13_L21_N]  

##################Set voltage level for ADC3 Pins -> Strom Phase 3
##Set Pin in LVDS Mode for differential Signal
#set_property IOSTANDARD LVDS_25 [get_ports B13_L3_P]   
#set_property IOSTANDARD LVDS_25 [get_ports B13_L3_N]   
#set_property IOSTANDARD LVDS_25 [get_ports B13_L12_P]     
#set_property IOSTANDARD LVDS_25 [get_ports B13_L12_N]  
##Set Pin in CMOS Mode for non differential Signal (normal/single Signal)
#set_property IOSTANDARD LVCMOS25 [get_ports B13_L22_N]  

##################Set voltage level for ADC4 Pins -> MUX
##Set Pin in LVDS Mode for differential Signal
#set_property IOSTANDARD LVDS_25 [get_ports B13_L9_P]   
#set_property IOSTANDARD LVDS_25 [get_ports B13_L9_N]   
#set_property IOSTANDARD LVDS_25 [get_ports B13_L11_P]   
#set_property IOSTANDARD LVDS_25 [get_ports B13_L11_N]  
##Set Pin in CMOS Mode for non differential Signal (normal/single Signal)
#set_property IOSTANDARD LVCMOS25 [get_ports B13_L22_P]  

###Set Pin on 3,3V, because its Bank35 (not Bank13) and in CMOS Mode for non differential Signal (normal/single Signal)
##set_property IOSTANDARD LVCMOS33 [get_ports B35_IO8]   
##set_property IOSTANDARD LVCMOS33 [get_ports B35_IO9]   
##set_property IOSTANDARD LVCMOS33 [get_ports B35_IO10]  
