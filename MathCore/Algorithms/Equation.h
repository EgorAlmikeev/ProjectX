#ifndef equation_h
#define equation_h
#include "../MathUtils.h"

double EqHalfDiv(char* func, double a, double b, double epsilon, int* countRef);
double EqChord(char* func, double a, double b, double epsilon, int* countRef);
double EqNewton(char* func, char* derivative, double x0, double epsilon, int* countRef); //derivative - указатель на производную функции

#endif /* equation_h */
