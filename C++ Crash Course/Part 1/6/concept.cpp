#include <cstddef>
#include <cstdio>
#include <type_traits>

template<typename T>
concept bool Averadgeable()
{
    return std::is_default_constructible<T>::value
        && requires(T a, T b)
        {
            {a += b} -> T;
            {a / size_t{1}} -> T;
        };
}

template<Averadgeable T>
T mean(T* values, size_t len)
{
    T result{};
    for(size_t i{}; i < len; i++)
    {
        result += values[i];
    }
    return result / len;
}

int main()
{
    double arr[]{1.f,2.f,3.f,4.f};
    auto result = mean(arr, 4);
    printf("%f\n", result);
}
