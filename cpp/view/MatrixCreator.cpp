#include "MatrixCreator.h"




//constructor
MatrixCreator::MatrixCreator(MatrixController* _controller, QWidget *parent)
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

      swapDialog(nullptr),
      swapFieldA(nullptr),
      swapFieldB(nullptr),

      substituteRowDialog(nullptr),
      subRowA(nullptr),
      subRowB(nullptr),
      subRowDouble(nullptr),

      controller(_controller)
{
    setMinimumSize(200,150); //dimenisoni minime finestra

    //istanzia layout principale
    QVBoxLayout* mainLayout = new QVBoxLayout;

    setLayout(mainLayout);      //imposta il layout principale

    buildDimensionsGroupBox();  //costruisce dimensionsGroupBox

    mainLayout->addWidget(dimensionsGroupBox); //aggiunge al layout dimensionsGroupBox

    buildOperationsSet();       //costruisce il layout per operationsSet

}

MatrixCreator::~MatrixCreator() {}

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
    QVBoxLayout* operationsLayout = new QVBoxLayout;

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

    operationsLayout->addLayout(gridOperationsLayout);
    operationsSet->setLayout(operationsLayout); //imposta il layout di operationsSet

    //impostazione del layout di operationsSet
//    vLayout->addWidget(operationsSet);
//    vLayout->addWidget(obtainResult);
    layout()->addWidget(operationsSet);
    layout()->addWidget(obtainResult);
    operationsSet->hide(); //nasconde operationsSet
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

//versione statica di setQSpinBox
void MatrixCreator::setSpinBoxLimits(QSpinBox* box, unsigned int min, unsigned int max, unsigned int _default) {
    box->setMinimum(min);       //imposta il valore minimo
    box->setMaximum(max);       //imposta il valore massimo
    box->setSingleStep(1);      //imposta lo step
    box->setValue(_default);    //imposta il valore di default
}

//SETTERS

void MatrixCreator::setDimensionsGroupBox(QGroupBox* groupBox) {
    if (dimensionsGroupBox != nullptr)
        delete dimensionsGroupBox;
    dimensionsGroupBox = groupBox;
}

void MatrixCreator::setSelectDimensions(QPushButton* button) {
    if (selectDimensions != nullptr)
        delete selectDimensions;
    selectDimensions = button;
}

void MatrixCreator::setSelectSecondMatrixDimensions(QPushButton* button) {
    if (selectSecondMatrixDimensions != nullptr)
        delete selectSecondMatrixDimensions;
    selectSecondMatrixDimensions = button;
}

void MatrixCreator::setSelectDimenionsLabel(QLabel* label) {
    if (selectDimensionsLabel != nullptr)
        delete selectDimensionsLabel;
    selectDimensionsLabel = label;
}

void MatrixCreator::setObtainResult(QPushButton* button) {
    if (obtainResult != nullptr)
        delete obtainResult;
    obtainResult = button;
}

void MatrixCreator::setRowBox(QSpinBox* box) {
    if (rowBox != nullptr)
        delete rowBox;
    rowBox = box;
}

void MatrixCreator::setColBox(QSpinBox* box) {
    if (colBox != nullptr)
        delete colBox;
    colBox = box;
}

void MatrixCreator::setMatrixBuilder(QGroupBox* groupBox) {
    if (matrixBuilder != nullptr)
        delete matrixBuilder;
    matrixBuilder = groupBox;
}

void MatrixCreator::setOperationsSet(QGroupBox* groupBox) {
    if (operationsSet!= nullptr)
        delete operationsSet;
    operationsSet = groupBox;
}

void MatrixCreator::setOperationSelected(MatrixCreator::Operation op) {
    operationSelected = op;
}

//GETTERS

QGroupBox* MatrixCreator::getDimensionsGroupBox() const {
    return dimensionsGroupBox;
}


QPushButton* MatrixCreator::getSelectDimensions() const {
    return selectDimensions;
}

QPushButton* MatrixCreator::getSelectSecondMatrixDimensions() const {
    return selectSecondMatrixDimensions;
}

QLabel* MatrixCreator::getSelectDimensionsLabel() const {
    return selectDimensionsLabel;
}

QLabel *MatrixCreator::getSelectSecondMatrixLabel() const {
    return selectSecondMatrixLabel;
}

QPushButton* MatrixCreator::getObtainResult() const {
    return obtainResult;
}

