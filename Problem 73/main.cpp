#include <stdio.h>
#include <stdlib.h>

int farey_based_solution(const int n) {
    int count = n % 3 == 0 ? 0 : 1;
    int a = 1;
    int b = 3;
    int c = n / 3;
    int d = c * 3 - 1;
    while(!(c == 1 && d == 2)) {
        ++count;
        int k = (n + b) / d;
        int temp = k * c - a;
        a = c;
        c = temp;
        temp = k * d - b;
        b = d;
        d = temp;
    }
    return count;
}

int main(int argc, const char * argv[]) {
    
    const int limit = 12000;
    printf("Farey based solution: %d\n", farey_based_solution(limit));
    
    return 0;
}
