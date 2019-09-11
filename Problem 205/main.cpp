#include <iostream>
#include <iomanip>
#include <vector>


using ull = unsigned long long;
using ld = long double;


// TODO: Can be made better by Newton's binomial
std::vector<ull> exp_polynome(const std::vector<ull>& polynom, size_t exp)
{
	auto result = polynom;
	result.resize((polynom.size()-1)*exp + 1);

	for (size_t i = 1; i < exp; ++i)
	{
		auto prev_value = std::vector<ull>(result.size(), 0);

		for (size_t j = 1; j < polynom.size(); ++j)
		{
			for (size_t k = 1; k < result.size(); ++k)
			{
				prev_value[j+k] += polynom[j] * result[k];
			}
		}

		result = std::move(prev_value);
	}

	return result;
}


std::vector<ull> countDiceCasesPerValues(size_t dice_count, size_t dice_max)
{
	std::vector<ull> origin(dice_max+1, 1);
	origin[0] = 0;

	return exp_polynome(origin, dice_count);
}


int main()
{
	ull win_count{0}, all_count{0};

	auto nine_four = countDiceCasesPerValues(9, 4);
	auto six_six = countDiceCasesPerValues(6, 6);

	for (size_t i = 0; i < nine_four.size(); ++i)
	{
		for (size_t j = 0; j < i; ++j)
		{
			win_count += nine_four[i] * six_six[j];
		}

		for (size_t j = 0; j < six_six.size(); ++j)
		{
			all_count += nine_four[i] * six_six[j];
		}
	}

	std::cout << std::setprecision(7) << ld(win_count)/ld(all_count) << std::endl;

	return 0;
}