#include <iostream>
#include <ctime>

bool isDigitsMoreInFirst(int first, int second)
{
	while((first/=10) && (second/=10)) 
	{}

	return first;
}

int main()
{
	int result = 0;
	unsigned long long int numerator = 1, denumerator = 1, last_denumerator = 1;

	for( int i = 0; i <= 1000; ++i) 
	{
		last_denumerator = denumerator;
		denumerator 	 = last_denumerator + numerator;
		numerator   	 = last_denumerator + denumerator;

		if(isDigitsMoreInFirst(numerator, denumerator))
		{
			++result;
		}

		if(numerator > (1 << 24)) { //approximation
			numerator /= 10;
			denumerator /= 10;
			last_denumerator /= 10;
		}
	}

	std::cout << result << std::endl;
	std::cout << "runtime = " << clock()/1000000.0f << "s" << std::endl;

	return 0;
}