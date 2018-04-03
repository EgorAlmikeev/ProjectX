//
//  main.c
//  XProjectLite
//
//  Created by error on 03.04.2018.
//  Copyright © 2018 codeholics. All rights reserved.
//

#include <stdio.h>
#include "XMath.h"

int main(int argc, const char * argv[]) {


    double ans;
    
    ans = IntLeftRect("sin(x)", 0, 1, 1000);
    
    printf("%lf\n", ans);

    return 0;
}
