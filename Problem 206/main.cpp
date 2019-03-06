#include <iostream>
#include <string>
#include <cmath>


using ull = unsigned long long int;

inline bool isOkay(ull num) {
	if(num%10 != 0) {
		return false;
	}
	num /= 100;

	for(int i = 9; i >= 1; --i) {
		if(num % 10 != i) {
			return false;
		}
		num /= 100;
	}

	return true;
}


int main() {
	ull result, a = sqrt(1020304050607080900), b = sqrt(1929394959697989990);
	for(a; a <= b; a+=10) {
		if(isOkay(a*a)) {
			result = a;
			break;
		}
	}
	
	std::cout << result << std::endl;

	return 0;
}