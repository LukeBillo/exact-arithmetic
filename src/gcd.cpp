#include "gcd.h"

namespace ExactArithmetic
{
    long long int gcd(long long int i, long long int j)
    {
        if (i == 0)
            return j;

        return gcd(j % i, i);
    }
}
