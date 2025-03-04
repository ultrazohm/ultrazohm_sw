-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\PMSM_Flux_NonLinear_FCS_FixPoint_Np1_V7\Counter_f_sw_V2_ip_src_Count_f_sw.vhd
-- Created: 2020-04-27 19:15:37
-- 
-- Generated by MATLAB 9.4 and HDL Coder 3.12
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: Counter_f_sw_V2_ip_src_Count_f_sw
-- Source Path: Counter_f_sw_V2/Count_f_sw
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;
USE work.Counter_f_sw_V2_ip_src_Counter_f_sw_V2_pkg.ALL;

ENTITY Counter_f_sw_V2_ip_src_Count_f_sw IS
  PORT( switchNumb                        :   IN    std_logic_vector(24 DOWNTO 0);  -- ufix25
        ss_v_old_0                        :   IN    std_logic;  -- boolean
        ss_v_old_1                        :   IN    std_logic;  -- boolean
        ss_v_old_2                        :   IN    std_logic;  -- boolean
        ss_v_old_3                        :   IN    std_logic;  -- boolean
        ss_v_old_4                        :   IN    std_logic;  -- boolean
        ss_v_old_5                        :   IN    std_logic;  -- boolean
        ss_v_0                            :   IN    std_logic;  -- boolean
        ss_v_1                            :   IN    std_logic;  -- boolean
        ss_v_2                            :   IN    std_logic;  -- boolean
        ss_v_3                            :   IN    std_logic;  -- boolean
        ss_v_4                            :   IN    std_logic;  -- boolean
        ss_v_5                            :   IN    std_logic;  -- boolean
        bReset                            :   IN    std_logic;  -- ufix1
        switchNumbOut                     :   OUT   std_logic_vector(24 DOWNTO 0)  -- ufix25
        );
END Counter_f_sw_V2_ip_src_Count_f_sw;


ARCHITECTURE rtl OF Counter_f_sw_V2_ip_src_Count_f_sw IS

  -- Signals
  SIGNAL switchNumb_unsigned              : unsigned(24 DOWNTO 0);  -- ufix25
  SIGNAL ss_v_old                         : std_logic_vector(0 TO 5);  -- boolean [6]
  SIGNAL ss_v                             : std_logic_vector(0 TO 5);  -- boolean [6]
  SIGNAL switchNumbOut_tmp                : unsigned(24 DOWNTO 0);  -- ufix25

BEGIN
  switchNumb_unsigned <= unsigned(switchNumb);

  ss_v_old(0) <= ss_v_old_0;
  ss_v_old(1) <= ss_v_old_1;
  ss_v_old(2) <= ss_v_old_2;
  ss_v_old(3) <= ss_v_old_3;
  ss_v_old(4) <= ss_v_old_4;
  ss_v_old(5) <= ss_v_old_5;

  ss_v(0) <= ss_v_0;
  ss_v(1) <= ss_v_1;
  ss_v(2) <= ss_v_2;
  ss_v(3) <= ss_v_3;
  ss_v(4) <= ss_v_4;
  ss_v(5) <= ss_v_5;

  Count_f_sw_output : PROCESS (switchNumb_unsigned, ss_v_old, ss_v, bReset)
    VARIABLE switchNumb1 : unsigned(24 DOWNTO 0);
    VARIABLE countSS : unsigned(7 DOWNTO 0);
    VARIABLE add_temp : vector_of_signed32(0 TO 5);
    VARIABLE sub_cast : vector_of_signed32(0 TO 5);
    VARIABLE sub_cast_0 : vector_of_signed32(0 TO 5);
  BEGIN
    switchNumb1 := switchNumb_unsigned;
    --MATLAB Function 'Count_f_sw'
    --    %% toDO
    --    %% Initialization
    -- I need this initialization, in order that the HDL Coder and Simulink knows the size of the vectors! Without these, i will get an error!
    -- idx_globalOld     = fi(1, 0, 8, 0); % Chosen position overall in the error vector
    --switchNumb = fi(0, 0, 25, 0);
    --    %% Reset the counters (similar to the THD, i will try to average the switching frequency over 20 fundamental periods. After this time, a Reset-Flag from the ARM processor will reset the counter) 
    IF bReset = '1' THEN 
      switchNumb1 := to_unsigned(16#0000000#, 25);
    END IF;
    --    %% Check if switching occurs. If yes count up.
    -- However, dependent of the ss_v before, switching can but do not have to occure, if the previously applied ss_v keeps.
    --Use a for-loop since in VHDL i have time and can do a resource streaming
    --Even if i need 6 cycles @100MHz, since it is not able to have have
    --switching (on/off inside of 60ns), this is ok (because T_cf = 10us and
    --and switching for such a short time is not allwoed nayway, since it is
    --not worth it (too much losses).)

    FOR countss_0 IN 0 TO 5 LOOP
      add_temp(countss_0) := to_signed(countss_0 + 1, 32);
      countSS := unsigned(add_temp(countss_0)(7 DOWNTO 0));
      --1:6
      sub_cast(countss_0) := signed(resize(countSS, 32));
      sub_cast_0(countss_0) := signed(resize(countSS, 32));
      IF ss_v(to_integer(sub_cast(countss_0) - 1)) /= ss_v_old(to_integer(sub_cast_0(countss_0) - 1)) THEN 
        --Check if switch has changed
        switchNumb1 := switchNumb1 + to_unsigned(16#0000001#, 25);
        -- +1 Increment the switch counter +1
      END IF;
    END LOOP;

    switchNumbOut_tmp <= switchNumb1;
  END PROCESS Count_f_sw_output;


  switchNumbOut <= std_logic_vector(switchNumbOut_tmp);

END rtl;

