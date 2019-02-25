#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int phi (int n) {
	int i, s;
	s = sqrt(n);
	for(i=2; i<=s; i++) {
	  if ((n%i)==0) return (i-1)*phi(n%i);
	}
	return n-1; 
}

int main() {
	size_t size{1000000}, result{1};

	for(size_t i = 3; i <= size; ++i) {
		result += phi(i);
	}

	std::cout << result << std::endl;

	return 0;
}