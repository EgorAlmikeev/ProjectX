#include "IntegralThreads.h"

IntThread::IntThread(QString func, double a, double b, int n, IntMode mode)
{
    this->func = func;
    this->a = a;
    this->b = b;
    this->n = n;
    this->mode = mode;
}

void IntThread::run()
{
    BaseCalcThread::run();
    
    switch(mode)
    {
        case ModeIntLeftRect:
            double ans = IntLeftRect(QStrToCStr(func), a, b, n);
            break;
       
        case ModeIntRightRect:
            double ans = IntRightRect(QStrToCStr(func), a, b, n);
            break;
            
        case ModeIntMedianRect:
            double ans = IntMedianRect(QStrToCStr(func), a, b, n);
            break;
            
        case ModeIntTrapeze:
            double ans = IntTrapeze(QStrToCStr(func), a, b, n);
            break;
            
        case ModeIntSimpson:
            double ans = IntSimpson(QStrToCStr(func), a, b, n);
            break;
        
        default:;
    }

    if(IsErrorCalc())
    {
        sendError(GetResultCode());
        return;
    }

    if(IsCancel())
        return;

    sendResult(ans);
}
