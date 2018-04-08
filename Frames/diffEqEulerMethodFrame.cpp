#include "diffEqEulerMethodFrame.h"
#include "ui_diffEqEulerMethodFrame.h"

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
