%% Init Parameters and Variables for uz_ninephase_VSD_transformation IP-core model

ts_uz_ninephase_VSD_transformation = 1/100e6;

gamma = pi/9;
tl1 = [1  cos(6*gamma) cos(12*gamma)   cos(gamma)  cos(7*gamma) cos(13*gamma)  cos(2*gamma) cos(8*gamma) cos(14*gamma)];
tl2 = [0  sin(6*gamma) sin(12*gamma)   sin(gamma)  sin(7*gamma) sin(13*gamma)  sin(2*gamma) sin(8*gamma) sin(14*gamma)];
tl3 = [1             1             1 cos(3*gamma)  cos(3*gamma)  cos(3*gamma)  cos(6*gamma) cos(6*gamma)  cos(6*gamma)];
tl4 = [0             0             0 sin(3*gamma)  sin(3*gamma)  sin(3*gamma)  sin(6*gamma) sin(6*gamma)   sin(6*gamma)];
tl5 = [1 cos(12*gamma)  cos(6*gamma) cos(5*gamma) cos(17*gamma) cos(11*gamma) cos(10*gamma) cos(4*gamma) cos(16*gamma)];
tl6 = [0 sin(12*gamma)  sin(6*gamma) sin(5*gamma) sin(17*gamma) sin(11*gamma) sin(10*gamma) sin(4*gamma) sin(16*gamma)];
tl7 = [1  cos(6*gamma) cos(12*gamma) cos(7*gamma) cos(13*gamma)    cos(gamma) cos(14*gamma) cos(2*gamma)  cos(8*gamma)];
tl8 = [0  sin(6*gamma) sin(12*gamma) sin(7*gamma) sin(13*gamma)    sin(gamma) sin(14*gamma) sin(2*gamma)  sin(8*gamma)];
tl9 = [1/2 1/2 1/2 -1/2 -1/2 -1/2 1/2 1/2 1/2];
c = 2/9*cat(1,tl1,tl2,tl3,tl4,tl5,tl6,tl7,tl8,tl9);