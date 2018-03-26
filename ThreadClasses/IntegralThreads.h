#ifndef INTEGRAL_THREADS_H
#define INTEGRAL_THREADS_H

#include "X.h"

class IntLeftRectThread : public BaseCalcThread
{
    Q_OBJECT

    QString func;
    double  a;
    double  b;
    int     n;

public :
    IntLeftRectThread(QString func, double a, double b, int n);
    void run();
};
#endif // INTEGRAL_THREADS_H
