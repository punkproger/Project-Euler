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

std::map<int, int> getFactorization(long x, const std::vector<unsigned int> & primes) { 
    std::map<int, int> ret; 
    size_t idx{0};

    while (x != 1) 
    { 
        if(x%primes[idx] == 0) {
        	++ret[primes[idx]];
        	x /= primes[idx];
        } else {
        	++idx;
        }
    }

    return ret; 
}

bool haveSameFactor(const std::map<int, int> & f_map, const std::map<int, int> & s_map) {
	for(const auto & f_pair : f_map) {
		if(s_map.find(f_pair.first) != s_map.end()) {
			if(s_map.at(f_pair.first) == f_pair.second) {
				return true;
			}
		}
	}

	return false;
}

int main() {
	std::vector<unsigned int> primes{get_primes(300000)};
	bool status{true};
	size_t idx{650};
	std::array<std::map<int, int>, 4> lastFour;

	while(true) {
		bool shouldStop{false};
		bool shouldContinue{false};

		for(int i = 0; i < lastFour.size(); ++i) {
			lastFour[i] = getFactorization(idx + i, primes);
			if(lastFour[i].size() != 4) {
				shouldContinue = true;
				break;
			}
		}
		if(shouldContinue) {
			++idx;
			continue;
		}

		for(int i = 0; i < lastFour.size(); ++i) {
			for(int j = i + 1; j < lastFour.size(); ++j) {
				if(haveSameFactor(lastFour[i], lastFour[j])) {
					shouldStop = true;
					break;
				}
			}
		}

		if(!shouldStop) {
			break;
		}

		++idx;
	}

	std::cout << idx << std::endl;

	return 0;
}