#ifndef Differential_h
#define Differential_h
#include "../MathUtils.h"

typedef struct    //волшебная структура
{
    double x, y;
} TPointF;

typedef TPointF *PointFArray;

double DifferentialEuler(char* func, double x0, double y0, int n, double h, PointFArray m);
double DifferentialRungeKutt(char* func, double x0, double y0, int n, double h, PointFArray m);


#endif /* Differential_h */
