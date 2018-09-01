#include <iostream>
#include <cmath>
#include <vector>

bool isPrime( int number )
{
	for( int i = 2 ; i <= sqrt( number ) ; i++ )
		if( number % i == 0 )
			return false ;
	return true ;
}

int main()
{
	int primesSize = 1000 , primesCount = 1 , currentNumber = 3;
	std::vector<unsigned int> primes( primesSize ) ;
	primes[0] = 2 ;
	while( primesCount != primesSize )
	{
		if( isPrime( currentNumber ) )
			primes[primesCount++] = currentNumber ;
		currentNumber += 2 ;
	}
	currentNumber = 33 ;
	while( true )
	{
		currentNumber += 2 ;
		if( isPrime( currentNumber ) )
			continue ;

		bool isGoldbah = false ;
		for( int i = 0 ; i < primes[i] ; i++ )
		{
			double tmp = (currentNumber - primes[ i ])/2.0f ;

			if( tmp > 0 && sqrt(tmp) == round(sqrt(tmp)) )
			{
				isGoldbah = true ;
				break ;
			}
		}

		if( isGoldbah == false )
			break ;
	}	
	std::cout << currentNumber << std::endl ;
	return 0 ;
}