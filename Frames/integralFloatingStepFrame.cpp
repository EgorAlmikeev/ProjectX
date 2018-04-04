#include "integralFloatingStepFrame.h"
#include "ui_integralFloatingStepFrame.h"

#include "UIConsts.h"

IntegralFloatingStepFrame::IntegralFloatingStepFrame(QWidget *parent) : FrameThreadHelper(parent), ui(new Ui::IntegralFloatingStepFrame)
{
    ui->setupUi(this);

    QRegExpValidator * validator = new QRegExpValidator;
    validator->setRegExp(QRegExp("^[+-]?[\\d]+($|[\\.][\\d]+|([\\.][\\d]+[Ee]|[Ee])[+-]?\\d+)$"));
    ui->epsilonEdit->setValidator(validator);

    this->setTimeOutUse(true);

    change();
}

IntegralFloatingStepFrame::~IntegralFloatingStepFrame()
{
    delete ui;
}

void IntegralFloatingStepFrame::change(void)
{
    double a, b, e;
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

    e = ui->epsilonEdit->text().toDouble();

    if(e >= 1 || e <= 1e-99)
    {
        showAnswer("Точность должна быть в пределах (1..1e-99)");
        return;
    }

    func = ui->functionEdit->text();
    mode = getMode();

    setThread(new IntFloatingStepThread(func, a, b, e, mode));

    connect(getThread(), SIGNAL(sendResultSignal(double,int)), SLOT(onResult(double,int)));
    connect(getThread(), SIGNAL(sendErrorSignal(int)), SLOT(onError(int)));

    start();

    showAnswer(sCalculating);
}

void IntegralFloatingStepFrame::showAnswer(QString ans)
{
    ui->answerEdit->setText(ans);
    ui->interationCountLabel->setText("");
}

void IntegralFloatingStepFrame::onResult(double value, int iterations)
{
    end();

    if(!IsNan(value))
        showAnswer(QString::number(value));
    else
        showAnswer(sNanError);

    ui->interationCountLabel->setText(sIterationsCountForAccuracy(QString::number(iterations)));
}

void IntegralFloatingStepFrame::onError(int code)
{
    end();

    if(code == CalcError)
    {
        showAnswer(sSyntaxError);
    }
        else showAnswer(sIntTimeoutError);
}

ModeInt IntegralFloatingStepFrame::getMode()
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

void IntegralFloatingStepFrame::on_epsilonEdit_textChanged(const QString &arg1)
{
//    double  min = 0.1,
//            max = 0.00000000001;

    change();
}

void IntegralFloatingStepFrame::on_limitAEdit_textChanged(const QString &arg1)
{
    change();
}

void IntegralFloatingStepFrame::on_limitBEdit_textChanged(const QString &arg1)
{
    change();
}

void IntegralFloatingStepFrame::on_functionEdit_textChanged(const QString &arg1)
{
    change();
}

void IntegralFloatingStepFrame::on_leftRectRadioButton_clicked()
{
    change();
}

void IntegralFloatingStepFrame::on_midRectRadioButton_clicked()
{
    change();
}

void IntegralFloatingStepFrame::on_rightRectRadioButton_clicked()
{
    change();
}

void IntegralFloatingStepFrame::on_trapezoidRadioButton_clicked()
{
    change();
}

void IntegralFloatingStepFrame::on_parabolicRadioButton_clicked()
{
    change();
}

