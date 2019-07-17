#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>

using ull = unsigned long int;

std::vector<ull> get_primes(ull max);
constexpr ull limit = 1e5, necessaryIndex = 1e4-1;


auto primes = std::move(get_primes(limit+10)); 


inline ull rad(ull val) {
	auto valCopy = val;
	ull result{1};
	std::set<ull> uniqueDivisors;

	for(ull i = 0; primes[i] <= val; ++i) {
		while((val % primes[i]) == 0) {
			//std::cout << val << "/" << primes[i] << std::endl;
			uniqueDivisors.insert(primes[i]);
			val /= primes[i];
		}
	}

	for(const auto uniqueVal : uniqueDivisors) {
		result *= uniqueVal;
	}
	
	return result;
}

inline std::vector<ull> get_primes(ull max){
    std::vector<ull> primes;
    char *sieve;
    sieve = new char[max/8+1];
    // Fill sieve with 1  
    memset(sieve, 0xFF, (max/8+1) * sizeof(char));
    for(ull x = 2; x <= max; x++)
        if(sieve[x/8] & (0x01 << (x % 8))){
            primes.push_back(x);
            // Is prime. Mark multiplicates.
            for(ull j = 2*x; j <= max; j += x)
                sieve[j/8] &= ~(0x01 << (j % 8));
        }
    delete[] sieve;
    return primes;
}

struct Element
{
	int idx;
	ull val;
};

int main() {
	std::vector<Element> divisorsMultVec(limit+1);

	for(int i = 1; i <= limit; ++i) {
		divisorsMultVec[i] = {i, rad(i)};
	}

	auto comp = [](const Element & first, const Element & second) {
		return first.val < second.val;
	};

	std::sort(divisorsMultVec.begin(), divisorsMultVec.end(), comp);

	std::cout << "Result: " << divisorsMultVec[necessaryIndex].idx << std::endl;

	return 0;
}