gains=readtable('gains.csv');
gains.d1_a_gain=gains.d1_a_amps./gains.d1_a_volt;
gains.d1_b_gain=gains.d1_a_amps./gains.d1_b_volt;
gains.d1_c_gain=gains.d1_c_amps./gains.d1_c_volt;
gains.d2_a_gain=gains.d2_a_amps./gains.d2_a_volt;
gains.d2_b_gain=gains.d2_a_amps./gains.d2_b_volt;
gains.d2_c_gain=gains.d2_c_amps./gains.d2_c_volt;

d1=table();
d1.a_gain=mean(gains.d1_a_gain);
d1.b_gain=mean(gains.d1_b_gain);
d1.c_gain=mean(gains.d1_c_gain);

d2=table();
d2.a_gain=mean(gains.d2_a_gain);
d2.b_gain=mean(gains.d2_b_gain);
d2.c_gain=mean(gains.d2_c_gain);