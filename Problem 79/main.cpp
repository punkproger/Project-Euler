#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

using bothSidesVec = std::pair<std::vector<int>, std::vector<int>>;

void addIfThereIsnt(std::vector<int> & vec, int val) {
	if(std::find(vec.begin(), vec.end(), val) == vec.end()) {
		vec.push_back(val);
	}
}

void deleteFromVec(std::vector<int> & vec, int val) {
	for(auto it = vec.begin(); it != vec.end(); ++it) {
		if(*it == val) {
			it = vec.erase(it);
			--it;
		}
	}
}

int main() {
	std::ifstream file("p079_keylog.txt");
	std::vector<std::string> passes;
	std::vector<std::string> possiblePasscodes;
	std::string str;
	std::map<int, bothSidesVec> valueMap;
	while(std::getline(file, str)) {
		passes.push_back(str);
	}

	for(const auto & pass : passes) {
		int f{std::stoi(pass.substr(0,1))};
		int s{std::stoi(pass.substr(1,1))};
		int t{std::stoi(pass.substr(2,1))};


		addIfThereIsnt(valueMap[f].second, s);
		addIfThereIsnt(valueMap[f].second, t);

		addIfThereIsnt(valueMap[s].first , f);
		addIfThereIsnt(valueMap[s].second, t);

		addIfThereIsnt(valueMap[t].first , f);
		addIfThereIsnt(valueMap[t].first , s);
	}

	std::string l_password;
	for(int i = 0; i < valueMap.size(); ++i) {
		for(const auto & item : valueMap) {
			bool isInLeft {l_password.find(std::to_string(item.first)) == l_password.npos};
			if(isInLeft && item.second.first.empty()) {
				l_password += std::to_string(item.first);
				for(auto & itemToDecrease : valueMap) {
					deleteFromVec(itemToDecrease.second.first, item.first);
				}
			}
		}
	}
	
	std::cout << l_password << std::endl;

	file.close();
	return 0;
}