#include <iostream>
#include <cmath>
#include <set>
#include <ctime>

inline bool isPandigital( int first , int second )
{	
	int arr[10] = { 0 } , third = first * second ;
	
	while( first > 0 )
	{
		++arr[ first % 10 ] ;
		first /= 10 ;
	}
	while( second > 0 )
	{
		++arr[ second % 10 ] ;
		second /= 10 ;
	}
	while( third > 0 )
	{
		++arr[ third % 10 ] ;
		third /= 10 ;
	}

	if( arr[0] != 0 )
		return false ;

	for( int i = 1 ; i < 10 ; i++ )
		if( arr[i] != 1 )
			return false ;

	return true ;
}


int main()
{
	unsigned long long int answer = 0 , panLimit = sqrt(987654321/10) + 1 ;
	std::set<unsigned long long int > set ;

	for( int i = 1 ; i <= 333 ; ++i )
	{
		int jStart =  pow( 10 , 3.5 ) / i , jLimit =  panLimit / i ;

		for( int j = (jStart > i ? jStart : i) ; j <= jLimit + 1 ; ++j )
		{
			if( isPandigital( i , j ) )
			{
				set.insert( i * j ) ;
			}
		}
	}

	for( auto num : set )
		answer += num ;

	std::cout << answer << std::endl ;
	std::cout << "runtime = " << clock()/1000.0f << "s" << std::endl;

	return 0 ;
}