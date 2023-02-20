
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.syn_functions_pkg;



entity test is
    generic
    (
        -- Core capacity
        NB_TERMS                    : positive  := 12;

        -- Signal widths
        TERM_WIDTH                  : positive  := 16
    );
    port
    (
        -- Clock domain
        clock_i                     : in  std_logic;
        clock_enable_i              : in  std_logic;

        -- Input interface
        input_term_concatenation_i  : in  std_logic_vector(0 to ((NB_TERMS * TERM_WIDTH) - 1));

        -- Output_interface
        output_sum_o                : out std_logic_vector(((TERM_WIDTH + syn_functions_pkg.ceil_log2(NB_TERMS)) - 1) downto 0)
    );
end entity test;



architecture rtl of test is

    constant    SUM_WIDTH                       : positive  := (TERM_WIDTH + syn_functions_pkg.ceil_log2(NB_TERMS));

    type        t_term_vector                   is array(natural range <>) of std_logic_vector((TERM_WIDTH - 1) downto 0);

    signal      reg_term_concatenation          : std_logic_vector(0 to ((NB_TERMS * TERM_WIDTH) - 1));
    signal      term_vector                     : t_term_vector(0 to (NB_TERMS - 1));

    function binary_adder_tree
    (
        input_term_vector   : t_term_vector
    )
    return std_logic_vector is
        constant    N                           : natural                       := input_term_vector'length;
        constant    term_vector                 : t_term_vector(0 to (N - 1))   := input_term_vector;
        constant    LEFT_TREE_N                 : natural                       := ((N + 1) / 2);
        constant    RIGHT_TREE_N                : natural                       := (N - LEFT_TREE_N);
        constant    LEFT_TREE_LOW_INDEX         : natural                       := 0;
        constant    LEFT_TREE_HIGH_INDEX        : natural                       := (LEFT_TREE_LOW_INDEX + LEFT_TREE_N - 1);
        constant    RIGHT_TREE_LOW_INDEX        : natural                       := (LEFT_TREE_HIGH_INDEX + 1);
        constant    RIGHT_TREE_HIGH_INDEX       : natural                       := (RIGHT_TREE_LOW_INDEX + RIGHT_TREE_N - 1);
        constant    SUM_WIDTH                   : natural                       := (TERM_WIDTH + syn_functions_pkg.ceil_log2(N));
    begin
        if (N = 1) then
            return term_vector(0);
        else
            return  std_logic_vector(
                            resize(signed(binary_adder_tree(term_vector(LEFT_TREE_LOW_INDEX to LEFT_TREE_HIGH_INDEX))), SUM_WIDTH)
                        +   resize(signed(binary_adder_tree(term_vector(RIGHT_TREE_LOW_INDEX to RIGHT_TREE_HIGH_INDEX))), SUM_WIDTH)
                    );
        end if;
    end function binary_adder_tree;

    signal      sum                             : std_logic_vector((SUM_WIDTH - 1) downto 0);
    signal      reg_sum                         : std_logic_vector((SUM_WIDTH - 1) downto 0);



begin

    term_registers : process(clock_i)
    begin
        if rising_edge(clock_i) then
            if (clock_enable_i = '1') then
                reg_term_concatenation  <= input_term_concatenation_i;
            end if;
        end if;
    end process term_registers;

    gen_term_vector : process(reg_term_concatenation)
    begin
        for TERM_INDEX in 0 to (NB_TERMS - 1) loop
            term_vector(TERM_INDEX)                 <= reg_term_concatenation((TERM_INDEX * TERM_WIDTH) to (((TERM_INDEX + 1) * TERM_WIDTH) - 1));
        end loop;
    end process gen_term_vector;



    sum <=          binary_adder_tree(term_vector);



    sum_registers : process(clock_i)
    begin
        if rising_edge(clock_i) then
            if (clock_enable_i = '1') then
                reg_sum <= sum;
            end if;
        end if;
    end process sum_registers;

    output_sum_o    <=          reg_sum;



end architecture rtl;



