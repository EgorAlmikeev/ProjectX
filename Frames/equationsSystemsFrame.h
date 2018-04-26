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

    ModeEqSys mode;

    QRegExpValidator *matrixItemValidator;

public:
    explicit EquationsSystemsFrame(QWidget *parent, ModeEqSys mode);
    ~EquationsSystemsFrame();

private slots:

    TEqMatrix  getMatrixValues();
    TEqArray getParamsValues();

    void on_matrixSizeSpin_valueChanged(int arg1);
    void on_EpsilonEdit_textChanged(const QString &arg1);

    void showAnswer(QString ans);

    void onResult(double *value, int n);
    void onError(int code);

    void onMatrixElementTextChanged();

    void on_clearButton_clicked();

    void createMatrixUI(int new_size);

private:
    bool isLoading = true;
    Ui::EquationsSystemsFrame *ui;
    void change();

    QLineEdit * createNewMatrixItem();
    void setMatrixTabOrder();
    void setDefaultValues();
};

#endif // EQUATIONSSYSTEMSFRAME_H
