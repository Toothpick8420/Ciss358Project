// File: Polynomial.h

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include "LongInt.h"

struct term {
    LongInt coefficient = 0;
    LongInt power = 0;
};


class Polynomial 
{
public:
    Polynomial(std::string str="0");

    Polynomial & operator+=(const Polynomial & poly);
    Polynomial & operator-=(const Polynomial & poly);

    friend
    std::ostream & operator<<(std::ostream & os, const Polynomial & poly);
    friend 
    std::istream & operator>>(std::istream & is, Polynomial & poly);
private:
    std::vector<term> terms_;
};

#endif
