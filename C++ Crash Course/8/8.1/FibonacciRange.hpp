#ifndef FIBONACCI_RANGE
#define FIBONACCI_RANGE

struct FibonacciRange
{
    explicit FibonacciRange(int max);
    
    FibonacciIterator begin() const;
    
    int end() const;
    
private:
    const int max;
};
#endif //FIBONACCI_RANGE
