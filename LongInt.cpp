// File: LongInt.cpp

#include "LongInt.h"


LongInt::LongInt(int num)
    : neg_(num < 0)
{
    num = (num >= 0 ? num : -num);
    // Taking the LSD putting it in the array then removing it from the number
    // and repeating
    while (num != 0) 
    {
        int digit = num % 10; 
        digits_.push_back(digit);
        num /= 10;
    }
}


LongInt & LongInt::operator=(const LongInt & num) 
{
    if (this == &num) return (*this);

    neg_ = num.neg_;
    digits_ = num.digits_;

    return (*this);
}


LongInt & LongInt::operator=(int num) 
{
    return (*this) = LongInt(num);
}


bool LongInt::operator==(const LongInt & num) const 
{
    // Kind of ugly with 3 return statements but I think its better than a lot
    // of nested if statements
    if ((neg_ != num.neg_) || (digits_.size() != num.digits_.size())) {
        return false;
    }
    
    for (int i = 0; i < digits_.size(); ++i) {
        if (digits_[i] != num.digits_[i]) return false;
    }

    return true;
}
bool LongInt::operator==(int num) const { return (*this) == LongInt(num); }


bool LongInt::operator!=(const LongInt & num) const 
{
    return !((*this) == num);
}
bool LongInt::operator!=(int num) const { return (*this) != LongInt(num); }




std::ostream & operator<<(std::ostream & os, const LongInt & num)
{
    if (num.neg_) { os << "-"; }
    
    for (int i = num.digits_.size() - 1; i >= 0; --i) 
    {
        os << num.digits_[i];
    }

    return os;
}


std::istream & operator>>(std::istream & is, LongInt & num) 
{
    std::string input;
    is >> input;

    int start_idx = 0;
    if (input[0] == '-') { num.neg_ = true; ++start_idx; }

    for (int i = input.size() - 1; i >= start_idx; --i) 
    {
        // 48 is the offset of ascii numbers to 0 i.e "0" = 48
        num.digits_.push_back(input[i] - 48);
    }

    return is;
}
