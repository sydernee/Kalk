#include "MatrixBuilder.h"
#include <QStringListModel>
#include <QHBoxLayout>
#include <QSpacerItem>
#include "MatrixCreator.h"

MatrixBuilder::MatrixBuilder(QWidget *parent)
    : QWidget(parent),
      stackedWidget(new QStackedWidget(this)),
      matrixSelectionBox(new QComboBox(stackedWidget)),
      matrixSelection(new QPushButton("Scegli", stackedWidget)),
      backButton(new QPushButton("Torna indietro", this))
{
    setWindowTitle("Scegli il tipo di matrice"); //imposta il titolo della finestra
    //setMinimumSize(150,75);             //imposta le dimensioni minime della finestra
    setWindowModality(Qt::ApplicationModal); //impedisce l'input su altre finestre

    pages.append(new QWidget(this));        //pages[0]
    pages.append(new MatrixCreator(this));  //pages[1]

    stackedWidget->addWidget(pages[0]);
    stackedWidget->addWidget(pages[1]);

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

    connect(backButton, SIGNAL(released()), this, SLOT(handleBackButton()));
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

//SLOTS

void MatrixBuilder::handleBackButton() {
    if (stackedWidget->currentWidget() == pages[0])
        close();
    else { //pages[1]
        //resetta il QWidget pages[1]
        delete pages[1];
        pages[1] = new MatrixCreator(this);
        stackedWidget->addWidget(pages[1]);
        stackedWidget->setCurrentWidget(pages[0]); //imposta pages[0] come attivo
    }
}

void MatrixBuilder::handleMatrixSelection() {
    QString choice = matrixSelectionBox->currentText();
    stackedWidget->setCurrentWidget(pages[1]);
    setMinimumSize(500,300);
    setWindowTitle("MatrixKalk");
    if (choice == "Matrice Quadrata") {
        //pages[1] è SquareMatrixCreator*
    }
}
