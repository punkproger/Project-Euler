#include <iostream>
#include <fstream>
#include <regex>


std::string optimizeRomanNumber(const std::string & number) {
	std::regex pattern("DCCCC|LXXXX|VIIII|CCCC|XXXX|IIII");
	std::smatch matchings;
	std::string replacement("SS"), result;

	result = std::regex_replace(number, pattern, replacement);

	return result;
}


int main() {
	std::ifstream file("p089_roman.txt");
	std::string str;
	int result = 0;

	while(std::getline(file, str)) {
		int tmp = str.size() - optimizeRomanNumber(str).size();
		result += tmp;
	}

	std::cout << result << std::endl;

	file.close();
	return 0;
}