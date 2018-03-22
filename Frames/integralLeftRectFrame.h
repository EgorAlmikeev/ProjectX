#ifndef INTEGRALLEFTRECTFRAME_H
#define INTEGRALLEFTRECTFRAME_H

#include <QWidget>
#include "X.h"

namespace Ui {
class IntegralLeftRectFrame;
}

class IntegralLeftRectFrame : public FrameThreadHelper
{
    Q_OBJECT

    void SetAns(QString ans);

public:
    explicit IntegralLeftRectFrame(QWidget *parent = 0);
    ~IntegralLeftRectFrame();

private slots:
    void on_iterationSpinBox_valueChanged(const QString &arg1);
    void on_functionEdit_textChanged(const QString &arg1);
    void on_limitAEdit_textChanged(const QString &arg1);
    void on_limitBEdit_textChanged(const QString &arg1);

    void onResult(double value);
    void onError(int code);


private:
    Ui::IntegralLeftRectFrame * ui;

    void change();
};

#endif // INTEGRALLEFTRECTFRAME_H
