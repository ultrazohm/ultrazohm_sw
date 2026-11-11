classdef Soll_Regelungsart_en < Simulink.IntEnumType
    enumeration
        Ctrl_Warten(0)
        Ctrl_Drehzahl(1)
        Ctrl_Strom(2)
        Ctrl_Position(3)
        Ctrl_Manuell(4)
        Ctrl_Error(99)
    end
end