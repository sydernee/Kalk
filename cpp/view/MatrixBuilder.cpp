#include "MatrixBuilder.h"
#include <QStringListModel>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QErrorMessage>
#include "../controller/SquareMatrixController.h"
#include "../controller/SparseMatrixController.h"
#include "SquareMatrixKalk.h"
#include "SparseMatrixKalk.h"

MatrixBuilder::MatrixBuilder(QWidget *parent)
    : QWidget(parent),
      stackedWidget(new QStackedWidget(this)),
      matrixSelectionBox(new QComboBox(stackedWidget)),
      matrixSelection(new QPushButton("Scegli", stackedWidget)),
      backButton(new QPushButton("Torna indietro", this)),
      controller(nullptr)
{
    setWindowTitle("Scegli il tipo di matrice"); //imposta il titolo della finestra

    pages.append(new QWidget(this));        //pages[0]
    pages.append(nullptr);  //pages[1], per MatrixKalk
    pages.append(nullptr);  //pages[2], per switchare tra MatrixKalk e SquareMatrixKalk

    stackedWidget->addWidget(pages[0]);

    buildMatrixSelectionBox();
    stackedWidget->setCurrentWidget(pages[0]);

    //Horizontal layout with two buttons
    QHBoxLayout *hblayout0 = new QHBoxLayout(pages[0]);
    hblayout0->addWidget(matrixSelectionBox);
    hblayout0->addWidget(matrixSelection);

    QHBoxLayout *backButtonGroup = new QHBoxLayout;
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    backButtonGroup->addItem(spacer);
    backButtonGroup->addWidget(backButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(backButtonGroup);
    layout->addWidget(stackedWidget);

    setLayout(layout);

    connect(backButton, SIGNAL(clicked()), this, SLOT(handleBackButton()));
    connect(matrixSelection, SIGNAL(clicked()), this, SLOT(handleMatrixSelection()));

}

void MatrixBuilder::buildMatrixSelectionBox() {
    //istanzia il modello per matrixSelectionBox
    matrixListModel = new QStringListModel(pages[0]);

    //lista di stringhe per matrixSelectionBox
    QStringList list;
    list << "Matrice" << "Matrice Quadrata" << "Matrice Sparsa";
    matrixListModel->setStringList(list);
    matrixSelectionBox->setModel(matrixListModel);
}

MatrixBuilder::~MatrixBuilder() {
    if (controller != nullptr)
        delete controller;
}

//SLOTS

void MatrixBuilder::handleBackButton() {
    if (stackedWidget->currentWidget() == pages[0]) {
        emit matrixBuilderCloseSignal();
        close();
    }
    else if (stackedWidget->currentWidget() == pages[1]) { //pages[1]
        //resetta il QWidget pages[1]
        delete pages[1];
        pages[1] = nullptr;
        stackedWidget->setCurrentWidget(pages[0]); //imposta pages[0] come attivo
        setWindowTitle("Scegli il tipo di matrice");

        //ridimensionamento finestra
        setMinimumSize(wWindowSize,hWindowSize);
        resize(wWindowSize,hWindowSize);
    }
    else { //pages[2]
        delete pages[1];
        delete pages[2];
        pages[1] = nullptr;
        pages[2] = nullptr;
        stackedWidget->setCurrentWidget(pages[0]);

        //ridimensionamento finestra
        setMinimumSize(wWindowSize,hWindowSize);
        resize(wWindowSize,hWindowSize);
    }
}

void MatrixBuilder::handleMatrixSelection() {
    QString choice = matrixSelectionBox->currentText();
    try {
        if (choice == "Matrice") {
            if (controller != nullptr)
                delete controller;
            controller = new MatrixController;
            pages[1] = new MatrixKalk(controller, this);
            setMinimumSize(wCreatorWindowSize,hCreatorWindowSize);
            QObject::connect(pages[1], SIGNAL(squareMatrixSignal()), this, SLOT(connectMatrixKalk()));
        }
        else if (choice == "Matrice Quadrata") {
            //pages[1] sarà SquareMatrixKalk*
            if (controller != nullptr)
                delete controller;
            controller = new SquareMatrixController;
            pages[1] = new SquareMatrixKalk(controller, this);
            setMinimumSize(wCreatorWindowSize,hCreatorWindowSize+100);
        }

        else if (choice == "Matrice Sparsa") {
            //pages[1] sarà SparseMatrixKalk*
            if (controller != nullptr)
                delete controller;
            controller = new SparseMatrixController;
            pages[1] = new SparseMatrixKalk(controller, this);
            setMinimumSize(wCreatorWindowSize, hCreatorWindowSize+100);
        }

        //sezione pages[2]
        if (pages[2] == nullptr) {
            controller = new SquareMatrixController;
            pages[2] = new SquareMatrixKalk(controller, this);
            setMinimumSize(wCreatorWindowSize, hCreatorWindowSize+100);
            stackedWidget->addWidget(pages[2]);
        }

        stackedWidget->removeWidget(pages[2]);
        stackedWidget->addWidget(pages[1]);
        stackedWidget->addWidget(pages[2]);
        stackedWidget->setCurrentWidget(pages[1]);
        setWindowTitle("MatrixKalk");

        //aggiusta il focus
        if (choice == "Matrice Quadrata")
            qobject_cast<MatrixKalk*>(stackedWidget->currentWidget())->getColBox()->setFocus();
        else
            qobject_cast<MatrixKalk*>(stackedWidget->currentWidget())->getRowBox()->setFocus();

    }
    catch(KalkException& e) {
        exceptionHandling(e);
    }

}

void MatrixBuilder::connectMatrixKalk()
{
    QObject::disconnect(pages[1], SIGNAL(squareMatrixSignal()), this, SLOT(connectMatrixKalk())); //sconnette pages[1] al segnale

    unsigned int dim = qobject_cast<MatrixKalk*>(pages[1])->getColBox()->value(); //ricorda la dimensione scelta

    SquareMatrixKalk* ptr = qobject_cast<SquareMatrixKalk*>(pages[2]);  //pages[2]
    ptr->getColBox()->setValue(dim); //imposta il valore scelto
    setMinimumSize(wCreatorWindowSize, hCreatorWindowSize+100);

    stackedWidget->setCurrentWidget(pages[2]);  //imposta come attivo pages[2]
    ptr->handleSelectDimensions();
}
