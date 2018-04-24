#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLabel"
#include "QTreeWidget"
#include "Core/CalcThread.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMinimumWidth(ui->menu->minimumWidth() + layout()->margin());

    createMenu();
    stackedWidgetSetup();
    selectFirstFrame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenu()
{
    itemWidgetMapping = new QMap<QTreeWidgetItem *, QWidget *>();

    const int integralItemsCount = 3;
    TMember integralItems[integralItemsCount] =
    {
        {"Постоянный шаг",          new IntegralConstStepFrame},
        {"Переменный шаг",          new IntegralFloatingStepFrame},
        {"Кратное интегрирование",  new IntegralMultipleFrame}
    };

    const int differentialEquationsItemsCount = 2;
    TMember differentialEquationsItems[differentialEquationsItemsCount] =
    {
        {"Метод Эйлера",        new DiffEqEulerMethodFrame(this, ModeDiffEuler)},
        {"Метод Рунге-Кутты",   new DiffEqEulerMethodFrame(this, ModeDiffRunge)}
    };

    const int nolinearItemsCount = 3;
    TMember nolinearItems[nolinearItemsCount] =
    {
        {"Метод Дихотомии", new NonlinearEquationsFrame(this, ModeEqHalfDiv)},
        {"Метод Хорд",      new NonlinearEquationsFrame(this, ModeEqChord)},
        {"Метод Ньютона",   new NonlinearEquationsFrame(this, ModeEqNewton)}
    };

    const int simpleFunctionsItemsCount = 2;
    TMember simpleFunctionsItems[simpleFunctionsItemsCount] =
    {
        {"Метод Маклорена",         new SinCosFrame(this, MaclaurinMode)},
        {"Метод Цифра за цифрой",   new SinCosFrame(this, CordicMode)}
    };

    const int equationsSystemsItemsCount = 4;
    TMember equationsSystemsItems[equationsSystemsItemsCount] =
    {
        {"Метод Гаусса",                        new EquationsSystemsFrame(this, ModeEqSysGauss)},
        {"Метод оптимальных исключений",        new EquationsSystemsFrame(this, ModeEqSysOptimal)},
        {"Гаусса-Жордана",                      new EquationsSystemsFrame(this, ModeEqSysJordan)},
        {"Метод наименьших квадратов",          new EquationsSystemsFrame(this, ModeEqSysSquare)},
    };

    const int menuItemsCount = 5;
    THeader menu[menuItemsCount] =
    {
        {
            "Интегрирование",
            integralItems,
            integralItemsCount
        },

        {
            "Дифференциальные уравнения",
            differentialEquationsItems,
            differentialEquationsItemsCount
        },

        {
            "Нелинейные уравнения",
            nolinearItems,
            nolinearItemsCount
        },

        {
            "Элементарные функции",
            simpleFunctionsItems,
            simpleFunctionsItemsCount
        },

        {
            "Решение СЛАУ",
            equationsSystemsItems,
            equationsSystemsItemsCount
        }
    };

    for(int i = 0; i < menuItemsCount; ++i)
    {
        QTreeWidgetItem *header = new QTreeWidgetItem(ui->menu);
        header->setText(0, menu[i].name);
        header->setFlags(header->flags() & ~Qt::ItemIsSelectable);

        PMember members = menu[i].members;

        for(int j = 0; j < menu[i].membersCount; ++j)
        {
            QTreeWidgetItem *member = new QTreeWidgetItem(header);
            member->setText(0, members[j].name);
            itemWidgetMapping->insert(member, members[j].widget);
        }
    }

    ui->menu->expandAll();
}

void MainWindow::stackedWidgetSetup()
{
    QMap<QTreeWidgetItem *, QWidget *>::iterator iter = itemWidgetMapping->begin();
    while(iter != itemWidgetMapping->end())
    {
        ui->stackedWidget->addWidget(iter.value());
        ++iter;
    }

    ui->stackedWidget->setFocus();
}

void MainWindow::selectFirstFrame()
{
    QTreeWidgetItem *item = ui->menu->topLevelItem(0)->child(0);
    item->setSelected(true);

    QMap<QTreeWidgetItem *, QWidget *>::iterator currentWidgetIterator = itemWidgetMapping->find(item);
    if(currentWidgetIterator != itemWidgetMapping->end())
    {
        ui->stackedWidget->setCurrentWidget(currentWidgetIterator.value());
        ui->frameName->setText(item->parent()->text(0) + ": " + item->text(0));
        if(dynamic_cast<FrameThreadHelper*>(currentWidgetIterator.value()))
            static_cast<FrameThreadHelper*>(currentWidgetIterator.value())->change();
    }
}

void MainWindow::on_menu_expanded(const QModelIndex &index)
{
    ui->menu->resizeColumnToContents(index.column());
}

void MainWindow::on_menu_collapsed(const QModelIndex &index)
{
    ui->menu->resizeColumnToContents(index.column());
}

void MainWindow::on_helpButton_clicked()
{
    createHelpDialog();
    helpDialogFrame->show();
    helpDialogFrame->setFocus();
}

void MainWindow::createHelpDialog()
{
    if(helpDialogFrame == nullptr)
        helpDialogFrame = new HelpDialogFrame;
}

void MainWindow::on_menu_itemSelectionChanged()
{
    QTreeWidgetItem *item = ui->menu->currentItem();

    QMap<QTreeWidgetItem *, QWidget *>::iterator currentWidgetIterator = itemWidgetMapping->find(item);
    if(currentWidgetIterator != itemWidgetMapping->end())
    {
        ui->stackedWidget->setCurrentWidget(currentWidgetIterator.value());
        ui->frameName->setText(item->parent()->text(0) + ": " + item->text(0));
        if(dynamic_cast<FrameThreadHelper*>(currentWidgetIterator.value()))
            static_cast<FrameThreadHelper*>(currentWidgetIterator.value())->change();
    }
}
