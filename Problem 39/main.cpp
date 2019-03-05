#include <iostream>
#include <utility>
#include <cmath>

int countTriangles (int p){

     int count =0;

     for (int a=2; a< (p/3); a++)
           if (p*(p-2*a) % (2*(p-a)) == 0) 
              count++;
          
    return count;
}



int main() {
	size_t result{0}, actual{0};
	for(int i = 2; i <= 1000; i += 1) {
		int tmp = countTriangles(i);
		if(result < tmp) {
			actual = i;
			result = tmp;
		}
	}
	std::cout << actual << std::endl;

	return 0;
}