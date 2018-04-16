#include "sinCosFrame.h"
#include "ui_sinCosFrame.h"
#include "X.h"
#include "UIConsts.h"

SinCosFrame::SinCosFrame(QWidget *parent, SinCosMode mode) :
    QWidget(parent),
    ui(new Ui::SinCosFrame)
{
    ui->setupUi(this);

    this->mode = mode;

    change();
}

SinCosFrame::~SinCosFrame()
{
    delete ui;
}

void SinCosFrame::on_xEdit_textChanged(const QString &arg1)
{
    change();
}

void SinCosFrame::on_epsilonEdit_textChanged(const QString &arg1)
{
    change();
}

int realDigits(double eps)
{
    int i = 0;

    while(eps < 1)
    {
        eps *= 10;
        i++;
        if(i >= 17)
            break;
    }

    return i;
}

void SinCosFrame::change()
{
    double sinX, cosX;
    int sinCount, cosCount;

    double x = Expression(QStrToCStr(ui->xEdit->text()));
    if(IsNan(x))
    {
        showError("Неверный параметр ""x""");
        return;
    }

    double eps = Expression(QStrToCStr(ui->epsilonEdit->text()));
    if(IsNan(eps) || eps > 1 || eps < 1e-99)
    {
        showError("Точность должна быть в пределах [1..1e-99]");
        return;
    }

    if(mode == MaclaurinMode)
    {
        sinX = MaclarinSin(x, eps, &sinCount);
        cosX = MaclarinCos(x, eps, &cosCount);
    }

    ui->sinEdit->setText(QString::number(sinX, 'g', realDigits(eps)));
    ui->sinCountLabel->setText(sIterationsCountForAccuracy(QString::number(sinCount)));

    ui->cosEdit->setText(QString::number(cosX, 'g', realDigits(eps)));
    ui->cosCountLabel->setText(sIterationsCountForAccuracy(QString::number(cosCount)));
}

void SinCosFrame::showError(QString s)
{
    ui->sinCountLabel->setText("");
    ui->cosCountLabel->setText("");
    ui->sinEdit->setText(s);
    ui->cosEdit->setText(s);
}
