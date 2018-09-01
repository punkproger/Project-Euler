#include <iostream>
#include <bitset>
#include <string>
#include <cmath>
#include <algorithm>



bool isPalindrome( int number )
{
	std::string fStr = std::to_string( number ) , sStr( fStr ) ;
	std:reverse(sStr.begin(),sStr.end()) ;
	return fStr == sStr ;
}

constexpr int get( int number )
{
	return log2( number ) + 1 ;
}

bool isPalindromeBinary( int number )
{
	const int value = number ;
	constexpr int degree = get(value) ;
	std::bitset< degree > bits( value ) ;
	std::bitset< constexpr(degree) > SBits( value ) ;
	SBits.flip() ;
	return bits == SBits ;
}


int main()
{
	int sum = 0 ;
	int number = 1 ;
	while( number != 1000000 )
	{
		if( isPalindromeBinary(number) && isPalindrome(number) ) 
			sum += number ;
		++number ;
	}

	std::cout << sum << std::endl ;

	return 0 ;
}