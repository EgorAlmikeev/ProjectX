//
//  Sole.h
//  XProjectLite
//
//  Created by Sophia Kramar on 21.04.18.
//  Copyright © 2018 codeholics. All rights reserved.
//

#ifndef Sole_h
#define Sole_h
#include "../MathUtils.h"

typedef double* TEqArray;
typedef double** TEqMatrix;

double GaussNoOptimal(TEqMatrix A, TEqArray B, int n, double epsilon, TEqArray X);
double Gauss(TEqMatrix A, TEqArray B, int n, double epsilon, TEqArray X);
double GaussJordan(TEqMatrix A, TEqArray B, int n, double epsilon, TEqArray X);

#endif /* Sole_h */
