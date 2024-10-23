// input: data.in -- expecting to read integer n>=1
// output: data.out

/* Computing the number of bases of the vector space Z[2]^n over Z[2]
(for small n, also generating them)

    Formula to obtain the number:  (2^n - 1)*(2^n - 2)*(2^n - 4)*...*(2^n - (2^(n-1)))  (*) -- proof below
                         (works for n up to 1000, in at most 10 seconds)
    To obtain every solution:  backtracking

Proof for formula (*):
The vector space Z[2]^n has dimension n. Therefore, a base is a set of n linearly independent vectors.
There are 2^n = a vectors in Z[2]^n.
The first vector (v1) may be anything but 0, so there are a-1 options to choose it from.
The second vector may be anything but 0 or v1, so there are a-2 options.
The third vector may be anything but a linear combination of v1 and v2, so there are a-2^2 options. (**) -- proof below
...
The n'th vector may be anything but a linear combination of v1,v2,...,v(n-1), so there are a-2^(n-1) choices. (**)
Hence, there are (a-1)(a-2)(a-2^2)...(a-2^(n-1)) bases.

Proof for (**)  (there are 2^n different results for a linear combination of n linearly independent vectors)
In a linear combination in Z[2]^n over Z[2], each coefficient can be either 0 or 1. Hence there are 2^n
different lists of coefficients.
Suppose two lists of coefficients lead to the same result. Then, by subtracting the two lists one would get
a list of coefficients, not all zero, which sum to 0. That means, the vectors are not independent.
Therefore, any list of coefficients leads to a different result, so there are 2^n different results.*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

std::ifstream fin("data.in");
std::ofstream fout("data.out");

const int MAX_DIGITS = 76000;  // how many digits in the "large" numbers, in base BASE
const int BASE = 1e4;  // for efficiency, the large numbers are stored in BASE 10000 (4 digits in one)

// numbers which can hold more than 300,000 digits
struct LargeNumber {  
    int noDigits;
    short digits[MAX_DIGITS + 1];
};

// Initialize a large number with a one-digit value
void init(LargeNumber &num, int val) {

    num.noDigits = 1;
    memset(num.digits, 0, sizeof(num.digits));  // make all digits 0
    num.digits[1] = val;
}

// Subtract two large numbers
LargeNumber sub(LargeNumber A, LargeNumber B) {
    LargeNumber result;
    init(result, 0);

    int borrow = 0;
    for (int i = 1; i <= A.noDigits; i++) {
        int localResult = A.digits[i] - B.digits[i] - borrow;
        borrow = 0;
        if (localResult < 0) {
            localResult += BASE;
            borrow = 1;
        }
        result.digits[i] = localResult;
    }

    result.noDigits = A.noDigits;
    while (result.digits[result.noDigits] == 0)
        result.noDigits--;

    return result;
}

// Multiply a large number by 2 and store the result directly in that number
void mult2(LargeNumber &num) {
    bool carry = 0;
    for (int i = 1; i <= num.noDigits + 1; i++) {
        num.digits[i] <<= 1;
        num.digits[i] += carry;

        if (num.digits[i] >= BASE) {
            num.digits[i] -= BASE;
            carry = 1;
        }
        else
            carry = 0;
    }

    num.noDigits++;
    while (num.digits[num.noDigits] == 0)
        num.noDigits--;
}

long long forMult[MAX_DIGITS];  // the intermediary results of multiplication don't fit on "short"

// Multiply two large numbers
LargeNumber mult(LargeNumber A, LargeNumber B) {
    LargeNumber result;
    init(result, 0);

    for (int i = 1; i <= A.noDigits + B.noDigits; i++)
        forMult[i] = 0;

    for (int i = 1; i <= A.noDigits; i++)
        for (int j = 1; j <= B.noDigits; j++)
            forMult[i + j - 1] += (int)A.digits[i] * B.digits[j];

    long long carry = 0;
    for (int i = 1; i <= A.noDigits + B.noDigits; i++) {
        long long here = forMult[i] + carry;
        
        carry = here / BASE;
        result.digits[i] = here - carry * BASE;  // = here % BASE (computes it faster)
    }

    result.noDigits = A.noDigits + B.noDigits;
    while (result.digits[result.noDigits] == 0)
        result.noDigits--;

    return result;
}

// Write to file "fo" (global) a given number
void printBigNumber(LargeNumber A) {
    fout << A.digits[A.noDigits];

    for (int i = A.noDigits - 1; i >= 1; i--) {
        std::string fourDigits = "";  // we need to do this so that "digit" 0021 isn't written as "21", per example
        int digits = A.digits[i];
        while (digits) {
            fourDigits += (digits % 10 + '0');
            digits /= 10;
        }

        while (fourDigits.size() < 4)  // add leading 0s
            fourDigits += "0";

        reverse(fourDigits.begin(), fourDigits.end());
        fout << fourDigits;
    }
}


int n;
std::vector<std::vector<short>> allBases;
LargeNumber ans, powerTwoN, powerTwoI;

/// @brief present the problem to the user
void printProblemInfo() {
    fout << "Computing the number of bases of the vector space Z[2]^n over Z[2]\n";
    fout << "(for n<=4, also generating them)\n";
    fout << "\nRead number " << n << " from file data.in.\n";
}

/// @brief Output the answer to the first question
void printAnswer1(LargeNumber answer) {
    fout << "There are ";
    printBigNumber(answer);
    fout << " such bases.";
}

/// @brief Output the answer to the questions, assuming we did the backtracking
void printAnswer12() {
    fout << "\nThere are " << allBases.size() << " such bases. ";
    fout << "The vectors of each such basis are:\n";

    for (int idxBase = 0; idxBase < allBases.size(); idxBase++) {
        std::vector<short> base = allBases[idxBase];
        fout << "\n\nThe " << idxBase + 1 << "'th basis is:\n";
        fout << "(";

        for (int idxVector = 0; idxVector < base.size(); idxVector++) {
            int v = base[idxVector];

            fout << "(";
            for (int i = n - 1; i >= 0; i--) {
                fout << ((v >> i) & 1);
                if (i > 0)
                    fout << ",";
            }
            fout << ")";
            if (idxVector < base.size() - 1)
                fout << ",";
        }
        fout << ")\n";
    }
}

/// @brief Update the set of all XOR subsums of a set with newly-inserted number maskV
std::unordered_set<short> extendXorSum(std::unordered_set<short> xorSum, short maskV) {
    std::unordered_set<short> newXorSum;
    for (short s: xorSum) {
        newXorSum.insert(s);
        newXorSum.insert(maskV ^ s);
    }
    newXorSum.insert(maskV);

    return newXorSum;
}

/// @brief backtracking to obtain all bases
/// @param base the current list of linearly independent vectors.
/// vectors are represented as 16-bit numbers, each bit being a number in Z[2]
/// @param xorSums all the vectors' linear combinations
void backtracking(std::vector<short> base, std::unordered_set<short> xorSums) {
    // We use bit masking to store the vectors, as it is faster
    // e.g.: (1, 0, 1, 1) is represented as 1011b = 11

    // We can observe that adding two vectors is equivalent to doing the XOR operation on their masks
    // Moreover, in a linear combination, the coefficients are either 0 or 1 (i.e., a vector either is, or isn't)
    // Thus, the set of linear combinations is the set of the XOR subsums of the vectors' masks

    if (base.size() == n) {  // n is the dimension of vector space Z[2]^n with respect to Z[2]
        allBases.push_back(base);
        return;
    }

    for (short maskV = 1; maskV < (1 << n); maskV++)  // the mask of v
        if (xorSums.find(maskV) == xorSums.end()) {  // check that v isn't generated by the others
            base.push_back(maskV);
            std::unordered_set<short> newXorSums = extendXorSum(xorSums, maskV);
            backtracking(base, newXorSums);

            base.pop_back();
        }
}

int main() {
    fin >> n;

    printProblemInfo();

    if (n <= 4) {  // for small n, we do backtracking
        std::vector<short> nullBase;
        std::unordered_set<short> nullSums;
        backtracking(nullBase, nullSums);

        printAnswer12();
    }
    else { 
        // formula (proof at the beginning):
        // (2^n - 1) * (2^n - 2) * (2^n - 4) * (2^n - 8) * ... * (2^n - 2^(n-1))
        init(ans, 1);

        init(powerTwoN, 1);  // 2^n
        for (int i = 1; i <= n; i++)
            mult2(powerTwoN);

        init(powerTwoI, 1);  // will be 2^i, for i=0,n-1

        for (int i = 1; i <= n; i++) {
            // choose the i'th vector
            ans = mult(ans, sub(powerTwoN, powerTwoI));

            mult2(powerTwoI);
        }

        printAnswer1(ans);
    }

    return 0;
}
