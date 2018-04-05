#ifndef INTEGRAL_H
#define INTEGRAL_H

// Интегрирование с фиксированным числом шагов
double IntLeftRect(char* func, double a, double b, int n);
double IntRightRect(char* func, double a, double b, int n);
double IntMedianRect(char* func, double a, double b, int n);
double IntTrapeze(char* func, double a, double b, int n);
double IntSimpson(char* func, double a, double b, int n);

typedef double (*IntFuncRef) (char* func, double a, double b, int n);
// Двойной пересчёт (в качестве IntFunc можно использовать любой метод)
double IntDoubleCalc(IntFuncRef IntFunc, char* func, double a, double b, double epsilon, int* count);

// Двойной интеграл
double CalcDoubleInt(char* func, double a, double b, double c, double d, int xn, int yn);

#endif // INTEGRAL_H
