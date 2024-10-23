%{
p = input("p=");
S = input("no. simulations=");

countZeros = 0;
countOnes = 0;
for simulationIndex = 1:S
    valueObtained = (rand() < p);
    if valueObtained
        countOnes = countOnes + 1;
    else 
        countZeros = countZeros + 1;
    end 

end

bernoulliPdf = [0, 1; countZeros / S, countOnes / S];

disp(bernoulliPdf)
%}

%{
p = input("p=");
n = input("n=");
S = input("no. simulations=");

binomialPdf = [0:n; zeros(1, n + 1)];
for simulationIndex = 1:S
    countSuccessfulTrials = 0;
    for trialIndex = 1:n
        trialResult = (rand() < p);
        countSuccessfulTrials = countSuccessfulTrials + trialResult;
    end
    binomialPdf(2, countSuccessfulTrials + 1) = binomialPdf(2, countSuccessfulTrials + 1) + 1;
end

binomialPdf = [binomialPdf(1, :); binomialPdf(2, :) / S];

disp(binomialPdf)
%}

%{
p = input("p=");
S = input("no. simulations=");

simulationResults = [];
for simulationIndex = 1:S
    failuresBeforeSuccess = 0;

    lastTrialResult = (rand() < p);
    while lastTrialResult ~= 1
        failuresBeforeSuccess = failuresBeforeSuccess + 1;
        lastTrialResult = (rand() < p);
    end

    simulationResults = [simulationResults, failuresBeforeSuccess];
end

geometricPdf = [0:max(simulationResults); zeros(1, max(simulationResults) + 1)];
for resultIndex = 1:length(simulationResults)
    result = simulationResults(resultIndex);
    geometricPdf(2, result + 1) = geometricPdf(2, result + 1) + 1;
end

geometricPdf = [geometricPdf(1, :); geometricPdf(2, :) / S];

disp(geometricPdf)
%}

p = input("p=");
n = input("n=");
S = input("no. simulations=");

simulationResults = [];
for simulationIndex = 1:S
    failuresBeforeSuccess = 0;

    countFailures = 0;
    countSuccesses = 0;
    while countSuccesses < n
        trialResult = (rand() < p);
        if trialResult 
            countSuccesses = countSuccesses + 1;
        else 
            countFailures = countFailures + 1;
        end
    end

    simulationResults = [simulationResults, countFailures];
end

hist(simulationResults, length(unique(simulationResults)));

pascalPdf = [0:max(simulationResults); zeros(1, max(simulationResults) + 1)];
for resultIndex = 1:length(simulationResults)
    result = simulationResults(resultIndex);
    pascalPdf(2, result + 1) = pascalPdf(2, result + 1) + 1;
end

pascalPdf = [pascalPdf(1, :); pascalPdf(2, :) / S];

disp(pascalPdf)

x = 0:max(simulationResults);
plot(x, pascalPdf(2, x + 1), x, nbinpdf(x, n, p))
legend('approximation', 'actual')








