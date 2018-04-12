#ifndef equation_h
#define equation_h
#include "../MathUtils.h"

typedef struct
{
    double x, y;
} TPointF;

typedef TPointF* PointFArray;

double EqHalfDiv(char* func, double a, double b, double epsilon, int* countRef);
double EqChord(char* func, double a, double b, double epsilon, int* countRef);
double DifferentialEuler(char* func, double x0, double y0, int n, double h, PointFArray m);

#endif /* equation_h */
