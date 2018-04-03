#ifndef MATH_PARSER
#define MATH_PARSER

double Expression(char *exp);
double FunctionX(char *exp, double x_val);
double FunctionXY(char *exp, double x_val, double y_val);
int IsSyntaxError(void);

#endif
