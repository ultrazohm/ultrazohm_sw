-- -------------------------------------------------------------
-- Created: 2019-07-29 14:30:00
-- 
-- Author S. Wendel
-- 
-- 
-- -------------------------------------------------------------
-- Description
-- -------------------------------------------------------------
-- SPI-Master Module 
-- Create Signals for the SPI protocol and Shiftregisters
-- 
-- -------------------------------------------------------------
-- Version 1.0
-- -------------------------------------------------------------
----- found another one in the internet---
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity spi_master is
    generic(INPUT_CLK_FREQUENCY : integer := 200000000; -- Hz 
            SPI_CLK_FREQUENCY   : integer := 100000000; -- hz / value will be used to calculate the Reload-Value of the Clock divider
            PRE_DELAY           : integer := 1; -- 1 := 10 ns / DELAY BETWEEN CS TO ACTIVE AND DATA TRANSMISSION
            POST_DELAY          : integer := 0; -- 1 := 20 ns / DELAY BETWEEN END OF DATA TRANSMISSION AND CS TO DISABLE 
            CONV_DELAY          : integer := 0; -- us / DELAY BETWEEN CS TO DISABLE AND CS TO ENABLE
            TRIGGER_ADC         : boolean := false;
            ADC_BITS            : integer := 16 -- WORDLENGTH
    );
    port(TX_DATA : in  STD_LOGIC_VECTOR(ADC_BITS - 1 downto 0); -- SENDWORD
         RX_DATA : out STD_LOGIC_VECTOR(ADC_BITS - 1 downto 0); -- RECEIVEDWORD
         CPHA    : in  STD_LOGIC;       -- Clock Phase
         CPOL    : in  STD_LOGIC;       -- Clock Polarity
         MOSI    : out STD_LOGIC;
		 ADC_END_CNV  : out STD_LOGIC;  --'1' => ADC ist gesampelt und muss nur noch ausgelsen werden -> Steigende High-Flanke kann schalten ausloesen fuer FCS! Uebergang von "0" auf "1" gibt Freigabe fuer FCS!
         ADC_DATA_Valid : out STD_LOGIC;  --'1' => Daten im "ADC_DATA_Reg" sind gueltig, '0' => ungueltig!!!
         MISO    : in  STD_LOGIC;
         SCLK    : out STD_LOGIC;
         SS_N    : out STD_LOGIC;
         BUSY    : out STD_LOGIC;
         ENABLE  : in  STD_LOGIC;
         RESET   : in  STD_LOGIC;
         TRIGGER_TRANSMISSION : in STD_LOGIC;
         --TX_Done  : out STD_LOGIC;
         CLOCK   : in  STD_LOGIC
    );
end spi_master;

architecture Behavioral of spi_master is
    signal delay         : integer range 0 to (INPUT_CLK_FREQUENCY / (2*SPI_CLK_FREQUENCY));
    signal delay_pre     : integer range 0 to (PRE_DELAY * (INPUT_CLK_FREQUENCY / 100000000));
    signal delay_post    : integer range 0 to (POST_DELAY * (INPUT_CLK_FREQUENCY / 100000000));
    signal delay_cnv     : integer range 0 to (CONV_DELAY * (INPUT_CLK_FREQUENCY / 100000000)); 
    constant clock_delay : integer := (INPUT_CLK_FREQUENCY / (2 * SPI_CLK_FREQUENCY)) - 1;

    
	-- FSM SPI-States
    type spitx_states is (spi_stx, del_pre, spi_txactive, del_post, spi_etx);
    signal spitxstate : spitx_states := spi_stx;

	-- FSM SPI-CLK
    type spi_clkstates is (shift, sample);
    signal spiclkstate : spi_clkstates;

    signal mosi_helper, mosi_helper_helper, mosi_helper_helper_helper : std_logic                               := '0';
    signal bitcounter                                                 : integer range 0 to ADC_BITS + 1; -- wenn bitcounter = Laenge --> alle Bits uebertragen
    signal tx_reg                                                     : std_logic_vector(ADC_BITS - 1 downto 0) := (others => '0');
    signal rx_reg                                                     : std_logic_vector(ADC_BITS - 1 downto 0) := (others => '0');
    signal sl_tx_reg_shift2                                           : std_logic                               := '0';
    signal sl_tx_reg_shift                                            : std_logic                               := '0';
    signal int_count_toggle                                           : integer range 0 to 5                    := 0;
  --  signal transmission_complete                                      : std_logic                               := '0'; -- eventuell wieder entfernen
