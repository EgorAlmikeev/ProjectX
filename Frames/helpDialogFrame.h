#ifndef HELPDIALOGFRAME_H
#define HELPDIALOGFRAME_H

#include <QDialog>

namespace Ui {
class HelpDialogFrame;
}

class HelpDialogFrame : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialogFrame(QWidget *parent = 0);
    ~HelpDialogFrame();

signals:
    void themeChanged(int);

private:
    Ui::HelpDialogFrame *ui;
};

#endif // HELPDIALOGFRAME_H
