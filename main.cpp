#include <cmath>
#include <vector>
#include "LongInt.h"
#include "Polynomial.h"

// The Tau function with q in it results in coefficients that match with the solution
// Aka tau(2) the first 2 coefficients match up with the solution of 
// The larger the n the more coefficients that lead and trail match with the 
// solution

Polynomial tau(const LongInt & t);

int main() {
    std::cout << "Enter n for the tau funciton: ";
    LongInt n = 0;
    std::cin >> n;

    Polynomial p = tau(n);
    std::cout << (p) << std::endl;

    return 0;
}


Polynomial tau(const LongInt & t) {
    std::string poly = "1x^0 - x^" + LongInt(1).to_string();
    Polynomial p(poly);
    p = p.pow(24);
    for (LongInt i = 2; i <= t; ++i) {
        std::cout << i << std::endl;
        std::string poly = "1x^0 - x^" + i.to_string();
        Polynomial q(poly);
        q = q.pow(24);
        p = p.slow_mult(q);
    }

    return p;
}
