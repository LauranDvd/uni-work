% B.
X = [7 7 4 5 9 9 4 12 8 1 8 7 3 13 2 1 17 7 12 5 6 2 1 13 14 10 2 4 9 11 ...
    3 5 12 6 10 7];

alpha = input("confidence (0...1)=");
alpha = 1 - alpha;

% a) we know sigma
%{
sigma = 5;
meanX = mean(X);
n = length(X);

% z[1-alpha/2] = norminv(1-alpha/2, 0, 1)   (works bcos. n>30)
zQuantile = norminv(1-alpha/2, 0, 1);

lowerBound = meanX - (sigma / sqrt(n)) * zQuantile;
upperBound = meanX + (sigma / sqrt(n)) * zQuantile;

%}

% b) we don't
%{
n = length(X);
meanX = sum(X) / n;
s = std(X);

tQuantile = tinv(1 - alpha/2, n - 1);

lowerBound = meanX - (s / sqrt(n)) * tQuantile;
upperBound = meanX + (s / sqrt(n)) * tQuantile;
%}

% c) for variance and std deviation
n = length(X);
s = std(X);

oneMinusAlphaOver2Quantile = chi2inv(1 - alpha/2, n - 1);
alphaOver2Quantile = chi2inv(alpha/2, n - 1);

lowerBound = ((n - 1) * s * s) / oneMinusAlphaOver2Quantile;
upperBound = ((n - 1) * s * s) / alphaOver2Quantile;

fprintf("(lower variance = %.5f) \n", sqrt(lowerBound));
fprintf("(upper variance = %.5f) \n", sqrt(upperBound));




fprintf("lower = %.5f \n", lowerBound);
fprintf("upper = %.5f \n", upperBound);











