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

    int columnCount = 0;
    int rowCount = 0;
    int paramCount = 0;

    ModeEqSys mode;

    QRegExpValidator *matrixItemValidator;

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

    void onMatrixElementTextChanged();

private:
    Ui::EquationsSystemsFrame *ui;
    void change();

    QLineEdit * createNewMatrixItem();
    void setMatrixTabOrder();
};

#endif // EQUATIONSSYSTEMSFRAME_H
