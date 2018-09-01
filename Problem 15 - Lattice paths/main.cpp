#include <iostream>
#include <vector>
#include <cstdlib>

class trying
{
private:
	std::vector<bool> way ;
	int current ;
public:
	trying()
	{
		way.resize( 40 ) ;
		current = 0 ;
	}

	void add( bool whatDid )
	{
		way[ current ] = whatDid ;
		++current ;
	}

	trying& operator=( trying & right )
	{
		way = right.way ;
	}

	void clear()
	{
		current = 0 ;
		way.clear() ;
		way.resize( 40 ) ;
	}

	bool operator==( trying right )
	{
		
		for( int i = 0 ; i < 40 ; i++ )
			if( way[ i ] != right.way[ i ] )
				return false ;

		return true ;
	}

};

struct IAM
{
	int x ;
	int y ;
};



int main()
{
	//int map[ 20 ] ;
	std::vector<trying> allTryings ;
	int sleeptime = 0 ;
	trying tmp ;
	IAM hero ;
	
	while( sleeptime < 400 )
	{ 
		hero.x = 0 ; hero.y = 0 ;

		while( hero.x != 19 && hero.y != 19 )
		{

			if( hero.x == 19 )
			{
				++hero.y ;
				tmp.add( true ) ;
			}
			else if( hero.y == 19 )
			{
				++hero.x ; 
				tmp.add( false ) ;
			}
			else
			{
				if( rand()%2 )
				{
					++hero.y ;
					tmp.add( true ) ;
				}
				else
				{
					++hero.x ; 
					tmp.add( false ) ;
				}

			}


		}

		bool unique = true ; 

		for( int i = 0 ; i < allTryings.size() ; i++ ) 
			if( tmp == allTryings[ i ] )
			{ 
				unique = false ;
				break ;
			}

		if( unique )
		{
			allTryings.push_back( tmp ) ;
			sleeptime = 0 ;
		}
		else
			++sleeptime ;

		std::cout << allTryings.size() << std::endl ;

		tmp.clear() ;
	}

	std::cout << allTryings.size() << std::endl ;

	return 0 ;
	

}