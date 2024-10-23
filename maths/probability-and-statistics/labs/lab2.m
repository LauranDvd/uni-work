clc
clf 
clear all 

%{
n = input("n=");

p = input("p=");

x = 0:1:n;
plot(x, binopdf(x, n, p))
hold on 
plot(x, binocdf(x, n, p))
legend("pdf", "cdf")
%}


% application
n = 3;
p = 1 / 2;

% a)
x = 0:1:n;
plot(x, binopdf(x, n, p));
PdfMatrix = [x; binopdf(x, n, p)];
disp(PdfMatrix);

% b)
plot(x, binocdf(x, n, p));

% c)
c1 = binopdf(0, n, p);
fprintf("c1 = %.3f\n", c1)
c2 = 1 - binopdf(1, n, p);
fprintf("c2 = %.3f\n", c2)

% d)
d1 = binocdf(2, n, p);
fprintf("d1 = %.3f\n", d1)
d2 = binocdf(2, n, p) - binopdf(2, n, p);
fprintf("d2 = %.3f\n", d2)

% e)
e1 = 1 - (binocdf(1, n, p) - binopdf(1, n, p));
fprintf("e1 = %.3f\n", e1)
e2 = e1 - binopdf(1, n, p);
fprintf("e2 = %.3f\n", e2)

% f)
S = input("how many simulations?");

SimResults = sum(rand(3, S) < 0.5);  % interesting

hist(SimResults)







