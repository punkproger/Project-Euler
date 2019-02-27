#include <iostream> 
#include <vector> 


std::vector<int> daysOfMonth {
			31,
			28,
			31,
			30,
			31,
			30,
			31,
			31,
			30,
			31,
			30,
			31
};


int main() {
	int year{1901}, day{1}, result{0}, month{0};
	for(year; year <= 2000; ++year) {
		for(month = 0; month < daysOfMonth.size(); ++month) {
			if(day % 7 == 6) {
				++result;
			}
			day += daysOfMonth[month] + ((month == 1 && year % 4 == 0 && year % 400 != 0)? 1 : 0);
		}
	}

	std::cout << result << std::endl;

	return 0;
}