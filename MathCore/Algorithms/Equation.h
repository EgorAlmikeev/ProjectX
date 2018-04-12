#ifndef equation_h
#define equation_h
#include "../MathUtils.h"
typedef double** TArrayXY;

double HalfDiv(char* func, double a, double b, double epsilon, int* countRef);
double Corde(char* func, double a, double b, double epsilon, int* countRef);
double DifferentialEuler(char* func, double x0, double y0, int n, double h, TArrayXY m);

#endif /* equation_h */
