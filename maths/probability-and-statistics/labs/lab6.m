clc 
clf 
clear all


% 1.
X = [7 7 4 5 9 9 4 12 8 1 8 7 3 13 2 1 17 7 12 5 6 2 1 13 14 10 2 4 9 11 ...
    3 5 12 6 10 7];

n = length(X);

% a) sigma=5; at 5% significance, does the data suggest the standard is met?
%{
sigma = 5;
alpha = .05;

thetaZero = 9;  % or 8.5???

[H, P, CI, statisticValue] = ztest(X, thetaZero, sigma, 'alpha', alpha, 'tail', 'left');

RR = [-inf, norminv(alpha)];

if H == 0
    fprintf("Hypothesis Not Rejected: the standard is met \n")
else 
    fprintf("Hypothesis Rejected: the standard is not met \n")
end

fprintf("Rejection region: %.5f %.5f \n", RR(1), RR(2))
fprintf("Value of the test statistic: %.5f \n", statisticValue)
fprintf("P-value: %.5f \n", P)
%}

% b) does the number of files stored exceed 5.5 on average? 5% significance
% level

alpha = .05;

thetaZero = 5.5;

[H, P, CI, statisticValue] = ttest(X, thetaZero, 'alpha', alpha, 'tail', 'right');

RR = [tinv(1 - alpha, n - 1), inf];

if H == 0
    fprintf("Hypothesis Not Rejected: on average, AT MOST 5.5 \n")
else 
    fprintf("Hypothesis Rejected: on average, EXCEEDS 5.5 \n")
end

fprintf("Rejection region: %.5f %.5f \n", RR(1), RR(2))
fprintf("Value of the test statistic: %.5f \n", statisticValue.tstat)
fprintf("P-value: %.5f \n", P)


