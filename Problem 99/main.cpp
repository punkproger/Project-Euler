#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <map>
#include <string>

using expr = std::pair<size_t, size_t>; 

int main() {
	std::ifstream file("p099_base_exp.txt");
	std::string line;

	std::vector<expr> expressions;
	size_t greatestExprPos{0};

	while(std::getline(file, line)) {
		size_t commaPos{line.find(',')}, lineSize{line.size()};
		size_t base{size_t(std::stoi(line.substr(0, commaPos)))};
		size_t exp{size_t(std::stoi(line.substr(commaPos + 1, lineSize - commaPos)))};
		expressions.push_back(std::make_pair(base, exp));
	}

	for(size_t i = 0; i < expressions.size(); ++i) {
		auto greatest{expressions[greatestExprPos]};
		auto item{expressions[i]};
		double val1{item.second * log10(item.first)}, val2{greatest.second * log10(greatest.first)};
		if(val1 > val2) {
			greatestExprPos = i;
		}
	}

	std::cout << greatestExprPos + 1 << std::endl;

	file.close();

	return 0;
}