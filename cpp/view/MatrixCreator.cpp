#include "MatrixCreator.h"
#include "../controller/MatrixController.h"
#include "../view/KeypadInput.h"
#include "../model/datatypes/Matrix.h"
//#include "NonScalarMulDialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDialog>
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
      selectSecondMatrixLabel(nullptr),
      rowBox(nullptr),
      colBox(nullptr),
      selectDimensions(nullptr),
      selectSecondMatrixDimensions(nullptr),
      obtainResult(nullptr),

      nonScalarMulDialog(nullptr),
      nonScalarMulInput(nullptr),

      controller(new MatrixController(this))
{
    setMinimumSize(200,150); //dimenisoni minime finestra

    //istanzia layout principale
    QVBoxLayout* mainLayout = new QVBoxLayout;

    setLayout(mainLayout);      //imposta il layout principale

    buildDimensionsGroupBox();  //costruisce dimensionsGroupBox

    mainLayout->addWidget(dimensionsGroupBox); //aggiunge al layout dimensionsGroupBox

    buildOperationsSet();       //costruisce il layout per operationsSet

}

MatrixCreator::~MatrixCreator() {
    delete controller;
}

//costruisce il set dei pulsanti per la selezione delle dimensioni
void MatrixCreator::buildDimensionsGroupBox() {
    dimensionsGroupBox = new QGroupBox(this);
    selectDimensions = new QPushButton("Seleziona", dimensionsGroupBox);
    selectSecondMatrixDimensions = new QPushButton("Seleziona", matrixBuilder);
    selectDimensionsLabel = new QLabel("Seleziona le dimensioni", dimensionsGroupBox);
    setRowBox();
    setColBox();

    //layout per dimensionsGroupBox
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(selectDimensionsLabel);
    layout->addWidget(rowBox);
    layout->addWidget(colBox);
    layout->addWidget(selectDimensions);
    layout->addWidget(selectSecondMatrixDimensions);
    dimensionsGroupBox->setLayout(layout);

    //serve solo per alcune operazioni
    selectSecondMatrixDimensions->hide();

    connect(selectDimensions, SIGNAL(clicked()), this, SLOT(handleSelectDimensions()));
    connect(selectSecondMatrixDimensions, SIGNAL(clicked()), this, SLOT(handleSelectSecondMatrixDimensions()));
}

//
void MatrixCreator::buildOperationsSet() {
    if (operationsSet != nullptr)
        delete operationsSet;

    operationsSet = new QGroupBox(this); //istanziazione operationsSet
//    QVBoxLayout* vLayout = new QVBoxLayout;
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
    obtainResult = new QPushButton("=", this);
    connect(obtainResult, SIGNAL(clicked()), this, SLOT(handleObtainResult()));
    obtainResult->hide();

    operationsSet->setLayout(gridOperationsLayout); //imposta il layout di operationsSet

    //impostazione del layout di operationsSet
//    vLayout->addWidget(operationsSet);
//    vLayout->addWidget(obtainResult);
    layout()->addWidget(operationsSet);
    layout()->addWidget(obtainResult);
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

void MatrixCreator::setOperationSelected(MatrixCreator::Operation op) {
    operationSelected = op;
}

MatrixCreator::Operation MatrixCreator::getOperationSelected() const {
    return operationSelected;
}

void MatrixCreator::clearCells() {
    foreach (KeypadInput* input, cells) {   //ogni elemento di cells
        delete input;                       //libera la memoria allocata della cella
    }
    cells.clear();                          //svuota cells
}

void MatrixCreator::resetCells() {
    foreach (KeypadInput* input, cells) {   //ogni elemento di cells
        input->clear();                     //input->setText("")
    }
}

void MatrixCreator::resetDimensionsGroupBox() {
    clearCells();
    selectDimensionsLabel->setText("Seleziona le dimensioni");
    rowBox->setEnabled(true);   //riattiva gli QSpinBox per le dimensioni
    colBox->setEnabled(true);
    dimensionsGroupBox->show(); //mostra dimensionsGroupBox
    selectDimensions->show();   //mostra selectDimensions
    selectSecondMatrixDimensions->hide(); //nasconde il pulsante
    matrixBuilder->hide();      //nasconde matrixBuilder
}

void MatrixCreator::initializeMatrixBuilder() {
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
            cells.last()->setPlaceholderText("0");

            gridMatrixLayout->addWidget(cells.last(),i,j);
        }
    }

    vLayout->addLayout(gridMatrixLayout);

    //imposta il layout di matrixBuilder
    matrixBuilder->setLayout(vLayout);

    //aggiunge i QWidget al layout principale
    layout()->addWidget(matrixBuilder);
}

//SLOTS

//selectDimensions button handler
void MatrixCreator::handleSelectDimensions() {
    initializeMatrixBuilder();

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
    selectDimensionsLabel->setText("Dimensioni");
    rowBox->setEnabled(false);
    colBox->setEnabled(false);
    selectDimensions->hide();
}

