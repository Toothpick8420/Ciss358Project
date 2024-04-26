// File: Polynomial.cpp
#include <algorithm>
#include <cmath>
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
    bool ended_on_x = false;
    for (auto & ch : input) {
        
        if (ch == 'x' || ch == 'X') {
            ended_on_x = true;
            coeff = false;
            if (buff.empty()) {
                t.coefficient = (neg ? -1 : 1);
            } else {
                t.coefficient = (neg ? -LongInt(buff) : LongInt(buff));
                buff.clear();
            }
            neg = false;
        }
        else if (ch == '-') { neg = true; ended_on_x = false; }
        else if (ch == '+') { neg = false; ended_on_x = false; }
        else if (ch == ' ') {
            coeff = true;
            if (buff.empty()) {
                if (ended_on_x) {
                    t.power = 1;
                    terms_.push_back(t);
                } else {
                    continue;
                }
            } else {
                t.power = (neg ? -LongInt(buff) : LongInt(buff));
                terms_.push_back(t);
                buff.clear();
            }
            ended_on_x = false;
        }
        else if (ch == '^') {
            ended_on_x = false;
            continue;
        }
        else {
            buff.push_back(ch);
            ended_on_x = false;
        }
    }

    if (!buff.empty()) {
        if (ended_on_x) {
            t.power = 1;
        } 
        else if (coeff){
            t.coefficient = (neg ? -LongInt(buff) : LongInt(buff));
            t.power = 0;
        } else {
            t.power = (neg ? -LongInt(buff) : LongInt(buff));
        }
        terms_.push_back(t);
    }

    simplify();

    // sort it by term
    std::sort(terms_.begin(), terms_.end(), [](term a, term b) {return a.power > b.power; });
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


// Slow n^2 polynomial multiplication for testing
Polynomial Polynomial::slow_mult(const Polynomial & poly) const 
{
    // Make more efficient maybe
    Polynomial ret;

    for (auto & t1 : terms_) {
        for (auto & t2: poly.terms_) {
            ret.terms_.push_back({t1.coefficient * t2.coefficient, t1.power + t2.power});
        }
    }

    ret.simplify(); 
    return ret;
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
        if (it->power == (it + 1)->power) {
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


// TODO: Make more memory conservative
Polynomial Polynomial::pow(const LongInt & p) const {
    Polynomial ret(*this);
    for (LongInt i = 1; i < p; ++i) {
        ret = ret.slow_mult((*this));
    }

    return ret;
}


LongInt Polynomial::eval(const LongInt & x) const {
    LongInt ret;
    for (auto & t : terms_) {
        std::cout << t.coefficient  << " " << x.pow(t.power) << std::endl;
        ret += (t.coefficient * (x.pow(t.power)));
    }

    return ret;
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
