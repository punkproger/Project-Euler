#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


int main()
{
	std::vector<std::string> start_sms{"6", "10", "9", "8", "7"};
	std::vector<std::string> another_symbols{"1", "2", "3", "4", "5"};
	std::string max_str, tmp;

	const auto elements_equal = [](const std::vector<int>& v)
	{
		for (int i = 0; i < v.size()-1; ++i)
		{
			if (v[i] != v[i+1])
			{
				return false;
			}
		}
		return true;		
	};

	do
	{
		std::vector<int> values(start_sms.size(), 0);
		tmp.clear();

		for (int i = 0; i < start_sms.size(); ++i)
		{
			std::string part_tmp;

			part_tmp += start_sms[i];
			part_tmp += another_symbols[i];
			part_tmp += another_symbols[(i+1) % 5];

			values[i] += std::stoi(start_sms[i]);
			values[i] += std::stoi(another_symbols[i]);
			values[i] += std::stoi(another_symbols[(i+1) % 5]);

			tmp += part_tmp;
		}

		if (max_str.empty() ||
			(tmp.size() == 16 &&
			 tmp > max_str &&
			 elements_equal(values)))
		{
			max_str = tmp;
		}
	} while(std::next_permutation(another_symbols.begin(), 
								  another_symbols.end()));

	std::cout << max_str << std::endl;

	return 0;
}