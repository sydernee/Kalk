#include "Widget.h"
#include "MatrixBuilder.h"
#include "NetworkManager.h"
#include <QRect>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      createMatrixKalk(new QPushButton("MatrixKalk", this)),
      createNetworkKalk(new QPushButton("NetworkKalk", this))
{
    setWindowTitle("Kalk"); //imposta il titolo della finestra
    setMinimumSize(150,75); //imposta le dimensioni minime della finestra

    connect(createMatrixKalk, SIGNAL(clicked()), this, SLOT(handleCreateMatrixKalkButton()));
    connect(createNetworkKalk, SIGNAL(clicked()), this, SLOT(handleNetworkManagerKalkButton()));

    QHBoxLayout* hblayout = new QHBoxLayout;
    hblayout->addWidget(createMatrixKalk);
    hblayout->addWidget(createNetworkKalk);    

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(hblayout);

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

    QObject::connect(matrixBuilder, SIGNAL(matrixBuilderCloseSignal()), this, SLOT(showWidget()));
    hide();
}

void Widget::handleNetworkManagerKalkButton() {
    QWidget* networkManager = new NetworkManager();
    networkManager->setAttribute(Qt::WA_DeleteOnClose); //delete on close
    networkManager->setMinimumSize(300,200);
    networkManager->show();

    QObject::connect(networkManager, SIGNAL(networkManagerCloseSignal()), this, SLOT(showWidget()));
    hide();
}

void Widget::showWidget() {
    show();
}
