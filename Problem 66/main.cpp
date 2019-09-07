#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>


using ull = unsigned long long;
using ld = long double;


std::pair<ull, ull> getInfFract(long double val, size_t iterations)
{
	std::vector<ull> a;

	ull p{1}, q{1};

	for (size_t i = 0; i < iterations; ++i)
	{
		a.push_back(floor(val));
		if (a.back() == 0)
		{
			break;
		}

		val = 1.0f/(val - static_cast<ld>(a.back()));
	}

	if (!a.empty())
	{
		q = a.back();
		for(auto it = a.crbegin() + 1; it != a.crend(); ++it)
		{
			p += (*it) * q;
			std::swap(p, q);
		}
		std::swap(p, q);
	}

	return std::pair<ull, ull>(p, q);
}

std::pair<ull, ull> solve(ull m)
{
	ld sqrt_of_m = sqrtl(m);
	
	if(sqrt_of_m != floor(sqrt_of_m))
	{
		for(int i = 2; i < 1e4; ++i)
		{
			auto pair = getInfFract(sqrt_of_m, i);
			if((pair.first*pair.first) - (pair.second*pair.second) * m == 1)
			{
				return pair;
			}
		}
	}

	return std::pair<ull, ull>(0, 0);
}


int main()
{
	ull max{0};

	for(ull i = 3; i <= 1e3; ++i)
	{
		std::cout << i << std::endl;
		auto pair = solve(i);
		if(pair.first > max)
		{
			max = pair.first;
		}
	}

	std::cout << max << std::endl;

	return 0;
}