void MatrixCreator::handleSelectSecondMatrixDimensions() {
    initializeMatrixBuilder();
    obtainResult->show();
    layout()->removeWidget(obtainResult);
    layout()->addWidget(obtainResult);

    //disattiva i pulsanti di dimensionsGroupBox
    selectDimensionsLabel->setText("Dimensioni");
    rowBox->setEnabled(false);
    colBox->setEnabled(false);
    selectSecondMatrixDimensions->hide();
}

//obtainResult button handler
void MatrixCreator::handleObtainResult() {
    //istanzia l'operando di destra
    controller->buildMatrix2(cells, rowBox->value(), colBox->value());

    //WARN: catena di if?
    if (getOperationSelected() == MatrixCreator::SUM) {
        MatrixController::displayMatrix(controller->sum());
    }

    else if (getOperationSelected() == MatrixCreator::SUBTRACTION) {
        MatrixController::displayMatrix(controller->subtract());
    }

    else if (getOperationSelected() == MatrixCreator::SCALAR_MULTIPLICATION) {
        MatrixController::displayMatrix(controller->scalarMultiply());
    }

    else if (getOperationSelected() == MatrixCreator::NON_SCALAR_MULTIPLICATION) {
        MatrixController::displayMatrix(controller->nonScalarMultiply(nonScalarMulInput->text().toDouble()));
        nonScalarMulDialog->close();
        operationsSet->hide();
    }

    resetDimensionsGroupBox();
    obtainResult->hide();
    selectSecondMatrixLabel->hide();
}


//sum button handler
void MatrixCreator::sumClicked() { //n x m + n x m
    //Istanzia l'operando di sinistra
    controller->buildMatrix1(cells, rowBox->value(), colBox->value());

    dimensionsGroupBox->hide();
    operationsSet->hide();
    obtainResult->show();
    selectSecondMatrixLabel->show();

    //riposiziona in fondo l'operando
    layout()->removeWidget(obtainResult);
    layout()->addWidget(obtainResult);

    setOperationSelected(SUM);
}

void MatrixCreator::subtractionClicked() { //n x m + n x m
    //Istanzia l'operando di sinistra
    //WARN: codice ripetuto
    controller->buildMatrix1(cells, rowBox->value(), colBox->value());

    dimensionsGroupBox->hide();
    operationsSet->hide();
    obtainResult->show();
    selectSecondMatrixLabel->show();

    layout()->removeWidget(obtainResult);
    layout()->addWidget(obtainResult);

    setOperationSelected(SUBTRACTION);
}

void MatrixCreator::scalarMultiplicationClicked() {

    //possibile prodotto solo tra n x m + m x l

    controller->buildMatrix1(cells, rowBox->value(), colBox->value()); //costruisce l'operando di sx

    operationsSet->hide();
    obtainResult->hide();
    rowBox->setValue(colBox->value()); //il prodotto scalare si può fare tra i x j, j x k
    colBox->setValue(2);

    resetDimensionsGroupBox(); //reset di dimensionsGroupBox
    rowBox->setEnabled(false); //row dev'essere uguale al col della prima matrice
    selectDimensions->hide();
    selectSecondMatrixDimensions->show();

    setOperationSelected(SCALAR_MULTIPLICATION);
}

void MatrixCreator::nonScalarMultiplicationClicked() {
    //Istanzia l'operando di sinistra
    controller->buildMatrix1(cells, rowBox->value(), colBox->value());

    nonScalarMulDialog = new QDialog;
    nonScalarMulDialog->setWindowTitle("Selezione scalare");    //titolo finestra
    nonScalarMulDialog->setWindowModality(Qt::ApplicationModal);//non permette l'input su altre finestre

    QVBoxLayout* dialogLayout = new QVBoxLayout;                //layout per nonScalarMulDialog
    dialogLayout->addWidget(new QLabel("Immetti il valore da moltiplicare", nonScalarMulDialog));

    QHBoxLayout* l = new QHBoxLayout;                           //layout che contiene input e pulsante
    nonScalarMulInput = new KeypadInput(nonScalarMulDialog);
    l->addWidget(nonScalarMulInput);
    QPushButton* button = new QPushButton("Ok", nonScalarMulDialog);
    l->addWidget(button);

    dialogLayout->addLayout(l);
    nonScalarMulDialog->setLayout(dialogLayout);

    nonScalarMulDialog->show();

    setOperationSelected(NON_SCALAR_MULTIPLICATION);
    connect(button, SIGNAL(clicked()), this, SLOT(handleObtainResult()));

}

void MatrixCreator::transposedClicked() {}

void MatrixCreator::swapRowsClicked() {}

void MatrixCreator::swapColsClicked() {}

void MatrixCreator::substituteRowClicked() {}

