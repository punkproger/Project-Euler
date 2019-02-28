#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#include <string.h>

bool isPrime(int num )
{
	int sqrtVal{sqrt( num )};
	for( int i = 2 ; i <= sqrtVal; i++ )
		if( num % i == 0 )
			return false ;

	return true ;
}

std::vector<unsigned long> get_primes_upper_1000(unsigned long max){
    std::vector<unsigned long> primes;
    char *sieve;
    sieve = new char[max/8+1];
    // Fill sieve with 1  
    memset(sieve, 0xFF, (max/8+1) * sizeof(char));
    for(unsigned long x = 2; x <= max; x++)
        if(sieve[x/8] & (0x01 << (x % 8))){
        	if(x > 1000) { //HERE
            	primes.push_back(x);
        	}
            // Is prime. Mark multiplicates.
            for(unsigned long j = 2*x; j <= max; j += x)
                sieve[j/8] &= ~(0x01 << (j % 8));
        }
    delete[] sieve;
    return primes;
}

std::vector<int> getPrimesWithSameDiff(std::vector<int> primes) {
	std::vector<int> result;
	std::map<int, std::pair<int, int>> difference;
	std::sort(primes.begin(), primes.end());
	for(int i = 0; i < primes.size() - 1; ++i) {
		for(int j = i + 1; j < primes.size(); ++j) {
			int diff = primes[j] - primes[i];
			difference[diff] = std::make_pair(primes[i], difference[diff].second + 1);
		}
	}
	for(auto diff : difference) {
		if(diff.second.second == 2) {
			int diffValue{diff.first};
			int item{diff.second.first};
			result = {item - diffValue, item, item + diffValue};
			if (std::find(primes.begin(), primes.end(), result[0]) == primes.end() ||
				std::find(primes.begin(), primes.end(), result[1]) == primes.end() ||
				std::find(primes.begin(), primes.end(), result[2]) == primes.end() ) {
				result = std::vector<int>();
				continue;
			}
			break;
		}
	}

	return result;
}

int main() {
	auto primes{get_primes_upper_1000(9999)};
	std::map<std::string, int> prime_map;
	std::vector<std::string> resDigits;
	std::vector<int> resultPrimes;

	for(int i = 0; i < primes.size(); ++i) {
		std::string str{std::to_string(primes[i])};
		std::sort(str.begin(), str.end());
		if(str != "1478") {
			++prime_map[str];
		}
	}

	for(auto prime_pair : prime_map) {
		if(prime_pair.second < 3) {
			continue;
		}
		std::string digits = prime_pair.first;
		std::set<int> tmpSeq;
		do {
			int value{std::stoi(digits)};
			if(value > 1000 && isPrime(value)) {
				tmpSeq.insert(value);
			}
		} while(std::next_permutation(digits.begin(), digits.end()));
		
		std::vector<int> tmpSeqVec;
		for(auto val : tmpSeq) {
			tmpSeqVec.push_back(val);
		}

		if(getPrimesWithSameDiff(tmpSeqVec).size() == 3) {
			resultPrimes = getPrimesWithSameDiff(tmpSeqVec);
			break;
		}
	}


	for(auto num : resultPrimes) {
		std::cout << num;
	}
	std::cout << std::endl;

	return 0;
}