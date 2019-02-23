#include <iostream>
#include <cmath>
#include <string>


int main()
{
	int result = 1 , degreeOfTen = 0 , currentNumber = 1 , positions = 0 ;
	while( degreeOfTen <= 6 )
	{
		positions += static_cast<int>( log10( currentNumber ) ) + 1 ;
		if( positions >= pow( 10 , degreeOfTen ) )
		{
			std::string str = std::to_string( currentNumber ) ;
			str = str.substr( str.size() - 1 - ( positions - pow( 10 , degreeOfTen ) ) , 1 ) ;
			result *= std::stoi( str ) ;
			++degreeOfTen ;
		}
		++currentNumber ;
	}
	
	std::cout << result << std::endl ;

	return 0 ;
}