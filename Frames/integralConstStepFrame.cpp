#include "integralConstStepFrame.h"
#include "ui_integralConstStepFrame.h"

#include "UIConsts.h"

IntegralConstStepFrame::IntegralConstStepFrame(QWidget *parent) : FrameThreadHelper(parent), ui(new Ui::IntegralConstStepFrame)
{
    ui->setupUi(this);
    change();
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
    ModeInt mode = ModeIntLeftRect; //default mode

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

    if(a >= b)
    {
        showAnswer("b должен быть больше a");
        return;
    }

    n = ui->iterationSpinBox->value();

    if(n <= 0)
    {
        showAnswer("n должен быть больше 0");
        return;
    }

    func = ui->functionEdit->text();

    mode = getMode();

    setThread(new IntConstStepThread(func, a, b, n, mode));

    connect(getThread(), SIGNAL(sendResultSignal(double)), SLOT(onResult(double)));
    connect(getThread(), SIGNAL(sendErrorSignal(int)), SLOT(onError(int)));

    start();

    showAnswer(sCalculating);
}

void IntegralConstStepFrame::showAnswer(QString ans)
{
    ui->answerEdit->setText(ans);
}

void IntegralConstStepFrame::onResult(double value)
{
    end();

    if(!IsNan(value))
        showAnswer(QString::number(value));
    else
        showAnswer(sNanError);
}

void IntegralConstStepFrame::onError(int code)
{
    end();

    if(code == CalcError)
        showAnswer(sSyntaxError);
    else showAnswer(sIntTimeoutError);
}

ModeInt IntegralConstStepFrame::getMode()
{
    if(ui->leftRectRadioButton->isChecked())
        return ModeIntLeftRect;
    else if(ui->rightRectRadioButton->isChecked())
        return ModeIntRightRect;
    else if(ui->midRectRadioButton->isChecked())
        return ModeIntMedianRect;
    else if(ui->trapezoidRadioButton->isChecked())
        return ModeIntTrapeze;
    else if(ui->parabolicRadioButton->isChecked())
        return ModeIntSimpson;
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

void IntegralConstStepFrame::on_midRectRadioButton_clicked()
{
    change();
}

void IntegralConstStepFrame::on_leftRectRadioButton_clicked()
{
    change();
}

void IntegralConstStepFrame::on_rightRectRadioButton_clicked()
{
    change();
}

void IntegralConstStepFrame::on_trapezoidRadioButton_clicked()
{
    change();
}

void IntegralConstStepFrame::on_parabolicRadioButton_clicked()
{
    change();
}
