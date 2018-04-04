#ifndef NONLINEAREQUATIONSFRAME_H
#define NONLINEAREQUATIONSFRAME_H

#include <QWidget>

namespace Ui {
class NonlinearEquationsFrame;
}

class NonlinearEquationsFrame : public QWidget
{
    Q_OBJECT

public:
    explicit NonlinearEquationsFrame(QWidget *parent = 0);
    ~NonlinearEquationsFrame();

private:
    Ui::NonlinearEquationsFrame *ui;
};

#endif // NONLINEAREQUATIONSFRAME_H
