#include <iostream>
#include <functional>
#include <vector>


using ull = unsigned long long;


ull count(ull items, size_t red_block_size)
{
	std::vector<ull> r(items), b(items);
	
	for(size_t i = 0; i < red_block_size; ++i)
	{

		r[i] = (i+1)/red_block_size;	
		b[i] = 1;
	}

	for(size_t i = red_block_size; i < items; ++i)
	{
		r[i] = r[i-red_block_size] + b[i-red_block_size];
		b[i] = r[i-1] + b[i-1];
	}
	
	// -1 for case that there should be at least one colored tape
	return r[items-1] + b[items-1] - 1;
}


int main()
{
	std::cout << count(50, 2) + count(50, 3) + count(50, 4) << std::endl;

	return 0;
}