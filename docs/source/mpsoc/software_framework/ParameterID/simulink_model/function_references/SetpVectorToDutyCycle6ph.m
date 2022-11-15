function [ElectricalID_output] = SetpVectorToDutyCycle6ph(ElectricalID_output_in,GlobalConfig,SetpVector)
    %Copy ElectricalID_output
    ElectricalID_output = ElectricalID_output_in;
    %Write DutyCycle to ElectricalID_output
    ElectricalID_output.PWM_Switch_a1 = GenerateDutyCycle(GlobalConfig,SetpVector(1));
    ElectricalID_output.PWM_Switch_b1 = GenerateDutyCycle(GlobalConfig,SetpVector(2));
    ElectricalID_output.PWM_Switch_c1 = GenerateDutyCycle(GlobalConfig,SetpVector(3));
    ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(GlobalConfig,SetpVector(4));
    ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(GlobalConfig,SetpVector(5));
    ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(GlobalConfig,SetpVector(6));
end

