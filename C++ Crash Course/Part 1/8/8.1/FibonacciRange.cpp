#include"FibonacciIterator.hpp"
#include"FibonacciRange.hpp"

FibonacciRange::FibonacciRange(int max) :
                                            max{max}
{
}
    
FibonacciIterator FibonacciRange::begin() const
{
    return FibonacciIterator{};
}
    
int FibonacciRange::end() const
{
    return max;
}
