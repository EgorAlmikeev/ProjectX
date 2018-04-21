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

typedef double* TMatt;
typedef double** TMat;
double Gauss(TMat m, TMatt M, int n, double epsilon, double* ans);

#endif /* Sole_h */
