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
    double ** matrix;
    double  * params;

public:
    EquationsSystemsThread(double **matrix, double *params, double e, ModeEqSys mode);
    void run();
};

#endif // EQUATIONSSYSTEMSTHREAD_H
