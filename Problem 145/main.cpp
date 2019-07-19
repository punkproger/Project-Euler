#include <iostream>

using ull = unsigned int;

const ull tens[] = {
	0,
	1,
	10,
	100,
	1000,
	10000,
	100000,
	1000000,
	10000000,
	100000000,
};

inline ull digitsCount( int x )
{
	ull answer = 0 ;
	while(x)
	{
		++answer ;
		x /= 10 ;
	}
	return answer ;
}

ull getReversed(ull value) {
	auto digits = digitsCount(value);
	ull result = 0;

	do {
		result += (value%10) * tens[digits];
		value /= 10; 
	} while(--digits);

	return result;
}

inline bool isReversible(ull value) {
	ull digits = digitsCount(value);

	ull copyForRev = value;
	ull fromLast = 0; 
	ull newValue = 0; 
	ull tmp;

	do {
		tmp = (value%10) + (copyForRev/tens[digits])+fromLast;
		newValue = tmp%10;
		fromLast = tmp/10;

		value /= 10;
		copyForRev %= tens[digits];

		if(!(newValue & 1)) {
			return false;
		}
	} while(--digits);

	return true;
}

int main() {
	int result = 0;

	for(ull i = 11; i < 1e9; ++i) {
		if(i % 10 != 0 && isReversible(i)) {
			++result;
		}
	}

	std::cout << result << std::endl;

	return 0;
}