#include "Widget.h"
#include "MatrixBuilder.h"
#include <QRect>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      dotButton(nullptr),
      assignmentButton(nullptr),
      createMatrix(new QPushButton("Crea una matrice", this))
{
    setWindowTitle("Kalk"); //imposta il titolo della finestra
    setMinimumSize(150,75); //imposta le dimensioni minime della finestra

    //costruisce il tastierino numerico
    //buildNumButtons(40,0,50,30);

    //createMatrix->setGeometry(0,0,100,30);
    connect(createMatrix, SIGNAL(released()), this, SLOT(handleCreateMatrixButton()));

    QHBoxLayout *hblayout = new QHBoxLayout(this);
    hblayout->addWidget(createMatrix);

    setLayout(hblayout);
}

Widget::~Widget() {}

/*
 buildNumButtons costruisce il tastierino numerico
x = spazio orizzontale lasciato bianco
y = spazio verticale lasciato bianco
w = dimensione orizzontale dei bottoni
h = dimensione verticale dei bottoni
*/
void Widget::buildNumButtons(int x, int y, int w, int h) {
    //bottone per 0 (posizionato sotto gli altri)
    NumericButtons.push_back(new QPushButton(QString::number(0), this));
    NumericButtons[0]->setShortcut(QString::number(0)); //key shortcut: 0
    connect(NumericButtons[0], SIGNAL(released()), this, SLOT(handleNumButtons()));

    int j = 0; //per l'allineamento verticale
    for (int i = 1, k = 0; i < 10; i++) {
        NumericButtons.push_back(new QPushButton(QString::number(i),  this));
        NumericButtons[i]->setGeometry(x+w*k,y+h*j,w,h);
        NumericButtons[i]->setShortcut(QString::number(i)); //i button key shortcut: i
        connect(NumericButtons[i], SIGNAL(released()), this, SLOT(handleNumButtons()));
        if (i != 0 && i % 3 == 0) { //a capo ogni 3 numeri
            j++;
            k = 0;
        }
        else {
            k++;
        }
    }
    NumericButtons[0]->setGeometry(x,y+h*j,w,h);

    //punto
    dotButton = new QPushButton(".", this);
    dotButton->setGeometry(x+w,h*j,w,h);
    dotButton->setShortcut('.'); //key shortcut: .
    connect(dotButton, SIGNAL(released()), this, SLOT(handleDotButton()));

    //ottenimento risultato (=)
    assignmentButton = new QPushButton("=", this);
    assignmentButton->setGeometry(x+2*w,h*j,w,h);
    assignmentButton->setShortcut('='); //key shortcut: =
    connect(assignmentButton, SIGNAL(released()), this, SLOT(handleAssignmentButton()));
}

void Widget::handleNumButtons() {}

void Widget::handleDotButton() {}

void Widget::handleAssignmentButton() {}

void Widget::handleCreateMatrixButton() {
    QWidget* matrixBuilder = new MatrixBuilder();
    matrixBuilder->setMinimumSize(100,50);
    matrixBuilder->show();
    //setDisabled(true);
}
