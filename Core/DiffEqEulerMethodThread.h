#ifndef DIFFEQEULERMETHODTHREAD_H
#define DIFFEQEULERMETHODTHREAD_H

#include "XCore.h"

#define ModeDiffEuler 0
#define ModeDiffRunge 1

#define ErrorTooLongN 1000

typedef int ModeDiff;

class DiffEqEulerMethodThread : public BaseCalcThread
{
    Q_OBJECT

    QString  func;
    double   xStart;
    double   xEnd;
    double   y0;
    double   h;
    int n;
    ModeDiff mode;

public:
    void sendResult(PointFArray value);

signals:
    void sendResultSignal(PointFArray, int);

public:
    DiffEqEulerMethodThread(QString func, double xStart, double xEnd, double y0, double h, ModeDiff mode);
    void run();
};

#endif // DIFFEQEULERMETHODTHREAD_H
