#ifndef MULTIPLEINTEGRALFRAME_H
#define MULTIPLEINTEGRALFRAME_H

#include <QWidget>
#include "X.h"

namespace Ui {
class IntegralMultipleFrame;
}

class IntegralMultipleFrame : public FrameThreadHelper
{
    Q_OBJECT

    void showAnswer(QString ans);

public:
    explicit IntegralMultipleFrame(QWidget *parent = 0);
    ~IntegralMultipleFrame();

private slots:
    void on_xIterationSpinBox_valueChanged(const QString &arg1);
    void on_yIterationSpinBox_valueChanged(const QString &arg1);
    void on_functionEdit_textChanged(const QString &arg1);
    void on_xLimitAEdit_textChanged(const QString &arg1);
    void on_xLimitBEdit_textChanged(const QString &arg1);
    void on_yLimitAEdit_textChanged(const QString &arg1);
    void on_yLimitBEdit_textChanged(const QString &arg1);

    void onResult(double value);
    void onError(int code);

private:
    Ui::IntegralMultipleFrame *ui;

    void change();
};

#endif // MULTIPLEINTEGRALFRAME_H
