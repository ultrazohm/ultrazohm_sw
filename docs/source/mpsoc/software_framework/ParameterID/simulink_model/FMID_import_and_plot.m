%% import data
data = zFCT_load_table(3, 'dq.csv');

%% plot figure
figure();
subplot(1,2,1);
zFCT_plot_fluxmap_fct(data.i_d, data.i_q, data.psi_d, "i_d", "i_q", "psi_d");
subplot(1,2,2);
zFCT_plot_fluxmap_fct(data.i_d, data.i_q, data.psi_q, "i_d", "i_q", "psi_q");

%% plot function
function zFCT_plot_fluxmap_fct(i_d, i_q, psi, x_label, y_label, psi_label)
%i_d: d-axis current (x-axis for xy)
%i_q: d-axis current (y-axis for xy)
%psi: flux to plot
%labels: strings for plot labels
hold on;
surf(i_d,transpose(i_q),psi);
xlabel(x_label); 
ylabel(y_label);
zlabel(psi_label);
view(3) 
grid on;
end

%% load data function
function data = zFCT_load_table(points_axs, tablename)
%points_axs: points per axis
%tablename: tablename
table = readtable(tablename); %log csv
points_total = points_axs*points_axs;
table(:,1:1:22) = []; %delete unnecessary columns
table(:,6) = []; %delete unnecessary row
table.Properties.VariableNames(1:5) = {'receive_field_2' 'receive_field_3' 'receive_field_4' 'receive_field_5' 'receive_field_6'};
for i = 1:points_total %create data struct
    index = find(table.receive_field_2==i,1);
    if(isempty(index))
        index = find(table.receive_field_2==i+0.05,1);
    end
    row = floor((i-1)/points_axs)+1;
    col = i-((row-1)*points_axs);
    data.i_d(row,col) = table.receive_field_3(index);
    data.i_q(row,col) = table.receive_field_3(index);
    data.psi_d(row,col) = table.receive_field_5(index)/1000;
    data.psi_q(row,col) = table.receive_field_6(index)/1000;

end

end