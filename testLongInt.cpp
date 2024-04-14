// File: testLongInt.cpp

#include <iostream>
#include "LongInt.h"


int main() {

    int option;
    std::cin >> option;

    switch (option) 
    {
        case 0: 
        {
            LongInt l;
            std::cin >> l;
            std::cout << l << std::endl;
            break;
        }
        case 1: 
        {
            LongInt a,b;
            std::cin >> a;
            b = a;
            std::cout << a << " = " << b << std::endl;
            break;
        }
        case 2: 
        {
            int a;
            LongInt b;
            std::cin >> a;
            b = a;
            std::cout << a << " = " << b << std::endl;
            break;
        }
        case 3:
        {
            LongInt a,b;
            std::cin >> a >> b;
            std::cout << a << (a == b ? " == " : " != ") << b << std::endl;
            break;
        }
        case 4:
        {
            LongInt a,b;
            std::cin >> a >> b;
            std::cout << a << (a != b ? " != " : " == ") << b << std::endl;
            break;
        }
        case 5: 
        {
            LongInt a, b;
            std::cin >> a >> b;
            std::cout << a << (a < b ? " < " : " !< ") << b << std::endl;
            break;
        }
        case 6: 
        {
            LongInt a, b;
            std::cin >> a >> b;
            std::cout << a << (a <= b ? " <= " : " !<= ") << b << std::endl;
            break;
        }
        case 7:
        {
            LongInt a, b;
            std::cin >> a >> b;
            std::cout << a << (a > b ? " > " : " !> ") << b << std::endl;
            break;
        }
        case 8:
        {
            LongInt a, b;
            std::cin >> a >> b;
            std::cout << a << (a >= b ? " >= " : " !>= ") << b << std::endl;
            break;
        }
        case 9:
        {
            LongInt a, b;
            std::cin >> a >> b;
            a += b;
            std::cout << a << std::endl;
            break;
        }
        case 10:
        {
            LongInt a, b;
            std::cin >> a >> b;
            a -= b;
            std::cout << a << std::endl;
            break;
        }
        case 11:
        {
            LongInt a, b;
            std::cin >> a >> b;
            std::cout << (a + b) << " " << a << std::endl;
            break;
        } 
        case 12:
        {
            LongInt a, b;
            std::cin >> a >> b;
            std::cout << (a - b) << " " << a << std::endl;
            break;
        }
        case 13:
        {
            LongInt a, b;
            std::cin >> a >> b;
            std::cout << (a.slow_mult(b)) << std::endl;
            break;
        }
        case 14:
        {
            LongInt a, b;
            std::cin >> a >> b;
            std::cout << (a.colm_mult(b)) << std::endl;
            break;
        }
    }
}
