#include "MatrixCreator.h"
#include "../controller/MatrixController.h"
#include "../view/KeypadInput.h"
#include "../model/datatypes/Matrix.h"

#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QDialog>
#include <cfloat>

//constructor
MatrixCreator::MatrixCreator(QWidget *parent)
    : QWidget(parent),
      dimensionsGroupBox(nullptr),
      matrixBuilder(nullptr),
      operationsSet(nullptr),

      selectDimensionsLabel(nullptr),
      selectSecondMatrixLabel(nullptr),
      rowBox(nullptr),
      colBox(nullptr),
      selectDimensions(nullptr),
      obtainResult(nullptr),

      controller(new MatrixController(this))
{
    setMinimumSize(200,150); //dimenisoni minime finestra

    //istanzia layout principale
    QVBoxLayout* mainLayout = new QVBoxLayout;

    buildDimensionsGroupBox();  //costruisce dimensionsGroupBox

    buildOperationsSet();       //costruisce il layout per operationsSet

    mainLayout->addWidget(dimensionsGroupBox); //aggiunge al layout dimensionsGroupBox
    setLayout(mainLayout); //imposta il layout principale
}

MatrixCreator::~MatrixCreator() {
    delete controller;
}

//costruisce il set dei pulsanti per la selezione delle dimensioni
void MatrixCreator::buildDimensionsGroupBox() {
    dimensionsGroupBox = new QGroupBox(this);
    selectDimensions = new QPushButton("Seleziona", dimensionsGroupBox);
    selectDimensionsLabel = new QLabel("Seleziona le dimensioni", dimensionsGroupBox);
    setRowBox();
    setColBox();

    //layout per dimensionsGroupBox
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(selectDimensionsLabel);
    layout->addWidget(rowBox);
    layout->addWidget(colBox);
    layout->addWidget(selectDimensions);
    dimensionsGroupBox->setLayout(layout);

    connect(selectDimensions, SIGNAL(released()), this, SLOT(handleSelectDimensions()));
}

//
void MatrixCreator::buildOperationsSet() {
    if (operationsSet != nullptr)
        delete operationsSet;

    operationsSet = new QGroupBox(this); //istanziazione operationsSet
    QVBoxLayout* vLayout = new QVBoxLayout;
    QGridLayout* gridOperationsLayout = new QGridLayout; //layout per operationsSet

    //istanziazione, connessioni e inserimento nel layout pulsanti per le operazioni
    QPushButton* sum = new QPushButton("+", operationsSet);
    connect(sum, SIGNAL(clicked()), this, SLOT(sumClicked()));
    gridOperationsLayout->addWidget(sum,0,0);

    QPushButton* subtraction = new QPushButton("-", operationsSet);
    connect(subtraction, SIGNAL(clicked()), this, SLOT(subtractionClicked()));
    gridOperationsLayout->addWidget(subtraction,0,1);

    QPushButton* scalarMultiplication = new QPushButton("* (scalare)", operationsSet);
    connect(scalarMultiplication, SIGNAL(clicked()), this, SLOT(scalarMultiplicationClicked()));
    gridOperationsLayout->addWidget(scalarMultiplication,0,2);

    QPushButton* nonScalarMultiplication = new QPushButton("*", operationsSet);
    connect(nonScalarMultiplication, SIGNAL(clicked()), this, SLOT(nonScalarMultiplicationClicked()));
    gridOperationsLayout->addWidget(nonScalarMultiplication,0,3);

    QPushButton* transposed = new QPushButton("trasposta()", operationsSet);
    connect(transposed, SIGNAL(clicked()), this, SLOT(transposedClicked()));
    gridOperationsLayout->addWidget(transposed, 1,0);

    QPushButton* swapRows = new QPushButton("swapRows()", operationsSet);
    connect(swapRows, SIGNAL(clicked()), this, SLOT(swapRowsClicked()));
    gridOperationsLayout->addWidget(swapRows,1,1);

    QPushButton* swapCols = new QPushButton("swapCols()", operationsSet);
    connect(swapCols, SIGNAL(clicked()), this, SLOT(swapColsClicked()));
    gridOperationsLayout->addWidget(swapCols,1,2);

    QPushButton* substituteRow = new QPushButton("substituteRow()", operationsSet);
    connect(substituteRow, SIGNAL(clicked()), this, SLOT(substituteRowClicked()));
    gridOperationsLayout->addWidget(substituteRow,1,3);

    //pulsante per =
    //QSpacerItem?
    obtainResult = new QPushButton("=", operationsSet);
    connect(obtainResult, SIGNAL(clicked()), this, SLOT(handleObtainResult()));
    obtainResult->hide();

    //impostazione del layout di operationsSet
    vLayout->addLayout(gridOperationsLayout);
    vLayout->addWidget(obtainResult);
    operationsSet->setLayout(vLayout); //imposta il layout di operationsSet
    operationsSet->hide(); //nasconde operationsSet
}

