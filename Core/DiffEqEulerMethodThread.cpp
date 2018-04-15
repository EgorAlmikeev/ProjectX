#include "DiffEqEulerMethodThread.h"

DiffEqEulerMethodThread::DiffEqEulerMethodThread(QString func, double xStart, double xEnd, double y0, double h, ModeDiff mode)
{
    this->setObjectName("DiffEqEulerMethodThread");
    this->func = func;
    this->xStart = xStart;
    this->xEnd = xEnd;
    this->y0 = y0;
    this->h = h;
    this->mode = mode;
}

void DiffEqEulerMethodThread::run()
{
    BaseCalcThread::run();

    n = (int)ceil(fabs(xStart - xEnd) / h) + 1;

    if(n > 10000 + 1)
    {
        sendError(ErrorTooLongN);
        return;
    }

    if(xEnd < xStart)
        h = -h;

    PointFArray result = (PointFArray)malloc(sizeof(TPointF) * n);

    switch(mode)
    {
        case ModeDiffEuler:
            DifferentialEuler(QStrToCStr(func), xStart, y0, n, h, result);
            break;

        case ModeDiffRunge:
            DifferentialRungeKutt(QStrToCStr(func), xStart, y0, n, h, result);
            break;

        default:
            return;
    }

    if(IsErrorCalc())
    {
        free(result);
        sendError(GetResultCode());
        return;
    }

    if(IsCancel())
    {
        free(result);
        return;
    }

    sendResult(result);
}

void DiffEqEulerMethodThread::sendResult(PointFArray value)
{
    emit sendResultSignal(value, n);
}
