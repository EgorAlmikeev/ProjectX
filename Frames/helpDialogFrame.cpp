#include "helpDialogFrame.h"
#include "ui_helpdialogframe.h"

HelpDialogFrame::HelpDialogFrame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialogFrame)
{
    ui->setupUi(this);

    connect(ui->comboBox, SIGNAL(activated(int)), SIGNAL(themeChanged(int)));
}

HelpDialogFrame::~HelpDialogFrame()
{
    delete ui;
}
