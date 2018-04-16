#ifndef XMATH_H
#define XMATH_H

#include "MathParser.h"
#include "MathUtils.h"

/*
 
 Типичное использование библиотеки XMath:
 
 #include "XMath.h"
 
 ...
 double ans;
 ...
 // вызов обязателен!
 BeginCalc();
 
 // вызов одной из функций вычисления, например
 ans = IntTrapeze("sin(x)", 0, 1, 10000);
 
 //-----------------------------------------------------------------------------
 // Из отдельного потока мы можем вызывать следующие функциии:
 // CancelCalc(); - для отмены текущего вычисления
 // TimeoutCalc(); - для прерывания по таймауту
 // данные функции устанавливают соответсвующий код заверешения: GetResultCode
 //-----------------------------------------------------------------------------
 
 // проверяем на ошибки
 if(IsErrorCalc())
 {
    // необходимые действия при ошибке
 }
 ...
 
*/

// Сишные алгоритмы ложить только сюда
#include "Algorithms/Integral.h"
#include "Algorithms/Equation.h"
#include "Algorithms/Differential.h"
#include "Algorithms/Maclarin.h"

#endif // XMATH_H
