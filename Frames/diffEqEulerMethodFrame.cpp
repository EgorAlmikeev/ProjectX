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
    double h, xStart, xEnd, y0;
    QString func;
    int n;

    cancel();

    xStart = Expression(QStrToCStr(ui->xStartEdit->text()));
    if(IsNan(xStart))
    {
        showAnswer("Неверный параметр Отрезок(начальная точка)");
        return;
    }

    xEnd = Expression(QStrToCStr(ui->xEndEdit->text()));
    if(IsNan(xEnd))
    {
        showAnswer("Неверный параметр Отрезок(конечная точка)");
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

    if(h < 1e-10 || h > 1)
    {
        showAnswer("n должен быть от 1e-10 до 1");
        return;
    }

    func = ui->functionEdit->text();

    setThread(new DiffEqEulerMethodThread(func, xStart, xEnd, y0, h, mode));
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
    // todo: добавить исключения!
    end();

    ui->answerEdit->clear();

    QString result_string;
    for(int i = 0; i < n; i++)
    {
        QString nStr = QString::number(i).append(":").leftJustified(5);
        QString xStr = QString::number(value[i].x).append(",").leftJustified(8);
        result_string = result_string.append(
                    QString("%1 x = %2 y = %3").arg(nStr).arg(xStr).arg(value[i].y)).append("\n");
    }
    ui->answerEdit->appendPlainText(result_string);

    free(value);
    ui->answerEdit->moveCursor(QTextCursor::Start);
}

void DiffEqEulerMethodFrame::onError(int code)
{
    end();

    if(code == CalcError)
        showAnswer(sSyntaxError);
    else if(code == ErrorTooLongN)
        showAnswer(sTooFewH);
    else
        showAnswer(sEqTimeoutError);
}

void DiffEqEulerMethodFrame::on_functionEdit_textChanged(const QString &arg1)
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

void DiffEqEulerMethodFrame::on_xStartEdit_textChanged(const QString &arg1)
{
    change();
}

void DiffEqEulerMethodFrame::on_xEndEdit_textChanged(const QString &arg1)
{
    change();
}
