#include <iostream>

using ull = unsigned int;


inline ull getReversed(ull n) {
    ull m = 0;
    while(n>0) {
        m *= 10;
        m += (n % 10);
        n /= 10;
    }
    return m;
}

inline bool isReversible(ull value) {
	value += getReversed(value);

	do {
		if(!(value & 1)) {
			return false;
		}
	} while(value/=10);

	return true;
}

int main() {
	int result = 0;

	for(ull i = 11; i < 1e9; i += 2) {
		if(i % 10 != 0 && isReversible(i)) {
			result += 2;
		}
	}

	std::cout << result << std::endl;

	return 0;
}