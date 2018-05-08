//  ProjectX
//  MathParser.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <setjmp.h>
#include <string.h>
#include "MathParser.h"

// types
typedef int boolean;
#define true 1
#define false 0
#define MaxTokenLength 32

typedef enum
{
    tokenUndefined,
    tokenEnd,
    tokenNumber,
    tokenAdd,
    tokenSub,
    tokenMul,
    tokenDiv,
    tokenPower,
    tokenFactorial,
    tokenLB,
    tokenRB,
    tokenValue,
    tokenFunction,
} tokens;

// parser variables
static char *eq;// указатель на формулу
static char *p;// указатель на текущий символ
static char *prevToken;// указатель на предидущий токен
static tokens token;// тип текущего токена
static double doubleValue;// последнее считанное значение
static char stringValue[MaxTokenLength + 1];// последнее считанное значение
static jmp_buf saveState;// используеться для восстановления состояния после ошибки
static double x = 0, y = 0;
static int isSyntaxError;

static void error(int isSyntaxErr, const char *str)
{
    isSyntaxError = isSyntaxErr;
    longjmp(saveState, 1);// восстанавливаем состояние
}

static void nextToken(void)
{
    int i;

    prevToken = p;

    while(*p == ' ' || *p == '\t')
      p++;

    switch(*p)
    {
        case '+':
            p++;
            token = tokenAdd;
            break;

        case '-':
            p++;
            token = tokenSub;
            break;

        case '*':
            p++;
            token = tokenMul;
            break;

        case '/':
            p++;
            token = tokenDiv;
            break;

        case '^':
            p++;
            token = tokenPower;
            break;

        case '(':
            p++;
            token = tokenLB;
            break;

        case ')':
            p++;
            token = tokenRB;
            break;

        case '!':
            p++;
            token = tokenFactorial;
            break;

        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            sscanf(p, "%lf%n", &doubleValue, &i);
            p += i;
            token = tokenNumber;
            break;

        case 0:
            token = tokenEnd;
            break;

        default:
            if((('a' <= *p) && ('z' >= *p)) ||
               (('A' <= *p) && ('Z' >= *p)) ||
               (*p == '_'))
            {
                i = 0;
                stringValue[i] = *p;
                while((('a' <= *p) && ('z' >= *p)) ||
                      (('A' <= *p) && ('Z' >= *p)) ||
                      (*p == '_') ||
                      (('0' <= *p) && ('9' >= *p)))
                {
                    stringValue[i] = *p;

                    if(i > MaxTokenLength)
                    {
                        error(1, "Too long token");
                    }

                    i++;
                    p++;
                }

                stringValue[i] = 0;
                token = tokenValue;
                if(*p == '(')
                {
                    token = tokenFunction;
                    p++;
                }
            }
            else
                error(1, "Unexpected symbol");
            break;
    }
}

static double tryPow(void);
static double tryAdd(void);

static int factorial(int n)
{
    int r;
    for (r = 1; n > 1; r *= (n--));
    return r;
}

static boolean compName(const char *s1, const char *s2)
{
    char c1, c2;
    for(;;)
    {
        if(*s1 == 0 || *s2 == 0)
            break;
        c1 = (*s1 >= 'A' && *s1 <= 'Z')? *s1 + 'a' - 'A' : *s1;
        c2 = (*s2 >= 'A' && *s2 <= 'Z')? *s2 + 'a' - 'A' : *s2;

        if(c1 != c2)
            return false;
        s1++;
        s2++;
    }
    return (*s1 == 0) && (*s2 == 0);
}

