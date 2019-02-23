#include <iostream>
#include <cmath>

size_t rectCount(size_t n, size_t m) 
{ 
    return (m * n * (n + 1) * (m + 1)) / 4; 
}

int main() {
	size_t size{150}, goal{2000000}, nearest{0}, gridArea{0};
	for(size_t m = 1; m < size; ++m) {
		for(size_t n = 1; n < size - m; ++n) {
			size_t rectVal{rectCount(m, n)};
			if(abs(goal - nearest) > abs(goal - rectVal)) {
				nearest= rectVal;
				gridArea = n * m;
			}
		}
	}

	std::cout << nearest << ", grid area(answ): " << gridArea << std::endl;

	return 0;
}