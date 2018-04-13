#ifndef DIFFEQEULERMETHODTHREAD_H
#define DIFFEQEULERMETHODTHREAD_H

#include "XCore.h"

#define ModeDiffEuler 0
#define ModeDiffRunge 1

typedef int ModeDiff;

class DiffEqEulerMethodThread : public BaseCalcThread
{
    Q_OBJECT

    QString  func;
    double   x0;
    double   y0;
    int      n;
    double   h;
    ModeDiff mode;

public:
    void sendResult(PointFArray value);

signals:
    void sendResultSignal(PointFArray, int);

public:
    DiffEqEulerMethodThread(QString func, double x0, double y0, int n, double h, ModeDiff mode);
    void run();
};

#endif // DIFFEQEULERMETHODTHREAD_H
