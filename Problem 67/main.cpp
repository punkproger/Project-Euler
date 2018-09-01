#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include <iostream>
#include <ctime>
#include <algorithm>

void chooseBestWays(int fromX , int fromY , const std::vector< std::vector<int> > & values , std::vector< std::vector<int> > & lenghts )
{
	if( fromY < 99 )
	{
		if( values[ fromY + 1 ][ fromX ] > values[ fromY + 1 ][ fromX + 1 ] )
		{
			for( int x = 0 ; x <= 1 ; x++ )
			{
				if( lenghts[ fromY + 1 ][fromX + x ] < lenghts[fromY][fromX] + values[fromY + 1 ][fromX + x ] )
				{
					lenghts[ fromY + 1 ][fromX + x ] = lenghts[fromY][fromX] + values[fromY + 1 ][fromX + x ] ;
					chooseBestWays( fromX + x , fromY + 1 , values , lenghts ) ;
				}
			}
		}
		else
		{
			for( int x = 1 ; x >= 0 ; x-- )
			{
				if( lenghts[ fromY + 1 ][fromX + x ] < lenghts[fromY][fromX] + values[fromY + 1 ][fromX + x ] )
				{
					lenghts[ fromY + 1 ][fromX + x ] = lenghts[fromY][fromX] + values[fromY + 1 ][fromX + x ] ;
					chooseBestWays( fromX + x , fromY + 1 , values , lenghts ) ;
				}
			}
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
    
	for( int i = 0 ; i < 100 ; i++ )
	{
		values.push_back( std::vector<int>( i + 1 ) ) ;
		lenghtsTo.push_back( std::vector<int>( i + 1 , 0 ) ) ;
		for( int j = 0 ; j <= i ; j++ )
		{
			values[i][j] = std::stoi(words[counter++]) ;
		}
	}

	lenghtsTo[0][0] = values[0][0] ;
	auto firstTime = clock() ;
	chooseBestWays( 0 , 0 , values , lenghtsTo ) ;

	std::cout << *std::max_element( lenghtsTo[99].begin() , lenghtsTo[99].end() ) << std::endl ;
	
	std::cout << "runtime = " << ( clock() - firstTime )/1000.0f << "s" << std::endl;
	
	return 0 ;
}

