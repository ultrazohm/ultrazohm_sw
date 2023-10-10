    i_dqXY(1,1:20001) = log.CH9(50000:70000)';
    i_dqXY(2,1:20001) = log.CH10(50000:70000)';
    i_dqXY(3,1:20001) = log.CH11(50000:70000)';
    i_dqXY(4,1:20001) = log.CH12(50000:70000)';
    i_dqXY(5,1:9591) = 2.0;
    i_dqXY(5,9592:20001) = 7.0;
    i_dqXY(6,1:20001) = 5.0;
t = 0:0.0001:2;
    figure
    plot(t,i_dqXY(1,:));
    hold on
    plot(t,i_dqXY(2,:));
    plot(t,i_dqXY(3,:));
    plot(t,i_dqXY(4,:));
    plot(t,i_dqXY(5,:),'-.','LineWidth',1.5);
    plot(t,i_dqXY(6,:),'-.','LineWidth',1.5);
    title('VSD currents');
grid on
xlabel('time in s')
ylabel('current in A')
axis([0 2 -8 8])
[hleg, hobj, hout, mout] = legend({'i_d','i_q','i_X','i_Y','i_q_,_r_e_f','i_q_,_l_i_m'},'Location','southeast');
set(hobj,'linewidth',1.5);