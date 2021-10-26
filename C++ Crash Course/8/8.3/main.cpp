#include "PrimeNumberRange.hpp"
#include"FibonacciRange.hpp"
#include <cstdio>

int main()
{
    printf("Prime:\n");
    for(const auto i: PrimeNumberRange{1000})
    {
        printf("%d ", i);
    }
    printf("\n");
    
    printf("Fibonacci:\n");
    for(const auto i : FibonacciRange{5000})
    {
        printf("%d ", i);
    }
    printf("\n");
    return 0;
}
