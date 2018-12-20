#include <iostream>
#include <cstdint>
#include <ctime>

typedef long long int l_int;

__int128 modexp(__int128 x, __int128 y, __int128 N)
{
  if (y == 0) return 1;
  __int128 z = modexp(x, y / 2, N);
  if (y % 2 == 0)
    return (z*z) % N;
  else
    return (x*z*z) % N;
}


int main()
{
	int degree = 7830457, multyplier = 28433, result = 2;
	
	std::cout << long(modexp(2, degree, long(1e10)) * multyplier+ 1) % long(1e10) << std::endl; 
	//There is troubles while using __int128 and 'cout <<' -- I converted to long
	std::cout << "runtime = " << clock()/1000000.0f << "s" << std::endl;
	return 0;
}