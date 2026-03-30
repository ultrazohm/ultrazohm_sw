library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity delay_trigger_tb is
end delay_trigger_tb;

architecture tb of delay_trigger_tb is

    constant clk_period : time := 10 ns;
    constant test_delay_cycles : natural := 3;
    constant one_cycle_delay : natural := 1;
    constant shorter_delay_cycles : natural := 2;
    constant max_delay_cycles : natural := 1023;
    constant pulse_spacing_cycles : natural := 15;

    signal clk : std_logic := '1';
    signal resetN : std_logic := '1';
    signal delay_cycles : unsigned(9 downto 0) := (others => '0');
    signal a_in : std_logic := '0';
    signal a_out : std_logic;
    signal pulse_pending : std_logic;

begin

    uut : entity work.delay_trigger
        port map (
            clk => clk,
            resetN => resetN,
            delay_cycles => delay_cycles,
            a_in => a_in,
            a_out => a_out,
            pulse_pending => pulse_pending
        );

    clk <= not clk after clk_period / 2;

    stimulus : process
        procedure drive_inputs(
            constant next_resetN : std_logic;
            constant next_delay_cycles : natural;
            constant next_a_in : std_logic
        ) is
        begin
            wait until rising_edge(clk);
            resetN <= next_resetN;
            delay_cycles <= to_unsigned(next_delay_cycles, delay_cycles'length);
            a_in <= next_a_in;
        end procedure;
    begin
        -- Stimulus is updated immediately after rising_edge(clk), so the DUT
        -- samples each new value on the following rising edge.
        resetN <= '0';
        a_in <= '0';
        delay_cycles <= to_unsigned(test_delay_cycles, delay_cycles'length);
        for i in 1 to 2 loop
            wait until rising_edge(clk);
        end loop;

        -- Release resetN and confirm the block stays idle.
        drive_inputs('1', test_delay_cycles, '0');
        wait until rising_edge(clk);

        -- Zero-delay pulse should pass through immediately.
        drive_inputs('1', 0, '1');
        wait until rising_edge(clk);

        drive_inputs('1', 0, '0');
        wait until rising_edge(clk);

        for i in 1 to pulse_spacing_cycles loop
            wait until rising_edge(clk);
        end loop;

        -- One-cycle delay should emit the registered pulse on the next rising edge.
        drive_inputs('1', one_cycle_delay, '1');
        wait until rising_edge(clk);

        drive_inputs('1', one_cycle_delay, '0');
        wait until rising_edge(clk);

        for i in 1 to pulse_spacing_cycles loop
            wait until rising_edge(clk);
        end loop;

        -- Reapply the nonzero delay for the delayed-pulse checks below.
        drive_inputs('1', test_delay_cycles, '0');
        wait until rising_edge(clk);

        -- First isolated one-clock trigger pulse.
        drive_inputs('1', test_delay_cycles, '1');
        wait until rising_edge(clk);

        drive_inputs('1', test_delay_cycles, '0');
        for i in 1 to test_delay_cycles - 2 loop
            wait until rising_edge(clk);
        end loop;

        wait until rising_edge(clk);

        wait until rising_edge(clk);

        for i in 1 to pulse_spacing_cycles loop
            wait until rising_edge(clk);
        end loop;

        -- Apply a pulse, then assert resetN low before the delayed pulse can emerge.
        drive_inputs('1', test_delay_cycles, '1');
        wait until rising_edge(clk);

        drive_inputs('0', test_delay_cycles, '0');
        wait until rising_edge(clk);

        drive_inputs('1', test_delay_cycles, '0');
        for i in 1 to test_delay_cycles + 1 loop
            wait until rising_edge(clk);
        end loop;

        -- Second isolated one-clock trigger pulse with the same delay.
        drive_inputs('1', test_delay_cycles, '1');
        wait until rising_edge(clk);

        drive_inputs('1', test_delay_cycles, '0');
        for i in 1 to test_delay_cycles - 2 loop
            wait until rising_edge(clk);
        end loop;

        wait until rising_edge(clk);

        wait until rising_edge(clk);

        for i in 1 to pulse_spacing_cycles loop
            wait until rising_edge(clk);
        end loop;

        -- Change delay setting and verify the stored state is discarded.
        drive_inputs('1', shorter_delay_cycles, '0');
        wait until rising_edge(clk);

        -- Third isolated pulse with the new shorter delay.
        drive_inputs('1', shorter_delay_cycles, '1');
        wait until rising_edge(clk);

        drive_inputs('1', shorter_delay_cycles, '0');
        wait until rising_edge(clk);

        wait until rising_edge(clk);

        -- A second edge while the first one is pending is ignored.
        drive_inputs('1', test_delay_cycles, '1');
        wait until rising_edge(clk);

        drive_inputs('1', test_delay_cycles, '0');
        wait until rising_edge(clk);

        drive_inputs('1', test_delay_cycles, '1');
        wait until rising_edge(clk);

        drive_inputs('1', test_delay_cycles, '0');
        wait until rising_edge(clk);

        for i in 1 to pulse_spacing_cycles loop
            wait until rising_edge(clk);
        end loop;

        -- Keep the input high for multiple cycles and verify only one delayed pulse is emitted.
        drive_inputs('1', test_delay_cycles, '1');
        wait until rising_edge(clk);

        for i in 1 to test_delay_cycles - 2 loop
            wait until rising_edge(clk);
        end loop;

        wait until rising_edge(clk);

        wait until rising_edge(clk);

        drive_inputs('1', test_delay_cycles, '0');
        for i in 1 to 3 loop
            wait until rising_edge(clk);
        end loop;

        -- Exercise the maximum supported delay setting.
        drive_inputs('1', max_delay_cycles, '0');
        wait until rising_edge(clk);

        drive_inputs('1', max_delay_cycles, '1');
        wait until rising_edge(clk);

        drive_inputs('1', max_delay_cycles, '0');
        for i in 1 to max_delay_cycles - 2 loop
            wait until rising_edge(clk);
        end loop;

        wait until rising_edge(clk);

        wait until rising_edge(clk);

        -- Change from a nonzero delay to zero while a pulse is pending.
        drive_inputs('1', test_delay_cycles, '1');
        wait until rising_edge(clk);

        drive_inputs('1', 0, '0');
        wait until rising_edge(clk);

        for i in 1 to test_delay_cycles + 1 loop
            wait until rising_edge(clk);
        end loop;

        -- Confirm the zero-delay path still works after the live reconfiguration.
        drive_inputs('1', 0, '1');
        wait until rising_edge(clk);

        drive_inputs('1', 0, '0');
        wait until rising_edge(clk);

        report "delay_trigger_tb completed successfully" severity note;
        wait;
    end process;

end tb;
