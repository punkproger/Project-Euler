#include <iostream>
#include <cmath>

int main()
{
	 int divisiors = 0 , count = 4 ;
	 int value = 6 ;
	while( divisiors < 500 )
	{
		divisiors = 0 ;
		value += count ;
		for( int i = 1 ; i < sqrt( value ) + 1 ; ++i )
			if( value % i == 0 )
				divisiors += 2 ;

		++count ;
	}

	std::cout << value << '\t' << divisiors << std::endl ;
}