#include "diffEqEulerMethodFrame.h"
#include "ui_diffEqEulerMethodFrame.h"

DiffEqEulerMethodFrame::DiffEqEulerMethodFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiffEqEulerMethodFrame)
{
    ui->setupUi(this);
}

DiffEqEulerMethodFrame::~DiffEqEulerMethodFrame()
{
    delete ui;
}
