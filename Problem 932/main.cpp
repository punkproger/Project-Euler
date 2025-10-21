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

using ull = unsigned long long;
using ld = long double;

static inline ull pow10_u(int d){
    static const ull p10[20] = {
        1ULL,10ULL,100ULL,1000ULL,10000ULL,100000ULL,1000000ULL,10000000ULL,100000000ULL,1000000000ULL,
        10000000000ULL,100000000000ULL,1000000000000ULL,10000000000000ULL,100000000000000ULL,
        1000000000000000ULL,10000000000000000ULL,100000000000000000ULL,1000000000000000000ULL,0ULL
    };
    return p10[d];
}

ull count_T(ull n)
{
    ull result{0};
    ull current_pow_10 = 1;
    ull current_max_pow_10 = 10;

    for (ull digs_ = 2; digs_ <= n; ++digs_)
    {
        ull digs_a{digs_ / 2}, digs_b{digs_ / 2 + digs_ % 2};
        for (ull a = pow10_u(digs_a-1); a < pow10_u(digs_a); ++a)
        {
            ull min_x = (pow10_u(digs_b) * a + pow10_u(digs_b-1));
            ull min_b = std::max(ull(sqrt(min_x)) - a, pow10_u(digs_b-1));

            for (ull b = min_b; b < pow10_u(digs_b); ++b)
            {
                ull calculated = a*a + 2*a*b + b*b;
                ull concatenated = pow10_u(digs_b) * a + b;

                if (calculated > concatenated)
                {
                    break;
                }

                if (calculated == concatenated)
                {
                    result += calculated;
                    // std::cout << calculated << " = " << a << "^2 + " << b << "^2" << " : " << result << std::endl; 
                    // std::cout << concatenated << " " << calculated << " --- " << a << " " << b << std::endl;
                }
            }
        }
    }

    return result;
}

int main()
{
    std::cout << count_T(16) << std::endl;
    return 0;
}
