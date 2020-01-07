#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>

using ull = unsigned int;

inline std::vector<ull> get_primes(ull max){
    std::vector<ull> primes;
    char *sieve;
    sieve = new char[max/8+1];
    // Fill sieve with 1  
    memset(sieve, 0xFF, (max/8+1) * sizeof(char));
    for(ull x = 2; x <= max; x++)
        if(sieve[x/8] & (0x01 << (x % 8))){
            primes.push_back(x);
            // Is prime. Mark multiplicates.
            for(ull j = 2*x; j <= max; j += x)
                sieve[j/8] &= ~(0x01 << (j % 8));
        }
    delete[] sieve;
    return primes;
}

int main()
{
	constexpr ull c_limit = static_cast<ull>(1e8);
	auto primes = get_primes(c_limit/2 + 100);
	const ull c_loop_limit = sqrt(primes.size());
	ull result{0};

	for (ull i = 0; i <= c_loop_limit ; ++i)
	{
		auto from = primes.begin() + i;
		auto to = std::upper_bound(from, primes.end(), c_limit/primes[i]);

		result += std::distance(from, to);
	}

	std::cout << result << std::endl;

	return 0;
}