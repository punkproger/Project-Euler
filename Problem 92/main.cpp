#include <iostream>
#include <vector>
#include <ctime>

using uint = unsigned int;
char numbers[568] = {0}; // 9^2 * 7 = 567

inline uint smartSquare(uint num)
{
	uint sum = 0;
	
	while(num != 0)
	{
		uint tmp = num % 10;
		sum += tmp*tmp;
		num /= 10;
	}

	return sum;
}

inline bool isCorrectChain(uint fNum)
{
	std::vector<int> chain;
	chain.reserve(20);

	while(fNum != 1 && fNum != 89)
	{
		if(fNum < 568 && numbers[fNum] != 0)
		{
			return (numbers[fNum] == 1? true : false);
		}

		chain.push_back(fNum);
		fNum = smartSquare(fNum);
	}

	if(fNum == 1)
	{
		for( int i = 0; i < chain.size(); i++)
		{
			if(chain[i] < 568)
			{
				numbers[chain[i]] = -1;
			}
		}
		return false;
	}

	for( int i = 0; i < chain.size(); i++)
	{
		if(chain[i] < 568)
		{
			numbers[chain[i]] = 1;
		}
	}
	return true;
}

int main()
{
	unsigned long long int result = 0;

	for( int i = 2; i < 10000000; ++i)
	{
		if(isCorrectChain(i))
		{
			++result;
		}
	}

	std::cout << result << std::endl ;
	std::cout << "runtime = " << clock()/1000000.0f << "s" << std::endl;

	return 0;
}