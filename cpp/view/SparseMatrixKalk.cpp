#include "SparseMatrixKalk.h"
#include "../controller/SparseMatrixController.h"

SparseMatrixKalk::SparseMatrixKalk(MatrixController* _controller, QWidget* parent)
    : MatrixCreator(_controller, parent)
{
    if (!dynamic_cast<SparseMatrixController*>(controller)) {
        //TODO throw Exception
    }

    insertSparseOperations();
}

SparseMatrixKalk::~SparseMatrixKalk() {}

void SparseMatrixKalk::insertSparseOperations() {
    QHBoxLayout* l = new QHBoxLayout;

    //istanziazione, connessioni e inserimento in l dei pulsanti
    QPushButton* sparsity = new QPushButton("sparsity()", getOperationsSet());
    connect(sparsity, SIGNAL(clicked()), this, SLOT(handleGetSparsity()));
    l->addWidget(sparsity);

    QPushButton* dense = new QPushButton("isDense()", getOperationsSet());
    connect(dense, SIGNAL(clicked()), this, SLOT(handleIsDense()));
    l->addWidget(dense);

    QPushButton* symmetric = new QPushButton("isSymmetric()", getOperationsSet());
    connect(symmetric, SIGNAL(clicked()), this, SLOT(handleIsSymmetric()));
    l->addWidget(symmetric);

    QVBoxLayout* ptr = qobject_cast<QVBoxLayout*>(getOperationsSet()->layout());
    if (!ptr)
        {}//TODO throw
    ptr->addLayout(l);
}

//SLOTS

void SparseMatrixKalk::handleGetSparsity() {
    controller->buildMatrix1(getCells(), getRowBox()->value(), getColBox()->value());

    QDialog* dialog = new QDialog;
    dialog->setMinimumSize(200,50);
    dialog->setWindowTitle("Sparsità");
    QLabel* label = new QLabel("Sparsità: " + QString::number(static_cast<SparseMatrixController*>(controller)->getSparsity()), dialog);
    label->setMargin(15);
    dialog->show();
}

void SparseMatrixKalk::handleIsDense() {
    controller->buildMatrix1(getCells(), getRowBox()->value(), getColBox()->value());

    QDialog* dialog = new QDialog;
    dialog->setMinimumSize(200,50);
    dialog->setWindowTitle("Densità");
    QLabel* label = new QLabel(dialog);

    if (static_cast<SparseMatrixController*>(controller)->isDense())
        label->setText("La matrice è densa.");
    else
        label->setText("La matrice non è densa.");
    label->setMargin(15);
    dialog->show();
}

void SparseMatrixKalk::handleIsSymmetric() {
    controller->buildMatrix1(getCells(), getRowBox()->value(), getColBox()->value());

    QDialog* dialog = new QDialog;
    dialog->setMinimumSize(200,50);
    dialog->setWindowTitle("Simmetria");
    QLabel* label = new QLabel(dialog);

    if (static_cast<SparseMatrixController*>(controller)->isSymmetric())
        label->setText("La matrice è simmetrica.");
    else
        label->setText("La matrice non è simmetrica.");
    label->setMargin(15);
    dialog->show();
}
