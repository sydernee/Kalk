#include "Widget.h"
#include "MatrixBuilder.h"
#include "Keypad.h"
#include <QRect>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      /*keypad(new QGroupBox(this)),
      dotButton(nullptr),
      assignmentButton(nullptr),*/
      keypad(new Keypad),
      createMatrix(new QPushButton("Crea una matrice", this))
{
    setWindowTitle("Kalk"); //imposta il titolo della finestra
    setMinimumSize(150,75); //imposta le dimensioni minime della finestra

    //costruisce il tastierino numerico
    //buildKeypad();

    //createMatrix->setGeometry(0,0,100,30);
    connect(createMatrix, SIGNAL(released()), this, SLOT(handleCreateMatrixButton()));

    QHBoxLayout* hblayout = new QHBoxLayout;
    hblayout->addWidget(createMatrix);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(hblayout);
    mainLayout->addWidget(keypad);

    setLayout(mainLayout);
}

Widget::~Widget() {}

/*
 buildNumButtons costruisce il tastierino numerico
x = spazio orizzontale lasciato bianco
y = spazio verticale lasciato bianco
w = dimensione orizzontale dei bottoni
h = dimensione verticale dei bottoni
*/
/*
void Widget::buildKeypad() {
    //bottone per 0 (posizionato sotto gli altri)
    NumericButtons.push_back(new QPushButton(QString::number(0)));
    NumericButtons[0]->setShortcut(QString::number(0)); //key shortcut: 0
    connect(NumericButtons[0], SIGNAL(released()), this, SLOT(handleNumButtons()));

    QGridLayout* keypadLayout = new QGridLayout; //layout per keypad
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            int cell = i*j+j;
            NumericButtons.push_back(new QPushButton(QString::number(cell)));
            keypadLayout->addWidget(NumericButtons[cell],i,j);

            NumericButtons[cell]->setShortcut(QString::number(cell)); //i button key shortcut: i
            connect(NumericButtons[cell], SIGNAL(released()), this, SLOT(handleNumButtons()));
        }
    keypadLayout->addWidget(NumericButtons[0],3,0);

    //punto
    dotButton = new QPushButton(".");
    keypadLayout->addWidget(dotButton,3,1);
    dotButton->setShortcut('.'); //key shortcut: .
    connect(dotButton, SIGNAL(released()), this, SLOT(handleDotButton()));

    //ottenimento risultato (=)
    assignmentButton = new QPushButton("=");
    keypadLayout->addWidget(assignmentButton,3,2);
    assignmentButton->setShortcut('='); //key shortcut: =
    connect(assignmentButton, SIGNAL(released()), this, SLOT(handleAssignmentButton()));

    keypad->setLayout(keypadLayout);
}
*/
void Widget::handleNumButtons() {}

void Widget::handleDotButton() {}

void Widget::handleAssignmentButton() {}

void Widget::handleCreateMatrixButton() {
    QWidget* matrixBuilder = new MatrixBuilder();
    matrixBuilder->setMinimumSize(100,50);
    matrixBuilder->show();
    //setDisabled(true);
}
