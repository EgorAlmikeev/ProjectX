#include "CalcThread.h"
#include "QDebug"

// BaseCalcThread

void BaseCalcThread::run()
{
    BeginCalc();
}

void BaseCalcThread::sendError(ResultCode error)
{
    emit sendErrorSignal(error);
}

void BaseCalcThread::sendResult(double value)
{
    emit sendResultSignal(value);
}

// FrameThreadHelper

FrameThreadHelper::FrameThreadHelper(QWidget * parent) : QWidget(parent)
{
    isTimeOutUse = false;
    thread = nullptr;

    timeoutTimer = new QTimer(this);
    connect(timeoutTimer, SIGNAL(timeout()), SLOT(onTimeout()));
}

void FrameThreadHelper::setTimeOutUse(bool isUse)
{
    this->isTimeOutUse = isUse;
}

FrameThreadHelper::~FrameThreadHelper(void)
{
    cancel();
}

void FrameThreadHelper::cancel(void)
{
    if(thread != nullptr)
    {
        CancelCalc();

        while(thread->isRunning())
            QThread::msleep(1);

        thread->deleteLater();
        thread = nullptr;
    }
}

#define TIME_OUT_MS 10000
void FrameThreadHelper::start(void)
{
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    timeoutTimer->start(TIME_OUT_MS);
    thread->start();
}

void FrameThreadHelper::setThread(BaseCalcThread * thread)
{
    this->thread = thread;
}

BaseCalcThread * FrameThreadHelper::getThread(void)
{
    return this->thread;
}

void FrameThreadHelper::onTimeout()
{
    if(isTimeOutUse && (thread != nullptr))
        TimeoutCalc();
}

void FrameThreadHelper::end()
{
    this->thread = nullptr;
}

void FrameThreadHelper::hideEvent(QHideEvent *event)
{
    cancel();
    end();
}
