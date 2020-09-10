
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY tb_extend_intr IS
END tb_extend_intr;

ARCHITECTURE behavior OF tb_extend_intr IS

COMPONENT extend_interrupt
PORT(
            clock :         in STD_LOGIC;
            interrupt_in :  in STD_LOGIC;
            interrupt_out: out STD_LOGIC  := '0'
);
END COMPONENT;

--Inputs
signal clock : std_logic := '0';
signal interrupt_in : std_logic := '0';

--Outputs
signal interrupt_out : std_logic;

 -- Clock period definitions
constant clk_period : time := 20 ns;

BEGIN

 -- Instantiate the Unit Under Test (UUT)
uut: extend_interrupt PORT MAP (
clock => clock,
interrupt_in => interrupt_in,
interrupt_out => interrupt_out
);

 -- Clock process definitions
clk_process :process
begin
clock <= '0';
wait for clk_period/2;
clock <= '1';
wait for clk_period/2;
end process;

 -- Stimulus process
stim_proc: process
begin
wait for 100 ns;
interrupt_in <= '1';
wait for 20 ns;
interrupt_in <= '0';
wait for 2us;
end process;

END;