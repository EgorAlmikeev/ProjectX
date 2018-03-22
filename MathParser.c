//
//  MathParser.c
//
//

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

typedef enum
{
    tokenUndefined,// !!!
    tokenEnd,// \0
    tokenNumber,// ###.###
    tokenAdd,// +
    tokenSub,// -
    tokenMul,// *
    tokenDiv,// /
    tokenPower,// ^
    tokenFactorial,// !
    tokenLB,// (
    tokenRB,// )
    tokenValue,// aaa
    tokenFunction,// aaa()
} tokens;

// parser variables
const char *eq;// указатель на формулу
const char *p;// указатель на текущий символ
const char *prevToken;// указатель на предидущий токен
tokens token;// тип текущего токена
double doubleValue;// последнее считанное значение
char stringValue[33];// последнее считанное значение
jmp_buf saveState;// используеться для восстановления состояния после ошибки
double x = 0;
int isSyntaxError;

void error(int isSyntaxErr, const char *str)
{
	isSyntaxError = isSyntaxErr;
    longjmp(saveState, 1);// восстанавливаем состояние
}

void nextToken(void)
{
    int i;

	prevToken = p;

	while(*p == ' ')
      p++;

    switch(*(p))
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
            //error("Unexpected symbol");
            if((('a' <= *p) && ('z' >= *p)) || (('A' <= *p) && ('Z' >= *p)) || (*p == '_'))
            {
                i = 0;
                stringValue[i] = *p;
                for(; (('a' <= *p) && ('z' >= *p)) || (('A' <= *p) && ('Z' >= *p)) ||
					  (*p == '_') || (('0' <= *p) && ('9' >= *p)); i++, p++)
				{
					stringValue[i] = *p;
					if(i == 31)
					{
					  i++;
					  break;
					}
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

double tryPow(void);
double tryAdd(void);

int factorial(int n)
{
    int r;
    for (r = 1; n > 1; r *= (n--));
    return r;
}

void bracketTest(void)
{
    if(token == tokenLB)
		error(1, "Unexpected symbol");
}

boolean compStr(const char *s1, const char *s2)
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

double tryPrim(void)
{
	double left, t;
    const char *temp;

    nextToken();
    left = doubleValue;

    switch (token)
    {
        case tokenNumber:
            //temp = prevToken;
            nextToken();
            //prevToken = temp;
            if(token == tokenLB)
				error(1, "Unexpected symbol");
            return left;

        case tokenSub:
            return -tryPow();

        case tokenLB:
            //temp = prevToken;
            left = tryAdd();
            if(token != tokenRB)
				error(1, "Expected right bracket");
            nextToken();
            //prevToken = temp;
            //if((token == tokenNumber) || (token == tokenLB) || (token == tokenValue) || (token == tokenFunction))
            //    error("Unexpected symbol");
            return left;

        case tokenValue:
            //temp = prevToken;
            if(compStr(stringValue, "pi"))
				left = M_PI;
			else if(compStr(stringValue, "x"))
				left = x;
            else
				error(1, "Identifier not found");
            nextToken();
            //prevToken = temp;
            if((token == tokenNumber) || (token == tokenLB) || (token == tokenValue) || (token == tokenFunction))
				error(1, "Unexpected symbol");
            return left;

        case tokenFunction:
            if(compStr(stringValue, "sin"))
            {
                left = sin(tryAdd());
            }
            else if(compStr(stringValue, "cos"))
            {
                left = cos(tryAdd());
			}
			else if(compStr(stringValue, "asin"))
			{
				t = tryAdd();
				if(fabs(t) > 1.0)
					error(0, "Bad angle");
				left = asin(t);
            }
			else if(compStr(stringValue, "acos"))
			{
				t = tryAdd();
				if(fabs(t) > 1.0)
					error(0, "Bad angle");
				left = acos(t);
			}
			else if(compStr(stringValue, "atan"))
			{
				left = atan(tryAdd());
			}
            else if(compStr(stringValue, "abs"))
            {
                left = fabs(tryAdd());
            }
            else if(compStr(stringValue, "tan"))
            {
                left = tan(tryAdd());
            }
            else if(compStr(stringValue, "log"))
            {
                left = log(tryAdd());
            }
            else if(compStr(stringValue, "exp"))
            {
                left = exp(tryAdd());
			}
			else if(compStr(stringValue, "sqrt"))
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

double tryFact(void)
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

double tryPow(void)
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

double tryMul(void)
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

double tryAdd(void)
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

double expression(char *exp)
{
    double result;

	isSyntaxError = 0;

    eq = exp;
    p = exp;

    if(setjmp(saveState) == 0)
    {
        result = tryAdd();
        if(token != tokenEnd)
			error(1, "Unexpected symbol (end)");
        return result;
    }
    else
        return 0.0/0.0;
}

double function_x(char *exp, double x_val)
{
	x = x_val;
	return expression(exp);
}

int is_syntax_error(void)
{
    return isSyntaxError;
}
