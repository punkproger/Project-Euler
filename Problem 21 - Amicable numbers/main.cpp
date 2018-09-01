#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>


int d( int x )
{
	int sumOfDivisors = 1 ;
	for( int i = 2 ; i <= sqrt( x ) ; i++ )
	{
		if( x % i == 0 )
			sumOfDivisors += i + (x / i) ; 
	}

	return sumOfDivisors ;
}


int main()
{
	int answer = 0 ;
	std::vector<int> valArr ;
	valArr.resize(10000) ;
	for( int i = 1 ; i < 10000 ; i++ )
	{
		valArr[ i ] = d(i) ;
	}

	for( int i = 1 ; i < 10000 ; i++ )
	{
		if( valArr[ i ] != i && i == valArr[ valArr[ i ] ]  )
		{
			std::cout << "xi = " << i << "   d(xi) = " << valArr[i] << "   xj = " << valArr[i] << "   d(xj) = " << valArr[ valArr[i] ] << std::endl ;
			answer += i ;
		}
	}

	std::cout << answer << std::endl ;

	return 0 ;



}