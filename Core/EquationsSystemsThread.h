#ifndef EQUATIONSSYSTEMSTHREAD_H
#define EQUATIONSSYSTEMSTHREAD_H

#include "XCore.h"

#define ModeEqSysGauss      0
#define ModeEqSysOptimal    1
#define ModeEqSysJordan     2
#define ModeEqSysSquare     3

typedef int ModeEqSys;

class EquationsSystemsThread : public BaseCalcThread
{
    Q_OBJECT

    ModeEqSys mode;
    double    e;
    TMat      matrix;
    TMatt     params;
    int       n;

public:
    void sendResult(double *ans);

signals:
    void sendResultSignal(double*, int);

public:
    EquationsSystemsThread(TMat matrix, TMatt params, int n, double e, ModeEqSys mode);
    void run();
};

#endif // EQUATIONSSYSTEMSTHREAD_H
