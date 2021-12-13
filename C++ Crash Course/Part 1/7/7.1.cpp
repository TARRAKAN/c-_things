#include <cstddef>
#include <cstdint>
class UnsignedBigInteger
{
public:
    explicit UnsignedBigInteger() :
    integer{new uint8_t[128]}
    {
    }
    
    explicit operator int() const
    {

    }   
    
    UnsignedBigInteger& operator+(const UnsignedBigInteger& other) const
    {

    }

    UnsignedBigInteger& operator-(const UnsignedBigInteger& other) const
    {

    }

    UnsignedBigInteger& operator+(const int& other) const
    {

    }
    
    UnsignedBigInteger& operator+(const int& other) const
    {
    
    }

    virtual ~UnsignedBigInteger()
    {
        delete[] integer;
    }
private:
    uint8_t *integer;
};

int main()
{
    UnsignedBigInteger num{};

}
