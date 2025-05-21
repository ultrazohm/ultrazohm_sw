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
ssi_clk_divider = 25; 

% bit width of the connected ssi encoder
% max. 25 bit per single-/multi-turn position information
% sum of single-turn, multi-turn, and status <= 64 bit

% ssi_encoder_bit_width_single_turn = uint32(14);
% ssi_encoder_bit_width_multi_turn = uint32(5);
% ssi_encoder_number_of_status_bits = uint32(2);
ssi_encoder_bit_width_single_turn = uint32(19);
ssi_encoder_bit_width_multi_turn = uint32(0);
ssi_encoder_number_of_status_bits = uint32(0);
bit_sum = ssi_encoder_bit_width_multi_turn+ssi_encoder_bit_width_single_turn+ssi_encoder_number_of_status_bits;

% encoding: false=binary, true=gray
binary_or_gray = false; 

% acc. to datasheet of manufacturer RLS encoders for ssi clock rates higher
% than 500 kHz, the first clk pulse after clock goes low in the beginning
% has to be delayed for 1.5µs in order to provide the position data for clock
% rates up to 2.5 MHz.
delay_first_clk_on_off = true;


%% PLL

PLL.fn  =  50;                  % Hz closed-loop nominal frequency of PLL
PLL.d   =  1;                   % closed-loop damping factor of PLL
PLL.ki  = (2*pi*PLL.fn)^2;      % 1/s^2 integral gain of PLL controller
PLL.kp  = 2*PLL.d*2*pi*PLL.fn;  % 1/s proportional gain of PLL controller

