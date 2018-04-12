#include "diffEqEulerMethodFrame.h"
#include "ui_diffEqEulerMethodFrame.h"

#include "UIConsts.h"

DiffEqEulerMethodFrame::DiffEqEulerMethodFrame(QWidget *parent) :
    FrameThreadHelper(parent),
    ui(new Ui::DiffEqEulerMethodFrame)
{
    ui->setupUi(this);
}

DiffEqEulerMethodFrame::~DiffEqEulerMethodFrame()
{
    delete ui;
}

void DiffEqEulerMethodFrame::change()
{
    qDebug() << "\n\n\nchange";
    double h, x0, y0;
    QString func;

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

    XYArrayLength = ui->iterationSpinBox->value();

    if(XYArrayLength < 5 || XYArrayLength > 1000)
    {
        showAnswer("n должен быть от 5 до 1000");
        return;
    }

    func = ui->functionEdit->text();

    if(XYArray == nullptr)
    {
        qDebug() << "try to malloc";
        XYArray = (PointFArray) malloc(sizeof(TPointF) * XYArrayLength);
        qDebug() << "success malloc";
    }
    else
    {
        qDebug() << "try to free";
        free(XYArray);
        qDebug() << "success free";
        XYArray = (PointFArray) malloc(sizeof(TPointF) * XYArrayLength);
    }

    setThread(new DiffEqEulerMethodThread(func, x0, y0, XYArrayLength, h, XYArray));
    connect(getThread(), SIGNAL(sendResultSignal()), SLOT(onResult()));
    connect(getThread(), SIGNAL(sendErrorSignal(int)), SLOT(onError(int)));
    start();

    showAnswer(sCalculating);
}

void DiffEqEulerMethodFrame::showAnswer(QString ans)
{
    ui->answerEdit->clear();
    ui->answerEdit->appendPlainText(ans);
}

void DiffEqEulerMethodFrame::onResult()
{
    end();

    qDebug() << "onResult";

    ui->answerEdit->clear();

    if(XYArray != nullptr)
    {
        for(int i = 0; i < XYArrayLength; ++i)
        {
            ui->answerEdit->appendPlainText(QString::number(i) +
                                            " : x=" + QString::number(XYArray[i].x) +
                                            "; y=" + QString::number(XYArray[i].y));
            qDebug() << QString::number(i) +
                        " : x=" + QString::number(XYArray[i].x) +
                        "; y=" + QString::number(XYArray[i].y);
        }

        qDebug() << "try to free";
        free(XYArray);
        XYArray = nullptr;
        qDebug() << "success free";
    }

//    if(!IsNan(value))
//        showAnswer(QString::number(value));
//    else
//        showAnswer(sNanError);
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

void DiffEqEulerMethodFrame::hideEvent(QHideEvent *event)
{
    if(XYArray != nullptr)
        free(XYArray);
}
