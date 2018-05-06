#ifndef CALCTHREAD_H
#define CALCTHREAD_H

#include <QtWidgets>

extern "C" {
    #include "../MathCore/XMath.h"
}

class BaseCalcThread : public QThread //от этого класса наследуют все классы вычислительных потоков
{
   Q_OBJECT    

public:
    void run();
    void sendError(ResultCode error);
    void sendResult(double value);

signals :
    void sendResultSignal(double /*value*/);
    void sendResultSignal(QString /*value*/);
    void sendErrorSignal(int /*error code*/);
};

class FrameThreadHelper : public QWidget //от эого класса наследуют все фреймы
{
    Q_OBJECT

    BaseCalcThread *thread;
    bool isTimeOutUse;

protected:
    QTimer *timeoutTimer;
    void hideEvent(QHideEvent *event);

public:
    FrameThreadHelper(QWidget *parent = 0);
    ~FrameThreadHelper(void);

    void end(void);
    void start(void);
    void cancel(void);

    virtual void change(void) = 0;
    BaseCalcThread *getThread(void);

    void setTimeOutUse(bool isUse);
    void setThread(BaseCalcThread *thread);

protected slots:
    void onTimeout();
};

#endif // CALCTHREAD_H
