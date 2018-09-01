#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

int main()
{
	int answer = 0 ;

	std::vector<unsigned long long int> number( 200 , 0 ) ;
	number[0] = 1 ;
	for( int i = 1 ; i <= 100 ; i++ )
	{
		for( int j = 0 ; j < number.size() ; j++ )
		{
			number[j] *= i ;
		}

		for( int j = 0 ; j < number.size() ; j++ )
		{
			if( number[j] > pow( 10 , 12 ) )
			{
				number[ j + 1 ] += static_cast<int>( number[ j ] / pow( 10 , 12 ) ) ;
				number[ j ] %= static_cast<unsigned long long int>( pow( 10 , 12 ) ) ;
			}
		}
	}

	for( auto & num : number )
	{
		while( num >= 1 )
		{
			answer += num % 10 ;
			num /= 10 ;
		}
	}

	std::cout  << answer << std::endl ;
	std::cout << "runtime = " << clock()/1000.0f << "s" << std::endl;

}