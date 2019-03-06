#include <iostream>
#include <cmath>

inline bool isPrime(int number)
{
	int root = sqrt( number );
	for(int i = 2 ; i <= root; i++ )
		if(number % i == 0)
			return false ;
	return true ;
}

int main() {
	int sideLen{3}, ru{3}, lu{5}, ld{7};
	double bothDiagLen{5}, primes{3};

	while((primes/bothDiagLen) >= 0.1f) {
		bothDiagLen += 4;
		ru = sideLen*sideLen + sideLen + 1;
		lu = ru + sideLen + 1;
		ld = lu + sideLen + 1;
		primes += isPrime(ru) + isPrime(lu) + isPrime(ld);
		sideLen += 2;
	}

	std::cout << sideLen << std::endl;

	return 0;
}