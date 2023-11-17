% Annahme: Sie haben drei lineare Funktionen f1, f2, f3 für die Punkte (5,:), (10,:), (15,:)
f1 = @(x) 1*x + 2;  % Ersetzen Sie dies durch Ihre eigene Funktion
f2 = @(x) 2*x + 3;  % Ersetzen Sie dies durch Ihre eigene Funktion
f3 = @(x) 2*x + 4;  % Ersetzen Sie dies durch Ihre eigene Funktion

% Annahme: Ihre ursprüngliche Matrix ist data_matrix (20x20)
data_matrix = rand(20, 20);  % Beispiel-Matrix, ersetzen Sie dies durch Ihre eigene Matrix

% Index für die Punkte, an denen Sie die Funktionen anwenden möchten
point1 = 5;
point2 = 10;
point3 = 15;

% Anwenden der linearen Funktionen auf die Punkte
approximation1 = f1(data_matrix(point1, :));
approximation2 = f2(data_matrix(point2, :));
approximation3 = f3(data_matrix(point3, :));

% Kombinieren Sie die Ergebnisse, um den ursprünglichen 3D-Plot zu approximieren
approximated_data = data_matrix;
approximated_data(point1, :) = approximation1;
approximated_data(point2, :) = approximation2;
approximated_data(point3, :) = approximation3;

% 3D-Plot des ursprünglichen und approximierten Plots
[X, Y] = meshgrid(1:size(data_matrix, 2), 1:size(data_matrix, 1));

figure;
subplot(1, 2, 1);
surf(X, Y, data_matrix);
title('Ursprünglicher 3D-Plot');

subplot(1, 2, 2);
surf(X, Y, approximated_data);
title('Approximierter 3D-Plot');

% Anzeigen des ursprünglichen und approximierten Plots (optional)
figure;
subplot(1, 2, 1);
imagesc(data_matrix);
title('Ursprünglicher Plot');

subplot(1, 2, 2);
imagesc(approximated_data);
title('Approximierter Plot');
