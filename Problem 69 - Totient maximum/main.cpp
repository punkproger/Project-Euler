#include <cmath>
#include <array>
#include <iostream>
#include <memory>

inline int euclidAlg( unsigned int first , unsigned int second )
{
	if( first % second == 0 )
		return second; 
	else
		euclidAlg( second , first % second ) ;
}

inline int fiFunc( int n , int * arr)
{
	//std::cout << n << std::endl ;

	if( arr[ n ] != 0 )
	{
		return arr[ n ] ;
	}
	
	for( int i = 2 ; i <= sqrt( n ) ; i++ )
	{
		if( n % i == 0 )
		{
			arr[ n ] = ( fiFunc( i , arr ) * fiFunc( n / i , arr ) * euclidAlg( i , (n / i) ) ) / fiFunc( euclidAlg( i , (n / i) ) , arr ) ;
			return arr[ n ];
		}
	}

	if( n == 1 )
	{
		arr[ n ] = 1 ;
		return arr[ n ] ;
	}

	arr[ n ] = n - 1 ;
	return arr[ n ] ;

}

int main()
{
	double maxKoef = -1 ;
	int limit = pow( 10 , 6 ) ; 
	int fiAnsw[1000001] ;
	for( int i = 0 ; i < 1000001 ; i++ )
		fiAnsw[i] = 0 ;
	int indexOfMinKoef = -1 ;
	for( int i = 3 ; i <= limit ; i++ )
	{
		if( static_cast<double>( i ) / static_cast<double>( fiFunc( i , fiAnsw ) ) > maxKoef )
		{
			indexOfMinKoef = i ;
			maxKoef = static_cast<double>( i ) / static_cast<double>( fiFunc( i , fiAnsw ) ) ;
		}
		
	}
	std::cout << "n with min koef = " << indexOfMinKoef << std::endl ;
}