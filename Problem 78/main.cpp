#include <iostream>
#include <array>

std::array<unsigned long long int,100000> counts = { 1 , 1 , 2 , 3 , 5 , 7 , 11 , 15 , 22 , 30 , 42 } ;

int count( int price )
{
	if( price < 0 )
		return 0 ;

	if( counts[ price ] != 0 )
		return counts[ price ] ;

	long long int sum = 0 ;

	for( int i = 1 ; i <= price && price >= ( i * ( 3 * i - 1 ) ) / 2  ; ++i )
	{
		sum += ( i % 2 == 0 ? -1 : 1 ) * ( count( price - ( i * ( 3 * i - 1 ) ) / 2 ) + count( price - ( i * ( 3 * i + 1 ) ) / 2 ) ) ; 
	}

	sum %= 1000000 ;

	counts[ price ] = sum ;

	return sum ;
}


int main()
{
	int i = 1 ;

	for( i ;  i < counts.size() && count( i ) != 0 ; )
		++i ;

	std::cout << i << std::endl;
	
	return 0 ;
}