----------------------------------------------------------------------------------
-- Self-checking testbench for delay_signals_falling_edge and delay_signals_rising_edge
--
-- Tests both modules with the same stimulus:
-- - delay_signals_falling_edge: rising edge immediate, falling edge delayed
-- - delay_signals_rising_edge: falling edge immediate, rising edge delayed
--
-- Test constraint: a_in minimum high time = 10 clock cycles
----------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.env.stop;

entity tb_delay_signals is
end entity;

architecture sim of tb_delay_signals is

    constant CLK_PERIOD : time := 10 ns;

    signal clk          : std_logic := '1';
    signal delay_cycles : unsigned(10 downto 0) := (others => '0');
    signal a_in         : std_logic := '0';

    -- Outputs from both DUTs
    signal a_out_falling : std_logic;
    signal a_out_rising  : std_logic;

begin

    -- DUT: Falling edge delay
    dut_falling : entity work.delay_signals_falling_edge
        port map(
            clk          => clk,
            delay_cycles => delay_cycles,
            a_in         => a_in,
            a_out        => a_out_falling
        );

    -- DUT: Rising edge delay
    dut_rising : entity work.delay_signals_rising_edge
        port map(
            clk          => clk,
            delay_cycles => delay_cycles,
            a_in         => a_in,
            a_out        => a_out_rising
        );

    -- Clock
    clk <= not clk after CLK_PERIOD/2;

    --------------------------------------------------------------------------
    -- Stimulus (rising-edge synchronous)
    --------------------------------------------------------------------------
    stimulus : process
        procedure drive_on_rising_edge(constant din : std_logic; constant dly : natural) is
        begin
            wait until rising_edge(clk);
            a_in         <= din;
            delay_cycles <= to_unsigned(dly, delay_cycles'length);
        end procedure;

        variable i : integer;
    begin
        -- Initial settle cycles (keep defaults)
        wait for 5*CLK_PERIOD;

        ----------------------------------------------------------------------
        -- Case A: delay_cycles = 0 (true pass-through)
        -- a_in high for 10 cycles, then low for 5 cycles
        ----------------------------------------------------------------------
        for i in 0 to 9 loop
            drive_on_rising_edge('1', 0);
        end loop;
        for i in 0 to 4 loop
            drive_on_rising_edge('0', 0);
        end loop;

        ----------------------------------------------------------------------
        -- Case B: delay_cycles = 3
        -- a_in high for 10 cycles, then low for 10 cycles
        ----------------------------------------------------------------------
        for i in 0 to 9 loop
            drive_on_rising_edge('1', 3);
        end loop;
        for i in 0 to 9 loop
            drive_on_rising_edge('0', 3);
        end loop;

        ----------------------------------------------------------------------
        -- Case C: delay_cycles = 5
        -- a_in high for 10 cycles, then low for 10 cycles
        ----------------------------------------------------------------------
        for i in 0 to 9 loop
            drive_on_rising_edge('1', 5);
        end loop;
        for i in 0 to 9 loop
            drive_on_rising_edge('0', 5);
        end loop;

        ----------------------------------------------------------------------
        -- Case D: Two pulses with delay_cycles = 2
        -- Each pulse: high for 10 cycles, low for 5 cycles
        ----------------------------------------------------------------------
        for i in 0 to 9 loop
            drive_on_rising_edge('1', 2);
        end loop;
        for i in 0 to 4 loop
            drive_on_rising_edge('0', 2);
        end loop;
        for i in 0 to 9 loop
            drive_on_rising_edge('1', 2);
        end loop;
        for i in 0 to 4 loop
            drive_on_rising_edge('0', 2);
        end loop;

        ----------------------------------------------------------------------
        -- Case E: Low pulse shorter than delay (2 cycles low, delay_cycles = 5)
        -- a_in high for 10 cycles, low for 2 cycles, then high for 10 cycles
        ----------------------------------------------------------------------
        for i in 0 to 9 loop
            drive_on_rising_edge('1', 5);
        end loop;
        for i in 0 to 1 loop
            drive_on_rising_edge('0', 5);
        end loop;
        for i in 0 to 9 loop
            drive_on_rising_edge('1', 5);
        end loop;

        -- Allow any delayed edges to flush out before the next case
        for i in 0 to 9 loop
            wait until rising_edge(clk);
        end loop;

        ----------------------------------------------------------------------
        -- Case F: Another pulse after short low-pulse test
        -- Verify modules recover correctly after Case E
        ----------------------------------------------------------------------
        for i in 0 to 9 loop
            drive_on_rising_edge('1', 3);
        end loop;
        for i in 0 to 9 loop
            drive_on_rising_edge('0', 3);
        end loop;

        report "All stimulus applied. If no assertion failed, test PASSED." severity note;

        wait for 5*CLK_PERIOD;
        report "Simulation finished." severity note;
        stop;
    end process;

    --------------------------------------------------------------------------
    -- Checker for falling edge delay module
    --------------------------------------------------------------------------
    checker_falling : process
        variable input_history : std_logic_vector(2046 downto 0) := (others => '0');
        variable history_or    : std_logic;
        variable expected      : std_logic;
        variable cycle         : natural := 0;
        variable sampled_a_in  : std_logic;
        variable dly           : integer range 0 to 2047;
    begin
        wait until rising_edge(clk);

        sampled_a_in := a_in;
        dly := to_integer(delay_cycles);

        input_history := input_history(input_history'high-1 downto 0) & sampled_a_in;

        wait for 1 ps;

        if dly = 0 then
            expected := a_in;
        else
            history_or := '0';
            for i in 0 to dly - 1 loop
                history_or := history_or or input_history(i);
            end loop;
            expected := a_in or history_or;
        end if;

        assert a_out_falling = expected
            report "[FALLING] Mismatch @cycle=" & integer'image(cycle) &
                   " delay=" & integer'image(dly) &
                   " a_in=" & std_logic'image(a_in) &
                   " expected=" & std_logic'image(expected) &
                   " got=" & std_logic'image(a_out_falling)
            severity error;

        cycle := cycle + 1;
    end process;

    --------------------------------------------------------------------------
    -- Checker for rising edge delay module
    --------------------------------------------------------------------------
    checker_rising : process
        variable input_history : std_logic_vector(2046 downto 0) := (others => '0');
        variable history_and   : std_logic;
        variable expected      : std_logic;
        variable cycle         : natural := 0;
        variable sampled_a_in  : std_logic;
        variable dly           : integer range 0 to 2047;
    begin
        wait until rising_edge(clk);

        sampled_a_in := a_in;
        dly := to_integer(delay_cycles);

        input_history := input_history(input_history'high-1 downto 0) & sampled_a_in;

        wait for 1 ps;

        if dly = 0 then
            expected := a_in;
        else
            history_and := '1';
            for i in 0 to dly - 1 loop
                history_and := history_and and input_history(i);
            end loop;
            expected := a_in and history_and;  -- AND for rising edge delay
        end if;

        assert a_out_rising = expected
            report "[RISING] Mismatch @cycle=" & integer'image(cycle) &
                   " delay=" & integer'image(dly) &
                   " a_in=" & std_logic'image(a_in) &
                   " expected=" & std_logic'image(expected) &
                   " got=" & std_logic'image(a_out_rising)
            severity error;

        cycle := cycle + 1;
    end process;

end architecture;
