#ifndef EQUATIONSSYSTEMSTHREAD_H
#define EQUATIONSSYSTEMSTHREAD_H

#include "XCore.h"

#define ModeEqSysGauss        0
#define ModeEqSysGaussOptimal 1
#define ModeEqSysGaussJordan  2
#define ModeEqSysSquare       3

typedef int ModeEqSys;

class EquationsSystemsThread : public BaseCalcThread
{
    Q_OBJECT

    ModeEqSys mode;
    double    e;
    TEqMatrix matrix;
    TEqArray  params;
    int       n;

public:
    void sendResult(double *ans);

signals:
    void sendResultSignal(double*, int);

public:
    EquationsSystemsThread(TEqMatrix matrix, TEqArray params, int n, double e, ModeEqSys mode);
    void run();
};

#endif // EQUATIONSSYSTEMSTHREAD_H
