#include "equationsSystemsFrame.h"
#include "ui_equationsSystemsFrame.h"

EquationsSystemsFrame::EquationsSystemsFrame(QWidget *parent) :
    FrameThreadHelper(parent),
    ui(new Ui::EquationsSystemsFrame)
{
    ui->setupUi(this);
}

EquationsSystemsFrame::~EquationsSystemsFrame()
{
    delete ui;
}

void EquationsSystemsFrame::change()
{

}

void EquationsSystemsFrame::on_rowsSpin_valueChanged(int arg1)
{
    //TODO: сделать tabOrder для элементов матрицы
    //TODO: сделать удаление по разности

    arg1--;

    if(arg1 > rows)
    {
        for(int i = rows + 1; i <= arg1; ++i)
            for(int j = 0; j <= columns; ++j)
            {
                QLineEdit *newItem = new QLineEdit;
                newItem->setMinimumHeight(24);
                newItem->setObjectName("item" + QString::number(i) + "_" + QString::number(j));
                ui->matrixGrid->addWidget(newItem, i, j);
            }
    }
    else
    {
        for(int i = rows; i > arg1; --i)
            for(int j = 0; j <= columns; ++j)
            {
                QLayoutItem *itemToRemove = ui->matrixGrid->itemAtPosition(i, j);
                ui->matrixGrid->removeWidget(itemToRemove->widget());
                delete itemToRemove->widget();
            }
    }

    rows = arg1;
}

void EquationsSystemsFrame::on_columnsSpin_valueChanged(int arg1)
{
    arg1--;

    if(arg1 > columns)
    {
        for(int i = 0; i <= rows; ++i)
            for(int j = columns + 1; j <= arg1; ++j)
            {
                QLineEdit *newItem = new QLineEdit;
                newItem->setMinimumHeight(24);
                newItem->setObjectName("item" + QString::number(i) + "_" + QString::number(j));
                ui->matrixGrid->addWidget(newItem, i, j);
            }
    }
    else
    {
        for(int i = 0; i <= rows; ++i)
            for(int j = columns; j > arg1; --j)
            {
                QLayoutItem *itemToRemove = ui->matrixGrid->itemAtPosition(i, j);
                ui->matrixGrid->removeWidget(itemToRemove->widget());
                delete itemToRemove->widget();
            }
    }

    columns = arg1;
}

/*
 * [][][][]
 * [][][][]
 * [][][][]
 * [][][][]
 */
