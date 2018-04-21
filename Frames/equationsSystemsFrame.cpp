#include "equationsSystemsFrame.h"
#include "ui_equationsSystemsFrame.h"

EquationsSystemsFrame::EquationsSystemsFrame(QWidget *parent) :
    FrameThreadHelper(parent),
    ui(new Ui::EquationsSystemsFrame)
{
    ui->setupUi(this);
//    setMatrixTabOrder();
}

EquationsSystemsFrame::~EquationsSystemsFrame()
{
    delete ui;
}

void EquationsSystemsFrame::change()
{

}

void EquationsSystemsFrame::setRows(int count)
{
    QGridLayout *matrixGrid = ui->matrixGrid;
    count--;

    if(count > rows)
    {
        for(int i = rows + 1; i <= count; ++i)
            for(int j = 0; j <= columns; ++j)
            {
                QLineEdit *newItem = new QLineEdit;
                newItem->setMinimumHeight(24);
                newItem->setMaximumWidth(40);
                newItem->setObjectName("item" + QString::number(i) + "_" + QString::number(j));
                matrixGrid->addWidget(newItem, i, j);

                if(j != 0)
                    QWidget::setTabOrder(matrixGrid->itemAtPosition(i, j - 1)->widget(), newItem);
            }
    }
    else
    {
        QList<QWidget*> remove_list;

        for(int i = rows; i > count; --i)
            for(int j = 0; j <= columns; ++j)
            {
                QLayoutItem *itemToRemove = matrixGrid->itemAtPosition(i, j);
                remove_list.append(itemToRemove->widget());
            }

        foreach (QWidget *item, remove_list) {
            matrixGrid->removeWidget(item);
            delete item;
        }
    }

    rows = count;
}

void EquationsSystemsFrame::setColumns(int count)
{
    QGridLayout *matrixGrid = ui->matrixGrid;
    count--;

    if(count > columns)
    {
        for(int i = 0; i <= rows; ++i)
            for(int j = columns + 1; j <= count; ++j)
            {
                QLineEdit *newItem = new QLineEdit;
                newItem->setMinimumHeight(24);
                newItem->setMaximumWidth(40);
                newItem->setObjectName("item" + QString::number(i) + "_" + QString::number(j));
                matrixGrid->addWidget(newItem, i, j);

                QWidget::setTabOrder(matrixGrid->itemAtPosition(i, j - 1)->widget(), newItem);
            }
    }
    else
    {
        QList<QWidget*> remove_list;

        for(int i = 0; i <= rows; ++i)
            for(int j = columns; j > count; --j)
            {
                QLayoutItem *itemToRemove = matrixGrid->itemAtPosition(i, j);
                remove_list.append(itemToRemove->widget());
            }

        foreach (QWidget *item, remove_list) {
            matrixGrid->removeWidget(item);
            delete item;
        }
    }

    columns = count;

    //TODO:пофиксить баг с таб ордером последнего элемента второй строки
}

void EquationsSystemsFrame::setParams(int count)
{
    QGridLayout *paramsGrid = ui->parameterGrid;
    count--;

    if(count > params)
    {
        for(int i = params + 1; i <= count; ++i)
        {
            QLineEdit *newItem = new QLineEdit;
            newItem->setMinimumHeight(24);
            newItem->setMaximumWidth(40);
            newItem->setObjectName("item" + QString::number(i));
            paramsGrid->addWidget(newItem, i, 0);

            QWidget::setTabOrder(paramsGrid->itemAtPosition(i - 1, 0)->widget(), newItem);
        }
    }
    else
    {
        QList<QWidget*> remove_list;


        for(int i = params; i > count; --i)
        {
            QLayoutItem *itemToRemove = paramsGrid->itemAtPosition(i, 0);
            remove_list.append(itemToRemove->widget());
        }

        foreach (QWidget *item, remove_list) {
            paramsGrid->removeWidget(item);
            delete item;
        }
    }

    params = count;
}

void EquationsSystemsFrame::on_matrixSizeSpin_valueChanged(int arg1)
{
    setColumns(arg1);
    setRows(arg1);
    setParams(arg1);
}
