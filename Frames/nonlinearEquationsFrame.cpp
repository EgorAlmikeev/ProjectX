#include "nonlinearEquationsFrame.h"
#include "ui_nonlinearEquationsFrame.h"

#include "UIConsts.h"

NonlinearEquationsFrame::NonlinearEquationsFrame(QWidget *parent, ModeEq mode) :
    FrameThreadHelper(parent),
    ui(new Ui::NonlinearEquationsFrame)
{
    ui->setupUi(this);
    this->mode = mode;
    validatorSetup();
    setTimeOutUse(true);
    //change();
}

NonlinearEquationsFrame::~NonlinearEquationsFrame()
{
    delete ui;
}

void NonlinearEquationsFrame::change()
{
    QString func;
    double a, b, e;

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

    func = ui->equationEdit->text();

    setThread(new EquationThread(func, a, b, e, mode));

    connect(getThread(), SIGNAL(sendResultSignal(double, int)), SLOT(onResult(double,int)));
    connect(getThread(), SIGNAL(sendErrorSignal(int)), SLOT(onError(int)));

    start();

    showAnswer(sCalculating);
}

void NonlinearEquationsFrame::showAnswer(QString ans)
{
    ui->answerEdit->setText(ans);
    ui->interationCountLabel->setText("");
}

void NonlinearEquationsFrame::onResult(double value, int iterations)
{
    end();

    if(!IsNan(value))
        showAnswer(QString::number(value));
    else
        showAnswer(sNanError);

    ui->interationCountLabel->setText(sIterationsCountForAccuracy(QString::number(iterations)));
}

void NonlinearEquationsFrame::onError(int code)
{
    end();

    if(code == CalcError)
        showAnswer(sSyntaxError);
    else showAnswer(sIntTimeoutError);
}

void NonlinearEquationsFrame::validatorSetup()
{
    QRegExpValidator *validator = new QRegExpValidator;
    validator->setRegExp(QRegExp("^[+-]?[\\d]+($|[\\.][\\d]+|([\\.][\\d]+[Ee]|[Ee])[+-]?\\d+)$"));
    ui->epsilonEdit->setValidator(validator);
}

void NonlinearEquationsFrame::on_equationEdit_textChanged(const QString &arg1)
{
    change();
}

void NonlinearEquationsFrame::on_limitAEdit_textChanged(const QString &arg1)
{
    change();
}

void NonlinearEquationsFrame::on_limitBEdit_textChanged(const QString &arg1)
{
    change();
}

void NonlinearEquationsFrame::on_epsilonEdit_textChanged(const QString &arg1)
{
    change();
}
