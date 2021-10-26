#ifndef PRIME_NUMBER_RANGE
#define PRIME_NUMBER_RANGE

struct PrimeNumberIterator
{
    explicit PrimeNumberIterator();
    
    bool operator!=(int num) const;

    PrimeNumberIterator& operator++();
    
    int operator*() const;

private:
    bool isPrime(int num) const;
    int current;
};

struct PrimeNumberRange
{
    explicit PrimeNumberRange(int max);
    
    PrimeNumberIterator begin() const;
    
    int end() const;

private:
    const int max;

};

#endif //PRIME_NUMBER_RANGE
