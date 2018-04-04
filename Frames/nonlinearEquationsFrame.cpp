#include "nonlinearEquationsFrame.h"
#include "ui_nonlinearEquationsFrame.h"

NonlinearEquationsFrame::NonlinearEquationsFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NonlinearEquationsFrame)
{
    ui->setupUi(this);
}

NonlinearEquationsFrame::~NonlinearEquationsFrame()
{
    delete ui;
}
