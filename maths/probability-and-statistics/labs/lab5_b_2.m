clc
clf
clear all


X1 = [22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20.0];
X2 = [17.7, 14.8, 19.6, 19.6, 12.1, 14.8, 15.4, 12.6, 14.0, 12.2];

alpha = 1 - input("confidence (0...1)=");

n1 = length(X1);
n2 = length(X2);

mean1 = mean(X1);
mean2 = mean(X2);

s1 = std(X1);
s2 = std(X2);

% a) sigma1=sigma2; C.I. for mu1-mu2 (true means)
%{
sp = sqrt(((n1 - 1) * s1 * s1 + (n2 - 1) * s2 * s2) / (n1 + n2 - 2));

tQuantile = tinv(1 - alpha / 2, n1 + n2 - 2);

lowerBound = mean1 - mean2 - tQuantile * sp * sqrt(1 / n1 + 1 / n2);
upperBound = mean1 - mean2 + tQuantile * sp * sqrt(1 / n1 + 1 / n2);
%}

% b) sigma1 != sigma2; C.I. for mu1-mu2
%{
c = (s1 * s1 / n1) / (s1 * s1 / n1 + s2 * s2 / n2);
n = 1 / (c * c / (n1 - 1) + (1 - c) * (1 - c) / (n2 - 1));

tQuantile = tinv(1 - alpha / 2, n);

lowerBound = mean1 - mean2 - tQuantile * sqrt(s1 * s1 / n1 + s2 * s2 / n2);
upperBound = mean1 - mean2 + tQuantile * sqrt(s1 * s1 / n1 + s2 * s2 / n2);
%}


% c) ratio (UNCHECKED!!!)
fQuantileOneMinus = finv(1 - alpha / 2, n1 - 1, n2 - 1);
fQuantileOverTwo = finv(alpha / 2, n1 - 1, n2 - 1);

lowerBound = (1 / fQuantileOneMinus) * (s1 * s1) / (s2 * s2);
upperBound = (1 / fQuantileOverTwo) * (s1 * s1) / (s2 * s2);








fprintf("lower = %.5f \n", lowerBound);
fprintf("upper = %.5f \n", upperBound);
