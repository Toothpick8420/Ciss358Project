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


        // Carrot symbol is always followed by a power
        if (ch == '^') {
            // i.e x^5
            // so no extra numbers were read in, coefficient is one
            if (buff.empty()) {
                t.coefficient = (neg ? -1 : 1);
            } else {
                // There was numbers in the buffer to be coefficient, check if it 
                // is negative and then set it to the coefficient
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
    
    simplify();

    // sort it by term
    std::sort(terms_.begin(), terms_.end(), [](term a, term b) {return a.power < b.power; });
}


Polynomial & Polynomial::operator+=(const Polynomial & poly) 
{
    std::vector<term>::iterator lh = terms_.begin();
    std::vector<term>::const_iterator rh = poly.terms_.begin();

    // iterate over the elements
    while (lh != terms_.end() && rh != poly.terms_.end()) {
        // If the left power is less than the right move up one term 
        // to see if the next term is the same power
        if (lh->power < rh->power) {
            ++lh;
        } 
        // If the left power is greater than there is no term with the same power
        // so insert the right hand exponent into the left polynomial
        else if (lh->power > rh->power) {
            terms_.insert(lh, (*rh));
            ++rh;
            ++lh;
        } 
        // They are the same power, just add
        else {
            lh->coefficient += rh->coefficient;
            ++rh;
            ++lh;
        }
    }
 
    // Anying remaining terms in the right hand side that haven't been added
    while (rh != poly.terms_.end()) {
        terms_.push_back((*rh));
        ++rh;
    }

    return (*this);
}


Polynomial & Polynomial::operator-=(const Polynomial & poly) 
{
    std::vector<term>::iterator lh = terms_.begin();
    std::vector<term>::const_iterator rh = poly.terms_.begin();

    // iterate over the elements
    while (lh != terms_.end() && rh != poly.terms_.end()) {
        if (lh->power < rh->power) {
            ++lh; 
        }

        else if (lh->power > rh->power) {
            terms_.insert(lh, {-rh->coefficient, rh->power});
            ++rh;
            ++lh;
        }

        else {
            lh->coefficient -= rh->coefficient;
            ++rh;
            ++lh;
        }
    }

    // Anything left in the right hand that wasn't subtracted
    while (rh != poly.terms_.end()) {
        terms_.push_back({-rh->coefficient, rh->power});
        ++rh;
    }

    simplify(); // combine like terms and remove 0x^6

    return (*this);
}


void Polynomial::simplify()
{
    std::sort(terms_.begin(), terms_.end(), [](term a, term b) { return a.power > b.power; });

    std::vector<term>::iterator it = terms_.begin();

    while(it != terms_.end() - 1) {
        // Remove terms with a 0 coefficient
        if (it->coefficient == 0) {
            terms_.erase(it);  
            // Reloop to check that its within the it != end() - 1
            // to avoid out of bounds errors
            continue; 
            
        }
        // Since its sorted the value to the right will be >=
        // and if they are == combine the terms
        else if (it->power == (it + 1)->power) {
            it->coefficient += (it + 1)->coefficient; // combine coefficient
            terms_.erase((it + 1));                   // remove the extra term
            // No need to increment the iterator since erasing the value effectivly 
            // does that
        } else {
            // next term
            ++it;
        }
    }
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
