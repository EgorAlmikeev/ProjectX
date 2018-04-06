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
        case ModeEqHalfDiv:
            ans = EqHalfDiv(QStrToCStr(func), a, b, e, &iterations);
            break;

        case ModeEqChord:
            ans = EqChord(QStrToCStr(func), a, b, e, &iterations);
            break;

        default:
            ans = 0;
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
