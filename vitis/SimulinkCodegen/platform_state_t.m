classdef platform_state_t < Simulink.IntEnumType
    enumeration
        idle_state(0)
        running_state(1)
        control_state(2)
        error_state(3)
    end
end