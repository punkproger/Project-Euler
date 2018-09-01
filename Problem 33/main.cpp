#include <iostream>
#include <ctime>

bool isNonTrivial( int first , int second )
{
	double firstF = first / 10 , firstS = first % 10 ;
	double secondF = second / 10 , secondS = second % 10 ;
	double firstVal = first , secondVal = second ;
	
	if(firstS == secondS && firstS == 0 )
		return false ;

	if( secondS > 0 && firstF == secondF &&  firstS / secondS == firstVal / secondVal )
		return true ;
	else if( secondF > 0 && firstF == secondS && firstS / secondF == firstVal / secondVal )
		return true ;
	else if( secondS > 0 && firstS == secondF && firstF / secondS == firstVal / secondVal )
		return true ;
	else if( secondF > 0 && firstS == secondS && firstF / secondF == firstVal / secondVal )
		return true ;

	return false ;

}

int gcd( int first , int second )
{
	if( first % second == 0 )
		return second ;
	return gcd( second , first % second ) ;
}

int main()
{
	int answer = 1 , fProduct = 1 , sProduct = 1 , count = 0 ;

	for( int i = 11 ; i <= 99 && count < 5 ; i++ )
	{
		for( int j = 10 ; j < i ; j++ )
		{
			if( isNonTrivial( j , i ) )
			{
				fProduct *= i ;
				sProduct *= j ;
				++count ;
			}

		}
	}
	answer = fProduct / gcd( fProduct , sProduct ) ;

	std::cout << answer << std::endl ;
	std::cout << "runtime = " << clock()/1000.0f << "s" << std::endl;

	return 0 ;
}