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

    if(arg1 > rows)
    {
        rows++;

        for(int i = 0; i < columns; ++i)
        {
            QLineEdit *newItem = new QLineEdit;
            newItem->setObjectName("item" + QString::number(rows) + "_" + QString::number(i));
            ui->matrixGrid->addWidget(newItem, rows - 1, i);
        }

    }
    else
    {
        for(int i = 0; i < columns; ++i)
        {
            QLayoutItem * itemToRemove = ui->matrixGrid->itemAtPosition(rows - 1, i);
            ui->matrixGrid->removeWidget(itemToRemove->widget());
            delete itemToRemove->widget();
        }

        rows--;
    }
}

void EquationsSystemsFrame::on_columnsSpin_valueChanged(int arg1)
{
    if(arg1 > columns)
    {
        columns++;

        for(int i = 0; i < rows; ++i)
        {
            QLineEdit *newItem = new QLineEdit;
            newItem->setObjectName("item" + QString::number(columns) + "_" + QString::number(i));
            ui->matrixGrid->addWidget(newItem, i, columns - 1);
        }

    }
    else
    {
        for(int i = 0; i < rows; ++i)
        {
            QLayoutItem * itemToRemove = ui->matrixGrid->itemAtPosition(i, columns - 1);
            ui->matrixGrid->removeWidget(itemToRemove->widget());
            delete itemToRemove->widget();
        }

        columns--;
    }
}

/*
 * [][][]
 * [][][]
 * [][][]
 */
