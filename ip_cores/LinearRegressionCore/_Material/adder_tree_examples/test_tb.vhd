
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;



entity test_tb is
end entity test_tb;



architecture rtl of test_tb is

    signal      clock                       : std_logic := '0';
    signal      clock_enable                : std_logic;
    signal      input_term_concatenation    : std_logic_vector(0 to 95);
    signal      output_sum                  : std_logic_vector(11 downto 0);



begin

    clock                       <=          not(clock) after 1 ns;

    clock_enable                <=          '1';

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
                                            );

    UUT : entity work.test
    generic map
    (
        -- Core capacity
        NB_TERMS                    => 12,

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



end architecture rtl;



