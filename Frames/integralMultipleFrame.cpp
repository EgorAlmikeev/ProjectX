#include "integralMultipleFrame.h"
#include "ui_integralMultipleFrame.h"

#include "UIConsts.h"

IntegralMultipleFrame::IntegralMultipleFrame(QWidget *parent) :
    FrameThreadHelper(parent),
    ui(new Ui::IntegralMultipleFrame)
{
    ui->setupUi(this);

    this->setTimeOutUse(true);

    change();
}

IntegralMultipleFrame::~IntegralMultipleFrame()
{
    delete ui;
}

void IntegralMultipleFrame::change()
{
    int xn, yn;
    double a, b, c, d;
    QString func;

    cancel();

    a = Expression(QStrToCStr(ui->xLimitAEdit->text()));
    if(IsNan(a))
    {
        showAnswer("Пределы X: Неверный параметр a");
        return;
    }

    b = Expression(QStrToCStr(ui->xLimitBEdit->text()));
    if(IsNan(b))
    {
        showAnswer("Пределы X: Неверный параметр b");
        return;
    }

    c = Expression(QStrToCStr(ui->yLimitAEdit->text()));
    if(IsNan(a))
    {
        showAnswer("Пределы Y: Неверный параметр a");
        return;
    }

    d = Expression(QStrToCStr(ui->yLimitBEdit->text()));
    if(IsNan(b))
    {
        showAnswer("Пределы Y: Неверный параметр b");
        return;
    }

    if(a >= b)
    {
        showAnswer("Пределы X: b должен быть больше a");
        return;
    }

    if(c >= d)
    {
        showAnswer("Пределы Y: b должен быть больше a");
        return;
    }

    xn = ui->xIterationSpinBox->value();

    if(xn <= 0)
    {
        showAnswer("Пределы X: колличество итераций должно быть > 0");
        return;
    }

    yn = ui->yIterationSpinBox->value();

    if(yn <= 0)
    {
        showAnswer("Пределы Y: колличество итераций должно быть > 0");
        return;
    }

    func = ui->functionEdit->text();

    setThread(new IntMultipleThread(func, a, b, c, d, xn, yn));

    connect(getThread(), SIGNAL(sendResultSignal(double)), SLOT(onResult(double)));
    connect(getThread(), SIGNAL(sendErrorSignal(int)), SLOT(onError(int)));

    start();

    showAnswer(sCalculating);
}

void IntegralMultipleFrame::showAnswer(QString ans)
{
    ui->answerEdit->setText(ans);
}

void IntegralMultipleFrame::onResult(double value)
{
    end();

    if(!IsNan(value))
        showAnswer(QString::number(value));
    else
        showAnswer(sNanError);
}

void IntegralMultipleFrame::onError(int code)
{
    end();

    if(code == CalcError)
    {
        showAnswer(sSyntaxError);
    }
        else showAnswer(sIntTimeoutError);
}

void IntegralMultipleFrame::on_functionEdit_textChanged(const QString &arg1)
{
    change();
}

void IntegralMultipleFrame::on_xLimitAEdit_textChanged(const QString &arg1)
{
    change();
}

void IntegralMultipleFrame::on_xLimitBEdit_textChanged(const QString &arg1)
{
    change();
}

void IntegralMultipleFrame::on_xIterationSpinBox_valueChanged(const QString &arg1)
{
    change();
}

void IntegralMultipleFrame::on_yLimitBEdit_textChanged(const QString &arg1)
{
    change();
}

void IntegralMultipleFrame::on_yIterationSpinBox_valueChanged(const QString &arg1)
{
    change();
}

void IntegralMultipleFrame::on_yLimitAEdit_textChanged(const QString &arg1)
{
    change();
}
