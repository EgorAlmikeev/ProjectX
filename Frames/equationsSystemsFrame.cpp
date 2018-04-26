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

    setDefaultValues();

    isLoading = false;
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

    if(isLoading)
        return;

    cancel();

    e = ui->EpsilonEdit->text().toDouble();
    n = size;

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

void EquationsSystemsFrame::createMatrixUI(int new_size)
{
    QGridLayout *matrixGrid = ui->matrixGrid;

    int rows = size;
    int columns = size + 2; //line + params

    QList<QWidget*> itemsList;

    //deleting old elements
    if(size != 0)
        for(int i = 0; i < rows; ++i)
            for(int j = 0; j < columns; ++j)
            {
                if(i > 0 && j == size)
                    continue;

                QLineEdit *edit = (QLineEdit*) matrixGrid->itemAtPosition(i, j)->widget();
                itemsList.append(edit);
            }

    foreach (QWidget *widget, itemsList)
    {
        delete widget;
    }
    itemsList.clear();
    //deleted

    size = new_size;
    rows = size;
    columns = size + 2;

    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < columns; ++j)
        {
            if(j != size) //if line place – skip it
            {
                QWidget *item = createNewMatrixItem();
                item->setObjectName("item" + QString::number(i) + "-" + QString::number(j));
                matrixGrid->addWidget(item, i, j);
            }
        }


    QFrame *line = new QFrame;
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setObjectName("line");

    matrixGrid->addWidget(line, 0, size, rows, 1);
}

TEqMatrix EquationsSystemsFrame::getMatrixValues()
{
    QGridLayout *matrixGrid = ui->matrixGrid;
    TEqMatrix matrixArray = nullptr;

    matrixArray = CreateMatrix(size, size);

    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
        {
            QLineEdit *edit = (QLineEdit*) matrixGrid->itemAtPosition(i, j)->widget();
            double digit = 0.0;
            if(!edit->text().isEmpty())
                digit = edit->text().toDouble();
            matrixArray[i][j] = digit;
        }

    return matrixArray;
}

TEqArray EquationsSystemsFrame::getParamsValues()
{
    QGridLayout *matrixGrid = ui->matrixGrid;
    TEqArray parametersArray = nullptr;

    int params_column = size + 1;

    parametersArray = (double *) malloc(size * sizeof(double));

    for(int i = 0; i < size; ++i)
        parametersArray[i] = ((QLineEdit*) matrixGrid->itemAtPosition(i, params_column)->widget())->text().toDouble();

    return parametersArray;
}

void EquationsSystemsFrame::showAnswer(QString ans)
{
    ui->answerEdit->clear();
    ui->answerEdit->appendPlainText(ans);
    ui->answerEdit->moveCursor(QTextCursor::Start);
}

void EquationsSystemsFrame::on_matrixSizeSpin_valueChanged(int arg1)
{
    createMatrixUI(arg1);
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

    QString result_string;

    for(int i = 0; i < n; i++)
    {
        result_string = result_string + "x" + QString::number(i + 1).append(" = ").leftJustified(2);
        result_string = result_string + QString::number(value[i]) + "\n";
    }

    showAnswer(result_string);

    free(value);
}

void EquationsSystemsFrame::onError(int code)
{
    end();

    showAnswer("Невозможно найти решения!");
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

    int rows = size;
    int columns = size + 2;

    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < columns; ++j)
            if(j != size)
                list.append(matrixGrid->itemAtPosition(i, j)->widget());

    for(int i = 1; i < list.size(); ++i)
        QWidget::setTabOrder(list.at(i - 1), list.at(i));
}

void EquationsSystemsFrame::on_clearButton_clicked()
{
    QGridLayout * matrixGrid = ui->matrixGrid;

    if(size != 0)
        for(int i = 0; i < size; ++i)
            for(int j = 0; j < size + 2; ++j)
            {
                if(j != size)
                {
                    QLineEdit *edit = (QLineEdit*) matrixGrid->itemAtPosition(i, j)->widget();
                    edit->clear();
                }
            }
}

void EquationsSystemsFrame::setDefaultValues()
{
    const int defaultSize = 3;
    on_matrixSizeSpin_valueChanged(defaultSize);

    const double arr[defaultSize][defaultSize + 1] =
    {
        { 2,  1, -1,   8},
        {-3, -1,  2, -11},
        {-2,  1,  2,  -3}
    };

    QGridLayout *matrixGrid = ui->matrixGrid;

    for(int i = 0; i < defaultSize; ++i)
        for(int j = 0; j < defaultSize; ++j)
            ((QLineEdit*) matrixGrid->itemAtPosition(i, j)->widget())->setText(QString::number(arr[i][j]));

    for(int i = 0; i < defaultSize; ++i)
        ((QLineEdit*) matrixGrid->itemAtPosition(i, defaultSize + 1)->widget())->setText(QString::number(arr[i][defaultSize]));
}
