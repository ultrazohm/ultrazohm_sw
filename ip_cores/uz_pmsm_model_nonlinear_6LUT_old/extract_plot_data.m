% open figure and extract data to workspace variables for psi_d
path('C:\SoSe23\Masterarbeit\MatlabtoTikz\src',path);
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
% plot figures with extracted data
figure;
surf(id,iq,psi_d);
xlabel('$i_d/A$', 'FontSize', 18,'Interpreter','Latex');
ylabel('$i_q/A$', 'FontSize', 18,'Interpreter','Latex');
zlabel('$\psi_d/Vs$', 'FontSize', 18,'Interpreter','Latex');
view(-127.5,30)

figure;
surf(id,iq,psi_q)
xlabel('$i_q/A$', 'FontSize', 18,'Interpreter','Latex');
ylabel('$i_d/A$', 'FontSize', 18,'Interpreter','Latex');
zlabel('$\psi_q/Vs$', 'FontSize', 18,'Interpreter','Latex');