//
//  equation.c
//  XProjectLite
//
//  Created by Sophia Kramar on 04.04.18.
//  Copyright © 2018 codeholics. All rights reserved.
//

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

double HalfDiv(char* func, double a, double b, int* count, double epsilon)
{
    double c;
    
    count = 0;
    
    if (fabs(FunctionX(func, a)) < epsilon)
    {
        CheckSyntax();
        CheckCancel();
        return a;
    }
    
    if (fabs(FunctionX(func,b)) < epsilon)
    {
        CheckSyntax();
        CheckCancel();
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
    }
    CheckCancel();
    
    return c;
}

double Corde(char* func, double a, double b, int* count, double epsilon)
{
    double x, t, aOld;
    
    count = 0;
    
    if (a > b)
    {
        t = b;
        b = a;
        a = t;
    }
    
     a = a - (FunctionX(func, a) * (b - a)) / (float)(FunctionX(func, b) - FunctionX(func, a));
    
    return a;
}
