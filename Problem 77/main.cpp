#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

std::vector<int> primes ;

bool isPrime( int num )
{
	for( int i = 2 ; i <= sqrt( num ) ; i++ )
		if( num % i == 0 )
			return false ;

	return true ;
}

int count( int price , int maxcoin )
{
	int sum = 0 ;
	
	for( int i = maxcoin ; i < primes.size() ; i++ )
	{
		if( price - primes[i] == 0 )
			sum += 1 ;
		else if( price - primes[i] > 0 )
			sum += count( price - primes[i] , i ) ;
		else
			break ;
	}

	return sum ;
}
int main()
{
	int i = 2 ;

	while( primes.size() != 100 )
	{
		if( isPrime( i ) )
			primes.push_back( i ) ;
		++i ;
	}	

	i = 2 ;

	while( count( ++i , 0 ) < 5000 )
	{}

	std::cout << i << std::endl ;

	std::cout << "runtime = " << clock()/1000000.0f << "s" << std::endl;

	return 0 ;
}