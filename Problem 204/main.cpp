#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>


using ull = unsigned long long;


std::vector<ull> getPrimes(ull max){
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


size_t hammingNumbersCount(size_t factor, ull limit)
{
	const auto primes = getPrimes(factor);
	const auto primes_size = primes.size();
	
	size_t result{0};

	std::function<void(ull, size_t)> impl;
	
	impl = [&primes, &impl, &result, limit, primes_size]
	(ull value, size_t current_prime_idx)
	{
		++result;

		for (size_t idx = current_prime_idx; idx < primes_size; ++idx)
		{
			if (value * primes[idx] > limit)
			{
				return;
			}

			impl(value * primes[idx], idx);
		}
	};

	impl(1, 0);

	return result;
}


int main()
{
	std::cout << hammingNumbersCount(100, 1e9) << std::endl;
	/*for(auto val : getPrimes(5))
	{
		std::cout << val << std::endl;
	}*/
	return 0;
}