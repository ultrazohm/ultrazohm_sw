classdef Soll_Regelungsart_en < Simulink.IntEnumType
    enumeration
        Drehzahl(0)
        Strom(1)
        Position(2)
        Error(99)
    end
end