function [ElectricalID_output] = SetpVectorToDutyCycle6ph(ElectricalID_output_in,VDC,SetpVector)
    %Copy ElectricalID_output
    ElectricalID_output = ElectricalID_output_in;
    %Write DutyCycle to ElectricalID_output
    ElectricalID_output.PWM_Switch_a1 = GenerateDutyCycle(VDC,SetpVector(1));
    ElectricalID_output.PWM_Switch_b1 = GenerateDutyCycle(VDC,SetpVector(2));
    ElectricalID_output.PWM_Switch_c1 = GenerateDutyCycle(VDC,SetpVector(3));
    ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4));
    ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5));
    ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6));
end

