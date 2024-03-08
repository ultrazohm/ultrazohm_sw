% open figure and extract data to workspace variables for psi_d
close all;
ch=openfig('Versuchsmotor_Hoerner_psi_d.fig')
h = gcf
axesObjs = get(h, 'Children')
dataObjs = get(axesObjs, 'Children')
id = dataObjs.XData;
iq = dataObjs.YData;
psi_d = dataObjs.ZData;

% open figure and extract data to workspace variables for psi_q
ch=openfig('Versuchsmotor_Hoerner_psi_q.fig')
h = gcf
axesObjs = get(h, 'Children')
dataObjs = get(axesObjs, 'Children')
% id = dataObjs.XData;
% iq = dataObjs.YData;
psi_q = dataObjs.ZData;
% test1 = flip(iq);
% test2 = flip(id);
% test3 = flip(psi_d);
% plot figures with extracted data
figure;
surf(id,iq,psi_d);
xlabel('$i_d/A$', 'FontSize', 18);
ylabel('$i_q/A$', 'FontSize', 18);
zlabel('$psi_d/Vs$', 'FontSize', 18);
view(-127.5,30)

figure;
surf(id,iq,psi_q)
xlabel('$i_q/A$', 'FontSize', 18);
ylabel('$i_d/A$', 'FontSize', 18);
zlabel('$psi_q/Vs$', 'FontSize', 18);