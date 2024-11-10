number_of_points=10;

id=linspace(-4.2,0,number_of_points);
iq=linspace(-1,1,number_of_points);

all_combinations=combinations(id,iq);
writematrix(all_combinations.id','id_setpoints_paraid.csv');
writematrix(all_combinations.iq','iq_setpoints_paraid.csv');