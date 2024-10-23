clc
clear all

X1 = [4.6 0.7 4.2 1.9 4.8 6.1 4.7 5.5 5.4];
X2 = [2.5 1.3 2.0 1.8 2.7 3.2 3.0 3.5 3.4];
n1 = length(X1);
n2 = length(X2);


% a)
% theta = sigma1^2 / sigma2^2
% H0: theta = 1
% H1: theta != 1
% => two-tailed test
% we will use TT=(s1^2 / sigma1 ^ 2) / (s2^2 / sigma2 ^ 2)
% belonging to F(n1-1, n2-1)

alpha = .05;

[H, P, ~, statistics] = vartest2(X1, X2, 'alpha', alpha);

RRinv = [finv(alpha/2, n1 - 1, n2 - 1), finv(1 - alpha/2, n1 - 1, n2 - 1)];

if H == 0
    fprintf("Null Hypothesis Not Rejected. The variances seem equal.\n")
else
    fprintf("Null Hypothesis Rejected. The variances DO NOT seem equal. (they seem to differ)\n")
end

fprintf("Rejection region: (-inf, %.5f) unite (%.5f, inf)\n", RRinv(1), RRinv(2))
fprintf("Value of the test statistic: %.5f\n", statistics.fstat)
fprintf("P-value: %.5f\n", P)

fprintf("------------------\n");

% b)
% theta = miu1-miu2
% H0: theta=0   (Steel DOES NOT lose more)
% H1: theta>0   (Steel does lose more)
% => right-tailed test
% from a) we get that the variances are probably different
% so we use the TT in the last line in 3), which belongs to T(n)
% n = (see below)
% TT = (mean1 - mean2 - (miu1-miu2)) / sqrt(s1*s1/n1+s2*s2/n2)

alpha = .05;  % same

[H, P, CI, statistics] = ttest2(X1, X2, alpha, 'right', 'unequal');

s1 = std(X1);
s2 = std(X2);
c = ((s1 * s1) / n1) / (s1 * s1 / n1 + s2 * s2 / n2);
n = 1 / ((c * c) / (n1 - 1) + ((1 - c) * (1 - c)) / (n2 - 1));
RR = [tinv(1 - alpha, n), inf];

if H == 0
    fprintf("Null Hypothesis Not Rejected. Steel DOES NOT seem to lose more\n")
else
    fprintf("Null Hypothesis Rejected. Steel does seem to lose more\n")
end

fprintf("Rejection region: %.5f %.5f \n", RR(1), RR(2))
fprintf("Value of the test statistic: %.5f \n", statistics.tstat)
fprintf("P-value: %.5f \n", P)







