#include "DiffEqEulerMethodThread.h"

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

    PointFArray result = (PointFArray) malloc(sizeof(TPointF) * n);

    DifferentialEuler(QStrToCStr(func), x0, y0, n, h, result);

    if(IsErrorCalc())
    {
//        free(result);
        sendError(GetResultCode());
        return;
    }

    if(IsCancel())
    {
//        free(result);
        return;
    }

    sendResult(result);
}

void DiffEqEulerMethodThread::sendResult(PointFArray value)
{
    emit sendResultSignal(value, n);
}
