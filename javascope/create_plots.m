clc
clear
close all

%ans =
%  21×1 cell array
%    {'time'                 }
%    {'CH1=(29) start_marker'}
%   {'CH2=(30) Speed_rpm'   }
%    {'CH3=(11) ia1'         }
%    {'CH4=(12) ib1'         }
%    {'CH5=(13) ic1'         }
%    {'CH6=(14) ia2'         }
%    {'CH7=(15) ib2'         }
%    {'CH8=(16) ic2'         }
%    {'CH9=(25) ud'          }
%    {'CH10=(26) uq'         }
%    {'CH11=(27) uX'         }
%    {'CH12=(28) uY'         }
%    {'CH13=(17) id'         }
%    {'CH14=(18) iq'         }
%    {'CH15=(19) iX'         }
%    {'CH16=(20) iY'         }
%    {'CH17=(21) iq_ref'     }
%    {'CH18=(22) id_ref'     }
%    {'CH19=(23) iX_ref'     }
%    {'CH20=(24) iY_ref'     }

ddpg_cil=load('Log_2023-07-20_14-38-50.mat');
% foc_0rpm=load('foc_0rpm.mat');
% 
% 
% foc_cil=load('foc_cil.mat');
% foc_real=load('foc_not_zero.mat');
% ddpg_cil=load('setup_1_3_agent_3555_cil.mat');
% ddpg_real=load('setup_1_3_agent_3555_real.mat');

color_1='#0072BD';

%% CIL zerlegen

% find all index in which the turn-on signal is changed
changes = find(diff(ddpg_cil.log.start_marker))+1;
ddpg_cil_start_0_rpm=changes(1);
ddpg_cil_start_500_rpm=changes(3);
ddpg_cil_start_1000_rpm=changes(5);
% ddpg_cil_start_2000_rpm=changes(7);
% ddpg_cil_start_3000_rpm=changes(9);
ddpg_cil_end_0_rpm=changes(2);
ddpg_cil_end_500_rpm=changes(4);
ddpg_cil_end_1000_rpm=changes(6);
% ddpg_cil_end_2000_rpm=changes(8);
% ddpg_cil_end_3000_rpm=changes(10);

% plot everything
figure
subplot(3,1,1)
ddpg_time_cil=ddpg_cil.log.time-ddpg_cil.log.time(ddpg_cil_start_0_rpm);
%foc_time_cil=foc_cil.log.time-foc_cil.log.time(foc_cil_start_0_rpm);

plot(ddpg_time_cil,ddpg_cil.log.iq,'r' ,'LineWidth',2);
hold on
%plot(foc_time_cil,foc_cil.log.CH19,'Color',color_1,'LineWidth',2 );
grid minor
plot(ddpg_time_cil,ddpg_cil.log.id,'b' ,'LineWidth',2);
plot(ddpg_time_cil,ddpg_cil.log.id_ref,'k' ,'LineWidth',1);
plot(ddpg_time_cil,ddpg_cil.log.iq_ref,'k' ,'LineWidth',1);
%plot(foc_time_cil,foc_cil.log.CH6,'k' ,'LineWidth',2 );


% 
% %
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 0 rpm
figure
subplot(3,1,1)
ddpg_time_cil=ddpg_cil.log.time(ddpg_cil_start_0_rpm:ddpg_cil_end_0_rpm)-ddpg_cil.log.time(ddpg_cil_start_0_rpm);
%foc_time_cil=ddpg_cil.log.time(ddpg_cil_start_0_rpm:ddpg_cil_end_0_rpm)-ddpg_cil.log.time(ddpg_cil_start_0_rpm);

plot(ddpg_time_cil,ddpg_cil.log.iq(ddpg_cil_start_0_rpm:ddpg_cil_end_0_rpm),'r' ,'LineWidth',2);
hold on
grid minor
plot(ddpg_time_cil,ddpg_cil.log.id(ddpg_cil_start_0_rpm:ddpg_cil_end_0_rpm),'b' ,'LineWidth',2);
plot(ddpg_time_cil,ddpg_cil.log.iq_ref(ddpg_cil_start_0_rpm:ddpg_cil_end_0_rpm),'k' ,'LineWidth',1);
plot(ddpg_time_cil,ddpg_cil.log.id_ref(ddpg_cil_start_0_rpm:ddpg_cil_end_0_rpm),'k' ,'LineWidth',1);

