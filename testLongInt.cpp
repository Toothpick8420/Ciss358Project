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
    }
}
