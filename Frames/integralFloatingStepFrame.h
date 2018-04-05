#ifndef INTEGRALFLOATINGSTEPFRAME_H
#define INTEGRALFLOATINGSTEPFRAME_H

#include <QWidget>
#include "X.h"

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

    void onResult(double value, int iterations);
    void onError(int code);

    void on_epsilonEdit_textChanged(const QString &arg1);

    void on_leftRectRadioButton_clicked();

    void on_midRectRadioButton_clicked();

    void on_rightRectRadioButton_clicked();

    void on_trapezoidRadioButton_clicked();

    void on_parabolicRadioButton_clicked();

private:
    Ui::IntegralFloatingStepFrame * ui;

    void change();
};

#endif // INTEGRALFLOATINGSTEPFRAME_H
