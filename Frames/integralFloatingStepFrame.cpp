#include "IntegralFloatingStepFrame.h"
#include "ui_IntegralFloatingStepFrame.h"

#include "UIConsts.h"

IntegralFloatingStepFrame::IntegralFloatingStepFrame(QWidget *parent) : FrameThreadHelper(parent), ui(new Ui::IntegralFloatingStepFrame)
{
    ui->setupUi(this);

    QRegExpValidator * validator = new QRegExpValidator;
    validator->setRegExp(QRegExp("^[+-]?[\\d]+($|[\\.][\\d]+|([\\.][\\d]+[Ee]|[Ee])[+-]?\\d+)$"));
    ui->epsilonEdit->setValidator(validator);

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
    ModeInt mode = ModeIntDoubleCalc; //default mode

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
    func = ui->functionEdit->text();
    mode = getMode();

    IntFloatingStepThread * floatingStepThread = new IntFloatingStepThread(func, a, b, e, mode);
    setThread(floatingStepThread);

    connect(floatingStepThread, SIGNAL(sendResultSignal(double,int)), SLOT(onResult(double,int)));
    connect(getThread(), SIGNAL(sendErrorSignal(int)), SLOT(onError(int)));

    start();

    ui->answerEdit->setText(sCalculating);
}

void IntegralFloatingStepFrame::showAnswer(QString ans)
{
    ui->answerEdit->setText(ans);
}

void IntegralFloatingStepFrame::onResult(double value, int iterations)
{
//    if(!IsNan(value))
//        showAnswer(QString::number(value));
//    else
//        showAnswer(sNanError);
}

void IntegralFloatingStepFrame::onError(int code)
{
    if(code == CalcError)
    {
        showAnswer(sSyntaxError);
    }
}

ModeInt IntegralFloatingStepFrame::getMode()
{
    //ifelse по радиобаттонам
    return ModeIntDoubleCalc;
}

void IntegralFloatingStepFrame::on_functionEdit_textChanged(const QString &arg1)
{
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

void IntegralFloatingStepFrame::on_epsilonEdit_textChanged(const QString &arg1)
{
    change();
}
