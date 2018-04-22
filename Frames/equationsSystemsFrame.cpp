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
    double e;

    e = ui->EpsilonEdit->text().toDouble();

    if(e > 1 || e < 1e-99)
    {
        showAnswer("Точность должна быть в пределах [1..1e-99]");
        return;
    }

    getMatrixValues();
    getParamsValues();

//    setThread(new EquationsSystemsThread());
}

void EquationsSystemsFrame::setRows(int count)
{
    QGridLayout *matrixGrid = ui->matrixGrid;

    if(count > rowCount)
    {
        for(int i = rowCount; i < count; ++i)
            for(int j = 0; j < columnCount; ++j)
            {
                QLineEdit *newItem = new QLineEdit;
                newItem->setMinimumHeight(24);
                newItem->setMaximumWidth(40);
                newItem->setObjectName("item" + QString::number(i) + "_" + QString::number(j));
                matrixGrid->addWidget(newItem, i, j);

//                if(j != 0)
//                    QWidget::setTabOrder(matrixGrid->itemAtPosition(i, j - 1)->widget(), newItem);
            }
    }
    else if(count < rowCount) //count = 2 rowCount = 3
    {
        QList<QWidget*> remove_list;

        for(int i = rowCount - 1; i > count - 1; --i)
            for(int j = 0; j < columnCount; ++j)
            {
                QLayoutItem *itemToRemove = matrixGrid->itemAtPosition(i, j);
                remove_list.append(itemToRemove->widget());
            }

        foreach (QWidget *item, remove_list) {
            matrixGrid->removeWidget(item);
            delete item;
        }
    }

    rowCount = count;
}

void EquationsSystemsFrame::setColumns(int count)
{
    QGridLayout *matrixGrid = ui->matrixGrid;

    if(count > columnCount)
    {
        for(int i = 0; i < rowCount; ++i)
            for(int j = columnCount; j < count; ++j)
            {
                QLineEdit *newItem = new QLineEdit;
                newItem->setMinimumHeight(24);
                newItem->setMaximumWidth(40);
                newItem->setObjectName("item" + QString::number(i) + "_" + QString::number(j));
                matrixGrid->addWidget(newItem, i, j);

//                QWidget::setTabOrder(matrixGrid->itemAtPosition(i, j - 1)->widget(), newItem);
            }
    }
    else if(count < columnCount)
    {
        QList<QWidget*> remove_list;

        for(int i = 0; i < rowCount; ++i)
            for(int j = columnCount - 1; j > count - 1; --j)
            {
                QLayoutItem *itemToRemove = matrixGrid->itemAtPosition(i, j);
                remove_list.append(itemToRemove->widget());
            }

        foreach (QWidget *item, remove_list) {
            matrixGrid->removeWidget(item);
            delete item;
        }
    }

    columnCount = count;

    //TODO:пофиксить баг с таб ордером последнего элемента второй строки
}

void EquationsSystemsFrame::setParams(int count)
{
    QGridLayout *paramsGrid = ui->parametersGrid;

    if(count > paramCount)
    {
        for(int i = paramCount; i < count; ++i)
        {
            QLineEdit *newItem = new QLineEdit;
            newItem->setMinimumHeight(24);
            newItem->setMaximumWidth(40);
            newItem->setObjectName("item" + QString::number(i));
            paramsGrid->addWidget(newItem, i, 0);

//            QWidget::setTabOrder(paramsGrid->itemAtPosition(i - 1, 0)->widget(), newItem);
        }
    }
    else if(count < paramCount)
    {
        QList<QWidget*> remove_list;


        for(int i = paramCount - 1; i > count - 1; --i)
        {
            QLayoutItem *itemToRemove = paramsGrid->itemAtPosition(i, 0);
            remove_list.append(itemToRemove->widget());
        }

        foreach (QWidget *item, remove_list) {
            paramsGrid->removeWidget(item);
            delete item;
        }
    }

    paramCount = count;
}

double ** EquationsSystemsFrame::getMatrixValues()
{
    QGridLayout *matrixGrid = ui->matrixGrid;

    double **matrixArray = nullptr;

    matrixArray = CreateMatrix(rowCount, columnCount);

    //этот цикл не может работать нормально

    for(int i = 0; i < rowCount; ++i)
    {
        for(int j = 0; j < columnCount; ++j)
        {
            QLineEdit *edit = (QLineEdit*) matrixGrid->itemAtPosition(i, j)->widget();
            double digit = edit->text().toDouble();
            matrixArray[i][j] = digit;
            qDebug() << "matrix[" << i << "][" << j << "] = " << digit << "\t from object " << edit->objectName();
        }
    }
}

double * EquationsSystemsFrame::getParamsValues()
{
    QGridLayout *parametersGrid = ui->parametersGrid;

    double *parametersArray = nullptr;

    parametersArray = (double *) malloc(paramCount * sizeof(double));

    for(int i = 0; i < paramCount; ++i)
        parametersArray[i] = ((QLineEdit*) parametersGrid->itemAtPosition(i, 0)->widget())->text().toDouble();
}

void EquationsSystemsFrame::showAnswer(QString ans)
{
    ui->answerEdit->setText(ans);
}

void EquationsSystemsFrame::on_matrixSizeSpin_valueChanged(int arg1)
{
    setColumns(arg1);
    setRows(arg1);
    setParams(arg1);

    change();
}

void EquationsSystemsFrame::on_EpsilonEdit_textChanged(const QString &arg1)
{
    change();
}
