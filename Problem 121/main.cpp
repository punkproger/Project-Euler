#include <iostream>
#include <vector>
#include <numeric>

using ull = unsigned long long;


ull fact(size_t x) {
	return x > 1 ? x * fact(x-1) : 1;
}

ull combinationsCount(int m, int n) {
	return fact(m)/(fact(n) * fact(m-n));
}

void generateCombinations(int offset
						 ,int k
						 ,const std::vector<int> & idxs
						 ,std::vector<std::vector<int>> & allCombinations
						 ,std::vector<int> & combination) {

  if(k == 0) {
  	allCombinations.push_back(combination);
  	return;
  }

  for (int i = offset; i <= idxs.size() - k; ++i) {
	combination.push_back(idxs[i]);
	generateCombinations(i+1, k-1, idxs, allCombinations, combination);
	combination.pop_back();
  }
}

ull paymentForWinning(ull turnsCount) {
	ull num{0};
	ull denom{fact(turnsCount+1)};
	
	const int maxRedCount = turnsCount/2 + (turnsCount % 2 == 0 ? -1 : 0 );
	
	std::vector<int> idxs(turnsCount);
	std::iota(idxs.begin(), idxs.end(), 1);

	for(int gotReds = 0; gotReds <= maxRedCount; ++gotReds) {
		std::vector<int> tmpVec;

		std::vector<std::vector<int>> allCombinations;
  		allCombinations.reserve(combinationsCount(idxs.size(), gotReds));
		
		generateCombinations(0, gotReds, idxs, allCombinations, tmpVec);
		
		for(const auto & combination : allCombinations) {
			ull tmpNum{1};
			for(const auto turn : combination) {
				tmpNum *= turn;
			}
			num += tmpNum;
		}
	}

	return denom/num;
}


int main() {
	std::cout << "Result: " << paymentForWinning(15) << std::endl;
	
	return 0;
}