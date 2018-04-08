#ifndef DIFFEQEULERMETHODFRAME_H
#define DIFFEQEULERMETHODFRAME_H

#include <QWidget>
#include "X.h"

namespace Ui {
class DiffEqEulerMethodFrame;
}

class DiffEqEulerMethodFrame : public FrameThreadHelper
{
    Q_OBJECT

    void showAnswer(QString ans);

public:
    explicit DiffEqEulerMethodFrame(QWidget *parent = 0);
    ~DiffEqEulerMethodFrame();

private slots:
    void on_functionEdit_textChanged(const QString &arg1);
    void on_xEdit_textChanged(const QString &arg1);
    void on_yEdit_textChanged(const QString &arg1);
    void on_stepEdit_textChanged(const QString &arg1);
    void on_iterationSpinBox_valueChanged(int arg1);

    void onResult();
    void onError(int code);

private:
    Ui::DiffEqEulerMethodFrame *ui;
    void change();
};

#endif // DIFFEQEULERMETHODFRAME_H
