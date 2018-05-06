#include "EquationsSystemsThread.h"

EquationsSystemsThread::EquationsSystemsThread(TEqMatrix matrix, TEqArray params, int n, double e, ModeEqSys mode)
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

    double *result = (double*)malloc(n * sizeof(double));
    double resultCode = 0;

    switch(mode)
    {
        case ModeEqSysGauss:
            resultCode = GaussNoOptimal(matrix, params, n, e, result);
            break;

        case ModeEqSysGaussOptimal:
            resultCode = Gauss(matrix, params, n, e, result);
            break;

        case ModeEqSysGaussJordan:
           resultCode = GaussJordan(matrix, params, n, e, result);
//           for(int i = 0; i < n; i++)
//           {
//               QString s = "";
//               for(int j = 0; j < n; j++)
//               {
//                   s = s + QString::number(matrix[i][j]) + ",  ";
//               }
//               qDebug() << s;
//           }
           break;

        case ModeEqSysSquare:

        for(int i = 0; i < n; ++i)
        {
            result[i] = i * i;
        }

            break;

        default:
            return;
    }

    DestroyMatrix(matrix, n);
    free(params);

    if(IsNan(resultCode))
    {
        ErrorCalc();
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

    sendResult(result);
}

void EquationsSystemsThread::sendResult(double *ans)
{
    emit sendResultSignal(ans, n);
}
