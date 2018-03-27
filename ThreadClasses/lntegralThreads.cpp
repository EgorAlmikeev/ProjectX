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
            
        case ModeIntMidRect:
            ans = IntMedianRect(QStrToCStr(func), a, b, n);
            break;
            
        case ModeIntTrapezoid:
            ans = IntTrapeze(QStrToCStr(func), a, b, n);
            break;
            
        case ModeIntParabolic:
            ans = IntSimpson(QStrToCStr(func), a, b, n);
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
