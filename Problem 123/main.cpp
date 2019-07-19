#include <iostream>
#include <vector>
#include <cstring>


using ull = __uint128_t;

std::ostream&
operator<<( std::ostream& dest, __int128_t value )
{
    std::ostream::sentry s( dest );
    if ( s ) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do
        {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );
        if ( value < 0 ) {
            -- d;
            *d = '-';
        }
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}


std::vector<ull> get_primes(ull max){
    std::vector<ull> primes;
    char *sieve;
    sieve = new char[max/8+1];
    // Fill sieve with 1  
    memset(sieve, 0xFF, (max/8+1) * sizeof(char));
    for(ull x = 2; x <= max; x++)
        if(sieve[x/8] & (0x01 << (x % 8))){
            primes.push_back(x);
            // Is prime. Mark multiplicates.
            for(ull j = 2*x; j <= max; j += x)
                sieve[j/8] &= ~(0x01 << (j % 8));
        }
    delete[] sieve;
    return primes;
}

inline ull binary_pow(ull base, ull exp, ull mod)
{
    //std::cout << base << "^" << exp << "%" << mod << " = ";

    ull result    = 1;
    ull decreaser = 5;
    ull newBase   = 1;

    for(int i = 0; i < decreaser; ++i) {
        newBase *= base;
    }

    while (exp >= decreaser)
    {
        result = (result * newBase) % mod;
        exp -= decreaser;
    }

    while (exp--)
    {
        result = (result * base) % mod;
        
    }
 
    //std::cout << result << std::endl;

    return result;
}

int main() {
    ull remainder{0};
    auto primes = get_primes(1e6);
    int i = 7037;

    for(i; i < primes.size() && remainder < 1e10; ++i) {
        ull prime = primes[i];
        ull mod   = prime*prime;
        ull exp   = i + 1;
        remainder = (binary_pow(prime-1, exp, mod) + binary_pow(prime+1, exp, mod)) % mod;
        //std::cout << std::endl;
    }

    std::cout << i << std::endl;

    return 0;
}