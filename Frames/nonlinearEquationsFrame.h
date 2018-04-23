#ifndef NONLINEAREQUATIONSFRAME_H
#define NONLINEAREQUATIONSFRAME_H

#include <QWidget>
#include "X.h"

namespace Ui {
class NonlinearEquationsFrame;
}

class NonlinearEquationsFrame : public FrameThreadHelper
{
    Q_OBJECT

    ModeEq mode;

    void showAnswer(QString ans);
    void validatorSetup();

public:
    explicit NonlinearEquationsFrame(QWidget *parent, ModeEq mode);
    ~NonlinearEquationsFrame();

private slots:
    void on_equationEdit_textChanged(const QString &arg1);
    void on_limitAEdit_textChanged(const QString &arg1);
    void on_limitBEdit_textChanged(const QString &arg1);
    void on_epsilonEdit_textChanged(const QString &arg1);

    void onResult(double value, int iterations);
    void onError(int code);

    void on_derivativeEdit_textChanged(const QString &arg1);

    void on_x0Edit_textChanged(const QString &arg1);

private:
    Ui::NonlinearEquationsFrame *ui;
    void change();
};

#endif // NONLINEAREQUATIONSFRAME_H
