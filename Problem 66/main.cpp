#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>

#include "num.hpp"

using ull = Num;
using ld = long double;

std::pair<ull, ull> solve(size_t input)
{
	Num limit = sqrt(input);
	Num m = 0;
    Num d = 1;
    Num val = limit;

	ull num1{1}, denum1{0};
	ull num{val}, denum{1};

	const ull D{int(input)};
	static const ull goal{1};

	if(limit*limit != D)
	{
		do
		{
			m   = d * val - m;
	        d   = (D - m * m) / d;
	        val = (limit + m) / d;

			ull num2 = num;
			ull denum2 = denum;

			num = val*num + num1;
			denum = val*denum + denum1;

			num1 = num2;
			denum1 = denum2;
		} while((num*num) - (denum*denum) * D != goal);
	}

	return std::pair<ull, ull>(num, denum);
}


int main()
{
	ull max{0};
	size_t max_idx{0};

	for(size_t i = 3; i <= 1e3; ++i)
	{
		auto pair = solve(i);
		if(pair.first > max)
		{
			max = pair.first;
			max_idx = i;
		}
	}

	std::cout << max_idx << std::endl;

	return 0;
}