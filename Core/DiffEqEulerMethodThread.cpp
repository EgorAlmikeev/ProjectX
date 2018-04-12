#include "DiffEqEulerMethodThread.h"

DiffEqEulerMethodThread::DiffEqEulerMethodThread(QString func, double x0, double y0, int n, double h, PointFArray XYArray)
{
    this->func = func;
    this->x0 = x0;
    this->y0 = y0;
    this->n = n;
    this->h = h;
    this->XYArray = XYArray;
}

void DiffEqEulerMethodThread::run()
{
    BaseCalcThread::run();

    DifferentialEuler(QStrToCStr(func), x0, y0, n, h, XYArray);

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
