#include <iostream>
#include <vector>
#include <ctime>

std::vector<int> nominals = { 1 , 2 , 5 , 10 , 20 , 50 , 100 , 200 } ;

int count( int price , int maxcoin )
{
	int sum = 0 ;
	
	if( maxcoin == 7 )
		return 1 ;
	
	for( int i = maxcoin ; i < 8 ; i++ )
	{
		if( price - nominals[i] == 0 )
			sum += 1 ;
		else if( price - nominals[i] > 0 )
			sum += count( price - nominals[i] , i ) ;
	}

	return sum ;
}
int main()
{
	std::cout << count( 200 , 0 ) << std::endl ;
	std::cout << "runtime = " << clock()/1000.0f << "s" << std::endl;

	return 0 ;
}