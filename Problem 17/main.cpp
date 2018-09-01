#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>

std::vector<std::vector<int>> wordLenght(
{
	{0,3,3,5,4,4,3,5,5,4,3,6,6,8,8,7,7,9,8,8},
	{0,0,6,6,5,5,5,7,6,6},
	{7}
});

int countLetter( int number )
{
	int result = 0 , counter = log10( number ) ;

	if( number > 100 && number % 100 != 0 )
		result += 3 ;

	if( number >= 100 )
	{
		result += wordLenght[0][ number/100 ] + wordLenght[2][0] ;
	}

	if( number % 100 == 0 )
	{
		return result ;
	}
	else if( number % 100 < 20 )
	{
		result += wordLenght[0][number % 100] ;
	}
	else
	{
		result += wordLenght[0][number % 10 ] ;
		number /= 10 ;
		result += wordLenght[1][number % 10 ] ;
	}
		
	

	return result;
}

int main()
{
	int answer = 11 ;
	for( int i = 1 ; i < 1000 ; i++ )
	{
		answer += countLetter( i ) ;
	}

	std::cout << answer << std::endl ;
	std::cout << "runtime = " << clock()/1000.0f << "s" << std::endl;
	
	return 0 ;
}