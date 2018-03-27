#ifndef X_H
#define X_H

// тут все C++ Core заголовки
#include "Core/CalcThread.h"
#include "Core/Utils.h"

//  тут все C MathCore и Algorithms заголовки
extern "C" {
    
    // core math
    #include "MathCore/MathParser.h"
    #include "MathCore/MathUtils.h"
    
    // algorithms
    // please add new algotithm there:
    #include "MathCore/Algorithms/Integral.h"
}

#endif // X_H
