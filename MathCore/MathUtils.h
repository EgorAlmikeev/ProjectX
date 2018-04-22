#ifndef MathUtils_h
#define MathUtils_h

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// чем закончилось последнее вычисление
// успешное завершение
#define CalcOk  0
// отмена вычисления
#define CalcCancel 1
// заершение по таймауту
#define CalcTimeout 2
// ошибка парсинга выражения/или другая ошибка
#define CalcError 3
// - calcError + n - пользовательские ошибки
#define ResultCode int

#ifndef NAN
    #define NAN (0.0/0.0)
#endif

#define IsNan(v) ((v) != (v))

#define CheckSyntax() \
    do{ \
        if(IsSyntaxError()) \
        { \
            ErrorCalc(); \
            return NAN; \
        } \
    }while(0)

#define CheckCancel() \
    do{ \
        if(IsCancel()) \
            return NAN; \
    }while(0)

// начало вычисления, необходимо вызвать перед циклом вычислений
void BeginCalc(void);

// принудительное завешение вычисления, вы должны дождатся завешения потока
// устанавливает ResultCode в CalcCancel
void CancelCalc(void);

// принудительное завешение вычисления по таймауту, вы должны дождатся завешения потока
// устанавливает ResultCode в CalcTimeout
void TimeoutCalc(void);

// устанавливает ResultCode в CalcError
void ErrorCalc(void);

// возвращает не 0, если вычисления необходимо прервать,
// данную функцию надо вызывать в основном цикле вычислений
int IsCancel(void);

// возвращает не 0, если есть ошибка в формуле,
// данную функцию надо вызывать в основном цикле вычислений
int IsErrorCalc(void);

// возвращает код, чем закончилось последнее вычисление
ResultCode GetResultCode(void);

// возвращает двумерный массив указанного размера
double ** CreateMatrix(const int rows, const int columns);

// освобождает память двумерного массива, с указанным количеством строк
void DestroyMatrix(double **matrix, const int rows);

#endif /* MathUtils_h */
