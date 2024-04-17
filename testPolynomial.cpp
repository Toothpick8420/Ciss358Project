// File: testPolynomial.cpp

#include <iostream>
#include "Polynomial.h"

int main() 
{
    int option = 0;
//    std::cin >> option;

    switch (option) 
    {
        case 0:
        {
            Polynomial p;
            std::cin >> p;
            std::cout << p << std::endl;
        }
    }
}
