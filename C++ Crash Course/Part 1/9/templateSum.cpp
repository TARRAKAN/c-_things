#include <cstdio>

template<typename T>
constexpr T sum(T x)
{
    return x;
}

template <typename T, typename... Args>
constexpr T sum(T x, Args... args)
{
    return x + sum(args...);
}

int main()
{
    printf("Answer: %d\n", sum(1,2,3,4,5,6,7,8,9));
    return 0;
}
