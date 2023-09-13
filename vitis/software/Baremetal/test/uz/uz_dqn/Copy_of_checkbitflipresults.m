clear
close all;

load("cumreward256_clipped.csv");
load("loss256_clipped.csv");
load("epsilon256_clipped.csv");

figure
subplot(3,1,1)
plot(cumreward256_clipped);
grid on;
xlabel('Episoden','interpreter','latex');
ylabel('Reward','interpreter','latex');

subplot(3,1,2)
plot(loss256_clipped);
grid on;
xlabel('Episoden','interpreter','latex');
ylabel('Loss','interpreter','latex');
subplot(3,1,3)
plot(epsilon256_clipped);
grid on;
xlabel('Episoden','interpreter','latex');
ylabel('epsilon','interpreter','latex');
sgtitle("Bitflip Ergebnisse NN 256 Neuronen clipped, seed 2, 2.0f beim Loss")

load("cumreward256_nur_action.csv")
figure
plot(cumreward256_nur_action);
grid on;
xlabel('Anzahl der Testschritte nach dem Training','interpreter','latex');
ylabel('Reward','interpreter','latex');
legend;
legend('Location','northeast');
