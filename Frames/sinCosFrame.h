#ifndef SINCOSFRAME_H
#define SINCOSFRAME_H

#include <QWidget>

namespace Ui {
class SinCosFrame;
}

typedef enum
{
    MaclaurinMode,
    CordicMode
} SinCosMode;

class SinCosFrame : public QWidget
{
    Q_OBJECT

public:
    explicit SinCosFrame(QWidget *parent, SinCosMode mode);
    ~SinCosFrame();

private slots:
    void on_xEdit_textChanged(const QString &arg1);

    void on_epsilonEdit_textChanged(const QString &arg1);

private:
    Ui::SinCosFrame *ui;
    SinCosMode mode;

    void change();
    void showError(QString s);
};

#endif
