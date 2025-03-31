clear
clc

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2020.1\bin\vivado.bat');

f_clock = 100e6;        % IP core clock freq in Hz
t_clock = 1/f_clock;    % IP core sample time in s

f_ADC =50e3;            % ADC interrupt freq in Hz
t_ADC = 1/f_ADC;        % ADC sample time in s

f_plant = 1e6;          % Plant simulation freq in Hz
t_plant = 1/f_plant;    % Plant sample time in s

% divider for the 100 MHz supply clock
% e.g. 100 MHz / (2*25) = 2 MHz
ssi_clk_divider = 25; 

% bit width of the connected ssi encoder
ssi_encoder_bit_width = 17; 

% acc. to datasheet of manufacturer RLS encoders for ssi clock rates higher
% than 500 kHz, the first clk pulse after clock goes low in the beginning
% has to be delayed for 1µs in order to provide the position data for clock
% rates up to 2.5 MHz.
delay_first_clk_on_off = true;
