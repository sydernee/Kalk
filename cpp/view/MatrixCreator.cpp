#include "MatrixCreator.h"
#include "../controller/MatrixController.h"

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
      selectDimensions(new QPushButton("Seleziona", this)),
      controller(new MatrixController(this))
{

    buildMatrixButton = nullptr;

    setMinimumSize(200,150); //dimenisoni minime finestra

    //istanzia layout principale
    QVBoxLayout* mainLayout = new QVBoxLayout;

    buildDimensionsGroupBox(); //costruisce dimensionsGroupBox
    mainLayout->addWidget(dimensionsGroupBox); //aggiunge al layout dimensionsGroupBox
    //mainLayout->addWidget(matrixBuilder);
    setLayout(mainLayout); //imposta il layout principale

    connect(selectDimensions, SIGNAL(released()), this, SLOT(handleSelectDimensions()));
}

MatrixCreator::~MatrixCreator() {
    delete controller;
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

    if (matrixBuilder != nullptr) {
        delete matrixBuilder;
    }
    matrixBuilder = new QGroupBox(this);
    QGridLayout* gridMatrixLayout = new QGridLayout;
    QDoubleValidator* cellValidator = new QDoubleValidator(DBL_MIN, DBL_MAX, 3, this);

    //se non è vuoto, svuota cells
    if (!cells.isEmpty())
        cells.clear();

    //istanzia cells
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cells.append(new QLineEdit(this)); //meglio KeypadInput?
            cells.last()->setValidator(cellValidator);
            gridMatrixLayout->addWidget(cells.last(),i,j);
        }
    }

    //imposta il layout di matrixBuilder
    matrixBuilder->setLayout(gridMatrixLayout);

    //se nullo, istanzia buildMatrixButton e lo connette
    if (buildMatrixButton == nullptr) {
        buildMatrixButton = new QPushButton("Crea", this);
        connect(buildMatrixButton, SIGNAL(pressed()), this, SLOT(handleBuildMatrixButton()));
    }

    //aggiunge i QWidget al layout
    layout()->addWidget(matrixBuilder);
    layout()->addWidget(buildMatrixButton);
}

void MatrixCreator::handleBuildMatrixButton() {
    controller->buildMatrix(rowBox->value(), colBox->value());
    buildMatrixSignal(controller->getMatrix());

    emit buildMatrixSignal(controller->getMatrix());
}
