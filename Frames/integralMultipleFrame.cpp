#include "integralMultipleFrame.h"
#include "ui_integralMultipleFrame.h"

IntegralMultipleFrame::IntegralMultipleFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntegralMultipleFrame)
{
    ui->setupUi(this);
}

IntegralMultipleFrame::~IntegralMultipleFrame()
{
    delete ui;
}
