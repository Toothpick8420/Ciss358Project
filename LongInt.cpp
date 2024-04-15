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
        while (num != 0) {
            int digit = num % 10; 
            digits_.push_back(digit);
            num /= 10;
        }
    }

}


LongInt::LongInt(std::vector<int> digits, bool neg) 
    : digits_(digits), neg_(neg) {}


LongInt & LongInt::operator=(const LongInt & num) 
{
    if (this == &num) return (*this);

    neg_ = num.neg_;
    digits_ = num.digits_;

    return (*this);
}


LongInt & LongInt::operator=(int num) { return (*this) = LongInt(num); }


LongInt & LongInt::operator++() { return (*this) += 1; }
LongInt & LongInt::operator--() { return (*this) -= 1; }


LongInt LongInt::operator++(int num) 
{
    LongInt ret = (*this); 
    ++(*this);
    return ret;
}


LongInt LongInt::operator--(int num) 
{
    LongInt ret = (*this);
    --(*this);
    return ret;
}


LongInt LongInt::operator-() const {
    LongInt ret; 
    ret.digits_ = digits_;
    ret.neg_ = !neg_;

    return ret;
}


LongInt LongInt::pos() const 
{
    LongInt ret = (*this);
    ret.neg_ = false;
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
    for (int i = 0; i < max_idx; ++i) {
        int digit = digits_[i] + num.digits_[i] + carry;
        if (digit >= 10) {
            carry = 1;
            digits_[i] = digit - 10;
        } else {
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
            } else {
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


LongInt LongInt::slow_mult(const LongInt & num) const 
{
    LongInt ret = (*this).pos();
    for (LongInt i = 1; i < num.pos(); ++i) {
        ret += (*this).pos(); 
    }

    if (neg_ != num.neg_) { ret.neg_ = true; }
    else { ret.neg_ = false; }
    return ret;
}


LongInt LongInt::colm_mult(const LongInt & num) const 
{
    // Hacky looking but effectively correct
    LongInt multiplicand;
    LongInt multiplier;

    if ((*this).digits_.size() < num.digits_.size()) {
        multiplier = (*this).pos();
        multiplicand = num.pos();
    } else {
        multiplier = num.pos();
        multiplicand = (*this).pos();
    }


    LongInt ret;
    for (int i = 0; i < multiplier.digits_.size(); ++i) {
        LongInt sum;
        for (int k = 0; k < i; ++k) { sum.digits_.push_back(0); }

        int carry = 0;
        for (int j = 0; j < multiplicand.digits_.size(); ++j) {
            int digit = multiplicand.digits_[j] * multiplier.digits_[i] + carry;
            if (digit >= 10) {
                carry = digit / 10;
                digit %= 10;
            } else {
                carry = 0;
            }

            // Hack to fix a bug
            if (j == 0) {
                sum.digits_[i] = digit;
            } else {
                sum.digits_.push_back(digit);
            }
        }
        if (carry != 0) sum.digits_.push_back(carry);
        ret += sum;
    }
    
    if (neg_ != num.neg_) { ret.neg_ = true; }
    else { ret.neg_ = false; }

    return ret;
}


LongInt LongInt::karatsuba(const LongInt & num) const
{
    if (digits_.size() == 1 || num.digits_.size() == 1) {
        return colm_mult(num);
    }

    if (num == 0) return 0;
    
    LongInt rh(num);
    LongInt lh(*this);

    // Make them the same size
    if (digits_.size() < rh.digits_.size()) {
        lh.add_leading_zeros(rh.digits_.size() - lh.digits_.size());
    } else {
        rh.add_leading_zeros(lh.digits_.size() - rh.digits_.size());
    }

    int mid = lh.digits_.size() / 2; 

    // Splitting the numbers up
    std::vector<int> Xl, Xr;
    std::vector<int> Yl, Yr;
    for (int i = 0; i < mid; ++i) {
        Xr.push_back(lh.digits_[i]);
        Yr.push_back(rh.digits_[i]);
    } 
    LongInt xR(Xr);
    LongInt yR(Yr);

    for (int i = mid; i < lh.digits_.size(); ++i) {
        Xl.push_back(lh.digits_[i]);
        Yl.push_back(rh.digits_[i]);
    }
    LongInt xL(Xl);
    LongInt yL(Yl);

    LongInt t1 = LongInt(Xl).karatsuba(LongInt(Yl));
    LongInt t2 = LongInt(Xr).karatsuba(LongInt(Yr));
    LongInt t3 = (LongInt(Xl) + LongInt(Xr)).karatsuba((LongInt(Yl) + LongInt(Yr))) 
        - t1 - t2;


    LongInt ret = t1.insert_trailing_zeros((mid * 2)) + t3.insert_trailing_zeros(mid) +
            t2;

    ret.remove_leading_zeros();

    if (neg_ != num.neg_) { 
        ret.neg_ = true;
    }

    return ret;
}



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
    while ((*it) == 0 && it != digits_.begin()) {
        digits_.erase(it);
        it = digits_.end() - 1;
    }
}


void LongInt::add_leading_zeros(int num) 
{
    for (int i = 0; i < num; ++i) {
        digits_.push_back(0);  
    }
}


LongInt & LongInt::insert_trailing_zeros(int num) 
{
    std::vector<int> new_digits; 
    for (int i = 0; i < num; ++i) { 
        new_digits.push_back(0);
    }


    for (int i = 0; i < digits_.size(); ++i) {
        new_digits.push_back(digits_[i]);
    }

    digits_ = new_digits;

    return (*this);
}


std::ostream & operator<<(std::ostream & os, const LongInt & num)
{
    if (num.neg_) { os << "-"; }
    
    for (int i = num.digits_.size() - 1; i >= 0; --i) {
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
        num.digits_.push_back(input[i] - '0');
    }

    return is;
}
