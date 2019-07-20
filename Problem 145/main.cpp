#include <iostream>

using ull = int;


ull getReversed(ull value) {
    ull reversed = 0;
    while(value > 0) {
        reversed *= 10;
        reversed += (value % 10);
        value /= 10;
    }
    return reversed;
}

bool isReversible(ull value) {
	value += getReversed(value);

	do {
		if(value % 2 == 0) {
			return false;
		}
	} while(value /= 10);

	return true;
}

int main() {
	ull result = 0, add = 2;
	constexpr ull limit = 1e8;

	for(ull i = 11; i < limit; i += 2) {
		if(isReversible(i)) {
			result += 2;
		}
	}

	std::cout << result << std::endl;

	return 0;
}