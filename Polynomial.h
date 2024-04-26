// File: Polynomial.h

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include "LongInt.h"

struct term {
    LongInt coefficient = 0;
    LongInt power = 0;
};

struct complex {
    LongInt real = 0;
    LongInt imaginary = 0;
};


class Polynomial 
{
public:
    Polynomial(std::string str="0");

    Polynomial & operator+=(const Polynomial & poly); // Requires the terms be sorted
    Polynomial & operator-=(const Polynomial & poly);

    Polynomial slow_mult(const Polynomial & poly) const;

    void simplify();
    Polynomial pow(const LongInt & pow) const;
    LongInt eval(const LongInt & x) const;
 

    friend
    std::ostream & operator<<(std::ostream & os, const Polynomial & poly);
    friend 
    std::istream & operator>>(std::istream & is, Polynomial & poly);
private:
    
    std::vector<term> terms_;
};

std::vector<term> FFT(std::vector<term> poly);
std::vector<term> IFFT(std::vector<term> poly);
complex operator*(complex c, LongInt l);

#endif
