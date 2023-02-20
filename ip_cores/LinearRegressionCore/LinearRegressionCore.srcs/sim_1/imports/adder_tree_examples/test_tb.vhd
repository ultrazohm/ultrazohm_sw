
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library syn_functions;
use syn_functions.syn_functions_pkg;

entity ExplicitBinaryTreeAdder_Generic_tb is
end entity ExplicitBinaryTreeAdder_Generic_tb;


architecture Behavioral of ExplicitBinaryTreeAdder_Generic_tb is

    signal      clock                       : std_logic := '0';
    signal      clock_enable                : std_logic;
    signal      input_term_concatenation    : std_logic_vector(399 downto 0);
    signal      output_sum                  : std_logic_vector(13 downto 0);

component ExplicitBinaryTreeAdder_Generic is
    generic
    (
        -- Core capacity
        NB_TERMS                    : positive  := 50;

        -- Signal widths
        TERM_WIDTH                  : positive  := 8
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
end component ExplicitBinaryTreeAdder_Generic;


begin

    clock                       <=          not(clock) after 1 ns;
    clock_enable                <=          '1';

    DUT : ExplicitBinaryTreeAdder_Generic
    generic map
    (
        -- Core capacity
        NB_TERMS                    => 50,

        -- Signal widths
        TERM_WIDTH                  => 8
    )
    port map
    (
        -- Clock domain
        clock_i                     => clock,
        clock_enable_i              => clock_enable,

        -- Input interface
        input_term_concatenation_i  => input_term_concatenation,

        -- Output_interface
        output_sum_o                => output_sum
    );

-- Stimuli
    input_term_concatenation    <=          std_logic_vector(
                                                    to_signed( 0, 8)
                                                &   to_signed( 1, 8)
                                                &   to_signed( 2, 8)
                                                &   to_signed( 3, 8)
                                                &   to_signed( 4, 8)
                                                &   to_signed( 5, 8)
                                                &   to_signed( 6, 8)
                                                &   to_signed( 7, 8)
                                                &   to_signed( 8, 8)
                                                &   to_signed( 9, 8)
                                                &   to_signed(10, 8)
                                                &   to_signed(11, 8)
                                                &   to_signed( 0, 8)
                                                &   to_signed( 1, 8)
                                                &   to_signed( 2, 8)
                                                &   to_signed( 3, 8)
                                                &   to_signed( 4, 8)
                                                &   to_signed( 5, 8)
                                                &   to_signed( 6, 8)
                                                &   to_signed( 7, 8)
                                                &   to_signed( 8, 8)
                                                &   to_signed( 9, 8)
                                                &   to_signed(10, 8)
                                                &   to_signed(11, 8)
                                                &   to_signed( 0, 8)
                                                &   to_signed( 1, 8)
                                                &   to_signed( 2, 8)
                                                &   to_signed( 3, 8)
                                                &   to_signed( 4, 8)
                                                &   to_signed( 5, 8)
                                                &   to_signed( 6, 8)
                                                &   to_signed( 7, 8)
                                                &   to_signed( 8, 8)
                                                &   to_signed( 9, 8)
                                                &   to_signed(10, 8)
                                                &   to_signed(11, 8)
                                                &   to_signed( 0, 8)
                                                &   to_signed( 1, 8)
                                                &   to_signed( 2, 8)
                                                &   to_signed( 3, 8)
                                                &   to_signed( 4, 8)
                                                &   to_signed( 5, 8)
                                                &   to_signed( 6, 8)
                                                &   to_signed( 7, 8)
                                                &   to_signed( 8, 8)
                                                &   to_signed( 9, 8)
                                                &   to_signed(10, 8)
                                                &   to_signed(11, 8)
                                                &   to_signed( 0, 8)
                                                &   to_signed( 1, 8)
                                            );

end architecture Behavioral;



