#include <iostream>
#include <vector>
#include <cmath>

size_t getValueOfRow(size_t row)
{
	size_t max_pow = log(row)/log(7);
	size_t pow_val = pow(7, max_pow);
	size_t res{1};

	while (pow_val != 0)
	{
		res *= (1+row/pow_val);
		row %= pow_val;
		pow_val /= 7;
	}

	return res;
}

size_t findSolution(size_t size)
{
	size_t items{0}, result{0};

	while (items+7 < size)
	{
		size_t part_items{1}, part_result{getValueOfRow(items)};

		while ((items + part_items * 7) < size)
		{
			part_result *= 4 * 7;
			part_items *= 7;
		}

		items += part_items;
		result += part_result;
	}
	


	size_t idx = items;

	for (size_t i = idx; i < size; i+=1)
	{
		result += getValueOfRow(i);
	}

	return result;
}

int main()
{
	constexpr size_t c_size{static_cast<size_t>(1e9)};

	std::cout << findSolution(c_size) << std::endl;

	return 0;
}