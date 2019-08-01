#include <iostream>
#include <cmath>


using ull = long double;

ull ldabs(ull val) {
	using ll = long long;
	return ll(val + 0.5f);
}

int main() {
	// x -- B count
	// y -- R count
	// c -- B+R(all)

	//P(BB) = x/c * (x-1)/(c-1) = (x^2 - x) / (c^2 - c)

	// (x^2 - x) / (c^2 - c) = 1/2
	// 2*(x^2 - x) = (c^2 - c)

	const double kVal = 2*sqrt(2);
	ull c{0}, x{0}, n{0};

	// Got formula from Wolfram Alpha for equation: 
	for(n; c < 1e12; ++n) {
		c = -(pow((3 - kVal), n) + sqrt(2) * pow((3 - kVal), n) + pow((3 + kVal), n) - sqrt(2) * pow((3 + kVal), n) + 2)/4 + 1;
		x = -(-2 * pow((3 - kVal), n) - sqrt(2) * pow((3 - kVal), n) - 2 * pow((3 + kVal), n) + sqrt(2) * pow((3 + kVal), n) + 4)/8 + 1;
	}
	
	std::cout.precision(15);
	std::cout << "Result: " << ldabs(x) << std::endl;

	return 0;
}