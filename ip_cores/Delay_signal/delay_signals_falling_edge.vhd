----------------------------------------------------------------------------------
-- Company: TUM HLU
-- Engineer: Aufderheide
--
-- Create Date: 2026-01-29
-- Module Name: delay_signals_falling_edge - Behavioral
--
-- Description:
--   Clock-cycle programmable delay that only delays the *falling edge* of a_in.
--   - Rising edge: passes through immediately (combinational).
--   - Falling edge: delayed by exactly delay_cycles clock cycles.
--   - delay_cycles = 0: true pass-through, a_out = a_in (both edges immediate).
--   - delay_cycles = N: rising edge immediate, falling edge delayed by N cycles.
--
-- Notes:
--   delay_cycles is interpreted in clock cycles. With an 11-bit unsigned input and a
--   2047-bit shift register, the valid range is 0..2047.
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity delay_signals_falling_edge is
    port(
        clk          : in  std_logic;
        delay_cycles : in  unsigned(10 downto 0);  -- delay in clock cycles (0..2047)
        a_in         : in  std_logic;
        a_out        : out std_logic := '0'
    );
end delay_signals_falling_edge;

architecture Behavioral of delay_signals_falling_edge is

    -- Shift register holding input history:
    -- input_shift_reg(0) = sample from 1 cycle ago, input_shift_reg(N) = sample from N+1 cycles ago
    signal input_shift_reg : std_logic_vector(2046 downto 0) := (others => '0');
    signal history_or      : std_logic := '0';

begin

    -- Sequential process: shift register only
    process(clk)
    begin
        if rising_edge(clk) then
            -- Shift in current sample
            input_shift_reg <= input_shift_reg(input_shift_reg'high-1 downto 0) & a_in;
        end if;
    end process;

    -- OR-reduce the last N samples (N = delay_cycles) to delay the falling edge
    process(delay_cycles, input_shift_reg)
        variable dly    : integer;
        variable or_acc : std_logic;
    begin
        dly := to_integer(delay_cycles);
        or_acc := '0';
        for i in 0 to input_shift_reg'high loop
            if i < dly then
                or_acc := or_acc or input_shift_reg(i);
            end if;
        end loop;
        history_or <= or_acc;
    end process;

    -- Combinational output: rising edge passes through immediately (via a_in),
    -- falling edge is delayed by delay_cycles (via history OR)
    -- delay_cycles=0: both edges immediate (a_out = a_in)
    -- delay_cycles=N: falling edge delayed by N cycles
    a_out <= a_in when delay_cycles = 0 else
             a_in or history_or;

end Behavioral;
