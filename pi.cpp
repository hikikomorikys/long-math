#include "longnumber.hpp"
#include "iostream"

namespace PI
{
    LongMath::LongNumber pi(int precision)
    {
        LongMath::LongNumber pi{0, precision};
        LongMath::LongNumber n0{1, precision};
        LongMath::LongNumber n = 16_ln;
        LongMath::LongNumber a0{4, precision};
        LongMath::LongNumber b0{2, precision};
        LongMath::LongNumber c0{1, precision};
        LongMath::LongNumber d0{1, precision};
        LongMath::LongNumber a = 1_ln;
        LongMath::LongNumber b = 4_ln;
        LongMath::LongNumber c = 5_ln;
        LongMath::LongNumber d = 6_ln;
        if (precision == 0){
            pi += 3_ln;
        }
        for (auto i = 0; i < precision; i++){
            pi += n0*(a0 / a - b0 / b - c0 / c - d0 / d);
            n0 /= n;
            a += 8_ln;
            b += 8_ln;
            c += 8_ln;
            d += 8_ln;
        }
        return pi;
    }
}
