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
        CheckSyntax();

        s = s + fx;
        x = x + h;

        CheckCancel();
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
        CheckSyntax();

        s = s + fx;
        x = x + h;

        CheckCancel();
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
        CheckSyntax();

        s = s + fx;
        x = x + h;

        CheckCancel();
    }

  return h * s;
}

double IntTrapeze(char* func, double a, double b, int n)
{
    double s, h, x, fx;
    double y1, y2;

    s = 0;

    h = (b - a) / (double)n;

    y1 = FunctionX(func, a);
    CheckSyntax();
    
    y2 = FunctionX(func, b);
    CheckSyntax();

    x = a + h;
    while(x < b)
    {
        fx = FunctionX(func, x);
        CheckSyntax();

        s = s + fx;
        x = x + h;

        CheckCancel();
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
        CheckSyntax();

        i = i + 2;
        CheckCancel();
    }

  return s * (h / (double)3);
}
