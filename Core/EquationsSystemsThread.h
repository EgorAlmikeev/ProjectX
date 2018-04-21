#ifndef EQUATIONSSYSTEMSTHREAD_H
#define EQUATIONSSYSTEMSTHREAD_H

#include "XCore.h"

class EquationsSystemsThread : public BaseCalcThread
{
    Q_OBJECT

public:
    EquationsSystemsThread();
    void run();
};

#endif // EQUATIONSSYSTEMSTHREAD_H
