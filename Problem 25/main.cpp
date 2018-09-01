#include <iostream>
#include <cmath>


const long double phi = 1.61803398874989484820458683436563811772030917980576  ;

double func( int x )
{
	return (log10(10) * x + log10(5)/2.0f )/log10(phi) ;
}

int main()
{
	std::cout << round(func(999)) << std::endl ;
	return 0 ;
}