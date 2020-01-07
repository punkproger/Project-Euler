#include <iostream>
#include <cmath>
#include <unordered_map>

using ull = int;

inline ull getTylesCount(ull n, ull n_hole)
{
	return n*n - n_hole*n_hole;
}

inline ull getLType(ull tyles)
{
	constexpr ull c_limit = 1000000;
	ull i, j, result{0};

	const ull i_start = sqrt(tyles);

	for (i = i_start;; i += 1)
	{
		const ull j_lim = (i%2 == 0 ? 2 : 1);
		const ull j_start = (i%2 == 0 ? 2 : 1);


		/*if (getTylesCount(i, j_lim) < tyles)
		{
			continue;
		}*/
		if (getTylesCount(i, i-2) > tyles)
		{
			break;
		}

		for (j = i-2; j >= j_lim; j -= 2)
		{
			ull t = getTylesCount(i, j);
			
			if (t == tyles)
			{
				++result;
			}
			else if (t > tyles)
			{
				break;
			}
		}
	}

	return result;
}

int main()
{

	int result{0};
	for (ull i = 8; i <= 1000000; i += 4)
	{
		ull tyles = getLType(i);
		if (tyles >= 1 && tyles <= 10)
		{
			++result;
		}
	}

	std::cout << result << std::endl;

	return 0;
}