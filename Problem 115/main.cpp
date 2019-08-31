#include <iostream>
#include <functional>
#include <vector>


using ull = unsigned long long;


ull count(ull items, size_t red_block_size)
{
	std::vector<ull> r(items), b(items);
	
	for(size_t i = 0; i < red_block_size; ++i)
	{

		r[i] = (i != (red_block_size-1) ? 0 : 1);	
		b[i] = 1;
	}

	for(size_t i = red_block_size; i < items; ++i)
	{
		r[i] = r[i-1] + b[i-red_block_size];
		b[i] = r[i-1] + b[i-1];
	}
	

	return r[items-1] + b[items-1];
}


int main()
{
	size_t func_value{0}, i;

	for(i = 100; func_value < 1e6;)
	{
		++i;
		func_value = count(i, 50);
	}

	std::cout << i << std::endl;

	return 0;
}