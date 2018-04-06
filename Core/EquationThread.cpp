#include "EquationThread.h"

EquationThread::EquationThread(QString func, double a, double b, double e, ModeEq mode)
{
    this->func = func;
    this->a = a;
    this->b = b;
    this->e = e;
    this->mode = mode;
}

void EquationThread::run()
{
    BaseCalcThread::run();
    int iterations;
    double ans;

    switch (mode) {
    case ModeEqDich:
        ans = HalfDiv(QStrToCStr(func), a, b, &iterations, e);
        break;
    case ModeEqChord:
//        ans = метод хорд;
        break;
    case ModeEqNewton:
//        ans = метод ньютона;
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

    sendResult(ans, iterations);
}

void EquationThread::sendResult(double value, int iterations)
{
    emit sendResultSignal(value, iterations);
}
