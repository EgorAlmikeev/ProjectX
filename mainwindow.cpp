#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLabel"
#include "QTreeWidget"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMinimumWidth(ui->menu->minimumWidth() + layout()->margin());

    createMenu();
    stackedWidgetSetup();
    selectFirstFrame();

    createStatusBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenu()
{
    itemWidgetMapping = new QMap<QTreeWidgetItem*, QWidget*>();

    const int integralItemsCount = 3;
    TMember integralItems[integralItemsCount] =
    {
        {"Постоянный шаг", new IntegralConstStepFrame},
        {"Переменный шаг", new QLabel("Переменный шаг")},
        {"Кратное интегрирование", new QLabel("Кратное интегрирование")}
    };

    const int differentialEquationsItemsCount = 2;
    TMember differentialEquationsItems[differentialEquationsItemsCount] =
    {
        {"Метод Эйлера", new QLabel("Метод Эйлера")},
        {"Метод Рунге-Кутты", new QLabel("Метод Рунге-Кутты")}
    };

    const int nolinearItemsCount = 3;
    TMember nolinearItems[nolinearItemsCount] =
    {
        {"Метод Дихотомии", new QLabel("Метод Дихотомии")},
        {"Метод касательных (Ньютона)", new QLabel("Метод касательных (Ньютона)")},
        {"Метод хорд", new QLabel("Метод хорд")}
    };

    const int simpleFunctionsItemsCount = 2;
    TMember simpleFunctionsItems[simpleFunctionsItemsCount] =
    {
        {"Метод Маклорена", new QLabel("Метод Маклорена")},
        {"Метод Цифра за цифрой", new QLabel("Метод Цифра за цифрой")}
    };

    const int equationsSystemsItemsCount = 5;
    TMember equationsSystemsItems[equationsSystemsItemsCount] =
    {
        {"Метод Гаусса", new QLabel("Метод Гаусса")},
        {"Гаусса-Жордана", new QLabel("Гаусса-Жордана")},
        {"Метод Гаусса с распараллеливаниями", new QLabel("Метод Гаусса с распараллеливаниями")},
        {"Метод Вращения", new QLabel("Метод Вращения")},
        {"Метод наименьших квадратов", new QLabel("Метод наименьших квадратов")}
    };

    const int menuItemsCount = 5;
    THeader menu[menuItemsCount] =
    {
        {"Интегрирование",
         integralItems,
         integralItemsCount},

        {"Дифференциальные уравнения",
         differentialEquationsItems,
         differentialEquationsItemsCount},

        {"Нелинейные уравнения",
        nolinearItems,
        nolinearItemsCount},

        {"Элементарные функции",
        simpleFunctionsItems,
        simpleFunctionsItemsCount},

        {"Решение СЛАУ",
        equationsSystemsItems,
        equationsSystemsItemsCount}
    };

    for(int i = 0; i < menuItemsCount; ++i)
    {
        QTreeWidgetItem * nextHeader = new QTreeWidgetItem(ui->menu);
        nextHeader->setText(0, menu[i].name);
        nextHeader->setFlags(nextHeader->flags() & ~Qt::ItemIsSelectable);

        PMember members = menu[i].members;

        for(int j = 0; j < menu[i].membersCount; ++j) {
            QTreeWidgetItem * nextMember = new QTreeWidgetItem(nextHeader);
            nextMember->setText(0, members[j].name);
            itemWidgetMapping->insert(nextMember, members[j].widget);
        }
    }

    ui->menu->expandAll();

}

void MainWindow::createStatusBar()
{
    helpButton = new QPushButton("Помощь");
    helpDialogFrame = new HelpDialogFrame;
    ui->statusBar->layout()->addWidget(helpButton);
    ui->statusBar->layout()->setAlignment(Qt::AlignRight);
    connect(helpButton, SIGNAL(clicked(bool)), SLOT(onHelpButtonClicked()));
}

void MainWindow::stackedWidgetSetup()
{
    ui->stackedWidget->setMaximumHeight(400);

    QMap<QTreeWidgetItem*, QWidget*>::iterator iter = itemWidgetMapping->begin();
    while(iter != itemWidgetMapping->end()) {
        ui->stackedWidget->addWidget(iter.value());
        ++iter;
    }
}

void MainWindow::selectFirstFrame()
{
    QTreeWidgetItem * item = ui->menu->topLevelItem(0)->child(0);

    item->setSelected(true);
    ui->stackedWidget->setCurrentWidget(itemWidgetMapping->find(item).value());
}

void MainWindow::on_menu_itemClicked(QTreeWidgetItem *item, int column)
{
    QMap<QTreeWidgetItem*, QWidget *>::iterator currentWidgetIterator = itemWidgetMapping->find(item);
    if(currentWidgetIterator != itemWidgetMapping->end())
        ui->stackedWidget->setCurrentWidget(currentWidgetIterator.value());
}

void MainWindow::on_menu_expanded(const QModelIndex &index)
{
    ui->menu->resizeColumnToContents(index.column());
}

void MainWindow::on_menu_collapsed(const QModelIndex &index)
{
    ui->menu->resizeColumnToContents(index.column());
}

void MainWindow::onHelpButtonClicked()
{
    ui->statusBar->repaint();
    helpDialogFrame->show();
    helpDialogFrame->setFocus();
}
