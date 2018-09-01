#include <iostream>
#include <cmath>
#include <ctime>


double getArgumentOfPentagonal( int out )
{
	return (1 + sqrt( 1.0f + 24.0f * out))/6.0f ;
}


int main()
{
	int currentArgumentOfHexagonal = 143 ;
	while( true )
	{
		++currentArgumentOfHexagonal ;
		double tmp = currentArgumentOfHexagonal*( 2 * currentArgumentOfHexagonal - 1 ) ;
		if( round( getArgumentOfPentagonal( tmp ) ) == getArgumentOfPentagonal( tmp ) )
		{
			std::cout << currentArgumentOfHexagonal*( 2 * currentArgumentOfHexagonal - 1 ) << std::endl ;
			break ;
		}
	}

	std::cout << "runtime = " << clock()/1000.0f << "s" << std::endl;
	return 0 ;
}