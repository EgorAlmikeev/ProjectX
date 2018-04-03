#ifndef INTEGRALFLOATINGSTEPFRAME_H
#define INTEGRALFLOATINGSTEPFRAME_H

#include <QWidget>
#include "../X.h"

namespace Ui {
    class IntegralFloatingStepFrame;
}
class IntegralFloatingStepFrame : public FrameThreadHelper
{
    Q_OBJECT

    void showAnswer(QString ans);
    ModeInt getMode(void);


public:
    explicit IntegralFloatingStepFrame(QWidget *parent = 0);
    ~IntegralFloatingStepFrame();

private slots:

    void on_functionEdit_textChanged(const QString &arg1);
    void on_limitAEdit_textChanged(const QString &arg1);
    void on_limitBEdit_textChanged(const QString &arg1);

    void onResult(double value);
    void onError(int code);


private:
    Ui::IntegralFloatingStepFrame * ui;

    void change();
};

#endif // INTEGRALFLOATINGSTEPFRAME_H
