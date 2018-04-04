#include "multipleIntegralFrame.h"
#include "ui_multipleIntegralFrame.h"

MultipleIntegralFrame::MultipleIntegralFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultipleIntegralFrame)
{
    ui->setupUi(this);
}

MultipleIntegralFrame::~MultipleIntegralFrame()
{
    delete ui;
}
