#include "diffEqEulerMethodFrame.h"
#include "ui_diffEqEulerMethodFrame.h"
#include <QMetaType>

#include "UIConsts.h"

DiffEqEulerMethodFrame::DiffEqEulerMethodFrame(QWidget *parent, ModeDiff mode) :
    FrameThreadHelper(parent),
    ui(new Ui::DiffEqEulerMethodFrame)
{
    ui->setupUi(this);

    this->mode = mode;

    qRegisterMetaType<PointFArray>("PointFArray");
}

DiffEqEulerMethodFrame::~DiffEqEulerMethodFrame()
{
    delete ui;
}

void DiffEqEulerMethodFrame::change()
{
    double h, x0, y0;
    QString func;
    int n;

    cancel();

    x0 = Expression(QStrToCStr(ui->xEdit->text()));
    if(IsNan(x0))
    {
        showAnswer("Неверный параметр x0");
        return;
    }

    y0 = Expression(QStrToCStr(ui->yEdit->text()));
    if(IsNan(y0))
    {
        showAnswer("Неверный параметр y0");
        return;
    }

    h = Expression(QStrToCStr(ui->stepEdit->text()));
    if(IsNan(h))
    {
        showAnswer("Неверный параметр h");
        return;
    }

    n = ui->iterationSpinBox->value();

    if(n < 5 || n > 1000)
    {
        showAnswer("n должен быть от 5 до 1000");
        return;
    }

    func = ui->functionEdit->text();

    setThread(new DiffEqEulerMethodThread(func, x0, y0, n, h, mode));
    connect(getThread(), SIGNAL(sendResultSignal(PointFArray, int)), SLOT(onResult(PointFArray, int)));
    connect(getThread(), SIGNAL(sendErrorSignal(int)), SLOT(onError(int)));
    start();

    showAnswer(sCalculating);
}

void DiffEqEulerMethodFrame::showAnswer(QString ans)
{
    ui->answerEdit->clear();
    ui->answerEdit->appendPlainText(ans);
}

void DiffEqEulerMethodFrame::onResult(PointFArray value, int n)
{
    end();

    ui->answerEdit->clear();

    QString result_string;
    for(int i = 0; i < n; ++i)
    {
        result_string = QString::number(i) +
                " : x=" + QString::number(value[i].x) +
                "; y=" + QString::number(value[i].y);

        ui->answerEdit->appendPlainText(result_string);
    }

    free(value);
    ui->answerEdit->moveCursor(QTextCursor::Start);
}

void DiffEqEulerMethodFrame::onError(int code)
{
    end();

    if(code == CalcError)
        showAnswer(sSyntaxError);
    else showAnswer(sEqTimeoutError);
}

void DiffEqEulerMethodFrame::on_functionEdit_textChanged(const QString &arg1)
{
    change();
}

void DiffEqEulerMethodFrame::on_xEdit_textChanged(const QString &arg1)
{
    change();
}

void DiffEqEulerMethodFrame::on_yEdit_textChanged(const QString &arg1)
{
    change();
}

void DiffEqEulerMethodFrame::on_stepEdit_textChanged(const QString &arg1)
{
    change();
}

void DiffEqEulerMethodFrame::on_iterationSpinBox_valueChanged(int arg1)
{
    change();
}

//Q_DECLARE_METATYPE(PointFArray);
