#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <cmath>

bool isPrime(unsigned int number)
{
	unsigned int limit = sqrt(number);
	for(int i = 2; i <= limit; i++)
	{
		if(number % i == 0)
		{
			return false ;
		}
	}

	return true ;
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
	size_t iterations{0};

	std::vector<int> digits{1,2,3,4,5,6,7,8,9};

	do {
		for(const auto& seq : seqs)
		{
			int size = 0;
			bool breaked{false};

			for(int digs : seq)
			{
				unsigned int value{0};
				unsigned int tens{1};

				for(int i = (size + digs) - 1; i >= size; --i)
				{
					value += tens * digits[i];
					tens *= 10;
				}

				size += digs;

				if(!isPrime(value))
				{
					breaked = true;
					break;
				}
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