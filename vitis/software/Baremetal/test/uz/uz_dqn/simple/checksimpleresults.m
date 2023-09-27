clear
close all;
 %% prepare for export to tikz
T = readtable("hyperparam.txt");

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

load("cumrewardsimple.csv");
load("losssimple.csv");
load("globalrewardrsimple.csv");
load("epsilonsimple.csv");
load("QCritic.csv");
load("QTarget.csv");

%% reshape
QCritic = reshape(QCritic,3,[]);
QTarget = reshape(QTarget,3,[]);

figure('units','normalized','outerposition',[0 0 1 1])
subplot(5,1,1)
plot(cumrewardsimple);
grid on;
% xlim([0 1000])
xlabel('Episoden','interpreter','latex');
ylabel('Reward','interpreter','latex');

subplot(5,1,2)
plot(losssimple);%,'x'
%ylim([0 1000])
grid on;
xlabel('Episoden','interpreter','latex');
ylabel('Loss','interpreter','latex');
subplot(5,1,3)
plot(globalrewardrsimple);
grid on;
xlabel('Episoden','interpreter','latex');
ylabel('Rewardmetrik','interpreter','latex');
grid on;
subplot(5,1,4)
plot(QCritic(1,:),'DisplayName',"1");
hold on;
plot(QCritic(2,:),'DisplayName',"2");
hold on;
plot(QCritic(3,:),'DisplayName',"3");
grid on;
xlabel('Episoden','interpreter','latex');
ylabel('Critic Values','interpreter','latex');
legend
subplot(5,1,5)
plot(QTarget(1,:),'DisplayName',"1");
hold on;
plot(QTarget(2,:),'DisplayName',"2");
hold on;
plot(QTarget(3,:),'DisplayName',"3");
grid on;
legend
xlabel('Episoden','interpreter','latex');
ylabel('Target Values','interpreter','latex');
sgtitle("Simple env, Buffer 2000")
% subplot(4,1,4)
% plot(dloss256_clipped);
% grid on;
% % xlim([0 1000])
% xlabel('Episoden','interpreter','latex');
% ylabel('dLoss','interpreter','latex');

% cleanfigure();
% matlab2tikz('bitflip_dervloss_clipped.tikz','showInfo', false,  ...
%      'width', '0.85\textwidth', 'height', '\fheight', 'extraaxisoptions', extraaxisoptions);

