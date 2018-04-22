#include "EquationsSystemsThread.h"

EquationsSystemsThread::EquationsSystemsThread(double **matrix, double *params, double e, ModeEqSys mode)
{
    this->matrix = matrix;
    this->params = params;
    this->e = e;
    this->mode = mode;
}

void EquationsSystemsThread::run()
{
    BaseCalcThread::run();


}
