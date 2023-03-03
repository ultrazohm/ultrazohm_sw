--npc_phase_state_machine.vhd
--State machine for a three-level NPC inverter
--Inserts deadtime between transitions and makes sure that the inverter is turned on and off in a safe way
--Only allowed and not harmful switching states can be set:
--s1 s2 s3 s4 (top IGBT to bottom IGBT) either 0000 (off state), 0100 (interlock high), 0110 (zero state), 0010 (interlock low), 1100 (high), 0011 (low)
--The interlock states are can be only left after the deadtime is over, even in case for turn off
--The switching state 10 (s1 s2) leads to 01 for s1 s2 (10 is not allowed)
--Peter Stolze, 19/10/2012

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity npc_phase_state_machine is port
(
	clock:					in std_logic := '0';					--FPGA system clock
	enable:					in std_logic := '0';					--Enable the inverter phase; 0: All IGBTs off; 1: Commanded switching state is set
	deadtime:               in integer range 0 to 1023 := 200;      -- with 100MHz -> 200/100MHz = 2us
	s1_in:					in std_logic := '0';					--First (upper) switch input signal (without deadtime)
	s2_in:					in std_logic := '0';					--Second switch input signal (without deadtime)
	
	s1_out:					out std_logic := '0';				--First (upper) switch input signal (with deadtime) which can be applied to the inverter
	s2_out:					out std_logic := '0';				--Second switch input signal (with deadtime) which can be applied to the inverter
	s3_out:					out std_logic := '0';				--Third switch input signal (with deadtime) which can be applied to the inverter
	s4_out:					out std_logic := '0';				--Fourth switch input signal (with deadtime) which can be applied to the inverter
	
	phase_off:				out std_logic := '1'					--Flag if the phase is off (0000)
);
end npc_phase_state_machine;

architecture npc_phase_state_machine_implementation of npc_phase_state_machine is
	type phase_states is (off_state, int_high, int_low, pos_state, zero_state, neg_state);		--All possible states of the inverter leg
	constant deadtime_init:						integer := 200;														--Deadtime for the PWM channels (40 clock cycles @ 20 MHz = 2 us)
	signal phase_state:						phase_states := off_state;										--Current state of the inverter leg
	signal commanded_state:					phase_states := off_state;										--The commanded inverter switching state, depending on enable, s1_in and s2_in
begin
	--Set the commanded state for the phase
	commanded_state <= off_state when enable = '0' else
							 pos_state when s1_in = '1' and s2_in = '1' else
							 neg_state when s1_in = '0' and s2_in = '0' else
							 zero_state; --(s1_in = '0' and s2_in = '1') or (s1_in = '1' and s2_in = '0') --Prevents the command for the state 1001 => will be 0110
							 

	state_machine_proc: process(clock)
		variable counter:				integer range 0 to 1023 := deadtime_init;					--Counter for the interlock states
	begin
		if rising_edge(clock) then
			case phase_state is
				when off_state =>
					if commanded_state = pos_state then
						phase_state <= int_high;
						counter := deadtime;
					elsif commanded_state = neg_state then
						phase_state <= int_low;
						counter := deadtime;
					elsif commanded_state = zero_state then
						phase_state <= zero_state;
					else --commanded_state = off_state
						phase_state <= off_state;
					end if;
				when int_high =>
					counter := counter - 1;
					
					if counter > 0 then	--Deadtime is still running
						phase_state <= int_high;
					else								--Deadtime is over
						if commanded_state = pos_state then
							phase_state <= pos_state;
						elsif commanded_state = neg_state then
							phase_state <= zero_state;
						elsif commanded_state = zero_state then
							phase_state <= zero_state;
						else --commanded_state = off_state
							phase_state <= off_state;
						end if;
					end if;
				when int_low =>
					counter := counter - 1;
					
					if counter > 0 then	--Deadtime is still running
						phase_state <= int_low;
					else								--Deadtime is over
						if commanded_state = pos_state then
							phase_state <= zero_state;
						elsif commanded_state = neg_state then
							phase_state <= neg_state;
						elsif commanded_state = zero_state then
							phase_state <= zero_state;
						else --commanded_state = off_state
							phase_state <= off_state;
						end if;
					end if;
				when pos_state =>
					if commanded_state = pos_state then
						phase_state <= pos_state;
					else --commanded_state = off_state, zero_state or neg_state
						phase_state <= int_high;
						counter := deadtime;
					end if;
				when neg_state =>
					if commanded_state = neg_state then
						phase_state <= neg_state;
					else --commanded_state = off_state, zero_state or pos_state
						phase_state <= int_low;
						counter := deadtime;
					end if;
				when others => --zero_state =>
					if commanded_state = pos_state then
						phase_state <= int_high;
						counter := deadtime;
					elsif commanded_state = neg_state then
						phase_state <= int_low;
						counter := deadtime;
					elsif commanded_state = zero_state then
						phase_state <= zero_state;
					else --commanded_state = off_state
						phase_state <= off_state;
					end if;
			end case;
		end if;
	end process state_machine_proc;
	
	--Assign the outputs
	phase_off <= '1' when phase_state = off_state else '0';
					 
	s1_out <= '1' when phase_state = pos_state else '0';
	s2_out <= '1' when phase_state = pos_state or phase_state = zero_state or phase_state = int_high else '0';
	s3_out <= '1' when phase_state = neg_state or phase_state = zero_state or phase_state = int_low  else '0';
	s4_out <= '1' when phase_state = neg_state else '0';
	
end npc_phase_state_machine_implementation;