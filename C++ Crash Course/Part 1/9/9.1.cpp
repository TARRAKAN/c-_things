#include <cstdio>
#include <cstdint>

template<typename Fn, typename In, typename Out>
constexpr Out fold(Fn function, In* input, size_t length, Out initial)//IDK what is "initial".
{
    Out toReturn{initial};
    for(size_t i{}; i < (length); i++)
    {
        toReturn = function(toReturn, input[i]);
    }
    return toReturn;
}

int main()
{
    int data[]{100, 200, 300, 400, 500};
    size_t data_len{5};
    auto sum = fold([](auto x, auto y){return x + y;}, data, data_len, 0);
    printf("Sum: %d\n", sum);
    auto max = fold([](auto x, auto y){return (x > y) ? x : y;}, data, data_len, 0);
    printf("Max: %d\n", max);
    auto min = fold([](auto x, auto y){return (x > y) ? y : x;}, data, data_len, 100);
    printf("Min: %d\n", min);
    auto ht200 = fold([](auto x, auto y){return (y > 200) ? ++x : x;}, data, data_len, 0);
    printf("ht200: %d\n", ht200);
    return 0;
}
