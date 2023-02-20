
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
    type        t_resized_term_vector           is array(natural range <>) of std_logic_vector((SUM_WIDTH - 1) downto 0);

    signal      reg_term_concatenation          : std_logic_vector(0 to ((NB_TERMS * TERM_WIDTH) - 1));
    signal      term_vector                     : t_term_vector(0 to (NB_TERMS - 1));

    constant    BINARY_ADDER_TREE_NB_TERMS      : positive  := (2 ** syn_functions_pkg.ceil_log2(NB_TERMS));
    constant    BINARY_ADDER_TREE_NB_ADDERS     : positive  := (BINARY_ADDER_TREE_NB_TERMS - 1);
    constant    BINARY_ADDER_TREE_NB_NODES      : positive  := (BINARY_ADDER_TREE_NB_ADDERS + BINARY_ADDER_TREE_NB_TERMS);
    signal      binary_adder_tree               : t_resized_term_vector(1 to BINARY_ADDER_TREE_NB_NODES);

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



    gen_binary_adder_tree : for NODE_INDEX in BINARY_ADDER_TREE_NB_NODES downto 1 generate
    begin
    
        gen_leave : if (NODE_INDEX > BINARY_ADDER_TREE_NB_ADDERS) generate
        begin
    
            gen_useless_leave : if (NODE_INDEX > (BINARY_ADDER_TREE_NB_ADDERS + NB_TERMS)) generate
            begin
                binary_adder_tree(NODE_INDEX)   <=          std_logic_vector(to_signed(0, SUM_WIDTH));
            end generate gen_useless_leave;
    
            gen_usefull_leave : if (NODE_INDEX <= (BINARY_ADDER_TREE_NB_ADDERS + NB_TERMS)) generate
            begin
                binary_adder_tree(NODE_INDEX)   <=          std_logic_vector(resize(signed(term_vector(NODE_INDEX - BINARY_ADDER_TREE_NB_ADDERS - 1)), SUM_WIDTH));
            end generate gen_usefull_leave;
    
        end generate gen_leave;
    
        gen_adder : if (NODE_INDEX <= BINARY_ADDER_TREE_NB_ADDERS) generate
        begin
            binary_adder_tree(NODE_INDEX)   <=          std_logic_vector(signed(binary_adder_tree(2 * NODE_INDEX)) + signed(binary_adder_tree((2 * NODE_INDEX) + 1)));
        end generate gen_adder;
    
    end generate gen_binary_adder_tree;
    
    sum <=          binary_adder_tree(1);



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



