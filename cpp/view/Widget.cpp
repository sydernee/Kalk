#include "Widget.h"
#include "MatrixBuilder.h"
#include "Keypad.h"
#include <QRect>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      keypad(new Keypad(this)),
      createMatrix(new QPushButton("Crea una matrice", this))
{
    setWindowTitle("Kalk"); //imposta il titolo della finestra
    setMinimumSize(150,75); //imposta le dimensioni minime della finestra

    connect(createMatrix, SIGNAL(clicked()), this, SLOT(handleCreateMatrixButton()));

    QHBoxLayout* hblayout = new QHBoxLayout;
    hblayout->addWidget(createMatrix);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(hblayout);
    mainLayout->addWidget(keypad);

    setLayout(mainLayout);

    /*
     * TODO connettere l'istanza di Widget con un'istanza di MatrixCreator
     * per poter ottenere in input una Matrix creata dall'istanza di MatrixCreator.
     * Idea: nuova classe che "conosce" entrambi?
     */
}

Widget::~Widget() {}

void Widget::handleNumButtons() {}

void Widget::handleDotButton() {}

void Widget::handleAssignmentButton() {}

void Widget::handleCreateMatrixButton() {
    QWidget* matrixBuilder = new MatrixBuilder;
    matrixBuilder->setMinimumSize(100,50);
    matrixBuilder->show();
    //setDisabled(true);
}
