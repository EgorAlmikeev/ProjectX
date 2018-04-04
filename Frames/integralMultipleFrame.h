#ifndef MULTIPLEINTEGRALFRAME_H
#define MULTIPLEINTEGRALFRAME_H

#include <QWidget>

namespace Ui {
class IntegralMultipleFrame;
}

class IntegralMultipleFrame : public QWidget
{
    Q_OBJECT

public:
    explicit IntegralMultipleFrame(QWidget *parent = 0);
    ~IntegralMultipleFrame();

private:
    Ui::IntegralMultipleFrame *ui;
};

#endif // MULTIPLEINTEGRALFRAME_H