% plot(foc_time_cil,foc_cil.log.CH19(foc_cil_start_0_rpm:foc_cil_end_0_rpm),'k--' ,'LineWidth',2 );

% plot(ddpg_time_cil,ddpg_cil.log.CH6(ddpg_cil_start_0_rpm:ddpg_cil_end_0_rpm),'r' ,'LineWidth',2);
% plot(foc_time_cil,foc_cil.log.CH6(foc_cil_start_0_rpm:foc_cil_end_0_rpm),'k' ,'LineWidth',2 );
% 
% subplot(3,1,2)
% plot(ddpg_time_cil,ddpg_cil.log.CH20(ddpg_cil_start_0_rpm:ddpg_cil_end_0_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_cil,foc_cil.log.CH20(foc_cil_start_0_rpm:foc_cil_end_0_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_cil,ddpg_cil.log.CH7(ddpg_cil_start_0_rpm:ddpg_cil_end_0_rpm),'r' ,'LineWidth',2);
% plot(foc_time_cil,foc_cil.log.CH7(foc_cil_start_0_rpm:foc_cil_end_0_rpm),'k' ,'LineWidth',2 );
% subplot(3,1,3)
% plot(ddpg_time_cil,ddpg_cil.log.CH2(ddpg_cil_start_0_rpm:ddpg_cil_end_0_rpm) );
% hold on
% plot(foc_time_cil,foc_cil.log.CH2(foc_cil_start_0_rpm:foc_cil_end_0_rpm) );
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 500 rpm
% figure
% subplot(3,1,1)
% ddpg_time_cil=ddpg_cil.log.time(ddpg_cil_start_500_rpm:ddpg_cil_end_500_rpm)-ddpg_cil.log.time(ddpg_cil_start_500_rpm);
% foc_time_cil=ddpg_cil.log.time(ddpg_cil_start_500_rpm:ddpg_cil_end_500_rpm)-ddpg_cil.log.time(ddpg_cil_start_500_rpm);
% 
% plot(ddpg_time_cil,ddpg_cil.log.CH19(ddpg_cil_start_500_rpm:ddpg_cil_end_500_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_cil,foc_cil.log.CH19(foc_cil_start_500_rpm:foc_cil_end_500_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_cil,ddpg_cil.log.CH6(ddpg_cil_start_500_rpm:ddpg_cil_end_500_rpm),'r' ,'LineWidth',2);
% plot(foc_time_cil,foc_cil.log.CH6(foc_cil_start_500_rpm:foc_cil_end_500_rpm),'k' ,'LineWidth',2 );
% 
% subplot(3,1,2)
% plot(ddpg_time_cil,ddpg_cil.log.CH20(ddpg_cil_start_500_rpm:ddpg_cil_end_500_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_cil,foc_cil.log.CH20(foc_cil_start_500_rpm:foc_cil_end_500_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_cil,ddpg_cil.log.CH7(ddpg_cil_start_500_rpm:ddpg_cil_end_500_rpm),'r' ,'LineWidth',2);
% plot(foc_time_cil,foc_cil.log.CH7(foc_cil_start_500_rpm:foc_cil_end_500_rpm),'k' ,'LineWidth',2 );
% subplot(3,1,3)
% plot(ddpg_time_cil,ddpg_cil.log.CH2(ddpg_cil_start_500_rpm:ddpg_cil_end_500_rpm) );
% hold on
% plot(foc_time_cil,foc_cil.log.CH2(foc_cil_start_500_rpm:foc_cil_end_500_rpm) );
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 1000 rpm
% figure
% subplot(3,1,1)
% ddpg_time_cil=ddpg_cil.log.time(ddpg_cil_start_1000_rpm:ddpg_cil_end_1000_rpm)-ddpg_cil.log.time(ddpg_cil_start_1000_rpm);
% foc_time_cil=ddpg_cil.log.time(ddpg_cil_start_1000_rpm:ddpg_cil_end_1000_rpm)-ddpg_cil.log.time(ddpg_cil_start_1000_rpm);
% 
% plot(ddpg_time_cil,ddpg_cil.log.CH19(ddpg_cil_start_1000_rpm:ddpg_cil_end_1000_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_cil,foc_cil.log.CH19(foc_cil_start_1000_rpm:foc_cil_end_1000_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_cil,ddpg_cil.log.CH6(ddpg_cil_start_1000_rpm:ddpg_cil_end_1000_rpm),'r' ,'LineWidth',2);
% plot(foc_time_cil,foc_cil.log.CH6(foc_cil_start_1000_rpm:foc_cil_end_1000_rpm),'k' ,'LineWidth',2 );
% 
% subplot(3,1,2)
% plot(ddpg_time_cil,ddpg_cil.log.CH20(ddpg_cil_start_1000_rpm:ddpg_cil_end_1000_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_cil,foc_cil.log.CH20(foc_cil_start_1000_rpm:foc_cil_end_1000_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_cil,ddpg_cil.log.CH7(ddpg_cil_start_1000_rpm:ddpg_cil_end_1000_rpm),'r' ,'LineWidth',2);
% plot(foc_time_cil,foc_cil.log.CH7(foc_cil_start_1000_rpm:foc_cil_end_1000_rpm),'k' ,'LineWidth',2 );
% subplot(3,1,3)
% plot(ddpg_time_cil,ddpg_cil.log.CH2(ddpg_cil_start_1000_rpm:ddpg_cil_end_1000_rpm) );
% hold on
% plot(foc_time_cil,foc_cil.log.CH2(foc_cil_start_1000_rpm:foc_cil_end_1000_rpm) );
% 
% 
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 2000 rpm
% figure
% subplot(3,1,1)
% ddpg_time_cil=ddpg_cil.log.time(ddpg_cil_start_2000_rpm:ddpg_cil_end_2000_rpm)-ddpg_cil.log.time(ddpg_cil_start_2000_rpm);
% foc_time_cil=ddpg_cil.log.time(ddpg_cil_start_2000_rpm:ddpg_cil_end_2000_rpm)-ddpg_cil.log.time(ddpg_cil_start_2000_rpm);
% 
% plot(ddpg_time_cil,ddpg_cil.log.CH19(ddpg_cil_start_2000_rpm:ddpg_cil_end_2000_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_cil,foc_cil.log.CH19(foc_cil_start_2000_rpm:foc_cil_end_2000_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_cil,ddpg_cil.log.CH6(ddpg_cil_start_2000_rpm:ddpg_cil_end_2000_rpm),'r' ,'LineWidth',2);
% plot(foc_time_cil,foc_cil.log.CH6(foc_cil_start_2000_rpm:foc_cil_end_2000_rpm),'k' ,'LineWidth',2 );
% 
% subplot(3,1,2)
% plot(ddpg_time_cil,ddpg_cil.log.CH20(ddpg_cil_start_2000_rpm:ddpg_cil_end_2000_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_cil,foc_cil.log.CH20(foc_cil_start_2000_rpm:foc_cil_end_2000_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_cil,ddpg_cil.log.CH7(ddpg_cil_start_2000_rpm:ddpg_cil_end_2000_rpm),'r' ,'LineWidth',2);
% plot(foc_time_cil,foc_cil.log.CH7(foc_cil_start_2000_rpm:foc_cil_end_2000_rpm),'k' ,'LineWidth',2 );
% subplot(3,1,3)
% plot(ddpg_time_cil,ddpg_cil.log.CH2(ddpg_cil_start_2000_rpm:ddpg_cil_end_2000_rpm) );
% hold on
% plot(foc_time_cil,foc_cil.log.CH2(foc_cil_start_2000_rpm:foc_cil_end_2000_rpm) );
% 
% 
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 3000 rpm
% figure
% subplot(3,1,1)
% ddpg_time_cil=ddpg_cil.log.time(ddpg_cil_start_3000_rpm:ddpg_cil_end_3000_rpm)-ddpg_cil.log.time(ddpg_cil_start_3000_rpm);
% foc_time_cil=ddpg_cil.log.time(ddpg_cil_start_3000_rpm:ddpg_cil_end_3000_rpm)-ddpg_cil.log.time(ddpg_cil_start_3000_rpm);
% 
% plot(ddpg_time_cil,ddpg_cil.log.CH19(ddpg_cil_start_3000_rpm:ddpg_cil_end_3000_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_cil,foc_cil.log.CH19(foc_cil_start_3000_rpm:foc_cil_end_3000_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_cil,ddpg_cil.log.CH6(ddpg_cil_start_3000_rpm:ddpg_cil_end_3000_rpm),'r' ,'LineWidth',2);
% plot(foc_time_cil,foc_cil.log.CH6(foc_cil_start_3000_rpm:foc_cil_end_3000_rpm),'k' ,'LineWidth',2 );
% 
% subplot(3,1,2)
% plot(ddpg_time_cil,ddpg_cil.log.CH20(ddpg_cil_start_3000_rpm:ddpg_cil_end_3000_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_cil,foc_cil.log.CH20(foc_cil_start_3000_rpm:foc_cil_end_3000_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_cil,ddpg_cil.log.CH7(ddpg_cil_start_3000_rpm:ddpg_cil_end_3000_rpm),'r' ,'LineWidth',2);
% plot(foc_time_cil,foc_cil.log.CH7(foc_cil_start_3000_rpm:foc_cil_end_3000_rpm),'k' ,'LineWidth',2 );
% subplot(3,1,3)
% plot(ddpg_time_cil,ddpg_cil.log.CH2(ddpg_cil_start_3000_rpm:ddpg_cil_end_3000_rpm) );
% hold on
% plot(foc_time_cil,foc_cil.log.CH2(foc_cil_start_3000_rpm:foc_cil_end_3000_rpm) );

% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %% real zerlegen
% 
% % find all index in which the turn-on signal is changed
% changes = find(diff(ddpg_real.log.CH1))+1;
% ddpg_real_start_500_rpm=changes(1);
% ddpg_real_start_1000_rpm=changes(3);
% ddpg_real_start_2000_rpm=changes(5);
% ddpg_real_start_3000_rpm=changes(7);
% ddpg_real_end_500_rpm=changes(2);
% ddpg_real_end_1000_rpm=changes(4);
% ddpg_real_end_2000_rpm=changes(6);
% ddpg_real_end_3000_rpm=changes(8);
% 
% % foc cil zerlegen
% 
% changes = find(diff(foc_real.log.CH1))+1;
% foc_real_start_500_rpm=changes(1);
% foc_real_start_1000_rpm=changes(3);
% foc_real_start_2000_rpm=changes(5);
% foc_real_start_3000_rpm=changes(7);
% foc_real_end_500_rpm=changes(2);
% foc_real_end_1000_rpm=changes(4);
% foc_real_end_2000_rpm=changes(6);
% foc_real_end_3000_rpm=changes(8);
% 
% 
% figure
% subplot(3,1,1)
% ddpg_time_real=ddpg_real.log.time-ddpg_real.log.time(ddpg_real_start_500_rpm);
% foc_time_cil=foc_real.log.time-foc_real.log.time(foc_real_start_500_rpm);
% 
% plot(ddpg_time_real,ddpg_real.log.CH19,'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_cil,foc_real.log.CH19,'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_real,ddpg_real.log.CH6,'r' ,'LineWidth',2);
% plot(foc_time_cil,foc_real.log.CH6,'k' ,'LineWidth',2 );
% 
% subplot(3,1,2)
% plot(ddpg_time_real,ddpg_real.log.CH20,'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_cil,foc_real.log.CH20,'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_real,ddpg_real.log.CH7,'r' ,'LineWidth',2);
% plot(foc_time_cil,foc_real.log.CH7,'k' ,'LineWidth',2 );
% subplot(3,1,3)
% plot(ddpg_time_real,ddpg_real.log.CH2 );
% hold on
% plot(foc_time_cil,foc_real.log.CH2 );
% 
% 
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 500 rpm
% figure
% subplot(3,1,1)
% ddpg_time_real=ddpg_real.log.time(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm)-ddpg_real.log.time(ddpg_real_start_500_rpm);
% foc_time_real=ddpg_real.log.time(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm)-ddpg_real.log.time(ddpg_real_start_500_rpm);
% 
% plot(ddpg_time_real,ddpg_real.log.CH19(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_real,foc_real.log.CH19(foc_real_start_500_rpm:foc_real_end_500_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_real,ddpg_real.log.CH6(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm),'r' ,'LineWidth',2);
% plot(foc_time_real,foc_real.log.CH6(foc_real_start_500_rpm:foc_real_end_500_rpm),'k' ,'LineWidth',2 );
% 
% subplot(3,1,2)
% plot(ddpg_time_real,ddpg_real.log.CH20(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_real,foc_real.log.CH20(foc_real_start_500_rpm:foc_real_end_500_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_real,ddpg_real.log.CH7(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm),'r' ,'LineWidth',2);
% plot(foc_time_real,foc_real.log.CH7(foc_real_start_500_rpm:foc_real_end_500_rpm),'k' ,'LineWidth',2 );
% subplot(3,1,3)
% plot(ddpg_time_real,ddpg_real.log.CH2(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm) );
% hold on
% plot(foc_time_real,foc_real.log.CH2(foc_real_start_500_rpm:foc_real_end_500_rpm) );
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 1000 rpm
% figure
% subplot(3,1,1)
% ddpg_time_real=ddpg_real.log.time(ddpg_real_start_1000_rpm:ddpg_real_end_1000_rpm)-ddpg_real.log.time(ddpg_real_start_1000_rpm);
% foc_time_real=ddpg_real.log.time(ddpg_real_start_1000_rpm:ddpg_real_end_1000_rpm)-ddpg_real.log.time(ddpg_real_start_1000_rpm);
% 
% plot(ddpg_time_real,ddpg_real.log.CH19(ddpg_real_start_1000_rpm:ddpg_real_end_1000_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_real,foc_real.log.CH19(foc_real_start_1000_rpm:foc_real_end_1000_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_real,ddpg_real.log.CH6(ddpg_real_start_1000_rpm:ddpg_real_end_1000_rpm),'r' ,'LineWidth',2);
% plot(foc_time_real,foc_real.log.CH6(foc_real_start_1000_rpm:foc_real_end_1000_rpm),'k' ,'LineWidth',2 );
% 
% subplot(3,1,2)
% plot(ddpg_time_real,ddpg_real.log.CH20(ddpg_real_start_1000_rpm:ddpg_real_end_1000_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_real,foc_real.log.CH20(foc_real_start_1000_rpm:foc_real_end_1000_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_real,ddpg_real.log.CH7(ddpg_real_start_1000_rpm:ddpg_real_end_1000_rpm),'r' ,'LineWidth',2);
% plot(foc_time_real,foc_real.log.CH7(foc_real_start_1000_rpm:foc_real_end_1000_rpm),'k' ,'LineWidth',2 );
% subplot(3,1,3)
% plot(ddpg_time_real,ddpg_real.log.CH2(ddpg_real_start_1000_rpm:ddpg_real_end_1000_rpm) );
% hold on
% plot(foc_time_real,foc_real.log.CH2(foc_real_start_1000_rpm:foc_real_end_1000_rpm) );
% 
% 
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 2000 rpm
% figure
% subplot(3,1,1)
% ddpg_time_real=ddpg_real.log.time(ddpg_real_start_2000_rpm:ddpg_real_end_2000_rpm)-ddpg_real.log.time(ddpg_real_start_2000_rpm);
% foc_time_real=ddpg_real.log.time(ddpg_real_start_2000_rpm:ddpg_real_end_2000_rpm)-ddpg_real.log.time(ddpg_real_start_2000_rpm);
% 
% plot(ddpg_time_real,ddpg_real.log.CH19(ddpg_real_start_2000_rpm:ddpg_real_end_2000_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_real,foc_real.log.CH19(foc_real_start_2000_rpm:foc_real_end_2000_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_real,ddpg_real.log.CH6(ddpg_real_start_2000_rpm:ddpg_real_end_2000_rpm),'r' ,'LineWidth',2);
% plot(foc_time_real,foc_real.log.CH6(foc_real_start_2000_rpm:foc_real_end_2000_rpm),'k' ,'LineWidth',2 );
% 
% subplot(3,1,2)
% plot(ddpg_time_real,ddpg_real.log.CH20(ddpg_real_start_2000_rpm:ddpg_real_end_2000_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_real,foc_real.log.CH20(foc_real_start_2000_rpm:foc_real_end_2000_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_real,ddpg_real.log.CH7(ddpg_real_start_2000_rpm:ddpg_real_end_2000_rpm),'r' ,'LineWidth',2);
% plot(foc_time_real,foc_real.log.CH7(foc_real_start_2000_rpm:foc_real_end_2000_rpm),'k' ,'LineWidth',2 );
% subplot(3,1,3)
% plot(ddpg_time_real,ddpg_real.log.CH2(ddpg_real_start_2000_rpm:ddpg_real_end_2000_rpm) );
% hold on
% plot(foc_time_real,foc_real.log.CH2(foc_real_start_2000_rpm:foc_real_end_2000_rpm) );
% 
% 
% 
% %% 3000 rpm
% figure
% subplot(3,1,1)
% ddpg_time_real=ddpg_real.log.time(ddpg_real_start_3000_rpm:ddpg_real_end_3000_rpm)-ddpg_real.log.time(ddpg_real_start_3000_rpm);
% foc_time_real=ddpg_real.log.time(ddpg_real_start_3000_rpm:ddpg_real_end_3000_rpm)-ddpg_real.log.time(ddpg_real_start_3000_rpm);
% 
% plot(ddpg_time_real,ddpg_real.log.CH19(ddpg_real_start_3000_rpm:ddpg_real_end_3000_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_real,foc_real.log.CH19(foc_real_start_3000_rpm:foc_real_end_3000_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_real,ddpg_real.log.CH6(ddpg_real_start_3000_rpm:ddpg_real_end_3000_rpm),'r' ,'LineWidth',2);
% plot(foc_time_real,foc_real.log.CH6(foc_real_start_3000_rpm:foc_real_end_3000_rpm),'k' ,'LineWidth',2 );
% 
% subplot(3,1,2)
% plot(ddpg_time_real,ddpg_real.log.CH20(ddpg_real_start_3000_rpm:ddpg_real_end_3000_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(foc_time_real,foc_real.log.CH20(foc_real_start_3000_rpm:foc_real_end_3000_rpm),'k--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_real,ddpg_real.log.CH7(ddpg_real_start_3000_rpm:ddpg_real_end_3000_rpm),'r' ,'LineWidth',2);
% plot(foc_time_real,foc_real.log.CH7(foc_real_start_3000_rpm:foc_real_end_3000_rpm),'k' ,'LineWidth',2 );
% subplot(3,1,3)
% plot(ddpg_time_real,ddpg_real.log.CH2(ddpg_real_start_3000_rpm:ddpg_real_end_3000_rpm) );
% hold on
% plot(foc_time_real,foc_real.log.CH2(foc_real_start_3000_rpm:foc_real_end_3000_rpm) );
% 
% 
% 
% 
% 
% 
% %%
% % find enable jump 0->1
% 
% ddpg_1_2_0rpm.jump_index= find(ddpg_1_2_0rpm.log.CH1, 1, 'first');
% ddpg_1_2_0rpm.jump_index=ddpg_1_2_0rpm.jump_index-200; % keep 10 values before jump
% 
% foc_0rpm.jump_index= find(foc_0rpm.log.CH1, 1, 'first');
% foc_0rpm.jump_index=foc_0rpm.jump_index-200; % keep 10 values before jump
% 
% ddpg_1_2_0rpm.t     =ddpg_1_2_0rpm.log.time(ddpg_1_2_0rpm.jump_index:end);
% ddpg_1_2_0rpm.id_set=ddpg_1_2_0rpm.log.CH19(ddpg_1_2_0rpm.jump_index:end);
% ddpg_1_2_0rpm.iq_set=ddpg_1_2_0rpm.log.CH20(ddpg_1_2_0rpm.jump_index:end);
% ddpg_1_2_0rpm.iq    =ddpg_1_2_0rpm.log.CH7(ddpg_1_2_0rpm.jump_index:end);
% ddpg_1_2_0rpm.id    =ddpg_1_2_0rpm.log.CH6(ddpg_1_2_0rpm.jump_index:end);
% ddpg_1_2_0rpm.enable=ddpg_1_2_0rpm.log.CH1(ddpg_1_2_0rpm.jump_index:end);
% ddpg_1_2_0rpm.t     =ddpg_1_2_0rpm.t-ddpg_1_2_0rpm.t(1); % start time at 0s
% 
% 
% foc_0rpm.t      =foc_0rpm.log.time(foc_0rpm.jump_index:end);
% foc_0rpm.id_set =foc_0rpm.log.CH19(foc_0rpm.jump_index:end);
% foc_0rpm.iq_set =foc_0rpm.log.CH20(foc_0rpm.jump_index:end);
% foc_0rpm.id     =foc_0rpm.log.CH6(foc_0rpm.jump_index:end);
% foc_0rpm.iq     =foc_0rpm.log.CH7(foc_0rpm.jump_index:end);
% foc_0rpm.enable =foc_0rpm.log.CH1(foc_0rpm.jump_index:end);
% foc_0rpm.t      =foc_0rpm.t-foc_0rpm.t(1);
% 
% 
% 
% 
% %%
% 
% ddpg_time_real=ddpg_real.log.time(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm)-ddpg_real.log.time(ddpg_real_start_500_rpm);
% foc_time_real=foc_real.log.time(foc_real_start_500_rpm:foc_real_end_500_rpm)-foc_real.log.time(foc_real_start_500_rpm);
% foc_time_cil=foc_cil.log.time(foc_cil_start_500_rpm:foc_cil_end_500_rpm)-ddpg_real.log.time(foc_cil_start_500_rpm);
% 
% close all
% figure
% linewidth_1=1;
% color_2='#D95319';
% color_3='#EDB120';
% 
% plot(ddpg_time_real,ddpg_real.log.CH6(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm),'Color',color_1,'LineWidth',1);
% hold on
% %[x,t]=my_resample(ddpg_real.log.CH6(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm),ddpg_time_real,5);
% %plot( resample(ddpg_time_real,1,5),resample(ddpg_real.log.CH6(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm),1,5),'Color','r','Marker','x','LineWidth',1);
% 
% hold on
% %plot(ddpg_time_cil,ddpg_cil.log.CH19(ddpg_cil_start_500_rpm:ddpg_cil_end_500_rpm),'g--' ,'LineWidth',2);
% plot(ddpg_time_real,ddpg_real.log.CH19(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm),'k--' ,'LineWidth',linewidth_1); % setpoint i_d
% %plot(ddpg_time_cil,ddpg_cil.log.CH6(ddpg_cil_start_500_rpm:ddpg_cil_end_500_rpm),'Color',color_2 ,'LineWidth',1);
% 
% xlim([0 0.62]);
% 
% %title('$THD_{I_a}$ over $I_{q}^*$ and $\omega_m$', 'Interpreter', 'latex');
% ylabel('Current in A', 'Interpreter', 'latex');
% xlabel('Time in s', 'Interpreter', 'latex');
% %legend(legend_labels,'Location','NorthEastOutside', 'Interpreter', 'latex');
% grid on
% box on
% cleanfigure();
% matlab2tikz('thd_over_current_dqn_1.tikz', 'height', '\fheight', 'width', '\fwidth' );
% 
% 
% t=ddpg_time_real;
% x=ddpg_real.log.CH6(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm);
% setpojint=ddpg_real.log.CH19(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm);
% itae_test=itae(setpojint,x,t)
% 
% 
% t=ddpg_time_real;
% x=ddpg_real.log.CH6(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm);
% setpojint=ddpg_real.log.CH19(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm);
% itae_test=itae(setpojint,x,t)
% 
% %%
% 
% 
% figure
% plot(ddpg_time_real,ddpg_real.log.CH20(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm),'r--' ,'LineWidth',2); % setpoint i_d
% hold on
% grid minor
% plot(ddpg_time_cil,ddpg_cil.log.CH20(ddpg_cil_start_500_rpm:ddpg_cil_end_500_rpm),'g--' ,'LineWidth',2);
% plot(ddpg_time_real,ddpg_real.log.CH7(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm),'r' ,'LineWidth',2);
% plot(ddpg_time_cil,ddpg_cil.log.CH7(ddpg_cil_start_500_rpm:ddpg_cil_end_500_rpm),'g' ,'LineWidth',2);
% xlim([0 0.062]);
% 
% 
% 
% %%
% figure
% subplot(2,1,1)
% ddpg_time_real=ddpg_real.log.time(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm)-ddpg_real.log.time(ddpg_real_start_500_rpm);
% ddpg_time_cil=ddpg_cil.log.time(ddpg_cil_start_500_rpm:ddpg_cil_end_500_rpm)-ddpg_cil.log.time(ddpg_cil_start_500_rpm);
% 
% plot(ddpg_time_real,ddpg_real.log.CH19(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm),'r--' ,'LineWidth',2);
% hold on
% plot(ddpg_time_cil,ddpg_cil.log.CH19(ddpg_cil_start_500_rpm:ddpg_cil_end_500_rpm),'g' ,'LineWidth',2);
% 
% hold on
% %plot(foc_time_real,foc_real.log.CH19(foc_real_start_500_rpm:foc_real_end_500_rpm),'b--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_real,ddpg_real.log.CH6(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm),'r' ,'LineWidth',2);
% %plot(foc_time_cil,foc_cil.log.CH6(foc_cil_start_500_rpm:foc_cil_end_500_rpm),'g' ,'LineWidth',2);
% %plot(foc_time_real,foc_real.log.CH6(foc_real_start_500_rpm:foc_real_end_500_rpm),'b' ,'LineWidth',2 );
% %xlim([0 0.01]);
% 
% subplot(2,1,2)
% plot(ddpg_time_real,ddpg_real.log.CH20(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm),'r--' ,'LineWidth',2);
% hold on
% %plot(foc_time_real,foc_real.log.CH20(foc_real_start_500_rpm:foc_real_end_500_rpm),'b--' ,'LineWidth',2 );
% grid minor
% plot(ddpg_time_real,ddpg_real.log.CH7(ddpg_real_start_500_rpm:ddpg_real_end_500_rpm),'r' ,'LineWidth',2);
% %plot(foc_time_real,foc_real.log.CH7(foc_real_start_500_rpm:foc_real_end_500_rpm),'b' ,'LineWidth',2 );
% %xlim([0 0.005]);
% %% test interpolation
% x = ddpg_time_cil;
% y = ddpg_cil.log.CH6(ddpg_cil_start_3000_rpm:ddpg_cil_end_3000_rpm); 
% xq1 = ddpg_time_cil(1):1/100000:ddpg_time_cil(end);
% m = makima(x,y,xq1);
% plot(xq1,m);
% hold on
% plot(ddpg_time_cil,ddpg_cil.log.CH6(ddpg_cil_start_3000_rpm:ddpg_cil_end_3000_rpm),'x' );
% 


%
function [data_upsampled,t_upsampled]=my_resample(data,time,factor)
time_diff=time(2)-time(1);
t_upsampled= time(1):time_diff/factor:time(end);
data_upsampled= makima(time,data,t_upsampled);

end
