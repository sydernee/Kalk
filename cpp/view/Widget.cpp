#include "Widget.h"
#include "MatrixBuilder.h"
#include "Keypad.h"
#include <QRect>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
//      keypad(new Keypad(this)),
      createMatrixKalk(new QPushButton("MatrixKalk", this))
{
    setWindowTitle("Kalk"); //imposta il titolo della finestra
    setMinimumSize(150,75); //imposta le dimensioni minime della finestra

    connect(createMatrixKalk, SIGNAL(clicked()), this, SLOT(handleCreateMatrixKalkButton()));

    QHBoxLayout* hblayout = new QHBoxLayout;
    hblayout->addWidget(createMatrixKalk);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(hblayout);
//    mainLayout->addWidget(keypad);

    setLayout(mainLayout);
}

Widget::~Widget() {}

void Widget::handleNumButtons() {}

void Widget::handleDotButton() {}

void Widget::handleAssignmentButton() {}

void Widget::handleCreateMatrixKalkButton() {
    QWidget* matrixBuilder = new MatrixBuilder;
    matrixBuilder->setAttribute(Qt::WA_DeleteOnClose); //delete on close
    matrixBuilder->setMinimumSize(300,200);
    matrixBuilder->show();
//    setDisabled(true);
    close();
}
