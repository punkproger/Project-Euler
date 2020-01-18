#include <iostream>
#include <cmath>
#include <array>
#include <algorithm>

struct point_t
{
	int x;
	int y;

	bool operator==(const point_t& rhs)
	{
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const point_t& rhs)
	{
		return !(*this == rhs);
	}
};

inline double distance(point_t f, point_t s)
{
	return sqrt((f.x-s.x)*(f.x-s.x) + (f.y-s.y)*(f.y-s.y));
}

inline bool is_equal(double f, double s)
{
	return fabs(f-s) < 1e-4;
}

inline bool isRightTriangle(point_t f, point_t s, point_t t)
{
	if (f == s || s == t || f == t)
	{
		return false;
	}

	std::array<double, 3> distances{distance(f, s),
									distance(f, t),
									distance(s, t)};
	auto max_distance_it =
		std::max_element(distances.begin(), distances.end());
	std::iter_swap(max_distance_it, distances.end()-1);
	
	return is_equal(distances[2]*distances[2], distances[1]*distances[1] +
										 	   distances[0]*distances[0]);
}

int main()
{
	constexpr int c_limit{50};
	int counter{0};

	for (int x_0 = 0; x_0 <= c_limit; ++x_0)
	{
		for (int y_0 = 0; y_0 <= c_limit; ++y_0)
		{
			for (int x_1 = 0; x_1 <= c_limit; ++x_1)
			{
				for (int y_1 = 0; y_1 <= c_limit; ++y_1)
				{
					point_t f{x_0, y_0}, s{x_1, y_1}, t{0, 0};
					if (isRightTriangle(f, s, t))
					{
						++counter;
					}
				}
			}
		}
	}

	std::cout << counter/2 << std::endl;

	return 0;
}