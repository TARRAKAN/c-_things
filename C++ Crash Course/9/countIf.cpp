#include <cstdio>
#include <cstdint>

struct CountIf
{
    CountIf(char x) : x{ x }
    {
    }
    
    size_t operator()(const char* str) const
    {
        size_t index{};
        size_t result{};
        while(str[index])
        {
            if(str[index] == x) result++;
            index++;
        }
        return result;
    }
private:
    const char x;
};

int main()
{
    CountIf counter{'s'};
    size_t sally = counter("Sally sells seashels by the seashore.");
    size_t sailor = counter("Sailor went to sea to see what he could see");
    size_t buffalo = CountIf{'f'}("Buffalo buffalo Buffalo buffalo Buffalo buffalo Buffalo buffalo.");
    printf("Sally: %zu\nSailor: %zu\nBuffalo: %zu\n", sally, sailor, buffalo);
    return 0;
}
