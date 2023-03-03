----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 27.03.2019 09:03:01
-- Design Name: 
-- Module Name: top_npc_state_machine - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity top_npc_state_machine is
--    generic 
--(	    
  --  pwm_mode:					pwm_mode_type := normal;	     --PWM mode
--);
    port(
            clock :         in STD_LOGIC;
            enable :        in STD_LOGIC;
            switching_signals : in std_logic_vector(5 downto 0) := (others => '0');
            --deadtime:       in integer range 0 to 1023 := 200;      -- with 100MHz -> 200/100MHz = 2us -- 10 bit!
            deadtime:       in std_logic_vector(9 downto 0) := "0001001000";    --0b1001000=200  -- with 100MHz -> 200/100MHz = 2us -- 10 bit!
           A_S1,A_S2,A_S3,A_S4 : out STD_LOGIC;
           B_S1,B_S2,B_S3,B_S4 : out STD_LOGIC;
           C_S1,C_S2,C_S3,C_S4 : out STD_LOGIC;                                    
           A_phase_off,B_phase_off,C_phase_off :   out STD_LOGIC
    );
end top_npc_state_machine;

architecture Behavioral of top_npc_state_machine is

    component npc_phase_state_machine is
      port (
        clock : in STD_LOGIC;
        enable : in STD_LOGIC;
        deadtime: in integer range 0 to 1023 := 200;      -- with 100MHz -> 200/100MHz = 2us
        s1_in : in STD_LOGIC;
        s2_in : in STD_LOGIC;
        s1_out : out STD_LOGIC;
        s2_out : out STD_LOGIC;
        s3_out : out STD_LOGIC;
        s4_out : out STD_LOGIC;
        phase_off : out STD_LOGIC
      );
    end component npc_phase_state_machine;

    signal clock_0 : STD_LOGIC;
    signal enable_0 : STD_LOGIC;
    signal reset_0 : STD_LOGIC;
    signal max_dutycycle_0 :  integer range 0 to 16383;
    signal deadtime_0: integer range 0 to 1023 := 200;      -- with 100MHz -> 200/100MHz = 2us
    signal switching_signals_0 : STD_LOGIC_VECTOR ( 5 downto 0 );

    --
    signal npc_FCM_phase_A_phase_off : STD_LOGIC;
    signal npc_FCM_phase_A_s1_out : STD_LOGIC;
    signal npc_FCM_phase_A_s2_out : STD_LOGIC;
    signal npc_FCM_phase_A_s3_out : STD_LOGIC;
    signal npc_FCM_phase_A_s4_out : STD_LOGIC;
    --
    signal npc_FCM_phase_B_phase_off : STD_LOGIC;
    signal npc_FCM_phase_B_s1_out : STD_LOGIC;
    signal npc_FCM_phase_B_s2_out : STD_LOGIC;
    signal npc_FCM_phase_B_s3_out : STD_LOGIC;
    signal npc_FCM_phase_B_s4_out : STD_LOGIC;
    --
    signal npc_FCM_phase_C_phase_off : STD_LOGIC;
    signal npc_FCM_phase_C_s1_out : STD_LOGIC;
    signal npc_FCM_phase_C_s2_out : STD_LOGIC;
    signal npc_FCM_phase_C_s3_out : STD_LOGIC;
    signal npc_FCM_phase_C_s4_out : STD_LOGIC;
    --
   
begin
-- instantiate components
npc_FCM_phase_A: component npc_phase_state_machine
     port map (
      clock => clock_0,
      enable => enable_0,
      deadtime => deadtime_0,
      phase_off => npc_FCM_phase_A_phase_off,
      s1_in => switching_signals_0(0),
      s2_in => switching_signals_0(1),
      s1_out => npc_FCM_phase_A_s1_out,
      s2_out => npc_FCM_phase_A_s2_out,
      s3_out => npc_FCM_phase_A_s3_out,
      s4_out => npc_FCM_phase_A_s4_out
    );

npc_FCM_phase_B: component npc_phase_state_machine
     port map (
      clock => clock_0,
      enable => enable_0,
      deadtime => deadtime_0,
      phase_off => npc_FCM_phase_B_phase_off,
      s1_in => switching_signals_0(2),
      s2_in => switching_signals_0(3),
      s1_out => npc_FCM_phase_B_s1_out,
      s2_out => npc_FCM_phase_B_s2_out,
      s3_out => npc_FCM_phase_B_s3_out,
      s4_out => npc_FCM_phase_B_s4_out
    );

npc_FCM_phase_C: component npc_phase_state_machine
     port map (
      clock => clock_0,
      enable => enable_0,
      deadtime => deadtime_0,
      phase_off => npc_FCM_phase_C_phase_off,
      s1_in => switching_signals_0(4),
      s2_in => switching_signals_0(5),
      s1_out => npc_FCM_phase_C_s1_out,
      s2_out => npc_FCM_phase_C_s2_out,
      s3_out => npc_FCM_phase_C_s3_out,
      s4_out => npc_FCM_phase_C_s4_out
    );

-- Zuweisung
    switching_signals_0 <= switching_signals; 
    clock_0 <= clock;
    enable_0 <= enable;
    deadtime_0 <= to_integer(unsigned(deadtime));
    --
    A_S1 <= npc_FCM_phase_A_s1_out;
    A_S2 <= npc_FCM_phase_A_s2_out;
    A_S3 <= npc_FCM_phase_A_s3_out;
    A_S4 <= npc_FCM_phase_A_s4_out;
    A_phase_off <= npc_FCM_phase_A_phase_off;
    --
    B_S1 <= npc_FCM_phase_B_s1_out;
    B_S2 <= npc_FCM_phase_B_s2_out;
    B_S3 <= npc_FCM_phase_B_s3_out;
    B_S4 <= npc_FCM_phase_B_s4_out;
    B_phase_off <= npc_FCM_phase_B_phase_off;
    --
    C_S1 <= npc_FCM_phase_C_s1_out;
    C_S2 <= npc_FCM_phase_C_s2_out;
    C_S3 <= npc_FCM_phase_C_s3_out;
    C_S4 <= npc_FCM_phase_C_s4_out;
    C_phase_off <= npc_FCM_phase_C_phase_off;

end Behavioral;
