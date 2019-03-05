#include <iostream>
#include <cmath>
#include <unordered_map>

using ull = long long;

std::unordered_map<ull, bool> primes;

bool isPrime(ull x) {
	if(x <= 1) {
		return false; 
	}

	if(primes.find(x) != primes.end()) {
		return primes[x];
	}
	ull root{sqrt(x)};
	for(ull i = 2; i <= root; ++i) {
		if(x%i==0) {
			primes.emplace(x, false);
			return false;
		}
	}

	primes.emplace(x, true);
	return true;
}


int main() {
	ull a{-999}, b{-1000}, a_l{999}, b_l{1000}, maxSeq{0}, max_a,max_b;
	for(a = -a_l; a <= a_l; ++a) {
		for(b = 3; b <= b_l; b += 2) {
			ull seqLen{0}, expr{seqLen*seqLen + a*seqLen + b};
			
			for(; isPrime(expr);++seqLen) { 
				expr = seqLen*seqLen + a*seqLen + b;
			}

			if(seqLen > maxSeq) {
				maxSeq = seqLen;
				max_a = a;
				max_b = b;
			}

		}
	}

	std::cout << max_a * max_b << std::endl;

	return 0;
}