#include <array>
using std::array;

//2.9

// #include <cstdio>
// int main()
// {
//     array<int, 4> arr{ 1, 2, 3, 4 };
//     printf("The third element is %d.\n", arr[2]);
//     arr[2] = 100;
//     printf("The third element is %d.\n", arr[2]);
// }

//2.10

// #include <cstddef>
// #include <cstdio>
// int main()
// {
//     unsigned long maximum = 0;
//     array<unsigned long, 5> values = { 10, 50, 20, 40, 0 };
//     for(size_t i=0; i < 5; i++){
//         if (values[i] > maximum) maximum = values[i];
//     }
//     printf("The maximum value is %lu", maximum);
// }

//2.11

// #include <cstdio>
// int main()
// {
//     unsigned long maximum = 0;
//     array<unsigned long, 5> values = { 10, 50, 20, 40, 0 };
//     for(auto value: values){
//         if (value > maximum) maximum = value;
//     }
//     printf("The maximum value is %lu", maximum);
// }
