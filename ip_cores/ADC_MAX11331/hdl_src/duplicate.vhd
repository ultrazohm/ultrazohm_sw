LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all;

-- duplicate a signal N times
-------------------------------------------
	entity duplicate IS
		generic (N: positive := 3); --array size
		port (
			inp:  in  STD_LOGIC;
			outp: out std_logic_vector(N-1 downto 0)
			);
	end entity;
	-------------------------------------------
	architecture duplicate of duplicate is
	begin
		gen: for i in 0 to N-1 generate 
			outp(i) <= inp;
		end generate;  
	end architecture;
	-------------------------------------------