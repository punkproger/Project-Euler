#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using uint = uint;


/*int getPeriodLength(const std::vector<int> & seq) {
	size_t possibleEntryStart;
	for(int i = 1; i < seq.size(); ++i) {
		if(seq[i] == seq[0]) {
			bool cyclic{true};
			std::vector<int> pattern;
			for(int j = 0; j < i; ++j) {
				pattern.push_back(seq[j]);
			}

			int idx=0;
			for(int j = 0; j < seq.size(); ++j, ++idx) {
				if(idx >= pattern.size()) {
					idx = 0;
				}
				if(seq[j] != pattern[idx]) {
					cyclic = false;
					break;
				}
			}
			if(cyclic) {
				return pattern.size();
			}

		}
	}

	return -1;
}*/

uint getPeriodLength(int number) {
	uint root{sqrt(number)};

	uint a = root;

	uint n = 0;
	uint d = 1;

	uint period = 0;

	while(a != root * 2) {
		n = d * a - n;
		d = (number - n*n)/d;
		a = (root + n)/d;

		++period;
	}

	return period;
}

int main() {
	constexpr size_t limit{10000}, length{100};
	size_t result{0};
	for(int i = 2; i <= limit; ++i) {
		int sqrtI = sqrt(i);
		if(sqrtI * sqrtI != i) {
			int period{getPeriodLength(i)};
			if(period > 0 && period % 2 == 1) {
				++result;
			}
		}	
	}
	std::cout << result << std::endl;
	return 0;
}