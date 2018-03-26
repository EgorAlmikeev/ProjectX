#include "IntegralThreads.h"

IntLeftRectThread::IntLeftRectThread(QString func, double a, double b, int n)
{
    this->func = func;
    this->a = a;
    this->b = b;
    this->n = n;
}

void IntLeftRectThread::run()
{
    BaseCalcThread::run();

    double ans = IntLeftRect(QStrToCStr(func), a, b, n);

    if(IsErrorCalc())
    {
        sendError(GetResultCode());
        return;
    }

    if(IsCancel())
        return;

    sendResult(ans);
}
