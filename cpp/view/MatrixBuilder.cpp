#include "MatrixBuilder.h"
#include <QStringListModel>
#include <QHBoxLayout>
#include <QSpacerItem>
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
    //setMinimumSize(150,75);             //imposta le dimensioni minime della finestra
//    setWindowModality(Qt::ApplicationModal); //impedisce l'input su altre finestre

    pages.append(new QWidget(this));        //pages[0]
    pages.append(nullptr);  //pages[1], per MatrixCreator

    stackedWidget->addWidget(pages[0]);
//    stackedWidget->addWidget(pages[1]);

    buildMatrixSelectionBox();
    stackedWidget->setCurrentWidget(pages[0]);

    //Horizontal layout with two buttons
    QHBoxLayout *hblayout0 = new QHBoxLayout(pages[0]);
    hblayout0->addWidget(matrixSelectionBox);
    hblayout0->addWidget(matrixSelection);

    QHBoxLayout *backButtonGroup = new QHBoxLayout;
    //memory leak?
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
        close();
    }
    else { //pages[1]
        //resetta il QWidget pages[1]
        delete pages[1];
        pages[1] = nullptr;
//        stackedWidget->addWidget(pages[1]);
        stackedWidget->setCurrentWidget(pages[0]); //imposta pages[0] come attivo

        //ridimensionamento finestra
        setMinimumSize(wWindowSize,hWindowSize);
        resize(wWindowSize,hWindowSize);
    }
}

void MatrixBuilder::handleMatrixSelection() {
    QString choice = matrixSelectionBox->currentText();
    if (choice == "Matrice") {
        if (controller != nullptr)
            delete controller;
        controller = new MatrixController;
        pages[1] = new MatrixCreator(controller, this);
        setMinimumSize(wCreatorWindowSize,hCreatorWindowSize);
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

    stackedWidget->addWidget(pages[1]);
    stackedWidget->setCurrentWidget(pages[1]);
    setWindowTitle("MatrixKalk");
}
