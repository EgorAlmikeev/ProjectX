#include "integralConstStepFrame.h"
#include "ui_integralconststepframe.h"

IntegralConstStepFrame::IntegralConstStepFrame(QWidget *parent) : FrameThreadHelper(parent), ui(new Ui::IntegralConstStepFrame)
{
    ui->setupUi(this);

    QWidget::setTabOrder(ui->limitAEdit, ui->limitBEdit);
    QWidget::setTabOrder(ui->limitBEdit, ui->functionEdit);
    QWidget::setTabOrder(ui->functionEdit, ui->iterationSpinBox);
}

IntegralConstStepFrame::~IntegralConstStepFrame()
{
    delete ui;
}

void IntegralConstStepFrame::change(void)
{
    int n;
    double a, b;
    QString func;
    ModeInt mode;

    cancel();

    a = Expression(QStrToCStr(ui->limitAEdit->text()));
    if(IsNan(a))
    {
        showAnswer("Неверный параметр a");
        return;
    }

    b = Expression(QStrToCStr(ui->limitBEdit->text()));
    if(IsNan(b))
    {
        showAnswer("Неверный параметр b");
        return;
    }

    if(a == b)
    {
        showAnswer("a не должна быть равна b");
        return;
    }

    n = ui->iterationSpinBox->value();

    if(n <= 0)
    {
        showAnswer("n должна быть больше 0");
        return;
    }

    func = ui->functionEdit->text();

    mode = getMode();

    setThread(new IntThread(func, a, b, n, mode));

    connect(getThread(), SIGNAL(sendResultSignal(double)), SLOT(onResult(double)));
    connect(getThread(), SIGNAL(sendErrorSignal(int)), SLOT(onError(int)));

    start();

    ui->answerEdit->setText("Calculating...");
}

void IntegralConstStepFrame::showAnswer(QString ans)
{
    ui->answerEdit->setText(ans);
}

void IntegralConstStepFrame::onResult(double value)
{
    showAnswer(QString::number(value));
}

void IntegralConstStepFrame::onError(int code)
{
    if(code == CalcError)
    {
        showAnswer("Ошибка в функции!");
    }
}

ModeInt IntegralConstStepFrame::getMode()
{
    if(ui->leftRectRadioButton->isChecked())
        return ModeIntLeftRect;
    else if(ui->rightRectRadioButton->isChecked())
        return ModeIntRightRect;
    else if(ui->midRectRadioButton)
        return ModeIntMidRect;
    else if(ui->trapezoidRadioButton)
        return ModeIntTrapezoid;
    else if(ui->parabolicRadioButton)
        return ModeIntParabolic;
}

void IntegralConstStepFrame::on_functionEdit_textChanged(const QString &arg1)
{
    change();
}

void IntegralConstStepFrame::on_limitAEdit_textChanged(const QString &arg1)
{
    change();
}

void IntegralConstStepFrame::on_limitBEdit_textChanged(const QString &arg1)
{
    change();
}

void IntegralConstStepFrame::on_iterationSpinBox_valueChanged(const QString &arg1)
{
    change();
}