QSpinBox* MatrixCreator::getRowBox() const {
    return rowBox;
}

QSpinBox* MatrixCreator::getColBox() const {
    return colBox;
}

QGroupBox* MatrixCreator::getMatrixBuilder() const {
    return matrixBuilder;
}

QGroupBox* MatrixCreator::getOperationsSet() const {
    return operationsSet;
}

QVector<KeypadInput *> MatrixCreator::getCells() const {
    return cells;
}

MatrixCreator::Operation MatrixCreator::getOperationSelected() const {
    return operationSelected;
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

    //WARN: catena di if?
    if (getOperationSelected() == MatrixCreator::SUM) {
        //istanzia l'operando di destra
        controller->buildMatrix2(cells, rowBox->value(), colBox->value());
        MatrixController::displayMatrix(controller->sum());
    }

    else if (getOperationSelected() == MatrixCreator::SUBTRACTION) {
        //istanzia l'operando di destra
        controller->buildMatrix2(cells, rowBox->value(), colBox->value());
        MatrixController::displayMatrix(controller->subtract());
    }

    else if (getOperationSelected() == MatrixCreator::SCALAR_MULTIPLICATION) {
        //istanzia l'operando di destra
        controller->buildMatrix2(cells, rowBox->value(), colBox->value());
        MatrixController::displayMatrix(controller->scalarMultiply());
    }

    else if (getOperationSelected() == MatrixCreator::NON_SCALAR_MULTIPLICATION) {
        MatrixController::displayMatrix(controller->nonScalarMultiply(nonScalarMulInput->text().toDouble()));
        nonScalarMulDialog->close();
        operationsSet->hide();
    }

    else if (getOperationSelected() == MatrixCreator::SWAP_ROWS) {
        MatrixController::displayMatrix(controller->swapRows(swapFieldA->value(), swapFieldB->value()));
        swapDialog->close();
        operationsSet->hide();
    }

    else if (getOperationSelected() == MatrixCreator::SWAP_COLS) {
        MatrixController::displayMatrix(controller->swapCols(swapFieldA->value(), swapFieldB->value()));
        swapDialog->close();
        operationsSet->hide();
    }

    else if (getOperationSelected() == MatrixCreator::SUBSTITUTE_ROW) {
        MatrixController::displayMatrix(controller->substituteRow(subRowA->value(), subRowB->value(), subRowDouble->text().toDouble()));
        substituteRowDialog->close();
        operationsSet->hide();
    }

    //reset dell'interfaccia
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

    setOperationSelected(MatrixCreator::SUM);
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

    setOperationSelected(MatrixCreator::SUBTRACTION);
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

    setOperationSelected(MatrixCreator::SCALAR_MULTIPLICATION);
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

    nonScalarMulDialog->show(); //mostra nonScalarMulDialog

    setOperationSelected(MatrixCreator::NON_SCALAR_MULTIPLICATION);
    connect(button, SIGNAL(clicked()), this, SLOT(handleObtainResult()));
}

void MatrixCreator::transposedClicked() {
    controller->buildMatrix1(cells, rowBox->value(), colBox->value());  //istanzia matrix1
    MatrixController::displayMatrix(controller->transposed());          //display di matrix1->transposed()

    //reset dell'interfaccia
    resetDimensionsGroupBox();
    obtainResult->hide();
    operationsSet->hide();
    selectSecondMatrixLabel->hide();
}

void MatrixCreator::swapRowsClicked() {
    //istanzia l'operando
    controller->buildMatrix1(cells, rowBox->value(), colBox->value());

    swapDialog = new QDialog; //istanzia swapDialog
    swapDialog->setWindowTitle("swapRows"); //titolo finestra
    swapDialog->setWindowModality(Qt::ApplicationModal); //impedisce l'input su altre finestre

    QVBoxLayout* dialogLayout = new QVBoxLayout;
    dialogLayout->addWidget(new QLabel("Seleziona le righe da scambiare", swapDialog));

    QHBoxLayout* l = new QHBoxLayout;

    //istanzia i QSpinBox per le righe da scambiare e imposta i limiti
    swapFieldA = new QSpinBox(swapDialog);
    swapFieldB = new QSpinBox(swapDialog);
    setSpinBoxLimits(swapFieldA, 0, rowBox->value()-1);
    setSpinBoxLimits(swapFieldB, 0, rowBox->value()-1);

    //aggiunge gli SpinBox al layout l
    l->addWidget(swapFieldA);
    l->addWidget(swapFieldB);

    //istanzia e aggiunge button a l
    QPushButton* button = new QPushButton("Ok", swapDialog);
    l->addWidget(button);

    //imposta il layout di swapDialog
    dialogLayout->addLayout(l);
    swapDialog->setLayout(dialogLayout);
    swapDialog->show(); //mostra swapDialog

    setOperationSelected(MatrixCreator::SWAP_ROWS);
    connect(button, SIGNAL(clicked()), this, SLOT(handleObtainResult()));
}

