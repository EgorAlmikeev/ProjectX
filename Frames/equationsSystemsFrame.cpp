#include "equationsSystemsFrame.h"
#include "ui_equationsSystemsFrame.h"

#include "UIConsts.h"

EquationsSystemsFrame::EquationsSystemsFrame(QWidget *parent, ModeEqSys mode) :
    FrameThreadHelper(parent),
    ui(new Ui::EquationsSystemsFrame)
{
    ui->setupUi(this);

    this->mode = mode;

    matrixItemValidator = new QRegExpValidator();
    matrixItemValidator->setRegExp(QRegExp("^[+-]?[\\d]+($|[\\.][\\d]+|([\\.][\\d]+[Ee]|[Ee])[+-]?\\d+)$"));

    setColumns(2);
    setRows(2);
    setParams(2);
    setMatrixTabOrder();
}

EquationsSystemsFrame::~EquationsSystemsFrame()
{
    delete ui;
}

void EquationsSystemsFrame::change()
{
    double e;
    TEqArray params;
    TEqMatrix  matrix;
    int n;

    cancel();

    e = ui->EpsilonEdit->text().toDouble();
    n = paramCount;

    if(e > 1 || e < 1e-99)
    {
        showAnswer("Точность должна быть в пределах [1..1e-99]");
        return;
    }

    matrix = getMatrixValues();
    params = getParamsValues();

    setThread(new EquationsSystemsThread(matrix, params, n, e, mode));
    connect(getThread(), SIGNAL(sendResultSignal(double*, int)), SLOT(onResult(double*, int)));
    connect(getThread(), SIGNAL(sendErrorSignal(int)), SLOT(onError(int)));

    start();

    showAnswer(sCalculating);
}

void EquationsSystemsFrame::setRows(int count)
{
    QGridLayout *matrixGrid = ui->matrixGrid;

    if(count > rowCount)
    {
        for(int i = rowCount; i < count; ++i)
            for(int j = 0; j < columnCount; ++j)
            {
                QLineEdit *newItem = createNewMatrixItem();
                matrixGrid->addWidget(newItem, i, j);
                newItem->setObjectName(QString::number(i) + QString::number(j) + "item");
            }
    }
    else if(count < rowCount)
    {
        QList<QWidget*> remove_list;

        for(int i = rowCount - 1; i > count - 1; --i)
            for(int j = 0; j < columnCount; ++j)
            {
                QLayoutItem *itemToRemove = matrixGrid->itemAtPosition(i, j);
                remove_list.append(itemToRemove->widget());
            }

        foreach (QWidget *item, remove_list)
        {
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
                QLineEdit *newItem = createNewMatrixItem();
                matrixGrid->addWidget(newItem, i, j);
                newItem->setObjectName(QString::number(i) + QString::number(j) + "item");
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

        foreach (QWidget *item, remove_list)
        {
            matrixGrid->removeWidget(item);
            delete item;
        }
    }

    columnCount = count;
}

void EquationsSystemsFrame::setParams(int count)
{
    QGridLayout *paramsGrid = ui->parametersGrid;

    if(count > paramCount)
    {
        for(int i = paramCount; i < count; ++i)
        {
            QLineEdit *newItem = createNewMatrixItem();
            paramsGrid->addWidget(newItem, i, 0);
            newItem->setObjectName(QString::number(i) + "item");
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

        foreach (QWidget *item, remove_list)
        {
            paramsGrid->removeWidget(item);
            delete item;
        }
    }

    paramCount = count;
}

TEqMatrix EquationsSystemsFrame::getMatrixValues()
{
    QGridLayout *matrixGrid = ui->matrixGrid;

    TEqMatrix matrixArray = nullptr;

    matrixArray = CreateMatrix(rowCount, columnCount);

    for(int i = 0; i < rowCount; ++i)
    {
        for(int j = 0; j < columnCount; ++j)
        {
            QLineEdit *edit = (QLineEdit*) matrixGrid->itemAtPosition(i, j)->widget();
            double digit = 0.0;
            if(!edit->text().isEmpty())
                 digit = edit->text().toDouble();
            matrixArray[i][j] = digit;
//            qDebug() << "matrix[" << i << "][" << j << "] = " << digit << "\t from object " << edit->objectName();
        }
    }

    return matrixArray;
}

TEqArray EquationsSystemsFrame::getParamsValues()
{
    QGridLayout *parametersGrid = ui->parametersGrid;

    TEqArray parametersArray = nullptr;

    parametersArray = (double *) malloc(paramCount * sizeof(double));

    for(int i = 0; i < paramCount; ++i)
        parametersArray[i] = ((QLineEdit*) parametersGrid->itemAtPosition(i, 0)->widget())->text().toDouble();

    return parametersArray;
}

void EquationsSystemsFrame::showAnswer(QString ans)
{
    ui->answerEdit->clear();
    ui->answerEdit->appendPlainText(ans);
}

void EquationsSystemsFrame::on_matrixSizeSpin_valueChanged(int arg1)
{
    setColumns(arg1);
    setRows(arg1);
    setParams(arg1);
    setMatrixTabOrder();

    change();
}

void EquationsSystemsFrame::on_EpsilonEdit_textChanged(const QString &arg1)
{
    change();
}

void EquationsSystemsFrame::onResult(double *value, int n)
{
    end();

    ui->answerEdit->clear();
    QString result_string;

    for(int i = 0; i < n; i++)
    {
        result_string.append(QString::number(i) + ": " + QString::number(value[i]) + "\n");
    }

    ui->answerEdit->appendPlainText(result_string);
    ui->answerEdit->moveCursor(QTextCursor::Start);

    free(value);
}

void EquationsSystemsFrame::onError(int code)
{

}

void EquationsSystemsFrame::onMatrixElementTextChanged()
{
    change();
}

QLineEdit * EquationsSystemsFrame::createNewMatrixItem()
{
    QLineEdit *newItem = new QLineEdit;
    newItem->setMinimumWidth(40);
    newItem->setAlignment(Qt::AlignCenter);
    newItem->setPlaceholderText("0");
    newItem->setValidator(matrixItemValidator);

    connect(newItem, SIGNAL(textChanged(QString)), SLOT(onMatrixElementTextChanged()));

    return newItem;
}

void EquationsSystemsFrame::setMatrixTabOrder()
{
    QGridLayout * matrixGrid = ui->matrixGrid;
    QList<QWidget*> list;

    for(int i = 0; i < columnCount; ++i)
        for(int j = 0; j < rowCount; ++j)
            list.append(matrixGrid->itemAtPosition(i, j)->widget());

    for(int i = 1; i < list.size(); ++i)
        QWidget::setTabOrder(list.at(i - 1), list.at(i));
}
