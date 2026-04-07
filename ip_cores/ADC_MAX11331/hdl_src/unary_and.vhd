LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all;


-- source: https://stackoverflow.com/questions/20296276/and-all-elements-of-an-n-bit-array-in-vhdl
--  I have an n-bit array. I want to AND all elements in the array. Similar to wiring each element to an n-bit AND gate. 

-------------------------------------------
	entity unary_AND IS
		generic (N: positive := 8); --array size
		port (
			inp: in std_logic_vector(N-1 downto 0);
			outp: out STD_LOGIC);
	end entity;
	-------------------------------------------
	architecture unary_AND of unary_AND is
		signal temp: std_logic_vector(N-1 downto 0);
	begin
		temp(0) <= inp(0);
		gen: for i in 1 to N-1 generate
			temp(i) <= temp(i-1) and inp(i);
		end generate; 
		outp <= temp(N-1); 
	end architecture;
	-------------------------------------------