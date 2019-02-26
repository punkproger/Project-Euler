#include <iostream>
#include <string>
#include <cmath>

using ull = unsigned long long;

size_t countDigits(ull number) {
	size_t digs{0};
	
	do {
		++digs;

	} while(number/=10);

	return digs;
}

bool haveSameNumbers(ull f_num, ull s_num) {
	int f_digs[10] = {0};
	int s_digs[10] = {0};

	while(f_num) {
		++f_digs[f_num%10];
		f_num /= 10;
	}

	while(s_num) {
		++s_digs[s_num%10];
		s_num /= 10;
	}
	for(int i = 0; i < 10; ++i) {
		if(f_digs[i] != s_digs[i]) {
			return false;
		}
	}

	return true;
}

bool isPermutedMultiple(ull number) {
	for(ull i = 2; i <= 6; ++i) {
		if(!haveSameNumbers(number, number * i)) {
			return false;
		}
	}

	return true;
}

int main() {
	ull current = 123;

	for(current;;++current) {
		if(countDigits(current) != countDigits(current * 6)) {
			current = pow(10, countDigits(current));
			continue;
		}
		if(isPermutedMultiple(current)) {
			break;
		}
	}

	std::cout << current << std::endl;

	return 0;
}