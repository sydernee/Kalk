#include "SquareMatrixKalk.h"
#include "../model/datatypes/SquareMatrix.h"
#include "../controller/SquareMatrixController.h"
#include "../exceptions/InvalidLayoutException.h"

#include <QErrorMessage>
#include <QDebug>

SquareMatrixKalk::SquareMatrixKalk(MatrixController* _controller, QWidget *parent)
    : MatrixKalk(_controller, parent),
      minorDialog(nullptr),
      minorX(nullptr),
      minorY(nullptr)
{
    if (!dynamic_cast<SquareMatrixController*>(controller))
        throw InvalidMatrixTypeException("SquareMatrixKalk::SquareMatrixKalk(): invalid controller dynamic type.");

    getDimensionsGroupBox()->layout()->removeWidget(getRowBox());
    getRowBox()->hide();

    try {
        insertSquareOperations();
    }
    catch(KalkException& e) {
        exceptionHandling(e);
    }

}

void SquareMatrixKalk::insertSquareOperations() {
    QHBoxLayout* l1 = new QHBoxLayout;
    QHBoxLayout* l2 = new QHBoxLayout;

    //istanziazione, connessioni e inserimento nel layout pulsanti per le nuove operazioni
    QPushButton* determinant = new QPushButton("determinant()", getOperationsSet());
    QObject::connect(determinant, SIGNAL(clicked()), this, SLOT(handleDeterminant()));
    l1->addWidget(determinant);

    QPushButton* symmetric = new QPushButton("isSymmetric()", getOperationsSet());
    QObject::connect(symmetric, SIGNAL(clicked()), this, SLOT(handleIsSymmetric()));
    l1->addWidget(symmetric);

    QPushButton* supTriangular = new QPushButton("supTriangular()", getOperationsSet());
    QObject::connect(supTriangular, SIGNAL(clicked()), this, SLOT(handleSupTriangular()));
    l1->addWidget(supTriangular);

    QPushButton* infTriangular = new QPushButton("infTriangular()", getOperationsSet());
    QObject::connect(infTriangular, SIGNAL(clicked()), this, SLOT(handleInfTriangular()));
    l1->addWidget(infTriangular);

    QPushButton* minor = new QPushButton("getMinor()", getOperationsSet());
    QObject::connect(minor, SIGNAL(clicked()), this, SLOT(handleGetMinor()));
    l2->addWidget(minor);

    QPushButton* isDiagonal = new QPushButton("isDiagonal()", getOperationsSet());
    QObject::connect(isDiagonal, SIGNAL(clicked()), this, SLOT(handleIsDiagonal()));
    l2->addWidget(isDiagonal);

    QPushButton* identityButton = new QPushButton("identityMatrix()", getOperationsSet());
    QObject::connect(identityButton, SIGNAL(clicked()), this, SLOT(handleIdentityMatrix()));
    l2->addWidget(identityButton);

    QPushButton* zeroButton = new QPushButton("zeroMatrix()", getOperationsSet());
    QObject::connect(zeroButton, SIGNAL(clicked()), this, SLOT(handleZeroMatrix()));
    l2->addWidget(zeroButton);

    QVBoxLayout* ptr = qobject_cast<QVBoxLayout*>(getOperationsSet()->layout());
    if (!ptr)    
        throw InvalidLayoutException("SquareMatrixKalk::insertSquareOperations(): invalid layout.");
    ptr->addLayout(l1);
    ptr->addLayout(l2);
}


//override
void SquareMatrixKalk::handleSelectDimensions() {
    getRowBox()->setValue(getColBox()->value());    //Una matrice quadrata ha colCount == rowCount
    MatrixKalk::handleSelectDimensions();        //si comporta come la funzione della classe base
}

void SquareMatrixKalk::handleSelectSecondMatrixDimensions() {
    getRowBox()->setValue(getColBox()->value());            //Una matrice quadrata ha colCount == rowCount
    MatrixKalk::handleSelectSecondMatrixDimensions();    //si comporta come la funzione della classe base
}

void SquareMatrixKalk::scalarMultiplicationClicked() {
    //istanzia la matrice
    try {
        controller->buildMatrix(getCells(), getRowBox()->value(), getColBox()->value());

        //mostra e nasconde i QWidget
        getDimensionsGroupBox()->hide();
        getOperationsSet()->hide();
        getObtainResult()->show();
        getSelectSecondMatrixLabel()->show();

        //riposiziona il obtainResult in fondo al layout
        layout()->removeWidget(getObtainResult());
        layout()->addWidget(getObtainResult());
        resetCells();   //azzera il contenuto delle celle

        //imposta il tipo di operazione
        setOperationSelected(SCALAR_MULTIPLICATION);
    }
    catch(KalkException& e) {
        exceptionHandling(e);
    }
}

void SquareMatrixKalk::handleDeterminant() {
    try {
        controller->buildMatrix(getCells(), getRowBox()->value(), getColBox()->value());

        QDialog* dialog = new QDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose); //delete on close
        dialog->setMinimumSize(200,50);
        dialog->setWindowTitle("Determinant");
        QLabel* label = new QLabel("Determinante: " + QString::number(static_cast<SquareMatrixController*>(controller)->determinant()), dialog);
        label->setMargin(15);
        dialog->show();
    }
    catch(KalkException& e) {
        exceptionHandling(e);
    }
}

