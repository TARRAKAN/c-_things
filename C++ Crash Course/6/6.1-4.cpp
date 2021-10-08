#include <cstdio>
#include <algorithm>
#include <type_traits>

template<typename T>
concept bool Modeable()
{
    return std::is_arithmetic<T>::value;
}

template<Modeable T, size_t length>
T mode(const T(&arr)[length])
{
    T values[length]{};

    T num{values[0]};
    T mode{values[0]};
    size_t counter{1};
    size_t counterMode{1};
    
    std::copy(arr, arr+length, values);
    std::sort(values, values+length);

    for(size_t i{1}; i < length; i++)
    {
        if(values[i] == num)
            counter++;
        else
        {
            if(counter > counterMode)
            {
                counterMode = counter;
                mode = num;
            }
            counter = 1;
            num = values[i];
        }
    }
    return mode;
}

int main()
{
    int arr[]{1, 1, 1, 2, 2, 2, 2, 1, 1, 3, 3, 4};
    printf("%d\n", mode(arr));
    float arrF[]{1.1, 1.2, 1.2, 1.2, 2.3, 2.3, 2.3, 1.2};
    printf("%f\n", mode(arrF));
    return 0;
}
