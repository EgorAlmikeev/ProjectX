#ifndef DIFFEQEULERMETHODFRAME_H
#define DIFFEQEULERMETHODFRAME_H

#include <QWidget>

namespace Ui {
class DiffEqEulerMethodFrame;
}

class DiffEqEulerMethodFrame : public QWidget
{
    Q_OBJECT

public:
    explicit DiffEqEulerMethodFrame(QWidget *parent = 0);
    ~DiffEqEulerMethodFrame();

private:
    Ui::DiffEqEulerMethodFrame *ui;
};

#endif // DIFFEQEULERMETHODFRAME_H