void SquareMatrixKalk::handleGetMinor() {

    try {
        //istanzia la matrice
        controller->buildMatrix(getCells(), getRowBox()->value(), getColBox()->value());

        minorDialog = new QDialog;   //istanzia minorDialog
        minorDialog->setAttribute(Qt::WA_DeleteOnClose); //delete on close
        minorDialog->setWindowTitle("getMinor"); //titolo finestra
        minorDialog->setWindowModality(Qt::ApplicationModal); //impedisce l'interazione con altre finestre

        minorX = new QSpinBox(minorDialog); //istanzia x
        minorY = new QSpinBox(minorDialog); //istanzia y

        //imposta i limiti dei due QSpinBox
        setSpinBoxLimits(minorX, 0, getRowBox()->value()-1);
        setSpinBoxLimits(minorY, 0, getColBox()->value()-1);

        QGridLayout* l = new QGridLayout; //layout operazioni input di minorDialog
        QVBoxLayout* dialogLayout = new QVBoxLayout; //layout di minorDialog

        //aggiunge i campi a l con la relativa label
        l->addWidget(new QLabel("Immetti la riga da elminare", minorDialog), 0, 0);
        l->addWidget(minorX, 0, 1);
        l->addWidget(new QLabel("Immetti la colonna da elminare", minorDialog), 1, 0);
        l->addWidget(minorY, 1, 1);

        //pulsante per ottenere il risultato
        QPushButton* button = new QPushButton("Ok", minorDialog);

        dialogLayout->addLayout(l);         //aggiunge l a dialogLayout
        dialogLayout->addWidget(button);    //aggiunge button a dialogLayout

        minorDialog->setLayout(dialogLayout);    //imposta il layout di minorDialog
        minorDialog->show();                     //mostra minorDialog

        //imposta il tipo di operazione e connette button
        setOperationSelected(GET_MINOR);
        connect(button, SIGNAL(clicked()), this, SLOT(handleSquareMatrixObtainResult()));
    }
    catch(KalkException& e) {
        exceptionHandling(e);
    }
}

void SquareMatrixKalk::handleIsSymmetric() {
    try {
        controller->buildMatrix(getCells(), getRowBox()->value(), getColBox()->value());

        QDialog* dialog = new QDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose); //delete on close
        dialog->setMinimumSize(200,50);
        dialog->setWindowTitle("Simmetria");
        QLabel* label = new QLabel(dialog);

        if (static_cast<SquareMatrixController*>(controller)->isSymmetric())
            label->setText("La matrice è simmetrica.");
        else
            label->setText("La matrice non è simmetrica.");
        label->setMargin(15);
        dialog->show();
    }
    catch(KalkException& e) {
        exceptionHandling(e);
    }
}

void SquareMatrixKalk::handleSupTriangular() {
    try {
        //istanzia la matrice
        controller->buildMatrix(getCells(), getRowBox()->value(), getColBox()->value());

        QDialog* dialog = new QDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose); //delete on close
        dialog->setMinimumSize(250,50);
        dialog->setWindowTitle("supTriangular");
        QLabel* label = new QLabel(dialog);

        //se è triangolare superiore
        if (static_cast<SquareMatrixController*>(controller)->isSupTriangular())
            label->setText("La matrice è triangolare superiore.");
        //altrimenti
        else
            label->setText("La matrice non è triangolare superiore.");

        label->setMargin(15);
        dialog->show();
    }
    catch(KalkException& e) {
        exceptionHandling(e);
    }
}

void SquareMatrixKalk::handleInfTriangular() {
    try {
        //istanzia la matrice
        controller->buildMatrix(getCells(), getRowBox()->value(), getColBox()->value());

        QDialog* dialog = new QDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose); //delete on close
        dialog->setMinimumSize(250,50);
        dialog->setWindowTitle("infTriangular");
        QLabel* label = new QLabel(dialog);

        //se è triangolare inferiore
        if (static_cast<SquareMatrixController*>(controller)->isInfTriangular())
            label->setText("La matrice è triangolare inferiore.");
        //altrimenti
        else
            label->setText("La matrice non è triangolare inferiore.");

        label->setMargin(15);
        dialog->show();
    }
    catch(KalkException& e) {
        exceptionHandling(e);
    }
}

void SquareMatrixKalk::handleIsDiagonal() {
    try {
        //istanzia la matrice
        controller->buildMatrix(getCells(), getRowBox()->value(), getColBox()->value());

        QDialog* dialog = new QDialog;
        dialog->setAttribute(Qt::WA_DeleteOnClose); //delete on close
        dialog->setMinimumSize(250,50);
        dialog->setWindowTitle("isDiagonal");
        QLabel* label = new QLabel(dialog);

        //se è triangolare diagonale
        if (static_cast<SquareMatrixController*>(controller)->isDiagonal())
            label->setText("La matrice è diagonale.");
        //altrimenti
        else
            label->setText("La matrice non è diagonale.");

        label->setMargin(15);
        dialog->show();
    }
    catch(KalkException& e) {
        exceptionHandling(e);
    }
}

void SquareMatrixKalk::handleIdentityMatrix() {
    controller->displayMatrix(SquareMatrix::identityMatrix(getColBox()->value()), "Risultato identityMatrix");
}

void SquareMatrixKalk::handleZeroMatrix() {
    controller->displayMatrix(SquareMatrix::zeroMatrix(getColBox()->value()), "Risultato zeroMatrix");
}

void SquareMatrixKalk::handleSquareMatrixObtainResult()
{
    try {
        if (getOperationSelected() == GET_MINOR) {
            MatrixController::displayMatrix(static_cast<SquareMatrixController*>(controller)->getMinor(minorX->value(), minorY->value()), "Risultato getMinor");
            minorDialog->close();
            getOperationsSet()->hide();
        }

        //reset dell'interfaccia
        resetDimensionsGroupBox();
        getObtainResult()->hide();
        getSelectSecondMatrixLabel()->hide();
    }
    catch(KalkException& e) {
        exceptionHandling(e);
    }
}

