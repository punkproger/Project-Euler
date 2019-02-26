#include <iostream>
#include <map>

using uint = unsigned int;

uint loops[1000000]={0};
constexpr uint limit{1000000};

uint factorial[] = {
	1,
	1,
	2,
	6,
	24,
	120,
	720,
	5040,
	40320,
	362880
};

inline uint getSumOfFact(uint number) {
	uint result{0};
	do {
		result += factorial[number%10];
		number /= 10;
	} while(number);

	return result;
}

uint findNonRepeateableNumber(uint number) {
	std::map<uint, bool> alreadySeen;
	uint current{number}, size{0};

	while(!alreadySeen[current]) {
        alreadySeen[current] = true;
        current = getSumOfFact(current);
        if(current < limit && loops[current]) {
            size += loops[current] + 1;
            break;
        }
        else
            ++size;
    }

	loops[number] = size;
	return size;
}

int main() {
	uint current{2}, result{0};
	loops[78] = 4;
	loops[145] = 1;
	loops[169] = 3;
	loops[540] = 2;
	loops[871] = 2;
	loops[872] = 2;
	loops[1454] = 3;
	loops[45360] = 3;
	loops[45361] = 2;
	loops[45362] = 2;
	loops[363600] = 4;
	loops[363601] = 3;
	for(current; current < limit; ++current) {
		if(findNonRepeateableNumber(current) == 60) {
			++result;
		}
	}

	std::cout << result << std::endl;

	return 0; 
}