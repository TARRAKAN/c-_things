#ifndef FIBONACCI_ITERATOR
#define FIBONACCI_ITERATOR

struct FibonacciIterator
{
    explicit FibonacciIterator();
    
    bool operator!=(int x) const;
    
    FibonacciIterator& operator++();
    
    int operator*() const;
    
private:
    int current;
    int last;
};

#endif //FIBONACCI_ITERATOR
