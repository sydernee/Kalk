#include "MatrixCreator.h"
#include "../controller/MatrixController.h"
#include "../view/KeypadInput.h"

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
      dimensionsGroupBox(nullptr),
      matrixBuilder(nullptr),
      operationsSet(nullptr),

      selectDimensionsLabel(nullptr),
      rowBox(nullptr),
      colBox(nullptr),
      selectDimensions(new QPushButton("Seleziona", this)),
//      buildMatrixButton(nullptr),
      controller(new MatrixController(this))
{
    setMinimumSize(200,150); //dimenisoni minime finestra

    //istanzia layout principale
    QVBoxLayout* mainLayout = new QVBoxLayout;

    buildDimensionsGroupBox();  //costruisce dimensionsGroupBox
    buildOperationsSet();       //costruisce il layout per operationsSet

    mainLayout->addWidget(dimensionsGroupBox); //aggiunge al layout dimensionsGroupBox
    setLayout(mainLayout); //imposta il layout principale

    connect(selectDimensions, SIGNAL(released()), this, SLOT(handleSelectDimensions()));
}

MatrixCreator::~MatrixCreator() {
    delete controller;
}

//costruisce il set dei pulsanti per la selezione delle dimensioni
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

//
void MatrixCreator::buildOperationsSet() {
    if (operationsSet != nullptr)
        delete operationsSet;

    operationsSet = new QGroupBox(this); //istanziazione operationsSet
    QGridLayout* gridOperationsLayout = new QGridLayout; //layout per operationsSet

    //istanziazione, connessioni e inserimento nel layout pulsanti per le operazioni
    QPushButton* sum = new QPushButton("+", this);
    connect(sum, SIGNAL(clicked()), this, SLOT(sumClicked()));
    gridOperationsLayout->addWidget(sum,0,0);

    QPushButton* subtraction = new QPushButton("-", this);
    connect(subtraction, SIGNAL(clicked()), this, SLOT(subtractionClicked()));
    gridOperationsLayout->addWidget(subtraction,0,1);

    QPushButton* scalarMultiplication = new QPushButton("* (scalare)", this);
    connect(scalarMultiplication, SIGNAL(clicked()), this, SLOT(scalarMultiplicationClicked()));
    gridOperationsLayout->addWidget(scalarMultiplication,0,2);

    QPushButton* nonScalarMultiplication = new QPushButton("*", this);
    connect(nonScalarMultiplication, SIGNAL(clicked()), this, SLOT(nonScalarMultiplicationClicked()));
    gridOperationsLayout->addWidget(nonScalarMultiplication,0,3);

    QPushButton* transposed = new QPushButton("trasposta()", this);
    connect(transposed, SIGNAL(clicked()), this, SLOT(transposedClicked()));
    gridOperationsLayout->addWidget(transposed, 1,0);

    QPushButton* swapRows = new QPushButton("swapRows()", this);
    connect(swapRows, SIGNAL(clicked()), this, SLOT(swapRowsClicked()));
    gridOperationsLayout->addWidget(swapRows,1,1);

    QPushButton* swapCols = new QPushButton("swapCols()", this);
    connect(swapCols, SIGNAL(clicked()), this, SLOT(swapColsClicked()));
    gridOperationsLayout->addWidget(swapCols,1,2);

    QPushButton* substituteRow = new QPushButton("substituteRow()", this);
    connect(substituteRow, SIGNAL(clicked()), this, SLOT(substituteRowClicked()));
    gridOperationsLayout->addWidget(substituteRow,1,3);

    operationsSet->setLayout(gridOperationsLayout); //imposta il layout di operationsSet
    operationsSet->hide(); //nasconde operationsSet

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
    if (matrixBuilder != nullptr) {
        delete matrixBuilder;
    }

    matrixBuilder = new QGroupBox(this);
    QGridLayout* gridMatrixLayout = new QGridLayout;

    //se non è vuoto, svuota cells
    if (!cells.isEmpty())
        cells.clear();

    int rows = rowBox->value();
    int cols = colBox->value();

    //istanzia cells
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cells.append(new KeypadInput(matrixBuilder));
            cells.last()->setText("0");
            gridMatrixLayout->addWidget(cells.last(),i,j);
        }
    }

    //imposta il layout di matrixBuilder
    matrixBuilder->setLayout(gridMatrixLayout);

    //aggiunge i QWidget al layout
    layout()->addWidget(matrixBuilder);

    //se l'operation set non è visibile, lo mostra
    //in ogni caso lo rimette in fondo nel layout
    if (!operationsSet->isVisible()) {
        operationsSet->show();
        layout()->removeWidget(operationsSet);
        layout()->addWidget(operationsSet);
    }
    else {
        layout()->removeWidget(operationsSet);
        layout()->addWidget(operationsSet);
    }
}

void MatrixCreator::sumClicked() {
    if (matrixBuilder != nullptr) {
        delete matrixBuilder;
        matrixBuilder = nullptr;
    }
}

void MatrixCreator::subtractionClicked() {}

void MatrixCreator::scalarMultiplicationClicked() {}

void MatrixCreator::nonScalarMultiplicationClicked() {}

void MatrixCreator::transposedClicked() {}

void MatrixCreator::swapRowsClicked() {}

void MatrixCreator::swapColsClicked() {}

void MatrixCreator::substituteRowClicked() {}
