#include "Differential.h"
#include "../MathParser.h"
#include "../MathUtils.h"

double DifferentialEuler(char* func, double x0, double y0, int n, double h, PointFArray m)
{
    int i;
    
    for (i = 0; i <= n; i++)
    {
        m[i].x = x0; //передаю в массив
        m[i].y = y0;
        y0 += h * FunctionXY(func, x0, y0);
        x0 += h;
        CheckSyntax();
        CheckCancel();
    }
    
    return 0; //пока так
}

double DifferentialRungeKutt(char* func, double x0, double y0, int n, double h, PointFArray m)
{
    int i;
    double k1,k2,k3,k4;
    
    for (i = 0; i <= n; i++)
    {
        m[i].x = x0;
        m[i].y = y0;
        
        k1 = FunctionXY(func, x0, y0);
        k2 = FunctionXY(func, x0 + h / (float)2, y0 + h * k1 / (float)2);
        k3 = FunctionXY(func, x0 + h / (float)2, y0 + h * k2 / (float)2);
        k4 = FunctionXY(func, x0 + h, y0 + h * k3);
        
        y0 += h*(k1 + 2 * k2 + 2 * k3 + k4) / (float)6;
        x0 += h;
        
        CheckSyntax();
        CheckCancel();
        
    }
    return y0; //пока так
}
