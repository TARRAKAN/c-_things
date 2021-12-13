#include "PrimeNumberRange.hpp"
#include<cmath>

PrimeNumberIterator::PrimeNumberIterator() :
                                        current{2}
{
}
    
bool PrimeNumberIterator::operator!=(int num) const
{
    return num >= current;
}

PrimeNumberIterator& PrimeNumberIterator::operator++()
{
    while(true)
    {
        if(isPrime(++current))
        {
            return *this;
        }
    }
    
}
    
int PrimeNumberIterator::operator*() const
{
    return current;
}

bool PrimeNumberIterator::isPrime(int num) const
{
    for(int i{2}; i <= sqrt(num); i++)
    {
        if(num % i == 0) return false;
    }
    return true;
}

PrimeNumberRange::PrimeNumberRange(int max) :
                                        max{max}
{
}

    
PrimeNumberIterator PrimeNumberRange::begin() const
{
    return PrimeNumberIterator{};
}

int PrimeNumberRange::end() const
{
    return max;
}
