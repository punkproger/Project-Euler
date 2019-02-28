#include <iostream>
#include <cmath>


using ull = unsigned long long;


ull binpow(ull base, ull exp)
{
    ull result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}


ull findBiggestRemainder(ull a) {
	ull result{0}, limit{binpow(a, 2)}, l{a-1}, r{a+1}, c_l{l}, c_r{r}, max{0};
	for(int i = 0; i <= a; ++i) {
		if(((2 * a * i)%limit) > max) {
			max = ((2 * a * i)%limit);
		}
	}

	return max;
}


int main() {
	ull result{0};
	for(int i = 3; i <= 1000; ++i) {
		result += findBiggestRemainder(i); 
	}

	std::cout << result << std::endl;
	return 0;
}