void MatrixCreator::setRowBox(unsigned int min, unsigned int max, unsigned int _default) {
    if (rowBox != nullptr)
        delete rowBox;
    rowBox = new QSpinBox(dimensionsGroupBox);
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
    colBox = new QSpinBox(dimensionsGroupBox);
    colBox->setMinimum(min);    //imposta il valore minimo
    colBox->setMaximum(max);    //imposta il valore massimo
    colBox->setSingleStep(1);   //imposta lo step
    colBox->setValue(_default); //imposta il valore di default
}

void MatrixCreator::setColBox() {
    setColBox(1,10);
}

void MatrixCreator::setOperationSelected(Operation op) {
    operationSelected = op;
}

Operation MatrixCreator::getOperationSelected() const {
    return operationSelected;
}

void MatrixCreator::clearCells() {
    foreach (KeypadInput* input, cells) {
        delete input;
    }
    cells.clear();
}

//SLOTS

//selectDimensions button handler
void MatrixCreator::handleSelectDimensions() {
    if (matrixBuilder != nullptr) {
        delete matrixBuilder;
    }

    matrixBuilder = new QGroupBox(this);
    QVBoxLayout* vLayout = new QVBoxLayout;             //layout principale di matrixBuilder
    QGridLayout* gridMatrixLayout = new QGridLayout;    //layout a griglia per la matrice

    selectSecondMatrixLabel = new QLabel("Inizializza le seconda matrice", matrixBuilder);
    vLayout->addWidget(selectSecondMatrixLabel);
    selectSecondMatrixLabel->hide();

    //se non è vuoto, svuota cells
    if (!cells.isEmpty())
        clearCells();

    int rows = rowBox->value();
    int cols = colBox->value();

    //istanzia cells
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cells.append(new KeypadInput(matrixBuilder));

            //text() come placeholder
            //da verificare se viene considerato effettivamente come text() o meno
            cells.last()->setPlaceholderText("0");

            gridMatrixLayout->addWidget(cells.last(),i,j);
        }
    }

    vLayout->addLayout(gridMatrixLayout);

    //imposta il layout di matrixBuilder
    matrixBuilder->setLayout(vLayout);

    //aggiunge i QWidget al layout principale
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

    //disattiva i pulsanti di dimensionsGroupBox
    rowBox->setEnabled(false);
    colBox->setEnabled(false);
    selectDimensions->setEnabled(false);
}

//obtainResult button handler
void MatrixCreator::handleObtainResult() {
    //istanzia l'operando di destra
    controller->buildMatrix2(cells, rowBox->value(), colBox->value());

    //WARN: catena di if?
    if (getOperationSelected() == SUM) {
        MatrixController::displayMatrix(controller->sum());
    }
}

//sum button handler
void MatrixCreator::sumClicked() { //n x m + n x m
    //Istanzia l'operando di sinistra
    controller->buildMatrix1(cells, rowBox->value(), colBox->value());

    //resetta il il testo delle celle di cells

    dimensionsGroupBox->hide();

    auto i = operationsSet->children();
    for (auto it = i.begin(); it < i.end(); it++) {
        if (qobject_cast<QPushButton*>(*it)){
            static_cast<QPushButton*>(*it)->hide();
        }
    }
    obtainResult->show();
    selectSecondMatrixLabel->show();

    setOperationSelected(SUM);
}

void MatrixCreator::subtractionClicked() {}

void MatrixCreator::scalarMultiplicationClicked() {

    //possibile prodotto solo tra n x m + m x l
//    rowBox->setValue(colBox->value());
//    colBox->setEnabled(true); //riattiva colBox per l'input

}

void MatrixCreator::nonScalarMultiplicationClicked() {}

void MatrixCreator::transposedClicked() {}

void MatrixCreator::swapRowsClicked() {}

void MatrixCreator::swapColsClicked() {}

void MatrixCreator::substituteRowClicked() {}
