// File: LongInt.cpp

#include "LongInt.h"


LongInt::LongInt(int num)
    : neg_(num < 0)
{
    if (num == 0) {
        digits_.push_back(0);
    } else {
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


LongInt LongInt::operator-() const {
    LongInt ret; 
    ret.digits_ = digits_;
    ret.neg_ = !neg_;

    return ret;
}


LongInt & LongInt::operator+=(const LongInt & num) 
{
    if (neg_ != num.neg_) {
        return (*this) -= (-num);
    } 

    // Go up the the MSD of the smaller number
    int max_idx = (digits_.size() < num.digits_.size() ? digits_.size() : num.digits_.size());
  

    bool carry = 0;
    for (int i = 0; i < max_idx; ++i) 
    {
        int digit = digits_[i] + num.digits_[i] + carry;
        if (digit >= 10) 
        {
            carry = 1;
            digits_[i] = digit - 10;
        } 
        else 
        {
            carry = 0;
            digits_[i] = digit;
        }
    }

    
    // If theres left over digits on the right
    if (digits_.size() < num.digits_.size()) {
        for (int i = max_idx; i < num.digits_.size(); ++i) {
            int digit = num.digits_[i] + carry;
            if (digit >= 10) {
                carry = 1;
                digits_.push_back(digit-10);
            }
            else 
            {
                carry = 0;
                digits_.push_back(digit);
            }
        }
        if (carry) digits_.push_back(1);
    } else {
        for (int i = max_idx; i < digits_.size(); ++i) {
            if (!carry) break; // If theres no carry it won't change just break
            int digit = digits_[i] + carry;
            if (digit >= 10) {
                carry = 1;
                digits_[i] = digit - 10;
            } else {
                carry = 0;
                digits_[i] = digit;
            }
        }
        if (carry) digits_.push_back(1);
    }
    
    return (*this);
}


LongInt & LongInt::operator-=(const LongInt & num) 
{
    if (neg_ != num.neg_) {
        return (*this) += (-num);
    } 
    if ((*this) == num) {
        return (*this) = LongInt(); 
    }


    bool neg = false; 
    bool rh_larger = false;
    if (neg_) {
        if (num < (*this)) { 
            neg = false;
            rh_larger = true;
        }
    } else {
        if (num >= (*this)) {
            neg = true;
            rh_larger = true;
        }
    }

  
    if (rh_larger) {
        LongInt rh = num;
        for (int i = 0; i < digits_.size(); ++i) {
            if (digits_[i] > rh.digits_[i]) {
                // Borrow
                for (int j = i + 1; j < rh.digits_.size(); ++j) {
                    if (rh.digits_[j] > 0) { 
                        --rh.digits_[j];
                        break;
                    } else {
                        rh.digits_[j] += 9;
                    }
                }
                rh.digits_[i] += 10;
            }
            rh.digits_[i] -= digits_[i];
        }
        (*this) = rh;
        neg_ = neg;
    } else {
        for (int i = 0; i < num.digits_.size(); ++i) {
            if (num.digits_[i] > digits_[i]) {
                // Borrow
                for (int j = i + 1; j < digits_.size(); ++j) {
                    if (digits_[j] > 0) {
                        --digits_[j];
                        break;
                    } else {
                        digits_[j] += 9;
                    }
                }
                digits_[i] += 10;
            }
            digits_[i] -= num.digits_[i];
        }
    }

    neg_ = neg;

    remove_leading_zeros();

    return (*this);
}


LongInt LongInt::operator+(const LongInt & num) const
{ return LongInt(*this) += num; }


LongInt LongInt::operator-(const LongInt & num) const
{ return LongInt(*this) -= num; }


LongInt & LongInt::operator+=(int num) { return (*this) += LongInt(num); }
LongInt & LongInt::operator-=(int num) { return (*this) -= LongInt(num); }
LongInt LongInt::operator+(int num) const { return (*this) + LongInt(num); }
LongInt LongInt::operator-(int num) const { return (*this) - LongInt(num); }


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


bool LongInt::operator!=(const LongInt & num) const 
{
    return !((*this) == num);
}


bool LongInt::operator<(const LongInt & num) const
{
    if (neg_ && !num.neg_) return true;
    else if (!neg_ && num.neg_) return false;
    else {
        if (neg_) {
            if (digits_.size() > num.digits_.size()) {
                return true;
            } else if (digits_.size() < num.digits_.size()) {
                return false;
            } else {
                for (int i = digits_.size() - 1; i >= 0; --i) {
                    if (digits_[i] > num.digits_[i]) return true;
                    else if (digits_[i] < num.digits_[i]) return false;
                }
            }
        } else {
            if (digits_.size() < num.digits_.size()) {
                return true;
            } else if (digits_.size() > num.digits_.size()) {
                return false;
            } else {
                for (int i = digits_.size() - 1; i >= 0; --i) {
                    if (digits_[i] < num.digits_[i]) return true;
                    else if (digits_[i] > num.digits_[i]) return false;
                }
            }
        }

    }
    
    return false;
}


bool LongInt::operator<=(const LongInt & num) const 
{ return (*this < num) || (*this == num); }


bool LongInt::operator> (const LongInt & num) const 
{ return !((*this) <= num); }


bool LongInt::operator>=(const LongInt & num) const
{ return (*this) == num || !(*this < num); }


bool LongInt::operator==(int num) const { return (*this) == LongInt(num); }
bool LongInt::operator!=(int num) const { return (*this) != LongInt(num); }
bool LongInt::operator< (int num) const { return (*this) <  LongInt(num); }
bool LongInt::operator<=(int num) const { return (*this) <= LongInt(num); }
bool LongInt::operator> (int num) const { return (*this) >  LongInt(num); }
bool LongInt::operator>=(int num) const { return (*this) >= LongInt(num); }


void LongInt::remove_leading_zeros() 
{
    std::vector<int>::iterator it = digits_.end() - 1;
    while ((*it) == 0) {
        digits_.erase(it);
        it = digits_.end() - 1;
    }
}


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

    num.digits_.clear();
    for (int i = input.size() - 1; i >= start_idx; --i) 
    {
        // 48 is the offset of ascii numbers to 0 i.e "0" = 48
        num.digits_.push_back(input[i] - 48);
    }

    return is;
}
