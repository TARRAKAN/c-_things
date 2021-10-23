#include<cstdio>
#include"FibonacciIterator.hpp"
#include"FibonacciRange.hpp"

int main()
{
    for(const auto i : FibonacciRange{5000})
    {
        printf("%d ", i);
    }
    printf("\n");
    return 0;
}
