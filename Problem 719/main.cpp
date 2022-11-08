#include <iostream>
#include <string>
#include <cmath>
#include <array>

using ull = unsigned long long int;
constexpr ull c_end_value = 1e12;
constexpr ull c_digits_count = 14;
const std::array<ull, 14> c_tens{
	static_cast<ull>(1e1),
	static_cast<ull>(1e2),
	static_cast<ull>(1e3),
	static_cast<ull>(1e4),
	static_cast<ull>(1e5),
	static_cast<ull>(1e6),
	static_cast<ull>(1e7),
	static_cast<ull>(1e8),
	static_cast<ull>(1e9),
	static_cast<ull>(1e10),
	static_cast<ull>(1e11),
	static_cast<ull>(1e12),
	static_cast<ull>(1e13),
	static_cast<ull>(1e14)};

ull count_digits(ull number) {
	ull digits{0};
	
	do
	{
		++digits;
	}
	while(number /= 10);

	return digits;
}

ull get_sum(const std::array<int, c_digits_count>& digits_array, ull from, ull to)
{
	ull sum{0}, multiplier{1};

	for (int i = to; i >= from && i >= 0; --i)
	{
		sum += digits_array[i] * multiplier;
		multiplier *= 10;
	}

	return sum;
}

bool check_is_seq_sum_has_value(const std::array<int, c_digits_count>& digits_array, ull necessary_value,
								ull digits_count, ull min_parts_count, ull start_id)
{
	int sum = -1;
	for (ull i = start_id; i < digits_count; ++i)
	{
		sum = sum == -1 ? digits_array[i] : sum * 10 + digits_array[i];

		if (necessary_value == sum && i == digits_count - 1 && min_parts_count == 1)
		{
			return true;
		}

		if (sum > necessary_value)
		{
			return false;
		}

		if (check_is_seq_sum_has_value(digits_array, necessary_value - sum, digits_count, 1, i + 1))
		{
			return true;
		}
	}

	return false;
}

bool is_okay(ull square, ull root)
{
	std::array<int, c_digits_count> digits_array = {-1};
	const ull digits_count = count_digits(square);
	ull last_digit_id = digits_count - 1;

	ull square_copy{square};
	while (square_copy > 0)
	{
		digits_array[last_digit_id] = square_copy % 10;
		square_copy /= 10;
		--last_digit_id;
	}

	return check_is_seq_sum_has_value(digits_array, root, digits_count, 2, 0);
}

int main()
{
	ull current_value{4}, result{0}, counter{1};

	while (current_value * current_value <= c_end_value)
	{
		if (is_okay(current_value * current_value, current_value))
		{
			result += current_value * current_value;
		}

		if (current_value * current_value > pow(10, counter))
		{
			++counter;
		}

		++current_value;
	}
	
	std::cout << result << std::endl;

	return 0;
}
