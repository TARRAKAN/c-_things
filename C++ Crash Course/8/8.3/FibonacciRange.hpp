#ifndef FIBONACCI_RANGE
#define FIBONACCI_RANGE
#include"FibonacciIterator.hpp"

struct FibonacciRange
{
    explicit FibonacciRange(int max);
    
    FibonacciIterator begin() const;
    
    int end() const;
    
private:
    const int max;
};
#endif //FIBONACCI_RANGE
