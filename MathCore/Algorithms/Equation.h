#ifndef equation_h
#define equation_h
#include "../MathUtils.h"

typedef struct
{
    double x, y;
} TPointF;

double EqHalfDiv(char* func, double a, double b, double epsilon, int* countRef);
double EqChord(char* func, double a, double b, double epsilon, int* countRef);

#endif /* equation_h */
