// File: Polynomial.cpp
#include <algorithm>
#include "Polynomial.h"

Polynomial::Polynomial(std::string input)
{
    /*
     * Example Inputs
     *
     *  1x^4 + 5x^4 - 4x^-3 + x^4
    */

    std::string buff;
    term t;
    bool coeff = true;
    bool neg   = false;
    for (auto & ch : input) {
        // Cases of things we can just ignore
        if (ch == ' ' && buff.empty()) continue;
        if (ch == 'x' || ch == 'X')    continue;


        if (ch == '^') {
            // i.e x^5
            if (buff.empty()) {
                t.coefficient = (neg ? -1 : 1);
            } else {
                LongInt num(buff);
                t.coefficient = (neg ? -num : num);
            }
            buff.clear();
            neg   = false; // assume exponents are positive
            coeff = false;
        }

        else if (ch == '+') {
            // No entered numbers can be assumed 1
            if (buff.empty()) {
                neg = false;
            } else {
                LongInt num(buff);
                if (coeff) {
                    t.coefficient = (neg ? -num : num);
                } else {
                    t.power = (neg ? -num : num);
                    terms_.push_back(t);
                    coeff = !coeff;
                }
            }
            buff.clear();
            neg = false; 
        } 
        else if (ch == '-') {
            // If no entered numbers we can assume its a 1
            if (buff.empty()) {
                neg = true;
            } else {
                LongInt num(buff);
                if (coeff) { 
                    t.coefficient = (neg ? -num : num);
                } else { 
                    t.power = (neg ? -num : num);
                    terms_.push_back(t);
                    coeff = !coeff;
                }
            }
            buff.clear();
            neg = true;
        } 

        else if (ch == ' ') {
            // If no entered numbers we can assume its a 1
            if (buff.empty()) {
                if (coeff) {
                    t.coefficient = (neg ? -1 : 1);
                } else {
                    t.power = (neg ? -1 : 1);
                    terms_.push_back(t);
                }
            } else {
                LongInt num(buff);
                if (coeff) {
                    t.coefficient = (neg ? -num : num);
                } else {
                    t.power = (neg ? -num : num);
                    terms_.push_back(t);
                    coeff = !coeff;
                }
            }
            buff.clear();
            neg = false;
        }

        else {
            buff.push_back(ch);
        }
    }

    if (!buff.empty()) {
        LongInt num(buff);
        if (coeff) {
            t.coefficient = (neg ? -num : num);
            t.power = 0;
        }
        else {
            t.power = (neg ? -num : num);
        }
        terms_.push_back(t);
    }

    // sort it by term
    std::sort(terms_.begin(), terms_.end(), [](term a, term b) {return a.power < b.power; });
}


Polynomial & Polynomial::operator+=(const Polynomial & poly) 
{

}


Polynomial & Polynomial::operator-=(const Polynomial & poly) 
{
        
}



std::ostream & operator<<(std::ostream & os, const Polynomial & poly) 
{
    if (poly.terms_.size() <= 0) return os;
    
    os << poly.terms_[0].coefficient;
    if (poly.terms_[0].power != 0) {
        os << "x^" << poly.terms_[0].power;
    }

    for (unsigned int i = 1; i < poly.terms_.size(); ++i) {
        // Prettier printing so if its a negative term, change it to positive
        // and make it subtract, the default is addition basically
        term t = poly.terms_[i];
        if (t.coefficient.is_negative()) {
            os << " - ";
            t.coefficient = t.coefficient.pos();
        } else {
            os << " + ";
        }

        // Now print the actual term
        os << t.coefficient;
        if (t.power != 0) {
            os << "x^" << t.power;
        }
    }
    return os;
}


// Try to catch most variations but also assumes itll be formatted reasonably
std::istream & operator>>(std::istream & is, Polynomial & poly)
{
    std::string input; 
    std::getline(std::cin, input);

    poly = Polynomial(input);

    return is;
}
