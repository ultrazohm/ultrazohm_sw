library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity delay_trigger_tb is
end delay_trigger_tb;

architecture tb of delay_trigger_tb is

    constant clk_period : time := 10 ns;
    constant test_delay_cycles : natural := 3;
    constant shorter_delay_cycles : natural := 2;
    constant max_delay_cycles : natural := 1023;
    constant pulse_spacing_cycles : natural := 15;

    signal clk : std_logic := '1';
    signal reset : std_logic := '0';
    signal delay_cycles : unsigned(9 downto 0) := (others => '0');
    signal a_in : std_logic := '0';
    signal a_out : std_logic;
    signal pulse_pending : std_logic;

begin

    uut : entity work.delay_trigger
        port map (
            clk => clk,
            reset => reset,
            delay_cycles => delay_cycles,
            a_in => a_in,
            a_out => a_out,
            pulse_pending => pulse_pending
        );

    clk <= not clk after clk_period / 2;

    stimulus : process
    begin
        -- Hold reset active long enough to clear the delayed edge block.
        reset <= '1';
        a_in <= '0';
        delay_cycles <= to_unsigned(test_delay_cycles, delay_cycles'length);
        for i in 1 to 2 loop
            wait until rising_edge(clk);
            wait for 1 ns;
            assert a_out = '0' report "reset should clear the delayed edge output" severity failure;
            assert pulse_pending = '0' report "reset should clear the delayed edge pending flag" severity failure;
        end loop;

        -- Release reset and confirm the block stays idle.
        wait until falling_edge(clk);
        reset <= '0';
        a_in <= '0';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "output should stay low after reset release" severity failure;
        assert pulse_pending = '0' report "pending flag should stay low after reset release" severity failure;

        -- Zero-delay pulse should pass through immediately.
        wait until falling_edge(clk);
        delay_cycles <= to_unsigned(0, delay_cycles'length);
        a_in <= '1';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '1' report "zero-delay pulse should appear immediately at the output" severity failure;
        assert pulse_pending = '1' report "zero-delay pulse should keep the block busy during the emitted pulse" severity failure;

        wait until falling_edge(clk);
        a_in <= '0';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "zero-delay pulse should be one clock wide" severity failure;
        assert pulse_pending = '0' report "pending flag should return low after the zero-delay pulse" severity failure;

        for i in 1 to pulse_spacing_cycles loop
            wait until rising_edge(clk);
            wait for 1 ns;
            assert a_out = '0' report "output should remain low after the zero-delay pulse" severity failure;
            assert pulse_pending = '0' report "pending flag should stay low after the zero-delay pulse" severity failure;
        end loop;

        -- Reapply the nonzero delay for the delayed-pulse checks below.
        wait until falling_edge(clk);
        delay_cycles <= to_unsigned(test_delay_cycles, delay_cycles'length);
        a_in <= '0';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "delay change to nonzero should clear the block state" severity failure;
        assert pulse_pending = '0' report "delay change to nonzero should clear the pending flag" severity failure;

        -- First isolated one-clock trigger pulse.
        wait until falling_edge(clk);
        a_in <= '1';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "pulse 1 appeared too early at the output" severity failure;
        assert pulse_pending = '1' report "pulse 1 should arm the pending flag" severity failure;

        wait until falling_edge(clk);
        a_in <= '0';
        for i in 1 to test_delay_cycles - 1 loop
            wait until rising_edge(clk);
            wait for 1 ns;
            assert a_out = '0' report "pulse 1 appeared before the programmed delay elapsed" severity failure;
            assert pulse_pending = '1' report "pending flag should stay high until pulse 1 is emitted" severity failure;
        end loop;

        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '1' report "pulse 1 missing after the programmed delay" severity failure;
        assert pulse_pending = '1' report "pending flag should stay high while pulse 1 is emitted" severity failure;

        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "pulse 1 should be one clock wide" severity failure;
        assert pulse_pending = '0' report "pending flag should clear after pulse 1" severity failure;

        for i in 1 to pulse_spacing_cycles loop
            wait until rising_edge(clk);
            wait for 1 ns;
            assert a_out = '0' report "output should remain low between isolated pulses" severity failure;
            assert pulse_pending = '0' report "pending flag should stay low between isolated pulses" severity failure;
        end loop;

        -- Apply a pulse, then reset before the delayed pulse can emerge.
        wait until falling_edge(clk);
        a_in <= '1';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "reset-flush pulse appeared too early at the output" severity failure;
        assert pulse_pending = '1' report "reset-flush test should arm the pending flag before reset" severity failure;

        wait until falling_edge(clk);
        a_in <= '0';
        reset <= '1';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "reset should force the output low" severity failure;
        assert pulse_pending = '0' report "reset should clear the pending flag" severity failure;

        wait until falling_edge(clk);
        reset <= '0';
        a_in <= '0';
        for i in 1 to test_delay_cycles + 1 loop
            wait until rising_edge(clk);
            wait for 1 ns;
            assert a_out = '0' report "reset should flush the pending delayed pulse" severity failure;
            assert pulse_pending = '0' report "reset should keep the pending flag low" severity failure;
        end loop;

        -- Second isolated one-clock trigger pulse with the same delay.
        wait until falling_edge(clk);
        a_in <= '1';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "pulse 2 appeared too early at the output" severity failure;
        assert pulse_pending = '1' report "pulse 2 should arm the pending flag" severity failure;

        wait until falling_edge(clk);
        a_in <= '0';
        for i in 1 to test_delay_cycles - 1 loop
            wait until rising_edge(clk);
            wait for 1 ns;
            assert a_out = '0' report "pulse 2 appeared before the programmed delay elapsed" severity failure;
            assert pulse_pending = '1' report "pending flag should stay high until pulse 2 is emitted" severity failure;
        end loop;

        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '1' report "pulse 2 missing after the programmed delay" severity failure;
        assert pulse_pending = '1' report "pending flag should stay high while pulse 2 is emitted" severity failure;

        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "pulse 2 should be one clock wide" severity failure;
        assert pulse_pending = '0' report "pending flag should clear after pulse 2" severity failure;

        for i in 1 to pulse_spacing_cycles loop
            wait until rising_edge(clk);
            wait for 1 ns;
            assert a_out = '0' report "output should return low after pulse 2" severity failure;
            assert pulse_pending = '0' report "pending flag should stay low after pulse 2" severity failure;
        end loop;

        -- Change delay setting and verify the stored state is discarded.
        wait until falling_edge(clk);
        delay_cycles <= to_unsigned(shorter_delay_cycles, delay_cycles'length);
        a_in <= '0';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "delay change should clear the block state" severity failure;
        assert pulse_pending = '0' report "delay change should clear the pending flag" severity failure;

        -- Third isolated pulse with the new shorter delay.
        wait until falling_edge(clk);
        a_in <= '1';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "pulse 3 appeared too early at the output" severity failure;
        assert pulse_pending = '1' report "pulse 3 should arm the pending flag" severity failure;

        wait until falling_edge(clk);
        a_in <= '0';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "pulse 3 appeared before the new delay elapsed" severity failure;
        assert pulse_pending = '1' report "pending flag should stay high until pulse 3 is emitted" severity failure;

        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '1' report "pulse 3 missing after the new shorter delay" severity failure;
        assert pulse_pending = '1' report "pending flag should stay high while pulse 3 is emitted" severity failure;

        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "pulse 3 should be one clock wide" severity failure;
        assert pulse_pending = '0' report "pending flag should clear after pulse 3" severity failure;

        -- A second edge while the first one is pending is ignored.
        wait until falling_edge(clk);
        delay_cycles <= to_unsigned(test_delay_cycles, delay_cycles'length);
        a_in <= '1';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "ignore-while-pending test: first edge appeared too early" severity failure;
        assert pulse_pending = '1' report "ignore-while-pending test: first edge should arm the pending flag" severity failure;

        wait until falling_edge(clk);
        a_in <= '0';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "ignore-while-pending test: output should still be low one cycle before the second edge" severity failure;
        assert pulse_pending = '1' report "ignore-while-pending test: pending flag should stay high before the second edge" severity failure;

        wait until falling_edge(clk);
        a_in <= '1';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "ignore-while-pending test: second edge must not produce an early output pulse" severity failure;
        assert pulse_pending = '1' report "ignore-while-pending test: second edge must not replace the pending pulse" severity failure;

        wait until falling_edge(clk);
        a_in <= '0';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '1' report "ignore-while-pending test: only the first edge should produce the delayed output pulse" severity failure;
        assert pulse_pending = '1' report "ignore-while-pending test: pending flag should stay high while the delayed output pulse is emitted" severity failure;

        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "ignore-while-pending test: output pulse should be one clock wide" severity failure;
        assert pulse_pending = '0' report "ignore-while-pending test: pending flag should stay low after the delayed pulse" severity failure;

        for i in 1 to pulse_spacing_cycles loop
            wait until rising_edge(clk);
            wait for 1 ns;
            assert a_out = '0' report "ignore-while-pending test: second edge should not create a later delayed output pulse" severity failure;
            assert pulse_pending = '0' report "ignore-while-pending test: pending flag should remain low after the ignored edge" severity failure;
        end loop;

        -- Keep the input high for multiple cycles and verify only one delayed pulse is emitted.
        wait until falling_edge(clk);
        a_in <= '1';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "sustained-high test: output appeared too early" severity failure;
        assert pulse_pending = '1' report "sustained-high test: first rising edge should arm the pending flag" severity failure;

        for i in 1 to test_delay_cycles - 1 loop
            wait until rising_edge(clk);
            wait for 1 ns;
            assert a_out = '0' report "sustained-high test: output appeared before the programmed delay elapsed" severity failure;
            assert pulse_pending = '1' report "sustained-high test: pending flag should stay high before the delayed pulse" severity failure;
        end loop;

        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '1' report "sustained-high test: output should emit one delayed pulse after the programmed delay" severity failure;
        assert pulse_pending = '1' report "sustained-high test: pending flag should stay high while the delayed pulse is emitted" severity failure;

        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "sustained-high test: output should return low after one pulse" severity failure;
        assert pulse_pending = '0' report "sustained-high test: pending flag should stay low after the pulse" severity failure;

        wait until falling_edge(clk);
        a_in <= '0';

        for i in 1 to 3 loop
            wait until rising_edge(clk);
            wait for 1 ns;
            assert a_out = '0' report "sustained-high test: output should stay low after the single delayed pulse" severity failure;
            assert pulse_pending = '0' report "sustained-high test: pending flag should stay low after the single delayed pulse" severity failure;
        end loop;

        -- Exercise the maximum supported delay setting.
        wait until falling_edge(clk);
        delay_cycles <= to_unsigned(max_delay_cycles, delay_cycles'length);
        a_in <= '0';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "max-delay test: reconfiguration should leave the output low" severity failure;
        assert pulse_pending = '0' report "max-delay test: reconfiguration should leave the pending flag low" severity failure;

        wait until falling_edge(clk);
        a_in <= '1';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "max-delay test: pulse appeared too early at the output" severity failure;
        assert pulse_pending = '1' report "max-delay test: trigger should arm the pending flag" severity failure;

        wait until falling_edge(clk);
        a_in <= '0';
        for i in 1 to max_delay_cycles - 1 loop
            wait until rising_edge(clk);
            wait for 1 ns;
            assert a_out = '0' report "max-delay test: output appeared before the maximum programmed delay elapsed" severity failure;
            assert pulse_pending = '1' report "max-delay test: pending flag should stay high until the delayed pulse is emitted" severity failure;
        end loop;

        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '1' report "max-delay test: pulse missing after the maximum programmed delay" severity failure;
        assert pulse_pending = '1' report "max-delay test: pending flag should stay high while the delayed pulse is emitted" severity failure;

        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "max-delay test: output pulse should still be one clock wide" severity failure;
        assert pulse_pending = '0' report "max-delay test: pending flag should clear after the delayed pulse" severity failure;

        -- Change from a nonzero delay to zero while a pulse is pending.
        wait until falling_edge(clk);
        delay_cycles <= to_unsigned(test_delay_cycles, delay_cycles'length);
        a_in <= '1';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "nonzero-to-zero test: pulse appeared too early before reconfiguration" severity failure;
        assert pulse_pending = '1' report "nonzero-to-zero test: pending flag should be high before reconfiguration" severity failure;

        wait until falling_edge(clk);
        a_in <= '0';
        delay_cycles <= to_unsigned(0, delay_cycles'length);
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "nonzero-to-zero test: changing delay to zero should flush the pending pulse" severity failure;
        assert pulse_pending = '0' report "nonzero-to-zero test: changing delay to zero should clear the pending flag" severity failure;

        for i in 1 to test_delay_cycles + 1 loop
            wait until rising_edge(clk);
            wait for 1 ns;
            assert a_out = '0' report "nonzero-to-zero test: flushed delayed pulse should not reappear later" severity failure;
            assert pulse_pending = '0' report "nonzero-to-zero test: pending flag should stay low after the flush" severity failure;
        end loop;

        -- Confirm the zero-delay path still works after the live reconfiguration.
        wait until falling_edge(clk);
        a_in <= '1';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '1' report "nonzero-to-zero test: zero-delay pulse should appear immediately after reconfiguration" severity failure;
        assert pulse_pending = '1' report "nonzero-to-zero test: zero-delay pulse should keep the block busy during the emitted pulse" severity failure;

        wait until falling_edge(clk);
        a_in <= '0';
        wait until rising_edge(clk);
        wait for 1 ns;
        assert a_out = '0' report "nonzero-to-zero test: zero-delay pulse should remain one clock wide after reconfiguration" severity failure;
        assert pulse_pending = '0' report "nonzero-to-zero test: pending flag should return low after the zero-delay recovery pulse" severity failure;

        report "delay_trigger_tb completed successfully" severity note;
        wait;
    end process;

end tb;
