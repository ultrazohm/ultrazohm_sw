function ActualVabc = DutyCycleToPhaseVoltage6ph(V_DC,ElectricalID_output)
    ActualVabc.a1 = V_DC * ElectricalID_output.PWM_Switch_a1;
    ActualVabc.b1 = V_DC * ElectricalID_output.PWM_Switch_b1;
    ActualVabc.c1 = V_DC * ElectricalID_output.PWM_Switch_c1;
    ActualVabc.a2 = V_DC * ElectricalID_output.PWM_Switch_a2;
    ActualVabc.b2 = V_DC * ElectricalID_output.PWM_Switch_b2;
    ActualVabc.c2 = V_DC * ElectricalID_output.PWM_Switch_c2;
end

