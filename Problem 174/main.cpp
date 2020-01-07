#include <iostream>
#include <array>
#include <algorithm>

using ull = int;


int main()
{
	constexpr ull c_limit{1000001};
	constexpr ull c_square_limit{250002};

	std::array<ull, c_limit> N;
	N.fill(0);
	std::array<ull, c_square_limit> squares;

	for (ull i = 1; i < squares.size(); ++i)
	{
		squares[i] = i*i;
	}

	for (ull i = 3; i < c_square_limit; ++i)
	{
		for (ull j = i-2; j > 0 && squares[i] - squares[j] < c_limit; j -= 2)
		{
			++N[squares[i] - squares[j]];
		}
	}

	ull result{0};
	for (ull i = 0; i < N.size(); ++i)
	{
		if (N[i] >= 1 && N[i] <= 10)
		{
			++result;
		}
	}


	std::cout << result << std::endl;

	return 0;
}