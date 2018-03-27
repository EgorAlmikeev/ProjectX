//
//  experiment
//

#ifndef MathUtils_h
#define MathUtils_h

#include <math.h>

/*
 пример работы в многопоточном окружении:
 
 var calcThread = nil;
 
 cancel()
 {
    if(calcThread != nil)
    {
        CancelCalc();
        while(!(calcThread.isEnd))
            nop;
    }
 }
 
 change()
 {
    cancel();
 
    output('please wait');
 
    calcThread = new Thread
    {
        mathCalc();
        output(result);
    }
 }
 
 mathCalc()
 {
    BeginCalc();
    while(...)
    {
        if(IsCancel())
            return NAN;
    }
 }
 
*/


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

int IsErrorCalc(void);

// возвращает результат вычисления
ResultCode GetResultCode(void);


#endif /* MathUtils_h */
