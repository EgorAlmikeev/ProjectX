#include "EquationSystems.h"
#include "../MathParser.h"
#include "../MathUtils.h"

static int ToTriangleMatrix(TEqMatrix A, TEqArray B, int n, double epsilon)
{
    double max; //{ Переменная для поиска макс. эл-та }
    int imax;  //{ Переменная для поиска макс. эл-та }
    double tmp, k; //{ Переменная для обмена элементов }
    int i, j, x;   //{ Счетчики циклов }

    for (j = 0; j < n; j++)
    {
        if(IsCancel())
            return 0;

        // ищем максимальный элемент с столбце
        imax = j;
        max = fabs(A[imax][j]);
        for (i = imax; i < n; i++)
            if (fabs(A[i][j]) > max)
            {
                max = fabs(A[i][j]);
                imax = i;
            }

        // такого нет - фейл
        if (max < epsilon)
            return 0;

        // меняем строки местами добиваясь того, чтобы главный элемент был на диагонали
        if (j != imax)
        {
            for (i = 0; i < n; i++)
            {
                tmp = A[j][i];
                A[j][i] = A[imax][i];
                A[imax][i] = -tmp;
            }
            tmp = B[j];
            B[j] = B[imax];
            B[imax] = -tmp;
        }

        // зануляем ниже стоящие элементы, преобразованиями
        for(i = j + 1; i < n; i++)
        {
            k = -A[i][j] / A[j][j];

            // проход по строке
            for(x = 0; x < n; x++)
            {
                A[i][x] = A[i][x] + A[j][x] * k;
            }
            B[i] = B[i] + B[j] * k;
        }

    }

    return 1;
}

static int ToTriangleMatrixNoOptimal(TEqMatrix A, TEqArray B, int n, double epsilon)
{
    int iNoNull;  //{ Переменная для поиска макс. эл-та }
    double tmp, k; //{ Переменная для обмена элементов }
    int i, j, x;   //{ Счетчики циклов }

    for (j = 0; j < n; j++)
    {
        if(IsCancel())
            return 0;

        // ищем не нулевой элемент с столбце
        iNoNull = j;
        for (i = iNoNull; i < n; i++)
            if (fabs(A[i][j]) >= epsilon)
            {
                iNoNull = i;
                break;
            }

        // такого нет - фейл
        if (fabs(A[iNoNull][j]) < epsilon)
            return 0;

        // меняем строки местами добиваясь того, чтобы не нулевой элемент был на диагонали
        if (j != iNoNull)
        {
            for (i = 0; i < n; i++)
            {
                tmp = A[j][i];
                A[j][i] = A[iNoNull][i];
                A[iNoNull][i] = -tmp;
            }
            tmp = B[j];
            B[j] = B[iNoNull];
            B[iNoNull] = -tmp;
        }

        // зануляем ниже стоящие элементы, преобразованиями
        for(i = j + 1; i < n; i++)
        {
            k = -A[i][j] / A[j][j];

            // проход по строке
            for(x = 0; x < n; x++)
            {
                A[i][x] = A[i][x] + A[j][x] * k;
            }
            B[i] = B[i] + B[j] * k;
        }

    }

    return 1;
}

static void ToDiagonalMatrix(TEqMatrix A, TEqArray B, int n)
{
    double k; // Переменная для обмена элементов
    int i, j, x;// Счетчики циклов
    
    for (j = n - 1; j >= 0; j--)
    {
        if(IsCancel())
            return;

        // зануляем вышестоящие элементы, преобразованиями
        for(i = 0; i < j; i++)
        {
            k = -A[i][j] / A[j][j];
            
            // проход по строке
            for(x = 0; x < n; x++)
            {
                A[i][x] = A[i][x] + A[j][x] * k;
            }
            B[i] = B[i] + B[j] * k;
        }   
    }
}

static double SummRow(TEqMatrix A, TEqArray X, int n, int row)
{
    int i;
    double s;

    s = 0;
    for(i = row + 1; i < n; i++)
    {
        s = s + A[row][i] * X[i];
    }

    return s;
}

double GaussNoOptimal(TEqMatrix A, TEqArray B, int n, double epsilon, TEqArray X)
{
    int i;

    if(ToTriangleMatrixNoOptimal(A, B, n, epsilon))
    {
        for(i = n - 1; i >= 0; i--)
        {
            X[i] = (B[i] - SummRow(A, X, n, i)) / A[i][i];
        }
    }
    else
        return NAN;

    return 0;// ok
}

double Gauss(TEqMatrix A, TEqArray B, int n, double epsilon, TEqArray X)
{
    int i;

    if(ToTriangleMatrix(A, B, n, epsilon))
    {
        for(i = n - 1; i >= 0; i--)
        {
            X[i] = (B[i] - SummRow(A, X, n, i)) / A[i][i];
        }
    }
    else
        return NAN;

    return 0;// ok
}

double GaussJordan(TEqMatrix A, TEqArray B, int n, double epsilon, TEqArray X)
{
    int i;

    if(!ToTriangleMatrix(A, B, n, epsilon))
        return NAN;

    ToDiagonalMatrix(A, B, n);

    for(i = 0; i < n; i++)
    {
        X[i] = B[i] / A[i][i];
    }

    return 0;
}



/*int Calc(int k, int n, TEqMatrix AnB, TEqArray M)
{
    int i, j;
   
    for (i = k; i < n; i++)
    {
        M[i] = AnB[i][k] / AnB[k][k]; //множители
        if (M[i] > 1)
        {
            return 0;
        }
    }

    for (i = k; i < n; i++)
        for (j = k; j < n; j++)
            AnB[i][j] = AnB[i][j] - M[i] * AnB[k][j];
    
    return 1;
}

double Summ(int j, int n, TEqMatrix AnB, TEqArray X)
{
    int i;
    double res;
    
    res = AnB[j][n + 1];
    for (i = n - 1; i <= j; i--)
        res = res - AnB[j][i] * X[i];
    
    return res;
}*/


// m - двумерный массив n*n, M - одномерный массив с параметрами
/*double Gauss(TEqMatrix m, TEqArray r, int n, double epsilon, TEqArray ans)
{
    int k;
    
    if(Normalize(m, r, n, epsilon) == 0)
        return -1; // невозможно решить
    

    for (k = 0; k < n; k++)
        if (Calc(k, n, m, ans) == 0)
            return -1; //невозможно решить, обосрались в вычислениях, юзер ввёл говнокоффициенты
    
    ans[n] = m[n][n+1] / m[n][n];
    for (k = n - 1; k < 0; k--)
        ans[k] = Summ(k, n, m, ans)/m[k][k];
    
    return 0; //пока возращаю 0, котому что пока костыль
}*/
