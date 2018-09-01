#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>


double getArgumentOfPentagonal( long int out )
{
	return (1 + sqrt( 1.0f + 24.0f * out)) / 6.0f ;
}

bool isPentagonal( long int value )
{
	return fmod( ( ( sqrt( 24 * value + 1 ) + 1 ) / 6 ) , 1.0) == 0.0; ;
}

long int pentagonalFunction( int x )
{
	return ( x * ( 3 * x - 1 ) ) / 2 ;
}

int main()
{
	int pentaSize = 3000 ;
	long int minD = 999999999 ;
	std::vector<long int> pentagonals( pentaSize ) ;
	for( int i = 0 ; i < pentagonals.size() ; i++ )
	{
		pentagonals[ i ] = pentagonalFunction( i + 1 ) ;
	}

	for( int i = 0 ; i < pentagonals.size() ; i++ )
	{
		for( int j = 0 ; j < i ; j++ )
		{
			if( i != j && abs( pentagonals[i] - pentagonals[j] ) < minD && isPentagonal( pentagonals[i] + pentagonals[j] ) && 
				isPentagonal( abs( pentagonals[i] - pentagonals[j] ) ) )
				minD = abs( pentagonals[i] - pentagonals[j] ) ;
		}
	}	
	std::cout << minD << std::endl ;
	std::cout << "runtime = " << clock()/1000.0f << "s" << std::endl;
	return 0 ;
}