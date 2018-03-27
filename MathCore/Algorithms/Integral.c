#include "Integral.h"
#include "../MathParser.h"
#include "../MathUtils.h"

double IntLeftRect(char* func, double a, double b, int n)
{
    double s, h, x, fx;

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

double IntRightRect(char* func, double a, double b, int n)
{
    double s, h, x, fx;

    s = 0;

    h = (b - a) / (double)n;
    x = a + h;

    while(x < b + h)
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

double IntMedianRect(char* func, double a, double b, int n)
{
    double s, h, x, fx;

    s = 0;

    h = (b - a) / (double)n;
    x = a + h * 0.5;

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

double IntTrapeze(char* func, double a, double b, int n)
{
    double s, h, x, fx;
    double y1, y2;

    s = 0;

    y1 = FunctionX(func, a);
    if(IsSyntaxError())
        {
            ErrorCalc();
            return NAN;
        }
    
    y2 = FunctionX(func, b);
    if(IsSyntaxError())
        {
            ErrorCalc();
            return NAN;
        }

    x = a + h;

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

  return h * ((y1 + y2) / (double)2 + s);
}

double IntSimpson(char* func, double a, double b, int n)
{
    double s, h;
    int i;

    h = (b - a) / (double)n;

    s = 0;
    i = 1;

    while(i <= n - 1)
    {
        s = s + FunctionX(func, (a + (i + 1) * h)) + FunctionX(func, (a + (i - 1) * h));// s1
        s = s + 4 * FunctionX(func, (a + i * h));// s2

        if(IsSyntaxError())
        {
            ErrorCalc();
            return NAN;
        }

        i = i + 2;
        if(IsCancel())
            return NAN;
    }

  return s * (h / (double)3);
}
