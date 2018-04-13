#ifndef DIFFEQEULERMETHODTHREAD_H
#define DIFFEQEULERMETHODTHREAD_H

#include "XCore.h"

class DiffEqEulerMethodThread : public BaseCalcThread
{
    Q_OBJECT

    QString     func;
    double      x0;
    double      y0;
    int         n;
    double      h;

public:
    void sendResult(PointFArray value);

signals:
    void sendResultSignal(PointFArray, int);

public:
    DiffEqEulerMethodThread(QString func, double x0, double y0, int n, double h);
    void run();
};

#endif // DIFFEQEULERMETHODTHREAD_H
