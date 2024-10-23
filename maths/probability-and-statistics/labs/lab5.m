clc
clf
clear all

% A.

X = [20 * ones(1, 2), 21 * ones(1, 1), 22 * ones(1, 3), 23 * ones(1, 6)...
    24 * ones(1, 5), 25 * ones(1, 9), 26 * ones(1, 2) 27 * ones(1, 2)];
Y = [75 * ones(1, 3), 76 * ones(1, 2), 77 * ones(1, 2), 78 * ones(1, 5)...
    79 * ones(1, 8), 80 * ones(1, 8), 81, 82];

fprintf("mean(x)=%.5f \n", mean(X));
fprintf("mean(y)=%.5f \n", mean(Y));

fprintf("var(x)=%.5f \n", var(X));
fprintf("var(y)=%.5f \n", var(Y));

fprintf("cov(X, Y)= \n");
disp(cov(X, Y));

fprintf("corrcoef(X, Y)= \n");
disp(corrcoef(X, Y));
