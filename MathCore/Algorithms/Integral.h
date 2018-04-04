#ifndef INTEGRAL_H
#define INTEGRAL_H

typedef double (*IntFuncRef) (char* func, double a, double b, int n);
double IntDoubleCalc(IntFuncRef IntFunc, char* func, double a, double b, double epsilon, int* count);// это - двойной пересчёт шага

double CalcDoubleInt(char* func, double a, double b, double c, double d, int xn, int yn); // а это - двойной интеграл

double IntLeftRect(char* func, double a, double b, int n);
double IntRightRect(char* func, double a, double b, int n);
double IntMedianRect(char* func, double a, double b, int n);
double IntTrapeze(char* func, double a, double b, int n);
double IntSimpson(char* func, double a, double b, int n);

#endif // INTEGRAL_H
