#ifndef INTEGRAL_THREADS_H
#define INTEGRAL_THREADS_H

#include "XCore.h"

#define ModeIntLeftRect     0
#define ModeIntRightRect    1
#define ModeIntMedianRect   2
#define ModeIntTrapeze      3
#define ModeIntSimpson      4
#define ModeIntDoubleCalc   5

typedef int ModeInt;

class IntConstStepThread : public BaseCalcThread
{
    Q_OBJECT

    QString func;
    double  a;
    double  b;
    int     n;
    ModeInt mode;

public :
    IntConstStepThread(QString func, double a, double b, int n, ModeInt mode);
    void run();
};


class IntFloatingStepThread : public BaseCalcThread
{
    Q_OBJECT

    QString func;
    double  a;
    double  b;
    double  e;
    ModeInt mode;

public:
    void sendResult(double value, int iterations);

signals:
    void sendResultSignal(double /*value*/, int /*iterations*/);

public :
    IntFloatingStepThread(QString func, double a, double b, double e, ModeInt mode);
    void run();
};

#endif // INTEGRAL_THREADS_H
