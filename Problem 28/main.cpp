#include <iostream>
#include <ctime>

int main()
{
	unsigned int answer = 1 ;
	
	for( int gridSize = 3 ; gridSize <= 1001 ; gridSize += 2 )
	{
		answer += 4 * gridSize * gridSize - 6 * ( gridSize - 1 ) ;
	}

	std::cout << answer << std::endl ;
	std::cout << "runtime = " << clock()/1000.0f << "s" << std::endl;

	return 0 ; 
}