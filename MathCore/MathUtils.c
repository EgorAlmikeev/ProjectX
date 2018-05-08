//
//  CoreMath.c
//  experiment
//

#include "MathUtils.h"

static ResultCode resultCode = CalcOk;
static int isCancel = 0;

void BeginCalc(void)
{
    resultCode = CalcOk;
    isCancel = 0;
}

int IsCancel(void)
{
    return isCancel;
}

void CancelCalc(void)
{
    isCancel = 1;
    resultCode = CalcCancel;
}

void TimeoutCalc(void)
{
    isCancel = 1;
    resultCode = CalcTimeout;
}

void ErrorCalc(void)
{

    resultCode = CalcError;
}

int IsErrorCalc(void)
{
    return resultCode >= CalcTimeout;
}

ResultCode GetResultCode(void)
{
    return resultCode;
}

double** CreateMatrix(const int rows, const int columns)
{
    double **matrix;
    int i;

    matrix = (double**)malloc(rows * sizeof(double *));

    for (i = 0; i < rows; ++i)
        matrix[i] = (double*)malloc(columns * sizeof(double));

    return matrix;
}

void DestroyMatrix(double** matrix, const int rows)
{
    int i;

    for (i = 0; i < rows; ++i)
        free(matrix[i]);

    free(matrix);
}
