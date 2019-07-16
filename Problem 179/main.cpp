#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <cmath>

using ull = unsigned int;

inline size_t divisorsCount(ull val) {
	size_t result{2};
	for(int i = 2; i <= sqrt(val); ++i) {
		if(val % i == 0) {
			result += i*i != val? 2 : 1;
		}
	}

	return result;
}

int main() {
	constexpr ull limit = 1e7;
	size_t result{0};
	std::vector<size_t> divisors_counts(limit);
	bool wasSameDivisorsCountBefore = false;
	for(ull i = 2; i < limit; ++i) {
		divisors_counts[i] = divisorsCount(i);

		if(divisors_counts[i] == divisors_counts[i-1]) {
			result += 1;
		} 

		if(i % 10000== 0) {
			std::cout << i << std::endl;
		}
	}

	

	std::cout << "Result: " << result << std::endl;

	return 0;
}