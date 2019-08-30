#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cmath>

bool isPrime(int n) {
	if (n < 2)
	    return false;
	if (n < 4)
	    return true;
	if (n % 2 == 0)
	    return false;
	if (n < 9)
	    return true;
	if (n % 3 == 0)
	    return false;
	if (n < 25)
	    return true;

	int s = sqrt(n);
	for (int i = 5; i <= s; i += 6)
	{
	    if (n % i == 0)
	    {
	        return false;
	    }
	    if (n % (i + 2) == 0)
	    {
	        return false;
	    }
	}

return true;
}

std::vector<std::vector<int>> getAllSeq(size_t elements)
{
	std::vector<std::vector<int>> seqs;

	std::function<void(size_t, size_t, std::vector<int>)> impl;
	impl = [&impl, &seqs](size_t elements, size_t max, std::vector<int> seq)
	{
		for(auto i = max; i <= elements; ++i)
		{
			if(i < elements)
			{
				auto vec = seq;
				vec.push_back(i);
				impl(elements-i, i, vec);
			}
			else if(i == elements)
			{
				seq.push_back(i);
				seqs.push_back(std::move(seq));
				return;
			}
			else
			{
				return;
			}
		}
	};

	impl(elements, 1, std::vector<int>());

	return seqs;
}


size_t getPrimeSeqsCount(const std::vector<std::vector<int>>& seqs)
{
	size_t result{0};

	std::vector<int> digits{1,2,3,4,5,6,7,8,9};

	do {
		for(const auto& seq : seqs)
		{
			int size{0};
			int prev_value{0};
			bool breaked{false};

			for(int digs : seq)
			{
				unsigned int value{0};

				for(int i = size; i < size + digs; ++i)
				{
					value = value * 10 + digits[i];
				}

				if(prev_value > value || !isPrime(value))
				{
					breaked = true;
					break;
				}

				size += digs;
				prev_value = value;
			}


			if(!breaked)
			{
				++result;
			}
		}
	} while (std::next_permutation(digits.begin(), digits.end()));


	return result;
}


int main()
{
	std::cout << getPrimeSeqsCount(getAllSeq(9)) << std::endl;

	return 0;
}