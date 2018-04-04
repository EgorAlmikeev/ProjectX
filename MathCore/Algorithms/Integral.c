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

#define DefaultInterationCount 10

double IntDoubleCalc(IntFuncRef IntFunc, char* func, double a, double b, double epsilon, int* count) //это - двойной пересчёт шага
{
    double s, s2;
    int InterationCount, n;

    n = DefaultInterationCount;
    InterationCount = n;
    s2 = IntFunc(func, a, b, n);
    CheckSyntax();
    
    do
    {
        s = s2;
        n = n * 2;
        s2 = IntFunc(func, a, b, n);
        CheckSyntax();
        
        InterationCount += n;
    
        CheckCancel();
    }
    while (fabs(s - s2) > epsilon);
    
    if(count != NULL)
        *count = InterationCount;
    
    return s2;
}

double CalcDoubleInt(char* func, double a, double b, double c, double d, int xn, int yn) // а это - двойной интеграл
{
    double x, y, xh, yh;
    double i = 0;
    
    xh = (b - a) / (float)xn;
    yh = (d - c) / (float)yn;
    
    for(x = a + xh * 0.5; x < b; x += xh)
    {
        for(y = c + yh * 0.5; y < d; y += yh)
        {
            i += FunctionXY(func, x, y);
            CheckSyntax();
            CheckCancel();
        }
        CheckCancel();
    }
    
    return i * xh * yh;
}
