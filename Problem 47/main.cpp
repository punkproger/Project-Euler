#include <iostream>
#include <vector>
#include <map>

#include <string.h>


std::vector<unsigned int> get_primes(unsigned int max){
    std::vector<unsigned int> primes;
    char *sieve;
    sieve = new char[max/8+1];
    // Fill sieve with 1  
    memset(sieve, 0xFF, (max/8+1) * sizeof(char));
    for(unsigned int x = 2; x <= max; x++)
        if(sieve[x/8] & (0x01 << (x % 8))){
            primes.push_back(x);
            // Is prime. Mark multiplicates.
            for(unsigned int j = 2*x; j <= max; j += x)
                sieve[j/8] &= ~(0x01 << (j % 8));
        }
    delete[] sieve;
    return primes;
}

int getNumberOfPrimeFactors(unsigned int x, const std::vector<unsigned int> & primes) { 
    int result{0};
    int prevResult{0};
    int idx{0};
    while (x != 1) 
    {
		if (primes[idx] * primes[idx] > x) {
            return ++result;
        }
    	prevResult = result;
        while(x%primes[idx] == 0) {
        	result = prevResult + 1;
        	x /= primes[idx];
        }
        ++idx;
    }

    return result; 
}


int main() {
	std::vector<unsigned int> primes{get_primes(300000)};
	bool status{true};
	size_t idx{650};
	int consec{0};

	while(true) {
		if(getNumberOfPrimeFactors(idx, primes) == 4) {
			++consec;
		} else {
			consec = 0;
		}

		if(consec == 4) {
			break;
		}
		++idx;
	}

	std::cout << idx - 3<< std::endl;

	return 0;
}