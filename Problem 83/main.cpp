#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include <iostream>
#include <ctime>
#include <algorithm>

void chooseBestWays(int fromX , int fromY , const std::vector< std::vector<int> > & values , std::vector< std::vector<int> > & lenghts )
{
	if( fromX != 79 || fromY != 79 )
	{	
			if( fromY != 79 && lenghts[fromY + 1 ][fromX] > lenghts[fromY][fromX] + values[fromY + 1 ][fromX] )
			{
				lenghts[fromY + 1 ][fromX] = lenghts[fromY][fromX] + values[fromY + 1 ][fromX] ;
				chooseBestWays( fromX , fromY + 1 , values , lenghts ) ;
			}

			if( fromY != 0 && lenghts[fromY - 1 ][fromX] > lenghts[fromY][fromX] + values[fromY - 1 ][fromX] )
			{
				lenghts[fromY - 1 ][fromX] = lenghts[fromY][fromX] + values[fromY - 1 ][fromX] ;
				chooseBestWays( fromX , fromY - 1 , values , lenghts ) ;
			}

			if( fromX != 79 && lenghts[fromY][fromX + 1] > lenghts[fromY][fromX] + values[fromY][fromX + 1] )
			{
				lenghts[fromY][fromX + 1] = lenghts[fromY][fromX] + values[fromY][fromX + 1] ;
				chooseBestWays( fromX + 1 , fromY , values , lenghts ) ;
			}

			if( fromX != 0 && lenghts[fromY][fromX - 1] > lenghts[fromY][fromX] + values[fromY][fromX - 1] )
			{
				lenghts[fromY][fromX - 1] = lenghts[fromY][fromX] + values[fromY][fromX - 1] ;
				chooseBestWays( fromX - 1 , fromY , values , lenghts ) ;
			}
	}
}

int main()
{
	std::vector< std::vector<int> > values , lenghtsTo ;

	std::ifstream ifs("text.txt");
    std::vector<std::string> words;

    std::copy(std::istream_iterator<std::string>(ifs), std::istream_iterator<std::string>(), std::back_inserter(words));
    int counter = 0 ;
    
	for( int i = 0 ; i < 80 ; i++ )
	{
		values.push_back( std::vector<int>( 80 ) ) ;
		lenghtsTo.push_back( std::vector<int>( 80 , 999999 ) ) ;
		for( int j = 0 ; j < 80 ; j++ )
		{
			values[i][j] = std::stoi(words[counter++]) ;
		}
	}

	lenghtsTo[0][0] = values[0][0] ;
	
	auto firstTime = clock() ;

	chooseBestWays( 0 , 0 , values , lenghtsTo ) ;

	std::cout << lenghtsTo[79][79] << std::endl ;
	
	std::cout << "runtime = " << ( clock() - firstTime )/1000.0f << "s" << std::endl;
	
	return 0 ;
}

