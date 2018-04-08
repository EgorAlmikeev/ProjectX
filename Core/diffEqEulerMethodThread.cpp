#include "diffEqEulerMethodThread.h"

DiffEqEulerMethodThread::DiffEqEulerMethodThread(QString func, double x0, double y0, int n, double h)
{
    this->func = func;
    this->x0 = x0;
    this->y0 = y0;
    this->n = n;
    this->h = h;
}

void DiffEqEulerMethodThread::run()
{
    BaseCalcThread::run();
    //тут каким-то образом будет вызываться алгоритм, в который будет передаваться какой-то указатель

    if(IsErrorCalc())
    {
        sendError(GetResultCode());
        return;
    }

    if(IsCancel())
        return;

    sendResult();
}

void DiffEqEulerMethodThread::sendResult()
{
    emit sendResultSignal();
}
