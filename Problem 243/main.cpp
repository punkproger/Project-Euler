#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using ull = long long;

ull phi(ull x, const std::vector<ull>& primes)
{
  auto result  = x;
  auto reduced = x;
  for (auto p : primes)
  {
    if (p*p > reduced)
      break;

    if (reduced % p != 0)
      continue;

    do
    {
      reduced /= p;
    } while (reduced % p == 0);

    result -= result / p;
  }

  if (reduced > 1)
    result -= result / reduced;

  return result;
}

int main()
{
	constexpr ull c_size{static_cast<ull>(1e9)};
	constexpr double c_necessary_ratio{15499.0/94744.0};
	std::vector<ull> primes;
	ull result{-1}, current{1};

	for (ull i = 2;; ++i)
	{
		bool is_prime{true};

		for (auto prime : primes)
		{
			if (prime*prime > i)
			{
				break;
			}
			if (i % prime == 0)
			{
				is_prime = false;
				break;
			}
		}

		if (!is_prime)
		{
			continue;
		}

		primes.push_back(i);	
		current *= i;
		if (phi(current, primes)/static_cast<double>(current-1) < c_necessary_ratio)
		{
			break;
		}
	}

	current /= primes.back();

	for (ull i = 1;; ++i)
	{
		ull next = current*i;

		if (static_cast<double>(phi(next, primes))/static_cast<double>(next-1) < c_necessary_ratio)
		{
			result = next;
			break;
		}
	}

	std::cout << result << std::endl;

	return 0;
}
