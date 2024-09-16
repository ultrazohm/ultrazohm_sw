% write data to a csv file
T = table(time',i_ph(1,:)',i_ph(2,:)',i_ph(3,:)',i_ph(4,:)',i_ph(5,:)',i_ph(6,:)',i_dqXY(1,:)',i_dqXY(2,:)',i_dqXY(3,:)',i_dqXY(4,:)');
T.Properties.VariableNames = {'time','ia1','ib1','ic1','ia2','ib2','ic2','id','iq','iX','iY'};
writetable(T,'mydata.csv','WriteMode','overwrite','Delimiter','tab')

T_FFT = table(freq',FFT_sig(:,1));
T_FFT.Properties.VariableNames = {'frequency','amplitude'};
writetable(T_FFT,'mydata_fft.csv','WriteMode','overwrite','Delimiter','tab')