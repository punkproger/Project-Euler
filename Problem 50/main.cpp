#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <string.h>

std::unordered_set<unsigned int> primes_set;

bool isPrime(unsigned long num )
{
	int sqrtVal{sqrt( num )};
	for( int i = 2 ; i <= sqrtVal; i++ )
		if( num % i == 0 )
			return false ;

	return true ;
}

std::vector<unsigned long> get_primes(unsigned long max){ // from: http://code.activestate.com/recipes/576559-fast-prime-generator/
    std::vector<unsigned long> primes;
    char *sieve;
    sieve = new char[max/8+1];
    // Fill sieve with 1  
    memset(sieve, 0xFF, (max/8+1) * sizeof(char));
    for(unsigned long x = 2; x <= max; x++)
        if(sieve[x/8] & (0x01 << (x % 8))){
            primes.push_back(x);
            primes_set.insert(x);
            // Is prime. Mark multiplicates.
            for(unsigned long j = 2*x; j <= max; j += x)
                sieve[j/8] &= ~(0x01 << (j % 8));
        }
    delete[] sieve;
    return primes;
}


int main() {
	constexpr size_t limit{1000000};
	size_t maxLength{0}, prime{0};
	auto primes{get_primes(limit)};

	for(int i = 0; i < primes.size(); ++i) {
		unsigned long sum{0};
		for(int j = i + 1; j < primes.size(); ++j) {
			sum += primes[j];
			if((j - i) < maxLength) {
				continue;
			}
			if(sum > limit) {
				break;
			} else if(primes_set.find(sum) != primes_set.end()) {
				maxLength = j - i;
				prime = sum;
			} 
			
		}
	}

	std::cout << prime << std::endl;

	return 0;
}