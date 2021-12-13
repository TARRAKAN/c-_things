#include <cstdio>
#include <cstdint>
#include <cstring>

int main(int argc, char* argv[])
{
    for(size_t i{1}; i < argc; i++)
    {
        printf("[%4ld]", i);
        for(size_t j{}; j < strlen(argv[i]); j++)
            printf("*");
        printf("\n");
    }
    return 0;
}
