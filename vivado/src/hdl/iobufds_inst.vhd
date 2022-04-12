library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library UNISIM;
use UNISIM.vcomponents.all;

entity iobufds_inst is
  generic (
    -- Users to add parameters here
    --DATA_WIDTH          : natural := 16;    -- Number of bits per SPI frame
    CHANNELS_PER_MASTER : natural := 8; -- Number of slaves that are controlled with the same SS_N and SCLK
    SPI_MASTER : natural := 1 -- Number of independent SPI Masters
  );
  port (
    MISO_IN : in std_logic_vector(2 * CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0);
    INVERT_OUTPUT : in std_logic_vector(CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0);
    MISO_OUT : out std_logic_vector(CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0);
    SCLK_IN : in std_logic_vector(SPI_MASTER - 1 downto 0);
    SCLK_OUT : out std_logic_vector(2 * SPI_MASTER - 1 downto 0)
  );
end iobufds_inst;

architecture rtl of iobufds_inst is
  signal S_MISO : std_logic_vector(CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0);
begin

  -- Generate differential output buffers
  gen_diff1 : for i in 0 to SPI_MASTER - 1 generate
    OBUFDS_inst : OBUFDS
    port map(
      O => SCLK_OUT(2 * i), -- 1-bit output: Diff_p output (connect directly to top-level port)   
      OB => SCLK_OUT(2 * i + 1), -- 1-bit output: Diff_n output (connect directly to top-level port)   
      I => SCLK_IN(i) -- 1-bit input: Buffer input
    );
    
    gen_diff2 : for j in 0 to CHANNELS_PER_MASTER - 1 generate
      IBUFDS_inst : IBUFDS
      generic map(DIFF_TERM => TRUE)
      port map(
        O => S_MISO(i * CHANNELS_PER_MASTER + j), -- 1-bit output: Buffer output   
        I => MISO_IN(2 * i * CHANNELS_PER_MASTER + 2 * j), -- 1-bit input: Diff_p buffer input (connect directly to top-level port)   
        IB => MISO_IN(2 * i * CHANNELS_PER_MASTER + 2 * j + 1) -- 1-bit input: Diff_n buffer input (connect directly to top-level port)
      );

    end generate gen_diff2;
  end generate gen_diff1;

  gen_miso_out : for i in CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0 generate
    MISO_OUT(i) <= not S_MISO(i) when INVERT_OUTPUT(i) = '1' else S_MISO(i);
  end generate;

end architecture;