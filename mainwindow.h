#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "Frames/frames.h"

namespace Ui
{
class MainWindow;
}

class QTreeWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT


    QMap<QTreeWidgetItem*, QWidget *> * itemWidgetMapping;

    typedef struct
    {
        QString name;
        QWidget* widget;
    } TMember, *PMember;

    typedef struct
    {
        QString name;
        PMember members;
        int membersCount;
    } THeader, *PHeader;

    void createMenu();
    void createStatusBar();
    void stackedWidgetSetup();
    void selectFirstFrame();


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_menu_itemClicked(QTreeWidgetItem *item, int column);

    void on_menu_expanded(const QModelIndex &index);

    void on_menu_collapsed(const QModelIndex &index);

    void onHelpButtonClicked();

private:
    Ui::MainWindow *ui;

    QPushButton * helpButton;
    HelpDialogFrame * helpDialogFrame;
};

#endif // MAINWINDOW_H
