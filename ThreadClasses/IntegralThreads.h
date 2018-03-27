#ifndef INTEGRAL_THREADS_H
#define INTEGRAL_THREADS_H

#include "X.h"

#define ModeIntLeftRect 0
#define ModeIntRightRect 1
#define ModeIntMedianRect 2
#define ModeIntTrapeze 3
#define ModeIntSimpson 4

typedef int ModeInt;

class IntLeftRectThread : public BaseCalcThread
{
    Q_OBJECT

    QString func;
    double  a;
    double  b;
    int     n;
    ModeInt mode;

public :
    IntThread(QString func, double a, double b, int n, ModeInt mode);
    void run();
};
#endif // INTEGRAL_THREADS_H
