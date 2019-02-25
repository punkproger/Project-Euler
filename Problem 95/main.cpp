#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <string.h>

using namespace std;

vector<unsigned long> get_primes(unsigned long max);

constexpr size_t size{1000000};
unsigned long divisors_sum[size] = {0};

vector<unsigned long> primes{get_primes(size)};
const size_t prime_size = primes.size();

int countDivisorsSum(int num) {
	if(divisors_sum[num] != 0) {
		return divisors_sum[num];
	}
	int res=1, limit{sqrt(num)};
	for(int i = 2; i <= limit; ++i) {
		if(num % i == 0) {
			if(i*i == num) {
				res += i;
			} else {
				res += i + (num/i);
			}
		}
	}
	divisors_sum[num] = res;
	return res;
}

int findCycleLenght(unsigned long num, int & minElem) {
	int current{num}, result{0}, elem_size{0};
	std::set<int> elementsOfPath;
	minElem = 99999999;

	do {
		if(current == 1 || current >= size) {
			return -1;
		}
		++result;
		elementsOfPath.insert(current);
		current = countDivisorsSum(current);
		if(current == num) {
			return result;
		}
		++elem_size;
		if(current < minElem) {
			minElem = current;
		}
	} while((elementsOfPath.size() == elem_size));

	return -1;
}

vector<unsigned long> get_primes(unsigned long max){
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
	int idxGreatest{0}, maxLength{0}, min_elem, result;
	for(auto prime : primes) {
		divisors_sum[prime] = 1;
	}
	findCycleLenght(402170, min_elem);
	for(int i = 5; i < size; ++i) {
		int length{findCycleLenght(i, min_elem)};
		if(length > maxLength) {
			maxLength = length;
			idxGreatest = i;
			result = i;
		}
	}

	std::cout << result << std::endl;

	return 0;
}