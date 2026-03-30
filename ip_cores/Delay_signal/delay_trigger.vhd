----------------------------------------------------------------------------------
-- Company:
-- Engineer:
--
-- Description:
-- 1-bit rising-edge delay block with configurable output pulse width.
-- - detects rising edges on a_in
-- - emits a pulse at a_out after delay_cycles samples
-- - pulse width is configured locally in this VHDL source
-- - delay_cycles supports 0..1023 via a 10-bit input
-- - pulse_width_cycles_c supports 1..64 clk cycles
-- - resetN is an active-low synchronous reset input
-- - changing delay_cycles clears any active operation
-- - a second rising edge while one pulse is active is ignored
-- - pulse_pending is high while a trigger is waiting or being emitted
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity delay_trigger is
    port(
        clk : in std_logic;
        resetN : in std_logic;
        delay_cycles : in unsigned(9 downto 0);
        a_in : in std_logic;
        a_out : out std_logic := '0';
        pulse_pending : out std_logic := '0'
    );
end delay_trigger;

architecture Behavioral of delay_trigger is

type pulse_state_t is (IDLE, WAIT_DELAY, OUTPUT_PULSE);

-- Output pulse width in clk cycles. Change this constant in VHDL if needed.
constant pulse_width_cycles_c : natural range 1 to 64 := 1;

-- Previous sampled input to detect a rising edge.
signal a_in_prev : std_logic := '0';
-- Previous delay setting to flush state after runtime changes.
signal delay_cycles_prev : unsigned(9 downto 0) := (others => '0');
-- State machine for the delayed pulse.
signal pulse_state : pulse_state_t := IDLE;
-- Countdown until the delayed pulse starts.
signal delay_counter : unsigned(9 downto 0) := (others => '0');
-- Remaining extra high cycles after the first emitted output cycle.
signal width_counter : unsigned(5 downto 0) := (others => '0');
-- Registered output for clean pulse_pending derivation.
signal a_out_i : std_logic := '0';

begin
    a_out <= a_out_i;
    pulse_pending <= '1' when (pulse_state /= IDLE) or (a_out_i = '1') else '0';

process(clk)
    variable delay_cycles_int : natural range 0 to 1023;
    variable pulse_width_int : natural range 1 to 64;
    variable rise_pulse : std_logic;
    variable config_changed : boolean;
begin
    if rising_edge(clk) then
        if resetN = '0' then
            a_in_prev <= '0';
            delay_cycles_prev <= (others => '0');
            pulse_state <= IDLE;
            delay_counter <= (others => '0');
            width_counter <= (others => '0');
            a_out_i <= '0';
        else
            delay_cycles_int := to_integer(delay_cycles);
            pulse_width_int := pulse_width_cycles_c;

            if (a_in = '1') and (a_in_prev = '0') then
                rise_pulse := '1';
            else
                rise_pulse := '0';
            end if;

            config_changed := (delay_cycles /= delay_cycles_prev);

            if config_changed then
                -- A changed delay invalidates any already accepted trigger.
                pulse_state <= IDLE;
                delay_counter <= (others => '0');
                width_counter <= (others => '0');
                a_out_i <= '0';

                if rise_pulse = '1' then
                    if delay_cycles_int = 0 then
                        a_out_i <= '1';
                        if pulse_width_int > 1 then
                            pulse_state <= OUTPUT_PULSE;
                            width_counter <= to_unsigned(pulse_width_int - 2, width_counter'length);
                        end if;
                    else
                        pulse_state <= WAIT_DELAY;
                        delay_counter <= to_unsigned(delay_cycles_int - 1, delay_counter'length);
                    end if;
                end if;
            else
                case pulse_state is
                    when IDLE =>
                        a_out_i <= '0';
                        delay_counter <= (others => '0');
                        width_counter <= (others => '0');

                        if rise_pulse = '1' then
                            if delay_cycles_int = 0 then
                                a_out_i <= '1';
                                if pulse_width_int > 1 then
                                    pulse_state <= OUTPUT_PULSE;
                                    width_counter <= to_unsigned(pulse_width_int - 2, width_counter'length);
                                end if;
                            else
                                pulse_state <= WAIT_DELAY;
                                delay_counter <= to_unsigned(delay_cycles_int - 1, delay_counter'length);
                            end if;
                        end if;

                    when WAIT_DELAY =>
                        assert rise_pulse = '0'
                            report "delay_trigger ignored a rising edge while a delayed pulse was already pending"
                            severity warning;

                        a_out_i <= '0';

                        if delay_counter = 0 then
                            a_out_i <= '1';
                            if pulse_width_int = 1 then
                                pulse_state <= IDLE;
                            else
                                pulse_state <= OUTPUT_PULSE;
                                width_counter <= to_unsigned(pulse_width_int - 2, width_counter'length);
                            end if;
                        else
                            delay_counter <= delay_counter - 1;
                        end if;

                    when OUTPUT_PULSE =>
                        assert rise_pulse = '0'
                            report "delay_trigger ignored a rising edge while the output pulse was still active"
                            severity warning;

                        a_out_i <= '1';

                        if width_counter = 0 then
                            pulse_state <= IDLE;
                        else
                            width_counter <= width_counter - 1;
                        end if;
                end case;
            end if;

            a_in_prev <= a_in;
            delay_cycles_prev <= delay_cycles;
        end if;
    end if;
end process;

end Behavioral;
