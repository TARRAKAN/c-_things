#include <cstdio>

using operation_func = float(*)(float, float);
float sum(float x, float y);
float sub(float x, float y);

int main()
{
    const float x{4.3};
    const float y{2.1};
    operation_func operation{sum};
    printf("%f\n", operation(x, y));
    operation = sub;
    printf("%f\n", operation(x, y));
    return 0;
}

float sum(float x, float y)
{
    return x + y;
}

float sub(float x, float y)
{
    return x - y;
}
