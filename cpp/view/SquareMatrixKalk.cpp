#include "SquareMatrixKalk.h"
#include "../model/datatypes/SquareMatrix.h"

SquareMatrixKalk::SquareMatrixKalk(MatrixController* _controller, QWidget *parent)
    : MatrixCreator(_controller, parent),
      getMinorDialog(nullptr),
      getMinorX(nullptr),
      getMinorY(nullptr)
{
    getDimensionsGroupBox()->layout()->removeWidget(getRowBox());
    getRowBox()->hide();

    insertSquareOperations();
}

SquareMatrixKalk::~SquareMatrixKalk() {}

void SquareMatrixKalk::insertSquareOperations() {
    QGridLayout* gridLayout = new QGridLayout;

    //istanziazione, connessioni e inserimento nel layout pulsanti per le nuove operazioni
    QPushButton* determinant = new QPushButton("determinant()", getOperationsSet());
    connect(determinant, SIGNAL(clicked()), this, SLOT(handleDeterminant()));
    gridLayout->addWidget(determinant,0,0);

    QPushButton* minor = new QPushButton("getMinor()", getOperationsSet());
    connect(minor, SIGNAL(clicked()), this, SLOT(handleGetMinor()));
    gridLayout->addWidget(minor, 0, 1);

    if (!qobject_cast<QVBoxLayout*>(getOperationsSet()->layout()))
        {}//TODO throw
    static_cast<QVBoxLayout*>(getOperationsSet()->layout())->addLayout(gridLayout);
}

//override
void SquareMatrixKalk::handleSelectDimensions() {
    getRowBox()->setValue(getColBox()->value());    //Una matrice quadrata ha colCount == rowCount
    MatrixCreator::handleSelectDimensions();        //si comporta come la funzione della classe base
}

void SquareMatrixKalk::handleSelectSecondMatrixDimensions() {
    getRowBox()->setValue(getColBox()->value());            //Una matrice quadrata ha colCount == rowCount
    MatrixCreator::handleSelectSecondMatrixDimensions();    //si comporta come la funzione della classe base

}

void SquareMatrixKalk::scalarMultiplicationClicked() {
    //istanzia la matrice
    controller->buildMatrix1(getCells(), getRowBox()->value(), getColBox()->value());

    //mostra e nasconde i QWidget
    getDimensionsGroupBox()->hide();
    getOperationsSet()->hide();
    getObtainResult()->show();
    getSelectSecondMatrixLabel()->show();

    //riposiziona il obtainResult in fondo al layout
    layout()->removeWidget(getObtainResult());
    layout()->addWidget(getObtainResult());

    //imposta il tipo di operazione
    setOperationSelected(MatrixCreator::SCALAR_MULTIPLICATION);
}

void SquareMatrixKalk::handleDeterminant() {
    controller->buildMatrix1(getCells(), getRowBox()->value(), getColBox()->value());

    QDialog* dialog = new QDialog;
    dialog->setMinimumSize(200,50);
    dialog->setWindowTitle("Determinante");
    QLabel* label = new QLabel("Determinante: " + QString::number(controller->determinant()), dialog);
    label->setMargin(15);
    dialog->show();
}

void SquareMatrixKalk::handleGetMinor() {
    //istanzia la matrice
    controller->buildMatrix1(getCells(), getRowBox()->value(), getColBox()->value());

    getMinorDialog = new QDialog;   //istanzia getMinorDialog
    getMinorDialog->setWindowTitle("getMinor"); //titolo finestra
    getMinorDialog->setWindowModality(Qt::ApplicationModal); //impedisce l'interazione con altre finestre

    getMinorX = new QSpinBox(getMinorDialog); //istanzia x
    getMinorY = new QSpinBox(getMinorDialog); //istanzia y

    //imposta i limiti dei due QSpinBox
    setSpinBoxLimits(getMinorX, 0, getRowBox()->value()-1);
    setSpinBoxLimits(getMinorY, 0, getColBox()->value()-1);

    QGridLayout* l = new QGridLayout; //layout operazioni input di getMinorDialog
    QVBoxLayout* dialogLayout = new QVBoxLayout; //layout di getMinorDialog

    //aggiunge i campi a l con la relativa label
    l->addWidget(new QLabel("Immetti la riga da elminare", getMinorDialog), 0, 0);
    l->addWidget(getMinorX, 0, 1);
    l->addWidget(new QLabel("Immetti la colonna da elminare", getMinorDialog), 1, 0);
    l->addWidget(getMinorY, 1, 1);

    //pulsante per ottenere il risultato
    QPushButton* button = new QPushButton("Ok", getMinorDialog);


    dialogLayout->addLayout(l);         //aggiunge l a dialogLayout
    dialogLayout->addWidget(button);    //aggiunge button a dialogLayout

    getMinorDialog->setLayout(dialogLayout);    //imposta il layout di getMinorDialog
    getMinorDialog->show();                     //mostra getMinorDialog

    //imposta il tipo di operazione e connette button
    setOperationSelected(MatrixCreator::GET_MINOR);
    connect(button, SIGNAL(clicked()), this, SLOT(handleSquareMatrixObtainResult()));
}

void SquareMatrixKalk::handleSquareMatrixObtainResult()
{
    if (getOperationSelected() == MatrixCreator::GET_MINOR) {
        MatrixController::displayMatrix(controller->getMinor(getMinorX->value(), getMinorY->value()));
        getMinorDialog->close();
        getOperationsSet()->close();
    }

    //reset dell'interfaccia
    resetDimensionsGroupBox();
    getObtainResult()->hide();
    getSelectSecondMatrixLabel()->hide();
}

