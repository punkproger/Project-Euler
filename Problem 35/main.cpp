#include <iostream>
#include <cmath>
#include <string>

bool isPrime( unsigned int number )
{
	for( int i = 2 ; i <= sqrt( number ) ; i++ )
		if( number % i == 0 )
			return false ;

	return true ;
}

bool isEveryDigitOdd( unsigned int number )
{
	while( number > 0 )
	{
		if( (number % 10) % 2 == 0 ) 
			return true ;
		number /= 10 ;
	}

	return false ;
}

int main()
{
	unsigned int answer = 1 ;
	
	for( int i = 3 ; i < 1000000 ; i += 2 )
	{
		if( !isEveryDigitOdd( i ) )
		{
			std::string text( std::to_string( i ) ) , tmp(text) ;
			bool isRight = true ;

			for( int j = 0 ; j < tmp.size() ; j++ )
			{
				auto sym = tmp[0] ;
				tmp = tmp.substr( 1 , tmp.size() - 1 ) + sym ;
				if( !isPrime( std::stoi( tmp ) ) )
				{
					isRight = false ;
					break ;
				}
			}
			answer += isRight ;
		}
	}

	std::cout << answer << std::endl ;

	return 0 ;
}