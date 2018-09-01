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

	

inline bool isPermutation(int a, int b) {
  std::array<int, 10> counta{}, countb{};
  do { ++counta[a % 10]; } while (a /= 10);
  do { ++countb[b % 10]; } while (b /= 10);
  return counta == countb;
}

int main()
{
	double minimalLoef = 9999999 ;
	int * fiAnsw = new int[10000001] ;
	for( int i = 0 ; i < 10000001 ; i++ )
		fiAnsw[i] = 0 ;
	int indexOfMinKoef = -1 ;
	int limit = pow( 10 , 7 ) ;
	for( int i = 200 ; i < 10000000 ; i++ )
	{
		if( static_cast<int>( log10( i ) ) == static_cast<int>( log10( fiFunc( i , fiAnsw ) ) ) && isPermutation( i , fiFunc( i , fiAnsw ) ) )
		{
			if( static_cast<double>( i ) / static_cast<double>( fiFunc( i , fiAnsw ) ) < minimalLoef )
			{
				indexOfMinKoef = i ;
				minimalLoef = static_cast<double>( i ) / static_cast<double>( fiFunc( i , fiAnsw ) ) ;
			}
		}
		//std::cout << i << std::endl ;
	}
	std::cout << "n with min koef = " << indexOfMinKoef << std::endl ;
	delete [] fiAnsw ;
	//std::cout << "fi(87109) = " << fiFunc(87109) << " isPermutation? : " << isPermutation( 87109 , fiFunc(87109) ) << std::endl ;
}