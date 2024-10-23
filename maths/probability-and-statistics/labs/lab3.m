fprintf("n: normal\n")
fprintf("t: student\n")
fprintf("c: chi2\n")
fprintf("f: fisher\n")

option = input("Choose model: ", "s");

alpha = input("alpha=");
beta = input("beta=");

switch option
    case "n"
        fprintf("you chose normal\n")
        miu = input("miu=");
        sigma = input("sigma=");

        a1 = normcdf(0, miu, sigma);
        a2 = 1 - a1;

        b1 = normcdf(1, miu, sigma) - normcdf(-1, miu, sigma);
        b2 = 1 - b1;

        c1 = norminv(alpha, miu, sigma);
        
        d1 = norminv(1 - beta, miu, sigma);
    case "t"
        n = input("n=");

        a1 = tcdf(0, n);
        a2 = 1 - a1;

        b1 = tcdf(1, n) - tcdf(-1, n);
        b2 = 1 - b1;

        c1 = tinv(alpha, n);
        
        d1 = tinv(1 - beta, n);
    case "c"
        n = input("n=");

        a1 = chi2cdf(0, n);
        a2 = 1 - a1;

        b1 = chi2cdf(1, n) - chi2cdf(-1, n);
        b2 = 1 - b1;

        c1 = chi2inv(alpha, n);
        
        d1 = chi2inv(1 - beta, n);
    case "f"
        m = input("m=");
        n = input("n=");

        a1 = fcdf(0, m, n);
        a2 = 1 - a1;

        b1 = fcdf(1, m, n) - fcdf(-1, m, n);
        b2 = 1 - b1;

        c1 = finv(alpha, m, n);
        
        d1 = finv(1 - beta, m, n);
end

fprintf("a1=%.5f \n", a1)
fprintf("a2=%.5f \n", a2)
fprintf("b1=%.5f \n", b1)
fprintf("c1=%.5f \n", c1)
fprintf("d1=%.5f \n", d1)



