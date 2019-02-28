#include <iostream>
#include <vector>
#include <algorithm>

constexpr size_t limit{200};
int cost[limit + 1];
int path[limit + 1]={0};

void find_shortest_exp_path(int power, int depth) {
    if (power > limit || depth > cost[power]) return;
    cost[power] = depth;
    path[depth] = power;
    for (int i = depth; i >= 0; i--)
        find_shortest_exp_path(power + path[i], depth + 1);
}


int main() {
	for(int i = 0; i <= limit; ++i) {
		cost[i] = 99999;
	}
	find_shortest_exp_path(1, 0);
	size_t result{0}; 

	for(int i = 1; i <= limit; ++i) {
		result += cost[i];
	}
	std::cout << result << std::endl;

	return 0;
}