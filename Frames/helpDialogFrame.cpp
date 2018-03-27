#include "helpDialogFrame.h"
#include "ui_helpdialogframe.h"

HelpDialogFrame::HelpDialogFrame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialogFrame)
{
    ui->setupUi(this);
}

HelpDialogFrame::~HelpDialogFrame()
{
    delete ui;
}
