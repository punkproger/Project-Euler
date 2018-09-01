#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <cctype> 

int main()
{
	std::map<unsigned int , unsigned int > funcValues ;

	for( int i = 1 ; i <= 100 ; i++ )
		funcValues[ (i * i + i)/2 ] = i ;

	std::ifstream input("text.txt") ;

	char symbol ;
	unsigned int tmpValue = 0 , answer = 0 ;

	while( input.get(symbol) )
	{
		if( isalpha(symbol) )
		{
			tmpValue += static_cast<unsigned int>( symbol ) - 64 ;
		}
		else if( tmpValue != 0 )
		{
			if( funcValues.find( tmpValue ) != funcValues.end() )
				++answer ;

			tmpValue = 0 ;
		}
	}

	std::cout << answer << std::endl ;

	input.close() ;

	return 0 ;
}
