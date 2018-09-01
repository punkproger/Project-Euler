#include <iostream>
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

int128_t power(int128_t x, int128_t y)
{
    int128_t res = 1;     // Initialize result
  
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
        {
            res = res*x;
            res = res % static_cast<int128_t>( pow( 10 , 10) ) ;
        }
  
        // n must be even now
        y = y>>1; // y = y/2
        x = x*x;  // Change x to x^2
        x = x % static_cast<int128_t>( pow( 10 , 10) ) ;
    }
    return res;
}

int main()
{
    int128_t answer = 0 ;
    
    for( int i = 1 ; i <= 1000 ; i++ ) // There is can be "1 < 1000" , because last 10 digits of 1000^1000 are zeroes
    {
        answer += power( i , i ) ;
        answer = answer % static_cast<int128_t>( pow( 10 , 10) ) ;
    }

    std::cout << answer << std::endl ;
    

    return 0 ;
}