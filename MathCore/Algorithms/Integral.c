#include "Integral.h"
#include "../MathParser.h"
#include "../MathUtils.h"

double IntLeftRect(char* func, double a, double b, int n)
{
    double s, h, x, fx;

    //BeginCalc();

    s = 0;

    h = (b - a) / (double)n;
    x = a;

    while(x < b)
    {
        fx = FunctionX(func, x);
        if(IsSyntaxError())
        {
            ErrorCalc();
            return NAN;
        }

        s = s + fx;
        x = x + h;

        if(IsCancel())
            return NAN;
    }

  return h * s;
}
