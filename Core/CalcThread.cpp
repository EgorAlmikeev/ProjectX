#include "CalcThread.h"

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

////////////////////////////////////////////////////////////////////////////////////////////

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

        while(!thread->wait(1))
            QThread::msleep(1);

        ResultCode  r = GetResultCode();


        thread = nullptr;
    }
}

void FrameThreadHelper::start(void)
{
    timeoutTimer->start(50);
    thread->start();
}

void FrameThreadHelper::end(void)
{
    timeoutTimer->stop();
}

void FrameThreadHelper::setThread(BaseCalcThread * thread)
{
    this->thread = thread;
    connect(thread, SIGNAL(sendErrorSignal(int)), SLOT(killThread()));
    connect(thread, SIGNAL(sendResultSignal(double)), SLOT(killThread()));
    connect(thread, SIGNAL(sendResultSignal(QString)), SLOT(killThread()));
}

BaseCalcThread * FrameThreadHelper::getThread(void)
{
    return this->thread;
}

void FrameThreadHelper::onTimeout()
{
    if(isTimeOutUse)
        TimeoutCalc();
}

void FrameThreadHelper::killThread()
{
    end();
}

void FrameThreadHelper::inputChanged()
{
    change();
}
