clear
close all;
 %% prepare for export to tikz
T = readtable("hyperparam.txt");
dirListing = dir("hyperparam.txt")
% Get the current time.
tNow = datestr(now)
% Create a title
caption = sprintf('File Date = %s. Right now it is %s',...
	dirListing.date, tNow);
 extraaxisoptions = [...
'y tick label style={/pgf/number format/.cd,scaled y ticks = false,precision=1, use comma,' ...
,'set thousands separator={},fixed,/tikz/.cd}'...
,',x tick label style={/pgf/number format/.cd,'...
'scaled x ticks = false,precision=5,set decimal separator={,},set thousands separator={},'...
,'fixed,/tikz/.cd}'...
,',ylabel style={yshift=-0.2cm,font=\small}'...
,',xlabel style={font=\small}'...
,',legend style={font=\tiny},'...
,',legend columns=1,',...
];

% load("cumreward16.csv");
% load("loss16.csv");
% load("dloss16.csv");
% figure
% subplot(3,1,1)
% plot(cumreward16);
% grid on;% xlabel('Episoden','interpreter','latex');
% ylabel('Kumulierter Reward pro Episode','interpreter','latex');
% legend;
% legend('Location','northeast');
% 
% subplot(3,1,2)
% plot(loss16);
% grid on;
% xlabel('Episoden','interpreter','latex');
% ylabel('Ableitung Loss','interpreter','latex');
% legend;
% legend('Location','northeast');
% subplot(3,1,3)
% plot(dloss16);
% grid on;
% xlabel('Episoden','interpreter','latex');
% ylabel('Loss','interpreter','latex');
% legend;
% legend('Location','northeast');
% sgtitle("Bitflip Ergebnisse NN 16 Neuronen")
% 

% load("cumreward256.csv");
% load("loss256.csv");
% load("dloss256.csv");
% load("epsilon256.csv");
% 
% figure
% subplot(4,1,1)
% plot(cumreward256);
% grid on;
% % xlim([0 1000])
% xlabel('Episoden','interpreter','latex');
% ylabel('Reward','interpreter','latex');
% 
% subplot(4,1,2)
% plot(dloss256);
% grid on;
% % xlim([0 1000])
% xlabel('Episoden','interpreter','latex');
% ylabel('dLoss','interpreter','latex');
% subplot(4,1,3)
% plot(loss256);
% grid on;
% % xlim([0 1000])
% xlabel('Episoden','interpreter','latex');
% ylabel('Loss','interpreter','latex');
% subplot(4,1,4)
% plot(epsilon256);
% grid on;
% % xlim([0 1000])
% xlabel('Episoden','interpreter','latex');
% ylabel('epsilon','interpreter','latex');
% sgtitle("Bitflip Ergebnisse NN 256 Neuronen not clipped")
% cleanfigure();
% matlab2tikz('bitflip_dervloss_not_clipped.tikz','showInfo', false,  ...
%      'width', '0.85\textwidth', 'height', '\fheight', 'extraaxisoptions', extraaxisoptions);

load("cumreward256_clipped.csv");
load("loss256_clipped.csv");
load("globalrewardr.csv");
load("epsilon256_clipped.csv");

figure('units','normalized','outerposition',[0 0 1 1])
subplot(5,1,1)
plot(cumreward256_clipped);
grid on;
% xlim([0 1000])
xlabel('Episoden','interpreter','latex');
ylabel('Reward','interpreter','latex');

subplot(5,1,2)
plot(loss256_clipped);%,'x'
%ylim([0 1000])
grid on;
xlabel('Episoden','interpreter','latex');
ylabel('Loss','interpreter','latex');
subplot(5,1,3)
plot(globalrewardr);
grid on;
xlabel('Episoden','interpreter','latex');
ylabel('Rewardmetrik','interpreter','latex');
grid on;
h = subplot(5,1,4);   
u = uitable('Data',T{:,:},'Units',h.Units,'Position',h.Position,'ColumnName',T.Properties.VariableNames); 
set(u,'ColumnWidth',{120})
h.Visible = 'Off'; 
subplot(5,1,5)
plot(epsilon256_clipped);
grid on;
xlabel('Episoden','interpreter','latex');
ylabel('epsilon','interpreter','latex');
sgtitle(caption)
% subplot(4,1,4)
% plot(dloss256_clipped);
% grid on;
% % xlim([0 1000])
% xlabel('Episoden','interpreter','latex');
% ylabel('dLoss','interpreter','latex');

% cleanfigure();
% matlab2tikz('bitflip_dervloss_clipped.tikz','showInfo', false,  ...
%      'width', '0.85\textwidth', 'height', '\fheight', 'extraaxisoptions', extraaxisoptions);
load("cumreward256_nur_action.csv")
figure
plot(cumreward256_nur_action);
grid on;
xlabel('Anzahl der Testschritte nach dem Training','interpreter','latex');
ylabel('Reward','interpreter','latex');
legend;
legend('Location','northeast');

load("QCritic.csv");
load("QTarget.csv");

%% reshape
QCritic = reshape(QCritic,3,[]);
QTarget = reshape(QTarget,3,[]);

figure
subplot(2,1,1)
plot(QCritic(1,:),'DisplayName',"QC1");
hold on;
plot(QCritic(2,:),'DisplayName',"QC2");
hold on;
plot(QCritic(3,:),'DisplayName',"QC3");

xlabel('Episoden','interpreter','latex');
ylabel('Critic Values','interpreter','latex');
legend
subplot(2,1,2)
plot(QTarget(1,:),'DisplayName',"QT1");
hold on;
plot(QTarget(2,:),'DisplayName',"QT2");
hold on;
plot(QTarget(3,:),'DisplayName',"QT3");

legend
xlabel('Episoden','interpreter','latex');
ylabel('Target Values','interpreter','latex');
sgtitle("Q Values")
