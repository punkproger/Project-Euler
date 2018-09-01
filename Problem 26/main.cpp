#include <iostream>
#include <map>
#include <ctime>


int getSequenceCount( int number , int size = 1000 )
{
	std::map< int , int > map ;
	int current = 10 ;
	for( int i = 0 ; i < size && current > 0 ; i++ )
	{
		if( current < number )
		{
			current *= 10 ;
			continue ;
		}
		else if( map.find( current % number ) == map.end() )
		{
			map[ current % number ] = i ;
			current %= number ;
			current *= 10 ;
		}
		else
		{
			return i - map.find( current % number )->second ;
		}
	}

	return 0 ;
}

int main()
{
	int bestMatch = 2 , bestValue = 0 ;
	for( int i = 3 ; i < 1000 ; i += 2 )
	{
		if( i % 2 != 0 && i % 5 != 0 && getSequenceCount(i) > bestValue )
		{
			bestMatch = i ;
			bestValue = getSequenceCount( i ) ;
		}
	}
	std::cout << "1/" << bestMatch << " has cycle sequence of " << bestValue << " digits " << std::endl ;
	std::cout << "runtime = " << clock()/1000.0f << "s" << std::endl;

	return 0 ;
}