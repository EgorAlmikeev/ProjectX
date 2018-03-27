#ifndef INTEGRAL_THREADS_H
#define INTEGRAL_THREADS_H

#include "X.h"

#define ModeIntLeftRect 0
#define ModeIntRightRect 1
#define ModeIntMidRect 2
#define ModeIntTrapezoid 3
#define ModeIntParabolic 4

typedef int ModeInt;

class IntThread : public BaseCalcThread
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
