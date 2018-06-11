#include "MatrixBuilder.h"
#include <QStringListModel>
#include <QHBoxLayout>
#include "MatrixCreator.h"

MatrixBuilder::MatrixBuilder(QWidget *parent)
    : QWidget(parent),
      stackedWidget(new QStackedWidget(this)),
      matrixSelectionBox(new QComboBox(stackedWidget)),
      matrixSelection(new QPushButton("Scegli", stackedWidget))
{
    setWindowTitle("Crea una matrice"); //imposta il titolo della finestra
    setMinimumSize(150,75);             //imposta le dimensioni minime della finestra
    setWindowModality(Qt::ApplicationModal); //impedisce l'input su altre finestre

    pages.append(new QWidget); //pages[0]
    pages.append(new MatrixCreator); //pages[1]

    stackedWidget->addWidget(pages[0]);
    stackedWidget->addWidget(pages[1]);

    buildMatrixSelectionBox();
    stackedWidget->setCurrentWidget(pages[0]);

    //Horizontal layout with two buttons
    QHBoxLayout *hblayout0 = new QHBoxLayout(pages[0]);
    hblayout0->addWidget(matrixSelectionBox);
    hblayout0->addWidget(matrixSelection);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stackedWidget);

    setLayout(layout);

    connect(matrixSelection, SIGNAL(released()), this, SLOT(handleMatrixSelection()));
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

MatrixBuilder::~MatrixBuilder() {}

void MatrixBuilder::handleMatrixSelection() {
    QString choice = matrixSelectionBox->currentText();
    stackedWidget->setCurrentWidget(pages[1]);
    if (choice == "Matrice Quadrata") {
        //pages[1] è SqareMatrixCreator*
    }
}
