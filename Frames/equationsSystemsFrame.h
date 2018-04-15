#ifndef EQUATIONSSYSTEMSFRAME_H
#define EQUATIONSSYSTEMSFRAME_H

#include <QWidget>
#include "X.h"

namespace Ui {
class EquationsSystemsFrame;
}

class EquationsSystemsFrame : public FrameThreadHelper
{
    Q_OBJECT

    short rows = 1;
    short columns = 1;

public:
    explicit EquationsSystemsFrame(QWidget *parent = 0);
    ~EquationsSystemsFrame();

private slots:
    void on_rowsSpin_valueChanged(int arg1);
    void on_columnsSpin_valueChanged(int arg1);

private:
    Ui::EquationsSystemsFrame *ui;
    void change();
    void setMatrixTabOrder();
};

#endif // EQUATIONSSYSTEMSFRAME_H
