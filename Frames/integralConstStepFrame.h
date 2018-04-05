#ifndef INTEGRALCONSTSTEPFRAME_H
#define INTEGRALCONSTSTEPFRAME_H

#include <QWidget>
#include "X.h"

namespace Ui {
    class IntegralConstStepFrame;
}
class IntegralConstStepFrame : public FrameThreadHelper
{
    Q_OBJECT

    void showAnswer(QString ans);
    ModeInt getMode(void);


public:
    explicit IntegralConstStepFrame(QWidget *parent = 0);
    ~IntegralConstStepFrame();

private slots:
    void on_iterationSpinBox_valueChanged(const QString &arg1);
    void on_functionEdit_textChanged(const QString &arg1);
    void on_limitAEdit_textChanged(const QString &arg1);
    void on_limitBEdit_textChanged(const QString &arg1);

    void onResult(double value);
    void onError(int code);


    void on_midRectRadioButton_clicked();

    void on_leftRectRadioButton_clicked();

    void on_rightRectRadioButton_clicked();

    void on_trapezoidRadioButton_clicked();

    void on_parabolicRadioButton_clicked();

private:
    Ui::IntegralConstStepFrame * ui;

    void change();
};

#endif // INTEGRALCONSTSTEPFRAME_H
