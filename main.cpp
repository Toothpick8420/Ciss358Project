#include <cmath>
#include <vector>
#include "LongInt.h"
#include "Polynomial.h"

Polynomial tau(const LongInt & t);

int main() {
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

    return p;
}
