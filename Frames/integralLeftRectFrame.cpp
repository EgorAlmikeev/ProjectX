#include "integralLeftRectFrame.h"
#include "ui_integralleftrectframe.h"
#include "ThreadClasses/InteralThreads.h"

IntegralLeftRectFrame::IntegralLeftRectFrame(QWidget *parent) : FrameThreadHelper(parent), ui(new Ui::IntegralLeftRectFrame)
{
    ui->setupUi(this);

    QWidget::setTabOrder(ui->limitAEdit, ui->limitBEdit);
    QWidget::setTabOrder(ui->limitBEdit, ui->functionEdit);
    QWidget::setTabOrder(ui->functionEdit, ui->iterationSpinBox);
}

IntegralLeftRectFrame::~IntegralLeftRectFrame()
{
    delete ui;
}

void IntegralLeftRectFrame::change(void)
{
    int n;
    double a, b;
    QString func;

    cancel();

    a = Expression(QStrToCStr(ui->limitAEdit->text()));
    if(IsNan(a))
    {
        SetAns("Неверный параметр a");
        return;
    }

    b = Expression(QStrToCStr(ui->limitBEdit->text()));
    if(IsNan(b))
    {
        SetAns("Неверный параметр b");
        return;
    }

    if(a == b)
    {
        SetAns("a не должна быть равна b");
        return;
    }

    n = ui->iterationSpinBox->value();

    if(n <= 0)
    {
        SetAns("n должна быть больше 0");
        return;
    }

    func = ui->functionEdit->text();
    setThread(new IntLeftRectThread(func, a, b, n));

    connect(getThread(), SIGNAL(sendResultSignal(double)), SLOT(onResult(double)));
    connect(getThread(), SIGNAL(sendErrorSignal(int)), SLOT(onError(int)));

    start();

    ui->answerEdit->setText("Calculating...");
}

void IntegralLeftRectFrame::SetAns(QString ans)
{
    ui->answerEdit->setText(ans);
}

void IntegralLeftRectFrame::onResult(double value)
{
    SetAns(QString::number(value));
}

void IntegralLeftRectFrame::onError(int code)
{
    if(code == CalcError)
    {
        SetAns("Ошибка в функции!");
    }
}

void IntegralLeftRectFrame::on_functionEdit_textChanged(const QString &arg1)
{
    change();
}

void IntegralLeftRectFrame::on_limitAEdit_textChanged(const QString &arg1)
{
    change();
}

void IntegralLeftRectFrame::on_limitBEdit_textChanged(const QString &arg1)
{
    change();
}

void IntegralLeftRectFrame::on_iterationSpinBox_valueChanged(const QString &arg1)
{
    change();
}
