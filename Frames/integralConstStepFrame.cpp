#include "integralConstStepFrame.h"
#include "ui_integralConstStepFrame.h"

#include "UIConsts.h"

IntegralConstStepFrame::IntegralConstStepFrame(QWidget *parent) : FrameThreadHelper(parent), ui(new Ui::IntegralConstStepFrame)
{
    ui->setupUi(this);

    connect(ui->leftRectRadioButton, SIGNAL(toggled(bool)), SLOT(inputChanged()));
    connect(ui->rightRectRadioButton, SIGNAL(toggled(bool)), SLOT(inputChanged()));
    connect(ui->midRectRadioButton, SIGNAL(toggled(bool)), SLOT(inputChanged()));
    connect(ui->trapezoidRadioButton, SIGNAL(toggled(bool)), SLOT(inputChanged()));
    connect(ui->parabolicRadioButton, SIGNAL(toggled(bool)), SLOT(inputChanged()));

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
        showAnswer("b должн быть больше a");
        return;
    }

    n = ui->iterationSpinBox->value();

    if(n <= 0)
    {
        showAnswer("n должн быть больше 10");
        return;
    }

    func = ui->functionEdit->text();

    mode = getMode();

    setThread(new IntThread(func, a, b, n, mode));

    connect(getThread(), SIGNAL(sendResultSignal(double)), SLOT(onResult(double)));
    connect(getThread(), SIGNAL(sendErrorSignal(int)), SLOT(onError(int)));

    start();

    ui->answerEdit->setText(sCalculating);
}

void IntegralConstStepFrame::showAnswer(QString ans)
{
    ui->answerEdit->setText(ans);
}

void IntegralConstStepFrame::onResult(double value)
{
    if(!IsNan(value))
        showAnswer(QString::number(value));
    else
        showAnswer(sNanError);
}

void IntegralConstStepFrame::onError(int code)
{
    if(code == CalcError)
    {
        showAnswer(sSyntaxError);
    }
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
