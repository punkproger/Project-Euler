#include <iostream>
#include <string>
#include <cmath>
#include <cstdint>

const __int128 cutted_limit = pow(10, 28); 
constexpr size_t size = 1000000;

const long double fi = 1.6180339887498948482045868343656381177203;
const long double fiveSqrt = sqrt(5);


size_t countDigits(__int128 number) {
	size_t digs{0};
	
	do {
		++digs;

	} while(number/=10);

	return digs;
}

__int128 fitToNine(__int128 number) {
	if(number < 100000000) {
		return number;
	}

	while(countDigits(number) != 9) {
		number /= 10;
	}

	return number;
}

unsigned long int getFirstNine(size_t idx) {
	long double l_res{1}, r_res{1}, res;
	size_t step{2};
	while(idx > step) {
		l_res *= pow(fi, step);
		if(l_res > 1000000000) {
			l_res /= 10.0f;
		}
		idx -= step;
	}
	l_res *= pow(fi, idx);
	
	res = fitToNine((l_res)/fiveSqrt);
	return res;
}

inline bool isPandigital(unsigned long long int number) {
	int arr[10] = {0};
	if(number < 123456789) {
		return false;
	}

	for(int i = 0; i < 9; ++i) {
		++arr[(number%10)];
		number /= 10;
	}
	
	if(arr[0] != 0) {
		return false;
	}

	for(int i =1; i < 10; ++i) {
		if(arr[i] != 1) {
			return false;
		}
	}

	return true;
}

int main() {
	unsigned long long int a{1}, b{1}, c{2}, limit{10000000000}, it{100};
	size_t idx = 2;

	while(true) {
		++idx;
		c = a + b;
		a = b;
		b = c;

		a %= limit;
		b %= limit;
		c %= limit;

		if(isPandigital(c) && isPandigital(getFirstNine(idx))) {
			std::cout << idx << std::endl;
			break;
		}
	}
	return 0;
}