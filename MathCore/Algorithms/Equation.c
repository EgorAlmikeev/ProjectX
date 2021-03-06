#include "Equation.h"
#include "../MathParser.h"
#include "../MathUtils.h"

static int Sign(double v)
{
    if(v < 0)
        return -1;
    else if(v > 0)
        return 1;
    else return 0;
}

double EqHalfDiv(char* func, double a, double b, double epsilon, int* countRef)
{
    double c = 0;
    int count;

    if(Sign(FunctionX(func, a)) == Sign(FunctionX(func, b)))
    {
        if(countRef != NULL)
            *countRef = 0;
        return NAN;
    }
    
    count = 0;

    if(fabs(FunctionX(func, a)) < epsilon)
    {
        CheckSyntax();
        
        if(countRef != NULL)
            *countRef = count;
        return a;
    }
    
    if(fabs(FunctionX(func, b)) < epsilon)
    {
        CheckSyntax();

        if(countRef != NULL)
            *countRef = count;
        return b;
    }

    while(fabs(b - a) > epsilon)
    {
        count++;
    
        c = a + (b - a) / (float)2;
    
        if (Sign(FunctionX(func, a)) != Sign(FunctionX(func, c)))
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

double EqChord(char* func, double a, double b, double epsilon, int* countRef)
{
    int count;
    
    if(fabs(b - a) < epsilon)
    {
        if(countRef != NULL)
            *countRef = 0;
        return NAN;
    }

    count = 0;   
    
    while(fabs(b - a) > epsilon)
    {
        count++;

        a = b - (b - a) * FunctionX(func, b) / (FunctionX(func, b) - FunctionX(func, a));
        b = a + (a - b) * FunctionX(func, a) / (FunctionX(func, a) - FunctionX(func, b));

        CheckSyntax();
        CheckCancel();
    }
    
    if(countRef != NULL)
        *countRef = count;
    return a;
}

double EqNewton(char* func, char* derivative, double x0, double epsilon, int* countRef)
{
    double x1;
    int count;
    
    count = 0;
    x1  = x0 - FunctionX(func, x0) / FunctionX(derivative, x0); // первое приближение
    CheckSyntax();
    
    if(fabs(x1-x0) < epsilon)
    {
        if(countRef != NULL)
            *countRef = 0;
        return NAN;
    }

    
    while(fabs(x1-x0) > epsilon)
    {
        count++;
        x0 = x1;
        x1 = x1 - FunctionX(func, x1) / FunctionX(derivative, x1);
        
        
        CheckSyntax();
        CheckCancel();
    }
    
    if(countRef != NULL)
        *countRef = count;
    
    return x1;
}

