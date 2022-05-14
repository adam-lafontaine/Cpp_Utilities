#include "math.hpp"

#include <cstdio>


int main()
{
    printf("\n**********************\n");
    printf("*                    *\n");
    printf("*  Hello from main!  *\n");
    printf("*                    *\n");
    printf("**********************\n\n");
    
    int a = 2;
    int b = 3;

    printf("%d plus %d equals %d\n", a, b, add(a, b));
    printf("%d minus %d equals %d\n", a, b, subtract(a, b));

    printf("Done.\n");
    
}