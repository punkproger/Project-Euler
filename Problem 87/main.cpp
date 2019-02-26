#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>
#include <unordered_set>

using namespace std;

int binpow(int base, int exp)
{
    int result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

vector<unsigned long> get_primes(unsigned long max){ // from: http://code.activestate.com/recipes/576559-fast-prime-generator/
    vector<unsigned long> primes;
    char *sieve;
    sieve = new char[max/8+1];
    // Fill sieve with 1  
    memset(sieve, 0xFF, (max/8+1) * sizeof(char));
    for(unsigned long x = 2; x <= max; x++)
        if(sieve[x/8] & (0x01 << (x % 8))){
            primes.push_back(x);
            // Is prime. Mark multiplicates.
            for(unsigned long j = 2*x; j <= max; j += x)
                sieve[j/8] &= ~(0x01 << (j % 8));
        }
    delete[] sieve;
    return primes;
}


int main() {
	constexpr unsigned long limit{50000000};
	auto primes{get_primes(sqrt(limit))};
	std::unordered_set<unsigned long> allNums;

	for(int i = 0; i < primes.size(); ++i) {
		if(binpow(primes[i], 2) > limit) {
					break;
		}
		for(int j = 0; j < primes.size(); ++j) {
			if(binpow(primes[j], 3) > limit) {
					break;
			}
			for(int k = 0; k < primes.size(); ++k) {
				if(binpow(primes[k], 4) > limit) {
					break;
				}
				unsigned long value = binpow(primes[i], 2) + binpow(primes[j], 3) + binpow(primes[k], 4);
				if(value < limit) {
					allNums.insert(value);
				}
			}
		}
	}

	std::cout << allNums.size() << std::endl;

	return 0;
}