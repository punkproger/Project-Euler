#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdint>

using ull = __int128_t;

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

inline ull digit_sum(ull number) {
	ull result = 0;
	
	do {
		result += number%10;
	}
	while(number /= 10);

	return result;
}

inline ull binary_pow(ull base, ull exp)
{
    ull result = 1;
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

int main() {
	constexpr ull necessaryIndex = 29;
	std::vector<ull> powerSums;
	powerSums.reserve(100);

	constexpr auto bitcount = 128;

	for(int x = 1; x < 100; ++x) {
		const int maxDegree = float(bitcount)/log2(x);
		for(int y = 1; y <= maxDegree; ++y) {
			const ull powValue = binary_pow(x, y);
			if(digit_sum(powValue) == x && powValue >= 10) {
				powerSums.push_back(powValue);
			}
		}
	}

	std::sort(powerSums.begin(), powerSums.end());

	std::cout << "Result: " << powerSums[necessaryIndex] << std::endl;

	return 0;
}