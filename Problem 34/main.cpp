#include <iostream>
#include <ctime>


unsigned long long int factorials[10] ;

int factorial( int x )
{
	if( x <= 1 )
		return 1 ;
	else
		return x * factorial( x - 1 ) ;
}

bool isDigitFactorial( int number )
{
	unsigned long long int numValue = number , value = 0 ;
	
	while( numValue > 0 )
	{
		value += factorials[ numValue % 10 ] ;
		numValue /= 10 ; 
	}

	return value == number ;
}

int main()
{
	unsigned long long int answer = 0 ;

	for( int i = 0 ; i < 10 ; i++ )
		factorials[ i ] = factorial( i ) ;

	for( int i = 10 ; i <= 362880 ; i++ )
	{
		if( isDigitFactorial( i ) )
			answer += i ;
	}

	std::cout << answer << std::endl ;
	std::cout << "runtime = " << clock()/1000.0f << "s" << std::endl;

	return 0 ;
}