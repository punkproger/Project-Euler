#include <iostream>
#include <cmath>
#include <ctime>


bool isPrime( int x )
{
	if( x == 1 )
		return false ;

	for( int i = 2 ; i <= sqrt( x ) ; i++ )
		if( x % i == 0 )
			return false ;

	return true ;
}

int digitsCount( int x )
{
	int answer = 0 ;
	while( x > 0 )
	{
		++answer ;
		x /= 10 ;
	}
	return answer ;
}

int pow(int base, int exp)
{
    int result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

bool isTruncatablePrime( int x )
{
	int value = x / 10 ;
	while( value > 0 )
	{
		if( !isPrime(value) )
			return false ;
		value /= 10 ;
	}
	
	value = pow( 10 , digitsCount( x ) - 1 ) ;
	
	while( value >= 10 )
	{
		if( !isPrime( x % value ) )
			return false ;

		value /= 10 ;
	}

	return true ;

}

int main()
{
	int answer = 0 , count = 0 ;

	for( int i = 11 ; i < 1000000  && count != 11 ; i += 2 )
		if( isPrime( i ) && isTruncatablePrime( i )  )
		{
			answer += i ;
			count++ ;
		}

	std::cout << answer << std::endl ;
	std::cout << "runtime = " << clock()/1000.0f << "s" << std::endl;

	return 0 ;
}