classdef Soll_Regelungsart_en < Simulink.IntEnumType
    enumeration
        Error(99)
        Drehzahl(0)
        Trajektorie(1)
        Strom(2)
    end
end