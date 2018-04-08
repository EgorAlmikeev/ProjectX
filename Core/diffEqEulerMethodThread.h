#ifndef DIFFEQEULERMETHODTHREAD_H
#define DIFFEQEULERMETHODTHREAD_H

#include "XCore.h"

class DiffEqEulerMethodThread : public BaseCalcThread
{
    Q_OBJECT

    QString func;
    int n;
    double h;
    double x0;
    double y0;

public:
    void sendResult();

signals:
    void sendResultSignal();

public:
    DiffEqEulerMethodThread(QString func, double x0, double y0, int n, double h);
    void run();
};

#endif // DIFFEQEULERMETHODTHREAD_H
