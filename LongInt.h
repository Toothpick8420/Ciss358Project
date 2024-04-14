// File: LongInt.h

#ifndef LONGINT_H
#define LONGINT_H

#include <iostream>
#include <vector>

class LongInt 
{
public:
    LongInt(int num = 0);

    LongInt & operator=(const LongInt & num);
    LongInt & operator=(int num);

    LongInt operator-() const;

    LongInt & operator+=(const LongInt & num);
    LongInt & operator-=(const LongInt & num);
    LongInt operator+(const LongInt & num) const;
    LongInt operator-(const LongInt & num) const;

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
    void remove_leading_zeros();

    std::vector<int> digits_;
    bool neg_;
};



#endif
