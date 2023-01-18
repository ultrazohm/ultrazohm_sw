function [out] = VSD6ph(VSD,abc_struct)
    abc_vector = cat(1,abc_struct.a1,abc_struct.b1,abc_struct.c1,abc_struct.a2,abc_struct.b2,abc_struct.c2);
    alphabeta_vector = VSD*abc_vector;
    out.alpha = alphabeta_vector(1);
    out.beta = alphabeta_vector(2);
    out.x = alphabeta_vector(3);
    out.y = alphabeta_vector(4);
    out.z1 = alphabeta_vector(5);
    out.z2 = alphabeta_vector(6);
end

