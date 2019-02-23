#include <iostream>
#include <cmath>

size_t countDigits(size_t number) {
	size_t digs{0};
	
	do {
		++digs;

	} while(number/=10);

	return digs;
}


int main() {
	size_t result{0}, limit{100};
	for(double x = 0; x <= limit; ++x) {
		for(double y = 1; y <= limit; ++y) {
			size_t digits{countDigits(pow(x, y))};
			if(digits > y) {
				break;
			} else if(digits < y) {
				continue;
			} else {
				++result;
			}
		}
	}

	std::cout << result << std::endl;

	return 0;
}