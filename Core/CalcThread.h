#ifndef CALCTHREAD_H
#define CALCTHREAD_H

#include <QtWidgets>

extern "C" {
    #include "MathCore/MathUtils.h"
}

class BaseCalcThread : public QThread //от этого класса наследуют все потоковые классы в ThreadClasses
{
   Q_OBJECT    

public:

    void run();
    void sendError(ResultCode error);
    void sendResult(double value);

signals :
    void sendErrorSignal    (int/* error code */);
    void sendResultSignal   (double/* value */);
    void sendResultSignal   (QString/* value */);
};

class FrameThreadHelper : public QWidget //от эого класса наследуют все фреймы
{
    Q_OBJECT

    BaseCalcThread * thread;

    bool isTimeOutUse;

protected:

    QTimer * timeoutTimer;

public:
    FrameThreadHelper(QWidget * parent = 0);
    ~FrameThreadHelper(void);

    void cancel(void);
    void start(void);
    void end(void);
    virtual void change(void) = 0;
    void setThread(BaseCalcThread * thread);
    BaseCalcThread * getThread(void);
    void setTimeOutUse(bool isUse);

protected slots:

    void killThread();
    void onTimeout();
};

#endif // CALCTHREAD_H
