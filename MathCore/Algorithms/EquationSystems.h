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
double Gauss(TEqMatrix m, TEqArray r, int n, double epsilon, TEqArray ans);

#endif /* Sole_h */
