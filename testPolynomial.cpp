// File: testPolynomial.cpp

#include <iostream>
#include "Polynomial.h"

int main() 
{
    int option = 2;
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
    }
}
