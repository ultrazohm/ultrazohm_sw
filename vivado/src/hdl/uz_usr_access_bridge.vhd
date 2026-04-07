-- uz_usr_access_bridge.vhd
-- Simple wrapper around the USR_ACCESS primitive.
-- Exposes the 32-bit USR_ACCESS DATA bus as an output signal
-- that you can feed into AXI GPIO or a custom AXI-Lite slave.

library ieee;
use ieee.std_logic_1164.all;

-- Xilinx device primitive library
library unisim;
use unisim.vcomponents.all;

entity uz_usr_access_bridge is
  port (
    usr_access_out : out std_logic_vector(31 downto 0)
  );
end entity uz_usr_access_bridge;

architecture rtl of uz_usr_access_bridge is

  signal bit_id    : std_logic_vector(31 downto 0);
  signal cfgclk    : std_logic;
  signal datavalid : std_logic;

begin

  -- For UltraScale / UltraScale+ devices, the primitive is USR_ACCESSE2  
  USR_ACCESS_inst : USR_ACCESSE2
    port map (
      CFGCLK    => cfgclk,     -- optional; not used here
      DATA      => bit_id,     -- 32-bit word from BITSTREAM.CONFIG.USR_ACCESS
      DATAVALID => datavalid   -- goes high when DATA is valid (after config)
    );

  -- DATA is stable after configuration, just forward it
  usr_access_out <= bit_id;

end architecture rtl;
