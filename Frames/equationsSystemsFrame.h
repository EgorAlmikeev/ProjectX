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

    int size = 0;
    int columns = 1;
    int rows = 1;
    int params = 1;

public:
    explicit EquationsSystemsFrame(QWidget *parent = 0);
    ~EquationsSystemsFrame();

private slots:
    void setRows(int count);
    void setColumns(int count);
    void setParams(int count);

    void on_matrixSizeSpin_valueChanged(int arg1);

private:
    Ui::EquationsSystemsFrame *ui;
    void change();
};

#endif // EQUATIONSSYSTEMSFRAME_H
