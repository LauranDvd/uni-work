clc 
clf 
clear all

X1 = [22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20.0];
X2 = [17.7, 14.8, 19.6, 19.6, 12.1, 14.8, 15.4, 12.6, 14.0, 12.2];

n1 = length(X1);
n2 = length(X2);

% a)
alpha = .05;

thetaZero = 1;

[H, P, CI, statistics] = vartest2(X1, X2, 'alpha', alpha);

RRinv = [finv(alpha/2, n1 - 1, n2 - 1), finv(1 - alpha/2, n1 - 1, n2 - 1)];

if H == 0
    fprintf("Hypothesis Not Rejected. The variances seem equal.\n")
else
    fprintf("Hypothesis Rejected. The variances DO NOT seem equal.\n")
end

fprintf("Rejection region: (-inf, %.5f) unite (%.5f, inf)\n", RRinv(1), RRinv(2))
fprintf("Value of the test statistic: %.5f\n", statistics.fstat)
fprintf("P-value: %.5f\n", P)


% b)
%{
alpha = .05;
thetaZero = 0;

[H, P, CI, statistics] = ttest2(X1, X2, 'alpha', alpha, 'tail', 'right');

RR = [tinv(1 - alpha, n1 + n2 - 2), inf];

if H == 0
    fprintf("Hypothesis Not Rejected. Premium DOES NOT have higher mileage\n")
else
    fprintf("Hypothesis Rejected. Premium does have higher mileage\n")
end

fprintf("Rejection region: %.5f %.5f \n", RR(1), RR(2))
fprintf("Value of the test statistic: %.5f \n", statistics.tstat)
fprintf("P-value: %.5f \n", P)
%}