begin
    


    ------ Verwaltung --------
    process
    begin
        wait until rising_edge(clock);       
        
        mosi       <= tx_reg(tx_reg'left);
        delay_post <= (POST_DELAY * (INPUT_CLK_FREQUENCY / 100000000));  -- POST-Delay  
        delay_pre  <= (PRE_DELAY * (INPUT_CLK_FREQUENCY / 100000000)); -- Initial-Delay  
        delay_cnv  <= (CONV_DELAY * (INPUT_CLK_FREQUENCY / 100000000));
        
        if (delay > 0) then
            delay <= delay - 1;
        else
            delay <= clock_delay;
        end if;
        if (reset = '1') then
            spitxstate <= spi_stx;
			ADC_END_CNV <= '0';
        else
            case spitxstate is
                when spi_stx =>
                    ss_n       <= '1';  -- slave select disabled
                    busy       <= '0';
                    bitcounter <= ADC_BITS;
                    sclk       <= CPOL;
                    if (enable = '1' and (TRIGGER_ADC = false or (TRIGGER_ADC = true and TRIGGER_TRANSMISSION = '1'))) then
                        spitxstate <= del_pre;
                    end if;

                when del_pre =>         -- SS aktivieren und Zeit abwarten 
                    ss_n <= '0';
                    sclk <= CPOL;
                    busy <= '1';
                    if (CPHA = '0') then
                        spiclkstate <= sample; -- sample at odd SCLK-edge  (1st, 3rd, 5th...)
                    else
                        spiclkstate <= shift; -- sample at even SCLK-edge (2nd, 4th, 6th...)
                    end if;
                    delay <= 0;
                    if (delay_pre > 0) then
                        delay_pre <= delay_pre - 1;
                    else
                        spitxstate <= spi_txactive;
                    end if;

                when spi_txactive =>
                    busy <= '1';        -- Daten aus tx_reg uebertragen
					ADC_END_CNV <= '1';
                    ---------------------------------------- SPI-Takt generieren -----------------------------
                    case spiclkstate is
                        when sample =>
                            sclk <= (CPOL xor CPHA);
                            if (delay = 0) then -- sample                     
                                spiclkstate <= shift;
                                if (CPHA = '1') then
                                    bitcounter <= bitcounter - 1;
                                end if;
                            end if;

                        when shift =>
                            sclk <= not (CPOL xor CPHA);
                            if (delay = 0) then -- shift
                                spiclkstate <= sample;
                                if (CPHA = '0') then
                                    bitcounter <= bitcounter - 1;
                                end if;
                            end if;
                    end case;
                    --if (delay = 0 and bitcounter = 0 and transmission_complete = '1') then -- alle Bits uebertragen -> deselektieren
                    if (delay = 0 and bitcounter = 0) then -- alle Bits uebertragen -> deselektieren
                        sclk       <= CPOL;
                        spitxstate <= del_post;
                    end if;
                ---------------------------------------- SPI-Takt fertig  -----------------------------
                when del_post =>

                    if (delay_post > 0) then
                        delay_post <= delay_post - 1;
                    else
                        ss_n <= '1';        -- disable Slave Select 
                        ADC_DATA_Valid <= '1';
                        spitxstate <= spi_etx;

                    end if;

                --		when spi_toggle1 =>
                --			SCLK <= '0' ;
                --			if (int_count_toggle=5) then
                --				spitxstate <= spi_etx ;
                --			end if;

                when spi_etx =>
                    --TX_Done <= '1';
                    --SCLK <= '1' ;
					ADC_END_CNV <= '0';
                    ADC_DATA_Valid <= '0';
                    busy <= '0';
                    if (delay_cnv > 0) then
                        delay_cnv <= delay_cnv - 1;
                    else
                   -- if (enable = '0') then -- Handshake: warten, bis Start-Flag geloescht
                        spitxstate <= spi_stx;
                    end if;
            end case;
        end if;
    end process;

    ---- Schieberegister in eigenem Prozess ist ressourcensparend -------
    process
    begin
        wait until rising_edge(clock);
        --     if (spitxstate=del_pre) then  -- Initialisierung weglassen spart Ressourcen: 1 Mux = 10 Slices
        --        rx_reg <= (others=>'0');
        --     end if;
     --   if (spitxstate = spi_txactive and spiclkstate = sample and delay = 0 and bitcounter /= 0) then
      if (spitxstate = spi_txactive and spiclkstate = sample and delay = 0 and bitcounter >= 0) then
            rx_reg <= rx_reg(rx_reg'left - 1 downto 0) & MISO;
--            if(bitcounter = 0) then
--                transmission_complete <= '1';
--            else
--                transmission_complete <= '0';

--              end if;
        end if;

        if (spitxstate = spi_stx) then
            --tx_reg(Laenge) <= '0' ;
            tx_reg <= TX_Data;
        end if;
        if (spitxstate = spi_txactive and spiclkstate = shift and delay = 0 and (cpha = '0' or bitcounter /= ADC_BITS)) then
            tx_reg <= tx_reg(tx_reg'left - 1 downto 0) & tx_reg(0);
        --sl_tx_reg_shift <= '1';
        else
            sl_tx_reg_shift <= '0';
        end if;
    end process;
    
    
    RX_Data <= rx_reg;


end Behavioral;
