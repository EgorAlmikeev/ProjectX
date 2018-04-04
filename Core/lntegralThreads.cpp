#include "IntegralThreads.h"

IntConstStepThread::IntConstStepThread(QString func, double a, double b, int n, ModeInt mode)
{
    this->func = func;
    this->a = a;
    this->b = b;
    this->n = n;
    this->mode = mode;
}

void IntConstStepThread::run()
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

IntFloatingStepThread::IntFloatingStepThread(QString func, double a, double b, double e, ModeInt mode)
{
    this->func = func;
    this->a = a;
    this->b = b;
    this->e = e;
    this->mode = mode;
}

void IntFloatingStepThread::sendResult(double value, int iterations)
{ emit sendResultSignal(value, iterations); }

void IntFloatingStepThread::run()
{
    BaseCalcThread::run();

    double ans = 0;
    int iterations = 0;
    IntFuncRef funcRef;

    switch(mode)
    {
        case ModeIntLeftRect:
            funcRef = IntLeftRect;
            break;

        case ModeIntRightRect:
            funcRef = IntRightRect;
            break;

        case ModeIntMedianRect:
            funcRef = IntMedianRect;
            break;

        case ModeIntTrapeze:
            funcRef = IntTrapeze;
            break;

        case ModeIntSimpson:
            funcRef = IntSimpson;
            break;

        default:
            ans = NAN;
    }

    if(!IsNan(ans))
        ans = IntDoubleCalc(funcRef, QStrToCStr(func), a, b, e);

    if(IsErrorCalc())
    {
        sendError(GetResultCode());
        return;
    }

    if(IsCancel())
        return;

    sendResult(ans, iterations);
}
