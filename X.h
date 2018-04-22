#ifndef X_H
#define X_H

extern "C" {
    #include "MathCore/XMath.h"
}

#include "Core/XCore.h"

// Тут все ссылки на все вычислительные треды
#include "Core/EquationThread.h"
#include "Core/IntegralThreads.h"
#include "Core/EquationsSystemsThread.h"
#include "Core/DiffEqEulerMethodThread.h"

#endif // X_H
