`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: TUM EAL
// Engineer: Eyke Liegmann
// 
// Create Date: 07.11.2018 11:09:11
// Design Name: 
// Module Name: tb_axi2tcm
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


// import package 
import axi_vip_pkg::*;
import design_1_axi_vip_0_0_pkg::*;

module tb_axi2tcm(

    );
    
    bit aclk = 0;
    bit aresetn=0;
    bit pulse_inp=0;
    bit[143:0] DATA_test = 144'hFFFFEEEE0123456789ABCDEFFEDCBA9876543210;

    always #5ns aclk = ~aclk; 
    
    //Instantiate the BD
    design_1_wrapper DUT
    (
        .aclk(aclk),
        .aresetn(aresetn),
        .m00_axi_init_axi_txn(pulse_inp),
        .DATA_IN(DATA_test)
    ); 
    
        
    // Declare agent
    design_1_axi_vip_0_0_slv_mem_t      slv_mem_agent;
    
    initial begin
        //Create an agent
        slv_mem_agent = new("slave vip agent",DUT.design_1_i.axi_vip_0.inst.IF);
        
        // set tag for agents for easy debug
        slv_mem_agent.set_agent_tag("Slave VIP");
        
        // set print out verbosity level.
        slv_mem_agent.set_verbosity(400);
        
        //Start the agent
        slv_mem_agent.start_slave();
    end
    
    initial begin
    
        #50ns
        aresetn = 1;
        
        #50ns
        pulse_inp = 1;
        
        #10ns
        pulse_inp = 0;
        
        #70us
        aresetn = 1;
        
    end
    
endmodule
