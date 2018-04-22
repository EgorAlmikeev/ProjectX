#include "EquationSystems.h"
#include "../MathParser.h"
#include "../MathUtils.h"

int Normalize(TMat AnB, int n, double epsilon)
{

    double max; //{ Переменная для поиска макс. эл-та }
    int imax;  //{ Переменная для поиска макс. эл-та }
    double tmp; //{ Переменная для обмена элементов }
    int i,j;   //{ Счетчики циклов }
    
    for (j = 1; j <= n; j++)
    {
        max = fabs(AnB[1][j]);
        imax = 1;
        for (i = 2; i <= n; i++)
        {
            if (fabs(AnB[i][j]) > max)
            {
                max = fabs(AnB[i][j]);
                imax = i;
            }
        if (max < epsilon)
        {
            return 0; //систему заданными методами решить не получится
        }
        else
        if (j != imax)
            for (i = 1; i <= n + 1; i++)
            {
                tmp = AnB[j][i];
                AnB[j][i] = AnB[imax][i];
                AnB[imax][i] = tmp;
            }
        }
    }
    for (i = 1; i <= n; i++)
    {
        tmp = 0;
        for (j = 1; j <= n; j++)
            if (i != j)
                tmp = tmp + fabs(AnB[i][j]);
            if (fabs(AnB[i][i]) < tmp)
                return 1; //с-му можно решить только методом Гаусса
    }
    return 2; //с-му можно решать любым методом
}

int Calc(int k, int n, TMat AnB, TMatt M)
{
    int i,j;
   
    for (i = k + 1; i <= n; i++)
    {
        M[i] = AnB[i][k]/AnB[k][k]; //множители
        if (M[i] > 1)
        {
            return 0;
        }
    }

    for (i = k + 1; i <= n; i++)
        for (j = k; j <= n + 1; j++)
            AnB[i][j] = AnB[i][j] - M[i] * AnB[k][j];
    
    return 1;
}

double Summ(int j, int n, TMat AnB, TMatt X)
{
    int i;
    double res;
    
    res = AnB[j][n+1];
    for (i = n; i <= j+1; i--)
        res = res - AnB[j][i] * X[i];
    
    return res;
}


// m - двумерный массив n*n, M - одномерный массив с параметрами
double Gauss(TMat m, TMatt M, int n, double epsilon, double* ans)
{
    int k;
    
    if (Normalize(m, n, epsilon) == 0)
        return -1 ; // невозможно решить, обосрались на нормализации, юзер ввёл говнокоффициенты
    
    for (k = 1; k <= n-1; k++)
        if (Calc(k, n, m, M) == 0)
            return -1; //невозможно решить, обосрались в вычислениях, юзер ввёл говнокоффициенты
    
    ans[n] = m[n][n+1] / m[n][n];
    for (k = n - 1; k <= 1; k--)
        ans[k] = Summ(k, n, m, M)/m[k][k];
    
    return ans[n]; //это массив с иксами, забирайте
}
