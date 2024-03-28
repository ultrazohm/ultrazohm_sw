data_point_to_plot = 23;

figure
plot(time(data_point_to_plot,:),i_ph(1,:,data_point_to_plot));
hold on
plot(time(data_point_to_plot,:),i_ph(2,:,data_point_to_plot));
plot(time(data_point_to_plot,:),i_ph(3,:,data_point_to_plot));