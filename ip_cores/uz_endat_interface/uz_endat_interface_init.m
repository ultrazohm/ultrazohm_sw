clear
clc

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2020.1\bin\vivado.bat');

f_clock = 100e6;        % IP core clock freq in Hz
t_clock = 1/f_clock;    % IP core sample time in s

f_ADC =20e3;            % ADC interrupt freq in Hz
t_ADC = 1/f_ADC;        % ADC sample time in s

f_plant = 1e6;          % Plant simulation freq in Hz
t_plant = 1/f_plant;    % Plant sample time in s

% divider for the 100 MHz supply clock
% e.g. 100 MHz / (2*25) = 2 MHz
endat_clk_divider = 10; % 10 = 5 MHz 


% bit width of the connected endat encoder
% sum of single-turn, multi-turn, and status <= 64 bit
endat_encoder_bit_width_single_turn = uint32(25);
endat_encoder_bit_width_multi_turn = uint32(12);
endat_encoder_number_of_CRC_bits = uint32(0);
bit_sum = endat_encoder_bit_width_multi_turn+endat_encoder_bit_width_single_turn+endat_encoder_number_of_CRC_bits;

% encoding: false=binary, true=gray
binary_or_gray = false; 

% acc. to datasheet of Heidenhain for EnDat clock rates 2...8 MHz, 
% the first clk pulse after clock goes low in the beginning
% has to be delayed for 2.0µs in order to provide the position data.
% Delay time for 16 MHz is 1.0µs and linearily changing from 8 MHz on to the 16 MHz value 
delay_first_clk_on_off = true;

%% PLL

PLL.fn  =  50;                  % Hz closed-loop nominal frequency of PLL
PLL.d   =  1;                   % closed-loop damping factor of PLL
PLL.ki  = (2*pi*PLL.fn)^2;      % 1/s^2 integral gain of PLL controller
PLL.kp  = 2*PLL.d*2*pi*PLL.fn;  % 1/s proportional gain of PLL controller

