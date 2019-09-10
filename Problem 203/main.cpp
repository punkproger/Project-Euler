#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cstring>


using ull = unsigned int;
using long_type = unsigned long long;

std::vector<ull> get_primes(ull max){
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


long_type isCSquarefree(size_t n, size_t k, const std::vector<ull>& primes)
{
	long_type result = 0;

	if (n < k)
	{
		return result;
	}

	std::vector<int> prime_divisors(primes.size(), 0);

	int denum_min = std::min(k, n-k);

	for (int i = 0; i < denum_min; ++i)
	{
		int value_low  = 1 + i;
		int value_high = n - i;

		for (int j = 0; j < primes.size() && (value_low != 1 || value_high != 1); ++j)
		{
			while (value_low % primes[j] == 0)
			{
				value_low /= primes[j];
				--prime_divisors[j];
			}

			while (value_high % primes[j] == 0)
			{
				value_high /= primes[j];
				++prime_divisors[j];
			}
		}
	}

	auto found_item = 
		std::find_if(prime_divisors.begin(), prime_divisors.end(), [](int count) {return count > 1;});

	if (found_item == prime_divisors.end())
	{
		result = 1;

		for(int i = 0; i < prime_divisors.size(); i++)
		{
			result *= pow(primes[i], prime_divisors[i]);
		}
	}

	return result;
}


int main()
{
	long_type result{0}, val;
	constexpr int rows{50};
	const auto primes = get_primes(rows);
	std::set<long_type> known_values;

	for (int i = 0; i <= rows/2; ++i)
	{
		for (int j = i*2; j <= rows; ++j)
		{
			val = isCSquarefree(j, i, primes);

			if (known_values.find(val) == known_values.end())
			{
				result += val;
				known_values.insert(val);
			}

		}
	}

	std::cout << result << std::endl;

	return 0;
}