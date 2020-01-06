#include <iostream>

using ull = int;

inline ull getTylesCount(ull n, ull n_hole)
{
	return n*n - n_hole*n_hole;
}

int main()
{
	constexpr ull c_limit = 1000000;

	ull i, j, result{0};
	for (i = 3;; i += 1)
	{
		const ull j_lim = (i%2 == 0 ? 2 : 1);
		
		for (j = i-2; j >= j_lim; j -= 2)
		{
			if (getTylesCount(i, j) <= c_limit)
			{
				++result;
			}
			else
			{
				break;
			}
		}
		if (getTylesCount(i, i-2) > c_limit)
		{
			break;
		}
	}

	std::cout << result << std::endl;

	return 0;
}