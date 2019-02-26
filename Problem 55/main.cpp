#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

inline bool isPalindrom( const std::string & digits )
{
	if(digits.size() == 1) {
		return true;
	}
	size_t size = digits.size();
	for( int i = 0 ; i < size / 2 ; i++ )
		if( digits[i] != digits[ size - 1 - i ] )
			return false ;

	return true ;
}

string findSum(string str1, string str2) //from: https://www.geeksforgeeks.org/sum-two-large-numbers/
{ 
    // Before proceeding further, make sure length 
    // of str2 is larger. 
    if (str1.length() > str2.length()) 
        swap(str1, str2); 
  
    // Take an empty string for storing result 
    string str = ""; 
  
    // Calculate lenght of both string 
    int n1 = str1.length(), n2 = str2.length(); 
  
    // Reverse both of strings 
    reverse(str1.begin(), str1.end()); 
    reverse(str2.begin(), str2.end()); 
  
    int carry = 0; 
    for (int i=0; i<n1; i++) 
    { 
        // Do school mathematics, compute sum of 
        // current digits and carry 
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry); 
        str.push_back(sum%10 + '0'); 
  
        // Calculate carry for next step 
        carry = sum/10; 
    } 
  
    // Add remaining digits of larger number 
    for (int i=n1; i<n2; i++) 
    { 
        int sum = ((str2[i]-'0')+carry); 
        str.push_back(sum%10 + '0'); 
        carry = sum/10; 
    } 
  
    // Add remaining carry 
    if (carry) 
        str.push_back(carry+'0'); 
  
    // reverse resultant string 
    reverse(str.begin(), str.end()); 
  
    return str; 
} 

bool isLychrel(int number) {
	const size_t limit{52};
	size_t length{0};
	std::string current(std::to_string(number));

	do {
		std::string tmp(current);
		std::reverse(current.begin(), current.end());
		current = findSum(current, tmp);
		++length;
	} while(length < 52 && !isPalindrom(current));

	return !isPalindrom(current);
}

int main() {
	constexpr size_t limit{10000};
	size_t result{0};

	for(int i = 0; i < limit; ++i) {
		if(isLychrel(i)) {
			++result;
		}
	}

	std::cout << result << std::endl;
	
	return 0;
}