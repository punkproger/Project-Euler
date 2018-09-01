#include <iostream>
#include <cmath>
#include <set>


int main()
{
	//It's so fucking stupid solution , in my opinion this an do only lazy and stupid programmer , I did this with another idea but turn back ,  because my ass *BOOM* , this is really so stupid way and 99/100 from Project Euler did like this , gg
	std::set<double> set ;
	for( int i = 2 ; i <= 100 ; i++ )
	{
		for( int j = 2 ; j <= 100 ; j++ )
			set.insert( pow( i , j ) ) ;
	}

	std::cout << set.size() << std::endl ;

	return 0 ;
		
}