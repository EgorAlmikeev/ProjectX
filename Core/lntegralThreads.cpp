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
    double ans = 0;
    int * iterations = new int;

//свич понадобится если потом придется выбирать метод интегрирования с переменным шагом
//    switch(mode)
//    {
//    case ModeIntDoubleCalc: IntDoubleCalc(..., iterations); break;
//    case ModeIntМетодЕЗ: IntМетодЕЗ; break;
//    default: ans = NAN;
//    }

    if(IsErrorCalc())
    {
        sendError(GetResultCode());
        return;
    }

    if(IsCancel())
        return;

    ans = 1234; //затычка
    sendResult(ans, *iterations);
}
