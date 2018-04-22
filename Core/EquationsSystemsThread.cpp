#include "EquationsSystemsThread.h"

EquationsSystemsThread::EquationsSystemsThread(TMat matrix, TMatt params, int n, double e, ModeEqSys mode)
{
    this->setObjectName("EquationsSystemsThread" + QString::number(mode));
    this->matrix = matrix;
    this->params = params;
    this->n = n;
    this->e = e;
    this->mode = mode;
}

void EquationsSystemsThread::run()
{
    BaseCalcThread::run();

    double *result = (double*) malloc(n * sizeof(double));

    switch(mode)
    {
    case ModeEqSysGauss:
//        Gauss(matrix, params, n, e, result);
        for(int i = 0; i < n; ++i)
        {
            result[i] = i * i;
        }
        break;

    case ModeEqSysJordan:

        break;

    case ModeEqSysOptimal:

        break;

    case ModeEqSysSquare:

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

    DestroyMatrix(matrix, n);
    free(params);

    sendResult(result);
}

void EquationsSystemsThread::sendResult(double *ans)
{
    emit sendResultSignal(ans, n);
}