void MatrixCreator::swapColsClicked() {
    //istanzia l'operando
    controller->buildMatrix1(cells, rowBox->value(), colBox->value());

    swapDialog = new QDialog;   //istanzia swapDialog
    swapDialog->setWindowTitle("swapCols"); //titolo finestra
    swapDialog->setWindowModality(Qt::ApplicationModal); //impedisce l'input su altre finestre

    QVBoxLayout* dialogLayout = new QVBoxLayout;
    dialogLayout->addWidget(new QLabel("Seleziona le colonne da scambiare", swapDialog));

    QHBoxLayout* l = new QHBoxLayout;

    //istanzia i QSpinBox per le colonne da scambiare e imposta i limiti
    swapFieldA = new QSpinBox(swapDialog);
    swapFieldB = new QSpinBox(swapDialog);
    setSpinBoxLimits(swapFieldA, 0, colBox->value()-1);
    setSpinBoxLimits(swapFieldB, 0, colBox->value()-1);

    //aggiunge gli SpinBox al layout l
    l->addWidget(swapFieldA);
    l->addWidget(swapFieldB);

    //istanzia e aggiunge button a l
    QPushButton* button = new QPushButton("Ok", swapDialog);
    l->addWidget(button);

    //imposta il layout di swapDialog
    dialogLayout->addLayout(l);
    swapDialog->setLayout(dialogLayout);
    swapDialog->show(); //mostra swapDialog

    //imposta il tipo di operazione e connette button
    setOperationSelected(MatrixCreator::SWAP_COLS);
    connect(button, SIGNAL(clicked()), this, SLOT(handleObtainResult()));
}

void MatrixCreator::substituteRowClicked() {
    //istanzia l'operando
    controller->buildMatrix1(cells, rowBox->value(), colBox->value());

    substituteRowDialog = new QDialog;  //istanzia substituteRowDialog
    substituteRowDialog->setWindowTitle("substituteRow"); //titolo finestra
    substituteRowDialog->setWindowModality(Qt::ApplicationModal); //impedisce l'input su altre finestre

    QVBoxLayout* dialogLayout = new QVBoxLayout;
    QGridLayout* l = new QGridLayout;

    //istanzia i field per le operazioni di input
    subRowA = new QSpinBox(substituteRowDialog);
    subRowB = new QSpinBox(substituteRowDialog);
    subRowDouble = new KeypadInput(substituteRowDialog);
    subRowDouble->setPlaceholderText("0");

    //imposta i limiti dei due QSpinBox
    setSpinBoxLimits(subRowA, 0, rowBox->value()-1);
    setSpinBoxLimits(subRowB, 0, rowBox->value()-1);

    //aggiunge i campi di input con la relativa label
    l->addWidget(new QLabel("Immetti la riga A iniziale", substituteRowDialog), 0, 0);
    l->addWidget(subRowA, 0, 1);
    l->addWidget(new QLabel("Immetti la riga B da sommare alla riga A", substituteRowDialog), 1, 0);
    l->addWidget(subRowB, 1, 1);
    l->addWidget(new QLabel("Valore da moltiplicare alla riga B", substituteRowDialog), 2, 0);
    l->addWidget(subRowDouble, 2, 1);

    dialogLayout->addLayout(l); //aggiunge l a dialogLayout

    //istanzia e aggiunge button a l
    QPushButton* button = new QPushButton("Ok", substituteRowDialog);
    dialogLayout->addWidget(button);

    //imposta il layout e mostra substituteRowDialog
    substituteRowDialog->setLayout(dialogLayout);
    substituteRowDialog->show();

    //imposta il tipo di operazione e connette button
    setOperationSelected(MatrixCreator::SUBSTITUTE_ROW);
    connect(button, SIGNAL(clicked()), this, SLOT(handleObtainResult()));
}
