#include "MatrixCreator.h"
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <cfloat>

//constructor
MatrixCreator::MatrixCreator(QWidget *parent)
    : QWidget(parent),
      matrix(nullptr),
      dimensionsGroupBox(nullptr),
      matrixBuilder(nullptr),
      selectDimensionsLabel(nullptr),
      rowBox(nullptr),
      colBox(nullptr),
      selectDimensions(new QPushButton("Seleziona", this))
{
    setMinimumSize(200,100); //dimenisoni minime finestra

    //istanzia layout principale
    QVBoxLayout* mainLayout = new QVBoxLayout;

    buildDimensionsGroupBox(); //costruisce dimensionsGroupBox
    mainLayout->addWidget(dimensionsGroupBox); //aggiunge al layout dimensionsGroupBox
    //mainLayout->addWidget(matrixBuilder);
    setLayout(mainLayout); //imposta il layout principale

    connect(selectDimensions, SIGNAL(released()), this, SLOT(handleSelectDimensions()));
}

void MatrixCreator::buildDimensionsGroupBox() {
    dimensionsGroupBox = new QGroupBox(this);
    selectDimensionsLabel = new QLabel("Seleziona le dimensioni", this);
    setRowBox();
    setColBox();

    //layout per dimensionsGroupBox
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(selectDimensionsLabel);
    layout->addWidget(rowBox);
    layout->addWidget(colBox);
    layout->addWidget(selectDimensions);
    dimensionsGroupBox->setLayout(layout);
}

void MatrixCreator::setRowBox(unsigned int min, unsigned int max, unsigned int _default) {
    if (rowBox != nullptr)
        delete rowBox;
    rowBox = new QSpinBox(this);
    rowBox->setMinimum(min);    //imposta il valore minimo
    rowBox->setMaximum(max);    //imposta il valore massimo
    rowBox->setSingleStep(1);   //imposta lo step
    rowBox->setValue(_default); //imposta il valore di default
}

void MatrixCreator::setRowBox() {
     setRowBox(1,10);
}

void MatrixCreator::setColBox(unsigned int min, unsigned int max, unsigned int _default) {
    if (colBox != nullptr)
        delete colBox;
    colBox = new QSpinBox(this);
    colBox->setMinimum(min);    //imposta il valore minimo
    colBox->setMaximum(max);    //imposta il valore massimo
    colBox->setSingleStep(1);   //imposta lo step
    colBox->setValue(_default); //imposta il valore di default
}

void MatrixCreator::setColBox() {
    setColBox(1,10);
}


//SLOTS

void MatrixCreator::handleSelectDimensions() {
    int rows = rowBox->value();
    int cols = colBox->value();

    if (matrixBuilder != nullptr)
        delete matrixBuilder;
    matrixBuilder = new QGroupBox(this);
    QGridLayout* gridMatrixLayout = new QGridLayout;
    //QVector<QHBoxLayout*> cellsLayout;
    QVector<QLineEdit*> cells;
    QDoubleValidator* cellValidator = new QDoubleValidator(DBL_MIN, DBL_MAX, 3, this);

    if (matrixBuilder->layout() != nullptr)
        delete matrixBuilder->layout();

    for (int i = 0; i < rows; i++) {
        //cellsLayout.append(new QHBoxLayout(this));
        for (int j = 0; j < cols; j++) {
            cells.append(new QLineEdit(this));
            cells.last()->setValidator(cellValidator);
            gridMatrixLayout->addWidget(cells.last(),i,j);
        }
        //gridMatrixLayout->addItem(cellsLayout[i]);
    }
    matrixBuilder->setLayout(gridMatrixLayout);

    layout()->addWidget(matrixBuilder);
    //TODO add matrixBuilder to mainLayout
}
