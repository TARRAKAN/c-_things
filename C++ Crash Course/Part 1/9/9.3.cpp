#include <cstdio>
#include <cstdint>

template <typename Fn, typename In>
constexpr bool all(Fn function, In* input, size_t length)
{
    for(size_t i{}; i < length; i++)
    {
        if(!function(input[i]))
            return false;
    }
    return true;
}

int main()
{
    int data[]{2,4,6,8,10};
    size_t data_len{5};
    auto vAll{all([](auto x){return !(x%2);}, data, data_len)};
    if(vAll) printf("OK\n");
    return 0;
}
