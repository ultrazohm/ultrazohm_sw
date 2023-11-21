% open figure and extract data to workspace variables for psi_d
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
figure
surf(id,iq,psi_d)

figure
surf(id,iq,psi_q)