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

    if(mode != ModeEqNewton)
    {
        ui->derivativeEdit->setVisible(false);
        ui->derivativeLabel->setVisible(false);
        ui->x0Edit->setVisible(false);
        ui->x0Label->setVisible(false);
    }
    else
    {
        ui->aLabel->setVisible(false);
        ui->bLabel->setVisible(false);
        ui->limitAEdit->setVisible(false);
        ui->limitBEdit->setVisible(false);
        ui->limitLabel->setVisible(false);
    }
}

NonlinearEquationsFrame::~NonlinearEquationsFrame()
{
    delete ui;
}

void NonlinearEquationsFrame::change()
{
    QString func;
    QString derivative;
    double a, b, e, x0;

    cancel();

    if(mode != ModeEqNewton)
    {
        a = Expression(QStrToCStr(ui->limitAEdit->text()));
        if(IsNan(a))
        {
            showAnswer("Неверный параметр ""от""");
            return;
        }

        b = Expression(QStrToCStr(ui->limitBEdit->text()));
        if(IsNan(b))
        {
            showAnswer("Неверный параметр ""до""");
            return;
        }
    }
    else
    {
        x0 = Expression(QStrToCStr(ui->x0Edit->text()));
        if(IsNan(x0))
        {
            showAnswer("Неверный параметр ""x0""");
            return;
        }

        derivative = ui->derivativeEdit->text();
    }

    e = ui->epsilonEdit->text().toDouble();
    if(e > 1 || e < 1e-99)
    {
        showAnswer("Точность должна быть в пределах [1..1e-99]");
        return;
    }

    func = ui->equationEdit->text();

    if(mode != ModeEqNewton)
        setThread(new EquationThread(func, a, b, e, mode));
    else
        setThread(new EquationThread(func, derivative, x0, e, mode));

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
    {
        showAnswer(sSpanError);
        return;
    }

    ui->interationCountLabel->setText(sIterationsCountForAccuracy(QString::number(iterations)));
}

void NonlinearEquationsFrame::onError(int code)
{
    end();

    if(code == CalcError)
        showAnswer(sSyntaxError);
    else showAnswer(sEqTimeoutError);
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

void NonlinearEquationsFrame::on_derivativeEdit_textChanged(const QString &arg1)
{
    change();
}

void NonlinearEquationsFrame::on_x0Edit_textChanged(const QString &arg1)
{
    change();
}
