clear all
clc
clf


% 1.
A = [1 0 -2; 2 1 3; 0 1 0];
B = [2 1 1; 1 0 -1; 1 1 0];

C = A - B;
D = A * B;
E = A .* B;

disp(E)


% 2.
X = 0:0.2:10;
Y1 = (X .^ 2) / 10;
Y2 = X .* sin(X);
Y3 = cos(X);

hold on
plot(X, Y1, ":");
title('Various functions')
plot(X, Y2, "--");
plot(X, Y3, "-.");
legend("x^2/10", "xsinx", "cosx")