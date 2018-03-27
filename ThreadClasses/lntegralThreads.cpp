#include "IntegralThreads.h"

IntThread::IntThread(QString func, double a, double b, int n, ModeInt mode)
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
    
    double ans;

    switch(mode)
    {
        case ModeIntLeftRect:
            ans = IntLeftRect(QStrToCStr(func), a, b, n);
            break;
       
        case ModeIntRightRect:
            ans = IntRightRect(QStrToCStr(func), a, b, n);
            break;

        case ModeIntMedianRect:
            ans = IntMedianRect(QStrToCStr(func), a, b, n);
            break;
            
        case ModeIntTrapeze:
            ans = IntTrapeze(QStrToCStr(func), a, b, n);
            break;
            
        case ModeIntSimpson:
            ans = IntSimpson(QStrToCStr(func), a, b, n);
            break;
        
        default:
            ans = NAN;
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
