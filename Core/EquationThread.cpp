#include "EquationThread.h"

EquationThread::EquationThread(QString func, double a, double b, double e, ModeEq mode)
{
    this->setObjectName("EquationThread");
    this->func = func;
    this->a = a;
    this->b = b;
    this->e = e;
    this->mode = mode;
}

EquationThread::EquationThread(QString func, QString derivative, double x1, double e, ModeEq mode)
{
    this->setObjectName("EquationThread");
    this->func = func;
    this->derivative = derivative;
    this->a = x1;
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

        case ModeEqNewton:
            ans = EqNewton(QStrToCStr(func), QStrToCStr(derivative), x1, e, &iterations);
            break;

        default:
            return;
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
