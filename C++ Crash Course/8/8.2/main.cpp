#include "PrimeNumberRange.hpp"
#include <cstdio>

int main()
{
    for(const auto i: PrimeNumberRange{1000})
    {
        printf("%d ", i);
    }
    printf("\n");
    return 0;
}
