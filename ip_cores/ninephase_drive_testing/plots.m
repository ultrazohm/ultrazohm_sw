f1=figure();
%
% tabledata = double(table2array(readtable('C:\Users\valen\Desktop\Log_2022-05-13_16-23-26.csv')));
%sampletime=1/20000;
range = 1:size(tabledata);
rpmstep = 91003;%min(find(tabledata(range,20))==50);
range = (rpmstep-.5/sampletime):(rpmstep+.5/sampletime);
uz_time = tabledata(range,1);
uz_time=uz_time-min(uz_time);
uz_a1 = tabledata(range,2);
uz_b1 = tabledata(range,3);
uz_c1 = tabledata(range,4);
uz_a2 = tabledata(range,5);
uz_b2 = tabledata(range,6);
uz_c2 = tabledata(range,7);
uz_a3 = tabledata(range,8);
uz_b3 = tabledata(range,9);
uz_c3 = tabledata(range,10);
uz_id = tabledata(range,11);
uz_iq = tabledata(range,12);
uz_ix1 = tabledata(range,13);
uz_iy1 = tabledata(range,14);
uz_ix2 = tabledata(range,15);
uz_iy2 = tabledata(range,16);
uz_iz1 = tabledata(range,17);
uz_iz2 = tabledata(range,18);
uz_iz3 = tabledata(range,19);
uz_omega = tabledata(range,20);

%Ströme
hold off;

subplot(4,2,1);
hold on;
grid on;
plot(uz_time,uz_a1);
plot(uz_time,uz_omega);
hold off;

subplot(4,2,3);
hold on;
grid on;
plot(uz_time,uz_a1);
plot(uz_time,uz_b1);
plot(uz_time,uz_c1);
hold off;

subplot(4,2,5);
hold on;
grid on;
plot(uz_time,uz_a2);
plot(uz_time,uz_b2);
plot(uz_time,uz_c2);
hold off;

subplot(4,2,7);
hold on;
grid on;
plot(uz_time,uz_a3);
plot(uz_time,uz_b3);
plot(uz_time,uz_c3);
hold off;

subplot(4,2,2);
hold on;
grid on;
plot(out.abc1.time,out.abc1.data(:,1));
plot(out.omega.time,out.omega.data);
hold off;

subplot(4,2,4);
hold on;
grid on;
plot(out.abc1.time,out.abc1.data);
hold off;

subplot(4,2,6);
hold on;
grid on;
plot(out.abc2.time,out.abc2.data);
hold off;

subplot(4,2,8);
hold on;
grid on;
plot(out.abc3.time,out.abc3.data);
hold off;

%Subsysteme
f2=figure();
hold off;

subplot(4,2,1);
hold on;
grid on;
plot(uz_time,uz_id);
plot(uz_time,uz_iq);
plot(uz_time,uz_omega);
hold off;

subplot(4,2,3);
hold on;
grid on;
plot(uz_time,uz_ix1);
plot(uz_time,uz_iy1);
hold off;

subplot(4,2,5);
hold on;
grid on;
plot(uz_time,uz_ix2);
plot(uz_time,uz_iy2);
hold off;

subplot(4,2,7);
hold on;
grid on;
plot(uz_time,uz_iz1);
plot(uz_time,uz_iz2);
plot(uz_time,uz_iz3);
hold off;

subplot(4,2,2);
hold on;
grid on;
plot(out.subspaces.time,out.subspaces.data(:,1));
plot(out.subspaces.time,out.subspaces.data(:,2));
plot(out.omega.time,out.omega.data);
hold off;

subplot(4,2,4);
hold on;
grid on;
plot(out.subspaces.time,out.subspaces.data(:,3));
plot(out.subspaces.time,out.subspaces.data(:,4));
hold off;

subplot(4,2,6);
hold on;
grid on;
plot(out.subspaces.time,out.subspaces.data(:,5));
plot(out.subspaces.time,out.subspaces.data(:,6));
hold off;

subplot(4,2,8);
hold on;
grid on;
plot(out.subspaces.time,out.subspaces.data(:,7));
plot(out.subspaces.time,out.subspaces.data(:,8));
plot(out.subspaces.time,out.subspaces.data(:,9));
hold off;
