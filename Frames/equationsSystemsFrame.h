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

    int columnCount = 2;
    int rowCount = 2;
    int paramCount = 2;

    ModeEqSys mode;

public:
    explicit EquationsSystemsFrame(QWidget *parent, ModeEqSys mode);
    ~EquationsSystemsFrame();

private slots:
    void setRows(int count);
    void setColumns(int count);
    void setParams(int count);

    TEqMatrix  getMatrixValues();
    TEqArray getParamsValues();

    void on_matrixSizeSpin_valueChanged(int arg1);
    void on_EpsilonEdit_textChanged(const QString &arg1);

    void showAnswer(QString ans);

    void onResult(double *value, int n);
    void onError(int code);

private:
    Ui::EquationsSystemsFrame *ui;
    void change();
};

#endif // EQUATIONSSYSTEMSFRAME_H
