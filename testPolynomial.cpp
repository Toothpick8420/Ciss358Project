// File: testPolynomial.cpp

#include <iostream>
#include "Polynomial.h"

int main() 
{
    int option = 3;
//    std::cin >> option;

    switch (option) 
    {
        case 0:
        {
            Polynomial p;
            std::cin >> p;
            std::cout << p << std::endl;
            break;
        }
        case 1:
        {
            Polynomial p, q;
            std::cin >> p >> q;
            std::cout << (p += q) << std::endl;
            break;
        }
        case 2:
        {
            Polynomial p, q;
            std::cin >> p >> q;
            std::cout << (p -= q) << std::endl;
            break;
        }
        case 3:
        {
            Polynomial p, q;
            std::cin >> p >> q;
            std::cout << p << std::endl;
            std::cout << q << std::endl;
            std::cout << (p.slow_mult(q)) << std::endl;
            break;
        }
        case 4:
        {
            Polynomial p;
            LongInt q;
            std::cin >> p >> q;
            std::cout << (p.eval(q)) << std::endl;
            break;
        }
        case 5:
        {
            Polynomial p;
            LongInt q;
            std::cin >> p >> q;
            std::cout << (p.pow(q)) << std::endl;
            break;
        }
    }
}
