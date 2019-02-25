#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

int main() {
	std::ifstream file("p107_network.txt");
	std::string str;
	constexpr size_t size{40};
	constexpr int INF = 9999;
	int fullVal{0};

	vector < pair < int, pair<int,int> > > KruskalTree;

	std::regex allNums("(\\d{1,4})|(-)");

	for(int i = 0; i < size; ++i) {
		std::getline(file, str);

		std::smatch matchings;
		
		for(int j = 0; j < size; ++j) {
			std::regex_search(str, matchings, allNums);
			if(is_number(matchings[1])) {
				KruskalTree.push_back(std::make_pair(std::stoi(matchings[1]), std::make_pair(i, j)));
				fullVal += std::stoi(matchings[1]);
			}
			str = matchings.suffix().str();
		}
	}

	int m = KruskalTree.size();
	int cost = 0;
	vector < pair<int,int> > res;
	std::vector<int> tree_id(size);
	for(int i = 0; i < size; ++i) {
		tree_id[i] = i;
	}

	sort (KruskalTree.begin(), KruskalTree.end());
	for(int i = 0; i < m; ++i) {
		int a{KruskalTree[i].second.first}, b{KruskalTree[i].second.second}, l{KruskalTree[i].first};
		if (tree_id[a] != tree_id[b])
		{
			cost += l;
			res.push_back (make_pair (a, b));
			int old_id = tree_id[b],  new_id = tree_id[a];
			for (int j=0; j<size; ++j)
				if (tree_id[j] == old_id)
					tree_id[j] = new_id;
		}
	}

	std::cout << (fullVal/2) - cost << std::endl;

	file.close();
	return 0;
}