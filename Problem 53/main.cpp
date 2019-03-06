#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>


double log_fact(int x) {
	double n = x;
	double res = n * log10(n) - n + log10(n * (1.0f + 4.0f*n*(1.0f + 2.0f*n)))/6.0f + log10(M_PI)/2.0f;

	return res;
}

double getLogOfC(int n, int r) {
	return log_fact(n) - (log_fact(r) + log_fact(n - r));
}


int main() {
	constexpr size_t goal{6};
	size_t result{0};

	for(int n = 1; n <= 100; ++n) {
		for(int r = 1; r < n; ++r) {
			if(getLogOfC(n, r) >= goal) {
				++result;
			}
		}
	}

	std::cout << result << std::endl;
	return 0;
}