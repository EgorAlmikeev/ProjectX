#include "DiffEqEulerMethodThread.h"

DiffEqEulerMethodThread::DiffEqEulerMethodThread(QString func, double x0, double y0, int n, double h, ModeDiff mode)
{
    this->func = func;
    this->x0 = x0;
    this->y0 = y0;
    this->n = n;
    this->h = h;
    this->mode = mode;
}

void DiffEqEulerMethodThread::run()
{
    BaseCalcThread::run();

    qDebug()<<"malloc mem " << n;
    PointFArray result = (PointFArray)malloc(sizeof(TPointF) * n);
    qDebug()<<"malloc mem - ok " << result;

    switch(mode)
    {
    case ModeDiffEuler:
        DifferentialEuler(QStrToCStr(func), x0, y0, n, h, result);
        break;

    case ModeDiffRunge:
        DifferentialRungeKutt(QStrToCStr(func), x0, y0, n, h, result);
        break;

    default:
        return;
    }

    if(IsErrorCalc())
    {
        free(result);
        qDebug()<<"free mem (error)";
        sendError(GetResultCode());
        return;
    }

    if(IsCancel())
    {
        qDebug()<<"free mem (cancel)";
        free(result);
        return;
    }

    sendResult(result);
}

void DiffEqEulerMethodThread::sendResult(PointFArray value)
{
    emit sendResultSignal(value, n);
}
