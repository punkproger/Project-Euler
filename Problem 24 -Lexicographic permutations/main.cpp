#include <string>
#include <algorithm>
#include <iostream>

int main()
{
	std::string text = "0123456789";
	int i = 1 ; 
	do {
		i++ ;
		
	} while (std::next_permutation(text.begin(), text.end()) && i <= 1000000);
	std::cout << text << '\n';
	return 0 ;
}