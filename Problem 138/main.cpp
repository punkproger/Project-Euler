#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <array>
#include <numeric>
#include <limits>
#include <set>
#include <algorithm>
#include <unordered_set>

using ull = __uint128_t;

std::ostream& operator << (std::ostream& os, ull val)
{
    std::string result;
    bool is_negative = val < 0;
    if (is_negative)
    {
        val *= -1;
    }

    do
    {
        result.push_back((val % 10) + '0');
        val /= 10;
    }
    while (val != 0);

    if (is_negative)
    {
        result.push_back('-');
    }

    std::reverse(result.begin(), result.end());
    return (os << result);
}

static inline bool isSquare128(ull n) {
    if (n < 2) return true;
    long double rt = sqrt((long double)n);
    ull r = (ull)llround(rt);
    return r*r == n || (r+1)*(r+1) == n || (r-1)*(r-1) == n;
}

/* Based on:
    L = sqrt(5*b^2/4 + 2*b + 1)
    L = sqrt(5*b^2/4 - 2*b + 1)
*/

ull gcd( ull first , ull second )
{
	if( first % second == 0 )
		return second ;
	return gcd( second , first % second ) ;
}

int main_stable() {
    ull counter{0}, result{0};
    std::cout.precision(30);
    for (ull b = 4;counter < 12; b += 2)
    {
        ull five_b_p2 = 5*b*b;

        if (five_b_p2%4 == 0)
        {
            ull res_1 = five_b_p2/4 + 2*b + 1;
            ull res_2 = five_b_p2/4 - 2*b + 1;
            if (isSquare128(res_1))
            {
                ull L = sqrt((long double)res_1);
                std::cout << L << " " << b << " " << b + 1 << std::endl;
                std::cout << "GCD: " << gcd(L, b/2) << " " << gcd(b/2, b + 1) << " " << gcd(L, b + 1) << std::endl;
                ++counter;
                result += L;
            }

            if (isSquare128(res_2))
            {
                ull L = sqrt((long double)res_2);
                std::cout << L << " " << b << " " << b - 1 << std::endl;
                std::cout << "GCD: " << gcd(L, b/2) << " " << gcd(b/2, b - 1) << " " << gcd(L, b - 1) << std::endl;
                ++counter;
                result += L;
            }

        }
    }

    std::cout << result << std::endl;

    return 0;
}


int main() {
    ull counter{0}, result{0}, prev_m{0};
    std::cout.precision(30);

    for (ull m = 4;counter < 12; ++m)
    {

        ull n = 1;
        if (prev_m != 0)
        {
            n = prev_m;
        }

        for (;n < m; ++n)
        {

            if (gcd(m, 1) != 1)
            {
                continue;
            }

            ull a = m*m - n*n;
            ull h = 2*m*n;
            ull L = m*m+n*n;

            if (a > h)
            {
                std::swap(a, h);
            }


            if ((h-a*2 == 1 || h-a*2 == -1) && gcd(a*2, h) == 1 && gcd(a*2, L) == 1 && gcd(L, h) == 1)
            {
                //std::cout << a << " " << h << " " << L << " --- " << m << " " << n << " " << (double)m/n << std::endl;
                result += L;
                ++counter;
                prev_m = m;
            }

            if (prev_m == n) break;
        }
    }

    std::cout << result << std::endl;

    return 0;
}
