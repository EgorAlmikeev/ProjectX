#include "Maclarin.h"
#include "../MathParser.h"
#include "../MathUtils.h"


// An/A(n-1) = -x^2/((2*n+2)*(2*n+3))
double MaclarinSin(double x, double epsilon, int* count)
{
    int c, n;
    double ans, mul, old;

    x = fmod(x, M_PI);

    mul = x;
    ans = x;

    c = 0;
    n = 0;
    do
    {
        old = mul;

        mul = mul * (-(x * x) / (double)((2 * n + 2) * (2 * n + 3)));
        ans = ans + mul;

        n++;
        c++;
    }
    while(fabs(mul - old) > epsilon);

    if(count != NULL)
        *count = c;

    return ans;
}

// An/A(n-1) = -x^2/((2*n+1)*(2*n+2))
double MaclarinCos(double x, double epsilon, int* count)
{
    int c, n;
    double ans, mul, old;

    x = fmod(x, M_PI);

    mul = 1;
    ans = 1;

    c = 0;
    n = 0;
    do
    {
        old = mul;

        mul = mul * (-(x * x) / (double)((2 * n + 1) * (2 * n + 2)));
        ans = ans + mul;

        n++;
        c++;
    }
    while(fabs(mul - old) > epsilon);

    if(count != NULL)
        *count = c;

    return ans;
}
