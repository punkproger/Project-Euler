#include <iostream>
#include <algorithm>
#include <random>
#include <functional>


using ull = unsigned int;

constexpr ull size = 15;
constexpr ull def_val = 0;

using vector_t = std::array<ull, size>; 
using matrix_t = std::array<vector_t, size>; 


void zeroMatrix(matrix_t& matrix) 
{
	for(auto& arr : matrix)
	{
		for(auto& item : arr)
		{
			item = def_val;
		}
	}
}

ull getMaxPath(const matrix_t& matrix)
{
	matrix_t lenghts;
	zeroMatrix(lenghts);


	std::function<void(size_t, size_t, std::array<bool, size>)> impl;
	impl = [&impl, &lenghts, &matrix]
	(size_t x, size_t y, std::array<bool, size> taken_rows)
	{
		if(x == size - 1)
		{
			return;
		}

		size_t next_x = x + 1;
		static std::vector<size_t> idxs{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};

		static std::random_device rd;
    	static std::mt19937 g(rd());

		std::shuffle(idxs.begin(), idxs.end(), g);

		for(size_t next_y : idxs)
		{
			const ull path_length = matrix[next_y][next_x] + lenghts[y][x];
			if(matrix[next_y][next_x] > 800 && false == taken_rows[next_y] && path_length > lenghts[next_y][next_x])
			{
				lenghts[next_y][next_x] = path_length;

				taken_rows[next_y] = true;
				impl(next_x, next_y, taken_rows);
				taken_rows[next_y] = false;
			}
		}
	};

	const size_t def_start_value = 200;
	size_t iterations = def_start_value;
	ull max{0}, prev_max{0};

	do
	{
		for(size_t y = 0; y < size; ++y)
		{
			std::array<bool, size> taken;
			std::fill(taken.begin(), taken.end(), false);
			taken[y] = true;

			lenghts[y][0] = matrix[y][0];

			impl(0, y, taken);

			for(size_t y_for_last = 0; y_for_last < size; ++y_for_last)
			{
				ull value = lenghts[y_for_last][size-1];
				if(max < value)
				{
					max = value;
				}
			}
			zeroMatrix(lenghts);
		}
		if (iterations == 1 && max > prev_max) 
		{
			iterations = def_start_value;
			prev_max = max;
		}
	}while(--iterations);

	return max;
}


int main()
{
	matrix_t matrix = 	   {vector_t{7  , 53,  183, 439, 863, 497, 383, 563, 79,  973, 287, 63, 343,  169, 583},
							vector_t{627, 343, 773, 959, 943, 767, 473, 103, 699, 303, 957, 703, 583, 639, 913},
							vector_t{447, 283, 463, 29,  23,  487, 463, 993, 119, 883, 327, 493, 423, 159, 743},
							vector_t{217, 623, 3,   399, 853, 407, 103, 983, 89,  463, 290, 516, 212, 462, 350},
							vector_t{960, 376, 682, 962, 300, 780, 486, 502, 912, 800, 250, 346, 172, 812, 350},
							vector_t{870, 456, 192, 162, 593, 473, 915, 45,  989, 873, 823, 965, 425, 329, 803},
							vector_t{973, 965, 905, 919, 133, 673, 665, 235, 509, 613, 673, 815, 165, 992, 326},
							vector_t{322, 148, 972, 962, 286, 255, 941, 541, 265, 323, 925, 281, 601, 95,  973},
							vector_t{445, 721, 11,  525, 473, 65,  511, 164, 138, 672, 18,  428, 154, 448, 848},
							vector_t{414, 456, 310, 312, 798, 104, 566, 520, 302, 248, 694, 976, 430, 392, 198},
							vector_t{184, 829, 373, 181, 631, 101, 969, 613, 840, 740, 778, 458, 284, 760, 390},
							vector_t{821, 461, 843, 513, 17,  901, 711, 993, 293, 157, 274, 94,  192, 156, 574},
							vector_t{34 , 124, 4,   878, 450, 476, 712, 914, 838, 669, 875, 299, 823, 329, 699},
							vector_t{815, 559, 813, 459, 522, 788, 168, 586, 966, 232, 308, 833, 251, 631, 107},
							vector_t{813, 883, 451, 509, 615, 77,  281, 613, 459, 205, 380, 274, 302, 35,  805}};

	std::cout << getMaxPath(matrix) << std::endl;
	
	return 0;
}
