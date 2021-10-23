#include"FibonacciIterator.hpp"

FibonacciIterator::FibonacciIterator() :
                                    current{1},
                                    last{1}
{
}
    
bool FibonacciIterator::operator!=(int x) const 
{
    return x >= current;
}
    
FibonacciIterator& FibonacciIterator::operator++()
{
    const auto tmp = current;
    current += last;
    last = tmp;
    return *this;
}
    
int FibonacciIterator::operator*() const
{
    return current;
}
