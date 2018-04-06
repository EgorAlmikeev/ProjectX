#include "Equation.h"
#include "../MathParser.h"
#include "../MathUtils.h"

int Sign(double v)
{
    if(v < 0)
        return -1;
    else if(v > 0)
        return 1;
    else return 0;
}

double HalfDiv(char* func, double a, double b, double epsilon, int* countRef)
{
    double c = 0;
    int count;
    
    count = 0;
    
    if (fabs(FunctionX(func, a)) < epsilon)
    {
        CheckSyntax();
        
        if(countRef != NULL)
            *countRef = count;
        return a;
    }
    
    if (fabs(FunctionX(func,b)) < epsilon)
    {
        CheckSyntax();
        if(countRef != NULL)
            *countRef = count;
        return b;
    }
    while (fabs(b - a) > epsilon)
    {
        count += 1;
    
        c = a + (b - a) / (float)2;
    
        if (Sign(FunctionX(func,a)) != Sign(FunctionX(func,c)))
            b = c;
        else
            a = c;
        CheckSyntax();
        CheckCancel();
    }
    
    if(countRef != NULL)
        *countRef = count;
    return c;
}

double Chord(char* func, double a, double b, double epsilon, int* countRef)
{
    double t, aOld;
    int count;
    
    count = 0;
    
    if (a > b)
    {
        t = b;
        b = a;
        a = t;
    }
    
    a = a - (FunctionX(func, a) * (b - a)) / (float)(FunctionX(func, b) - FunctionX(func, a));
    CheckSyntax();
    do
    {
        count = count + 1;
    
        aOld = a;
        a = a - (FunctionX(func, a) * (b - a)) / (float)(FunctionX(func, b) - FunctionX(func, a));
        CheckSyntax();
        CheckCancel();

    }
    while (fabs(a - aOld) > epsilon);
    
    if(countRef != NULL)
        *countRef = count;
    return a;
}
