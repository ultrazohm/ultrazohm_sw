----------------------------------------------------------------------------------
-- Company: TUM HLU
-- Engineer: Aufderheide
--
-- Create Date: 2026-01-29
-- Module Name: delay_signals_rising_edge - Behavioral
--
-- Description:
--   Clock-cycle programmable delay that only delays the *rising edge* of a_in.
--   - Falling edge: passes through immediately (combinational).
--   - Rising edge: delayed by exactly delay_cycles clock cycles.
--   - delay_cycles = 0: true pass-through, a_out = a_in (both edges immediate).
--   - delay_cycles = N: falling edge immediate, rising edge delayed by N cycles.
--
-- Notes:
--   delay_cycles is interpreted in clock cycles. With an 11-bit unsigned input and a
--   2047-bit shift register, the valid range is 0..2047.
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity delay_signals_rising_edge is
    port(
        clk          : in  std_logic;
        delay_cycles : in  unsigned(10 downto 0);  -- delay in clock cycles (0..2047)
        a_in         : in  std_logic;
        a_out        : out std_logic := '0'
    );
end delay_signals_rising_edge;

architecture Behavioral of delay_signals_rising_edge is

    -- Shift register holding input history:
    -- input_shift_reg(0) = sample from 1 cycle ago, input_shift_reg(N) = sample from N+1 cycles ago
    signal input_shift_reg : std_logic_vector(2046 downto 0) := (others => '0');
    signal history_and     : std_logic := '0';

begin

    -- Sequential process: shift register only
    process(clk)
    begin
        if rising_edge(clk) then
            -- Shift in current sample
            input_shift_reg <= input_shift_reg(input_shift_reg'high-1 downto 0) & a_in;
        end if;
    end process;

    -- AND-reduce the last N samples (N = delay_cycles) to delay the rising edge
    process(delay_cycles, input_shift_reg)
        variable dly     : integer;
        variable and_acc : std_logic;
    begin
        dly := to_integer(delay_cycles);
        and_acc := '1';
        for i in 0 to input_shift_reg'high loop
            if i < dly then
                and_acc := and_acc and input_shift_reg(i);
            end if;
        end loop;
        history_and <= and_acc;
    end process;

    -- Combinational output: falling edge passes through immediately (via a_in),
    -- rising edge is delayed by delay_cycles (via history AND)
    -- delay_cycles=0: both edges immediate (a_out = a_in)
    -- delay_cycles=N: rising edge delayed by N cycles
    a_out <= a_in when delay_cycles = 0 else
             a_in and history_and;

end Behavioral;
