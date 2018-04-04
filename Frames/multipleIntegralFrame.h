#ifndef MULTIPLEINTEGRALFRAME_H
#define MULTIPLEINTEGRALFRAME_H

#include <QWidget>

namespace Ui {
class MultipleIntegralFrame;
}

class MultipleIntegralFrame : public QWidget
{
    Q_OBJECT

public:
    explicit MultipleIntegralFrame(QWidget *parent = 0);
    ~MultipleIntegralFrame();

private:
    Ui::MultipleIntegralFrame *ui;
};

#endif // MULTIPLEINTEGRALFRAME_H
