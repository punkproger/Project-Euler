#include <iostream>
#include <string>
#include <cmath>
#include <vector>

int main()
{

	long long int arr[10] = { 0 } ;

	std::string tmp , token[10] ;

	for( int j = 0 ; j < 100 ; j++ )
	{
		std::cin >> tmp ;

		for( int i = 9 ; i >= 0 ; i-- )
		{
			token[i] = tmp ;
			token[i].erase( 0 , i * 5 ) ;
			token[i].erase( 5 , token[i].size() - 5 ) ;

			arr[i] += std::stoi( token[i] ) ;


			if( i != 0 )
			{
				arr[ i - 1 ] += arr[ i ] / static_cast<int>( pow( 10 , 5 ) ) ;
				arr[i] = arr[i] % static_cast<int>( pow( 10 , 5 ) ) ;
			}
		}

	}



	
	std::cout << "\n\n\n\n\n\n\n\n" ;


	/*for( auto num : arr )
		std::cout << num ;*/

	std::cout << arr[0] << ' ' << arr[1] ;
	std::cout << std::endl ;

	return 0 ;
}