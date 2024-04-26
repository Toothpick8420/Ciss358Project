// File: testLongInt.cpp

#include <iostream>
#include "LongInt.h"


int main() {

    int option;
    //std::cin >> option;
    option = 12;

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
        case 15:
        {
            LongInt a, b, c, d;
            std::cin >> a >> b;
            std::cout << std::endl;
            std::cout << (c = a.karatsuba(b)) << std::endl << std::endl;
            std::cout << (d = a.colm_mult(b)) << std::endl << std::endl;
            std::cout << (c == d ? "a == b" : "a != b") << std::endl;
            break;
        }
        case 16:
        {
            LongInt a, b;
            std::cin >> a >> b;
            std::cout << (a.slow_div(b)) << std::endl;
            break;
        }
        case 17:
        {
            LongInt a, b;
            std::cin >> a >> b;
            std::cout << (a % b) << std::endl;
            break;
        }
        case 18:
        {
            LongInt a, b;
            std::cin >> a >> b;
            std::cout << (a /= b) << std::endl;
            break;
        }
        case 19:
        {
            LongInt a, b;
            std::cin >> a >> b;
            std::cout << (a %= b) << std::endl;
            break;
        }
        case 20:
        {
            LongInt a;
            unsigned int b;
            std::cin >> a >> b;
            std::cout << (a.shift_left(b)) << std::endl;
            break;
        }
        case 21:
        {
            LongInt a;
            unsigned int b;
            std::cin >> a >> b;
            std::cout << (a.shift_right(b)) << std::endl;
            break;
        }
        case 22:
        {
            LongInt a, b;
            std::cin >> a >> b;
            std::cout << (a.fast_div(b)) << std::endl;
            break;
        }
        case 23:
        {
            std::string num;
            std::cin >> num;
            std::cout << (LongInt(num)) << std::endl;
            break;
        }
        case 24:
        {
            LongInt a, b;
            std::cin >> a >> b;
            std::cout << (a *= b) << std::endl;
            break;
        }
        case 25:
        {
            LongInt a, b;
            std::cin >> a >> b;
            std::cout << (a.pow(b)) << std::endl;
            break;
        }
        case 26: 
        {
            LongInt a;
            std::cin >> a;
            std::cout << (a.to_string()) << std::endl;
            break;
        }
    }
}
