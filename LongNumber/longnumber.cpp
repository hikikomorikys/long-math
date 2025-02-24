#include "longnumber.hpp"
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>

namespace LongMath{
    LongNumber::LongNumber(){
        precision = 100;
	point = 0;
	sign = false;
        bits.push_back(0);
    }

    LongNumber::LongNumber(int number){
        precision = 100;
	point = 0;
	sign = (number < 0);
        if (number < 0) number = -number;
        if (number == 0){
            bits.push_back(0);
            return;
        }
        while (number > 0){
            bits.push_back(number % 2);
            number /= 2;
        }
    }
    LongNumber::LongNumber(std::string binary){
        sign = (binary[0] == '-');
        if (sign) binary.erase(binary.begin());
        auto dot = binary.find('.');
        if (dot != std::string::npos){
            point = binary.length() - dot - 1;
            binary.erase(binary.begin() + dot);
        }
	else{
            point = 0;
        }
        precision = std::max(100u, point + 10);
        for (int i = binary.size() - 1; i >= 0; i--){
            bits.push_back(binary[i] - '0');
        }
        removezeros();
    }
    void LongNumber::removezeros(){
        while (bits.size() > 1 && bits.back() == 0){
            bits.pop_back();
        }
    }
    bool LongNumber::iszero() const{
        return bits.size() == 1 && bits[0] == 0;
    }
    int LongNumber::magnitude() const{
        return bits.size() - point;
    }
    std::string LongNumber::toString() const{
        std::string res = (sign ? "-" : "");
        for (int i = bits.size() - 1; i >= 0; i--){
            res += (bits[i] ? '1' : '0');
            if (i == point && point > 0) res += '.';
        }
        return res;
    }

    LongNumber operator+(const LongNumber &a, const LongNumber &b){
        if (a.sign != b.sign){
            return a.sign ? (b - (-a)) : (a - (-b));
        }
        LongNumber res;
        res.sign = a.sign;
        std::vector<bool> larger = a.bits;
        std::vector<bool> smaller = b.bits;
        if (b.bits.size() > a.bits.size()){
            larger = b.bits;
            smaller = a.bits;
        }
        bool carry = false;
        for (size_t i = 0; i < larger.size(); i++){
            bool sum = larger[i] ^ (i < smaller.size() ? smaller[i] : 0) ^ carry;
            carry = (larger[i] & (i < smaller.size() ? smaller[i] : 0)) | (carry & (larger[i] ^ (i < smaller.size() ? smaller[i] : 0)));
            res.bits.push_back(sum);
        }
        if (carry) res.bits.push_back(true);
        return res;
    }

    LongNumber operator-(const LongNumber &a, const LongNumber &b){
        if (a == b) return LongNumber(0);
        if (a.sign != b.sign) return a + (-b);
        return a;
    }

    LongNumber operator*(const LongNumber &a, const LongNumber &b){
        LongNumber res;
        res.bits.assign(a.bits.size() + b.bits.size(), false);
        res.sign = (a.sign != b.sign);
        for (size_t i = 0; i < b.bits.size(); i++){
            if (b.bits[i]){
                LongNumber temp = a;
                temp.bits.insert(temp.bits.begin(), i, false);
                res = res + temp;
            }
        }
        res.removezeros();
        return res;
    }

    LongNumber operator/(const LongNumber &a, const LongNumber &b){
        if (b.iszero()){
            throw std::runtime_error("Деление на ноль");
        }
        LongNumber res;
        LongNumber remainder;
        res.bits.resize(a.bits.size());
        res.sign = (a.sign != b.sign);
        for (int i = a.bits.size() - 1; i >= 0; i--){
            remainder.bits.insert(remainder.bits.begin(), a.bits[i]);
            remainder.removezeros();
            if (remainder >= b){
                remainder = remainder - b;
                res.bits[i] = 1;
            }
	    else{
                res.bits[i] = 0;
            }
        }
        res.removezeros();
        return res;
    }

    LongNumber LongNumber::operator-() const{
        LongNumber negated(*this);
        negated.sign = !sign;
        return negated;
    }

    bool operator==(const LongNumber &a, const LongNumber &b){
        return a.sign == b.sign && a.bits == b.bits && a.point == b.point;
    }

    bool operator!=(const LongNumber &a, const LongNumber &b){
        return !(a == b);
    }

    bool operator>(const LongNumber &a, const LongNumber &b){
        if (a.sign != b.sign){
            return b.sign;
        }
        if (a.bits.size() != b.bits.size()){
            return (a.bits.size() > b.bits.size()) ^ a.sign;
        }
        for (int i = a.bits.size() - 1; i >= 0; i--){
            if (a.bits[i] != b.bits[i]) {
                return (a.bits[i] > b.bits[i]) ^ a.sign;
            }
        }
        return false;
    }

    bool operator<(const LongNumber &a, const LongNumber &b){
        return (b > a);
    }
}

LongMath::LongNumber operator""_longnum(long double number){
    return LongMath::LongNumber(static_cast<int>(number));
}
