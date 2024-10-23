clc
clf
clear all

%{
p = 0;
while p < 0.05 || p > 0.95
    p = input("p=");
end

for n=1:100
    x = 0:n;
    y1 = binopdf(x, n, p);
    y2 = normpdf(x, n * p, sqrt(n * p * (1 - p)));

    plot(x, y1, x, y2)
    title('approx of binopdf using normpdf')
    legend('binopdf', 'normpdf(np, sqrt(np(1-p)))')
    pause(0.5)
end
%}

p = 1;
while p > 0.05
    p = input("p=");
end

for n=15:60
    x = 0:n;
    y1 = binopdf(x, n, p);
    y2 = poisspdf(x, n * p);

    plot(x, y1, x, y2)
    title("approx of binopdf using normpdf. n=" + n)
    legend('binopdf', 'poisspdf(np)')
    pause(0.5)
end
