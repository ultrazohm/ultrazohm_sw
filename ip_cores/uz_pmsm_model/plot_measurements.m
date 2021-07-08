A=readmatrix('vector_core.csv');

figure
subplot(2,1,1)
grid on
hold on
plot(A(:,1),A(:,2));
plot(A(:,1),A(:,3));
plot(A(:,1),A(:,4));

subplot(2,1,2);
plot(A(:,1),A(:,5));