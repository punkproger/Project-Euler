#include <iostream>
#include <functional>
#include <vector>


using ull = unsigned long long;


ull count(ull items)
{
	std::vector<ull> r(items), b(items);
	r[0] = 0; r[1] = 0; r[2] = 1; 
	b[0] = 1; b[1] = 1; b[2] = 1;

	for(size_t i = 3; i < items; ++i)
	{
		r[i] = r[i-1] + b[i-3];
		b[i] = r[i-1] + b[i-1];
	}
	

	return r[items-1] + b[items-1];
}


int main()
{
	std::cout << count(50) << std::endl;

	return 0;
}