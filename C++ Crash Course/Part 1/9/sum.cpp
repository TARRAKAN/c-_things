#include <cstdio>
#include <cstdint>
#include <cstdarg>

int sum(size_t n, ...);

int main()
{
    printf("Answer: %d\n", sum(9,1,2,3,4,5,6,7,8,9));//45
    return 0;
}

int sum(size_t n, ...)
{
    va_list args;
    va_start(args, n);
    int result{};
    while(n--)
    {
        auto next_element = va_arg(args, int);
        result+= next_element;
    }
    va_end(args);
    return result;
}