static double tryPrim(void)
{
    double left, t;

    nextToken();
    left = doubleValue;

    switch (token)
    {
        case tokenNumber:
            nextToken();
            if(token == tokenLB)
                error(1, "Unexpected symbol");
            return left;

        case tokenSub:
            return -tryPow();

        case tokenLB:
            left = tryAdd();
            if(token != tokenRB)
                error(1, "Expected right bracket");
            nextToken();
            return left;

        case tokenValue:
            if(compName(stringValue, "pi"))
                left = M_PI;
            else if(compName(stringValue, "e"))
                left = M_E;
            else if(compName(stringValue, "x"))
                left = x;
            else if(compName(stringValue, "y"))
                left = y;
            else
                error(1, "Identifier not found");
            nextToken();
            if((token == tokenNumber) || (token == tokenLB) || (token == tokenValue) || (token == tokenFunction))
                error(1, "Unexpected symbol");
            return left;

        case tokenFunction:
            if(compName(stringValue, "sin"))
            {
                left = sin(tryAdd());
            }
            else if(compName(stringValue, "cos"))
            {
                left = cos(tryAdd());
            }
            else if(compName(stringValue, "asin"))
            {
                t = tryAdd();
                if(fabs(t) > 1.0)
                    error(0, "Bad angle");
                left = asin(t);
            }
            else if(compName(stringValue, "acos"))
            {
                t = tryAdd();
                if(fabs(t) > 1.0)
                    error(0, "Bad angle");
                left = acos(t);
            }
            else if(compName(stringValue, "atan"))
            {
                left = atan(tryAdd());
            }
            else if(compName(stringValue, "abs"))
            {
                left = fabs(tryAdd());
            }
            else if(compName(stringValue, "tan"))
            {
                left = tan(tryAdd());
            }
            else if(compName(stringValue, "ctan"))
            {
                t = tryAdd();
                if((sin(t) == 0.0))
                    error(0, "Bad angle");
                left = cos(t) / sin(t);
            }
            else if(compName(stringValue, "actan"))
            {
                t = tryAdd();
                left = M_PI / 2.0 - atan(t);
            }
            else if(compName(stringValue, "log"))
            {
                left = log(tryAdd());
            }
            else if(compName(stringValue, "exp"))
            {
                left = exp(tryAdd());
            }
            else if(compName(stringValue, "sqrt"))
            {
                t = tryAdd();
                if(t >= 0.0)
                    left = sqrt(t);
                else
                    error(0, "Negative sqrt");
            }
            else
                error(1, "Identifier not found");
            if(token != tokenRB)
                error(1, "Expected right bracket");
            nextToken();
            if((token == tokenNumber) || (token == tokenLB) || (token == tokenValue) || (token == tokenFunction))
                error(1, "Unexpected symbol");
            return left;

        default:
            if(token == tokenEnd)
                error(1, "Unexpected end");
            else
                error(1, "Unexpected symbol");
            return left;
    }
}

static double tryFact(void)
{
    double left;

    left = tryPrim();

    for(;;)
    {
        switch (token)
        {
            case tokenFactorial:
                if(left < 0)
                    error(0, "Negative factorial");
                left = factorial((int)left);
                nextToken();
                break;

            default:
                return left;
        }
    }
}

static double tryPow(void)
{
    double left;

    left = tryFact();

    for(;;)
    {
        switch (token)
        {
            case tokenPower:
                left = powf(left, tryFact());
                break;

            default:
                return left;
        }
    }
}

static double tryMul(void)
{
    double left, d;

    left = tryPow();

    for(;;)
    {
        switch (token)
        {
            case tokenMul:
                left = left * tryPow();
                break;

            case tokenDiv:
                d = tryPow();
                if(d != 0)
                    left = left / d;
                else
                    error(0, "Division by zero");
                break;

            default:
                return left;
        }
    }
}

static double tryAdd(void)
{
    double left;

    left = tryMul();

    for(;;)
    {
        switch (token)
        {
            case tokenAdd:
                left = left + tryMul();
                break;

            case tokenSub:
                left = left - tryMul();
                break;

            default:
                return left;
        }
    }
}

double Expression(char *exp)
{
    double result;

    isSyntaxError = 0;

    eq = exp;
    p = exp;

    if(setjmp(saveState) == 0)
    {
        if(exp[0] == '\0')
            error(1, "Empty String");
        result = tryAdd();
        if(token != tokenEnd)
            error(1, "Unexpected symbol (end)");
        return result;
    }
    else
        return 0.0/0.0;
}

double FunctionX(char *exp, double x_val)
{
    x = x_val;
    return Expression(exp);
}

double FunctionXY(char *exp, double x_val, double y_val)
{
    x = x_val;
    y = y_val;
    return Expression(exp);
}

int IsSyntaxError(void)
{
    return isSyntaxError;
}
