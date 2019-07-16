#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <cmath>

using ull = int;


int main() {
	constexpr ull limit = 1e7;
	size_t result{0};
	std::vector<int> divnums(limit);
	
	for (int i = 1; i < 10000000; ++i) {
		divnums[i] += 1;
		for (int j = 2; (1+i)*j < 10000000; ++j) {
			divnums[(i+1)*j] += 1;
		}
		if (i > 1) {
			result += (divnums[i] == divnums[i-1]);
		}
	}

	

	std::cout << "Result: " << result << std::endl;

	return 0;
}