#include "helpDialogFrame.h"
#include "ui_helpDialogFrame.h"

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
