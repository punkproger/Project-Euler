#include <iostream>
#include <ctime>

int function( int x )
{
	int result = 0 , tmp ;
	while( x > 0 )
	{
		tmp = x % 10 ;
		result += tmp * tmp * tmp * tmp * tmp ;
		x /= 10 ;
	}

	return result ;
}

int main()
{
	int answer = 0 ; 
	for( int i = 2 ; i <= 354294 ; i++ )
		if( i == function( i ) )
		{
			answer += i ;
		}

	std::cout << answer << std::endl ;
	std::cout << "runtime = " << clock()/1000.0f << "s" << std::endl;

	return 0 ;
}
