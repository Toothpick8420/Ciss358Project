// File: LongInt.h

#ifndef LONGINT_H
#define LONGINT_H

#include <iostream>
#include <vector>

class LongInt 
{
public:
    LongInt(int num = 0);
    LongInt(std::vector<int> num, bool neg=false);

    LongInt & operator=(const LongInt & num);
    LongInt & operator=(int num);

    LongInt & operator++();
    LongInt & operator--();
    LongInt operator++(int num);
    LongInt operator--(int num);

    LongInt operator-() const;
    LongInt pos() const;

    LongInt & operator+=(const LongInt & num);
    LongInt & operator-=(const LongInt & num);
    LongInt operator+(const LongInt & num) const;
    LongInt operator-(const LongInt & num) const;

    LongInt slow_mult(const LongInt & num) const; // Addition looping
    LongInt colm_mult(const LongInt & num) const; // HS Multiplation
    LongInt karatsuba(const LongInt & num) const;       // Karatsuba Multiplication


    LongInt & operator+=(int num);
    LongInt & operator-=(int num);
    LongInt operator+(int num) const;
    LongInt operator-(int num) const;

    bool operator==(const LongInt & num) const;
    bool operator!=(const LongInt & num) const;
    bool operator< (const LongInt & num) const;
    bool operator<=(const LongInt & num) const;
    bool operator> (const LongInt & num) const;
    bool operator>=(const LongInt & num) const;
 
    bool operator==(int num) const;
    bool operator!=(int num) const;
    bool operator< (int num) const;
    bool operator<=(int num) const;
    bool operator> (int num) const;
    bool operator>=(int num) const;


    friend
    std::ostream & operator<<(std::ostream & os, const LongInt & num);
    friend
    std::istream & operator>>(std::istream & is, LongInt & num);
private:
    void remove_leading_zeros();         // 0001 -> 1
    void add_leading_zeros(int num);
    LongInt & insert_trailing_zeros(int num); // Essentially multiplying by 10 

    std::vector<int> digits_;
    bool neg_;
};



#endif
