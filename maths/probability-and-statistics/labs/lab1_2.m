% 2.
X = 0:0.2:10;
Y1 = (X .^ 2) / 10;
Y2 = X .* sin(X);
Y3 = cos(X);

subplot(3, 1, 1);
plot(X, Y1, ":");
title('x^2/10')
subplot(3, 1, 2);
plot(X, Y2, "--");
title('xsinx')
subplot(3, 1, 3);
plot(X, Y3, "-.");
title('cosx')
