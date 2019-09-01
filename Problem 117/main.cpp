#include <iostream>
#include <functional>
#include <vector>


using ull = unsigned long long;

ull count(int m)
{
    ull a{0}, b{0}, c{0}, d{1};

    for (int i = 0; i < m; ++i)
    {
    	auto tmp = a+b+c+d;

    	a = b;
    	b = c;
    	c = d;
    	d = tmp;
    }

    return d;
}



int main()
{
	std::cout << count(50) << std::endl;

	return 0;
}