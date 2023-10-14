function [ElectricalID_output] = ResetDutyCycle(ElectricalID_struct)
ElectricalID_output = ElectricalID_struct;
ElectricalID_output.PWM_Switch_0 = single(0);
ElectricalID_output.PWM_Switch_2 = single(0);
ElectricalID_output.PWM_Switch_4 = single(0);
ElectricalID_output.PWM_Switch_a2 = single(0);
ElectricalID_output.PWM_Switch_b2 = single(0);
ElectricalID_output.PWM_Switch_c2 = single(0);
end

