#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

struct Point
{
	int x;
	int y;
};

struct Triangle
{
	Point a;
	Point b;
	Point c;
};

double getArea(const Triangle& triangle)
{
	auto& a = triangle.a;
	auto& b = triangle.b;
	auto& c = triangle.c;

	return fabs(a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y)) / 2.0f;
}

bool doesContainOrigin(const Triangle& triangle)
{
	constexpr double eps{0.00000001f};
	constexpr Point origin{0, 0}; 

	double fullArea = getArea({origin, triangle.a, triangle.b})
					+ getArea({origin, triangle.b, triangle.c})
					+ getArea({origin, triangle.a, triangle.c});


	return abs(fullArea - getArea(triangle)) < eps;
}

int main()
{
	std::ifstream file("p102_triangles.txt");
	std::string line;

	size_t result = 0;

	while(std::getline(file, line))
	{
		std::replace(line.begin(), line.end(), ',', ' ');
		std::istringstream in(line);
		std::vector<int> vec;

		std::copy(std::istream_iterator<int>(in), std::istream_iterator<int>(), std::back_inserter(vec));

		result += doesContainOrigin(Triangle{Point{vec[0], vec[1]},
									 		 Point{vec[2], vec[3]},
									 		 Point{vec[4], vec[5]}});
	}

	std::cout << result << std::endl;

	return 0;
}