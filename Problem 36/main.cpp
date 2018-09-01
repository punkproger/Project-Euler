#include <iostream>
#include <vector>
#include <ctime>

inline bool isPalindrom( int number , int system )
{
	std::vector<int> digits ;

	while( number > 0 )
	{
		digits.push_back( number % system ) ;
		number /= system ;
	}
	
	int size = digits.size() ;

	for( int i = 0 ; i < size / 2 ; i++ )
		if( digits[i] != digits[ size - 1 - i ] )
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

int main()
{
	int answer = 0 ;
	for( int i = 1 ; i < 1000000 ; i += 2 )
	{
		if( (i % 10) == i / pow( 10 , digitsCount( i ) - 1 ) && isPalindrom( i , 10 ) && isPalindrom( i , 2 ) )
			answer += i ;
	}
	std::cout << answer << std::endl ;
	std::cout << "runtime = " << clock()/1000.0f << "s" << std::endl;
	return 0 ;
}