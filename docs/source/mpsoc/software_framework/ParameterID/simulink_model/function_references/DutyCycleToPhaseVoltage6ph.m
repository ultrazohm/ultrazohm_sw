function ActualVabc = DutyCycleToPhaseVoltage6ph(GlobalConfig,ElectricalID_output)
    ActualVabc.a1 = GlobalConfig.VDC * ElectricalID_output.PWM_Switch_a1;
    ActualVabc.b1 = GlobalConfig.VDC * ElectricalID_output.PWM_Switch_b1;
    ActualVabc.c1 = GlobalConfig.VDC * ElectricalID_output.PWM_Switch_c1;
    ActualVabc.a2 = GlobalConfig.VDC * ElectricalID_output.PWM_Switch_a2;
    ActualVabc.b2 = GlobalConfig.VDC * ElectricalID_output.PWM_Switch_b2;
    ActualVabc.c2 = GlobalConfig.VDC * ElectricalID_output.PWM_Switch_c2;
end

