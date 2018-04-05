#ifndef EQUATIONTHREADS_H
#define EQUATIONTHREADS_H

#include "XCore.h"

#define ModeEqDich      0
#define ModeEqChord     1
#define ModeEqNewton    2

typedef int ModeEq;

class EquationThread : public BaseCalcThread
{
    Q_OBJECT

    QString func;
    double  a;
    double  b;
    double  e;
    ModeEq  mode;

public:
    void sendResult(double value, int iterations);

signals:
    void sendResultSignal(double, int);

public:
    EquationThread(QString func, double a, double b, double e, ModeEq mode);
    void run();
};

#endif // EQUATIONTHREADS_H
