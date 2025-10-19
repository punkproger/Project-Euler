#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <cstring>
#include <array>
#include <numeric>
#include <limits>

using ll = long long;
constexpr ll c_limit{1000000};


/* Based on:
    x^2 - y^2 - z^2 = n, n > 0, n < 1000000
    x^2 - (x - e)^2 - (x - 2 * e)^2 = n
    x^2 - (x^2 - 2*x*e + e^2) - (x^2 - 2*x*(2*e) + (2*e)^2) = n
    2*x*e - e^2 - x^2 + 4*x*e - 4e^2 = n
    2*x*e - x^2 + 4*x*e - 5e^2 = n
    -x^2 + 6xe -5e^2 = n
*/

int main() {
    std::array<ll, c_limit> distinct_solutions_counter({0});
    double min{10000}, max;
    for (ll x = 4; x < c_limit*1.5; ++x)
    {
        ll e = x / 2;

        if (x > 30000) e = x / 4.95;

        for (;e > 0; --e)
        {
            ll n = -x*x + 6*x*e - 5*e*e;

            ll y = x - e;
            ll z = y - e;

            if (n < 0)
            {
                break;
            }

            if (n > 0 && n < c_limit && y > 0 && z > 0)
            {
                ++distinct_solutions_counter[n];
            }
        }
    }

    ll result{0};

    for (auto count : distinct_solutions_counter)
    {
        if (count == 10)
        {
            ++result;
        }
    }

    std::cout << result << std::endl;

    return 0;
}
