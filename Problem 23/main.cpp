#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

bool isAbundant( int number )
{
	int sumOfDivisors = 1 ;
	for( int i = 2 ; i <= sqrt(number) ; i++ )
		if( number % i == 0 )
			sumOfDivisors += i + ( i == (number/i) ? 0 : ( number / i ) ) ;

	return sumOfDivisors > number ;
} 

int main()
{
	int answer = 0 ;
	std::vector< int > abundants ;
	std::vector< char > sumOfAbudants( 28124 , 0 ) ;

	for( int i = 12 ; i <= 28123 ; i++ )
		if( isAbundant( i ) ) 
			abundants.push_back( i ) ;

	for( int i = 0 ; i < abundants.size() ; i++ )
		for( int j = 0 ; j < abundants.size() ; j++ )
		{
			if( abundants[i] + abundants[j] <= 28123 )
			{
				sumOfAbudants[ abundants[i] + abundants[j] ] = 1 ;
			}
			else
			{
				break;
			}
		}	

	for( int i = 1 ; i <= 28123 ; i++ )
	{
		if( sumOfAbudants[ i ] == 0 )
			answer += i ;
	}

	std::cout << answer << std::endl ;
	std::cout << "runtime = " << clock()/1000.0f << "s" << std::endl;

	return 0 ;
}