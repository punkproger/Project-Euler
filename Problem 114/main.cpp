#include <iostream>
#include <functional>
#include <vector>


using ull = unsigned long long;


ull count(ull items)
{
	ull result{0};

	std::function<void(ull, bool)> impl;
	impl = [&impl, &result](ull items, bool previousIsGrey)
	{
		if (items == 0)
		{
			++result;
			return;
		}

		// gray color
		impl(items-1, true);

		// red color
		if(previousIsGrey)
		{
			if(items >= 3)
			{
				impl(items-3, false);
			}
		}
		else
		{
			impl(items-1, false);
		}
	};

	impl(items, true);

	return result;
}


int main()
{
	std::cout << count(50) << std::endl;

	return 0;
}