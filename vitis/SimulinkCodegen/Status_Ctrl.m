classdef Status_Ctrl < Simulink.IntEnumType
    enumeration
        Error_Status(99)
        Ready(0)
        Run(1)
        En(2)
        Dis(3)
    end
end