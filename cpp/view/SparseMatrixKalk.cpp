#include "SparseMatrixKalk.h"
#include "../controller/SparseMatrixController.h"
#include <QErrorMessage>

SparseMatrixKalk::SparseMatrixKalk(MatrixController* _controller, QWidget* parent)
    : MatrixKalk(_controller, parent),
      nonZeroDialog(nullptr),
      nonZeroSpinBox(nullptr)
{
    if (!dynamic_cast<SparseMatrixController*>(controller)) {
        throw InvalidMatrixTypeException("SparseMatrixKalk::SparseMatrixKalk(): Invalid controller dynamic type.");
    }
    try {
        insertSparseOperations();
    }
    catch(KalkException& e) {
        exceptionHandling(e);
        close();
    }
}

void SparseMatrixKalk::insertSparseOperations() {
    QHBoxLayout* l = new QHBoxLayout;

    //istanziazione, connessioni e inserimento in l dei pulsanti
    QPushButton* sparsity = new QPushButton("sparsity()", getOperationsSet());
    connect(sparsity, SIGNAL(clicked()), this, SLOT(handleGetSparsity()));
    l->addWidget(sparsity);

    QPushButton* dense = new QPushButton("isDense()", getOperationsSet());
    connect(dense, SIGNAL(clicked()), this, SLOT(handleIsDense()));
    l->addWidget(dense);

    QPushButton* nonZeroRow = new QPushButton("nonZeroRow()", getOperationsSet());
    connect(nonZeroRow, SIGNAL(clicked()), this, SLOT(handleNonZeroRow()));
    l->addWidget(nonZeroRow);

    QPushButton* nonZeroCol = new QPushButton("nonZeroCol()", getOperationsSet());
    connect(nonZeroCol, SIGNAL(clicked()), this, SLOT(handleNonZeroCol()));
    l->addWidget(nonZeroCol);

    QVBoxLayout* ptr = qobject_cast<QVBoxLayout*>(getOperationsSet()->layout());

    if (!ptr)
        throw NullPointerException("SparseMatrix::insertSparseOperations(): InvalidLayout.");

    ptr->addLayout(l);
}

//SLOTS

void SparseMatrixKalk::handleGetSparsity() {
    controller->buildMatrix(getCells(), getRowBox()->value(), getColBox()->value());

    QDialog* dialog = new QDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose); //delete on close
    dialog->setMinimumSize(200,50);
    dialog->setWindowTitle("Sparsità");
    QLabel* label = new QLabel("Sparsità: " + QString::number(static_cast<SparseMatrixController*>(controller)->getSparsity()), dialog);
    label->setMargin(15);
    dialog->show();
}

void SparseMatrixKalk::handleIsDense() {
    controller->buildMatrix(getCells(), getRowBox()->value(), getColBox()->value());

    QDialog* dialog = new QDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose); //delete on close
    dialog->setMinimumSize(200,50);
    dialog->setWindowTitle("Densità");
    QLabel* label = new QLabel(dialog);

    try {
        if (static_cast<SparseMatrixController*>(controller)->isDense())
            label->setText("La matrice è densa.");
        else
            label->setText("La matrice non è densa.");
        label->setMargin(15);
        dialog->show();
    }
    catch(KalkException& e) {
        exceptionHandling(e);
        dialog->close();
    }
}

void SparseMatrixKalk::handleNonZeroRow() {
    controller->buildMatrix(getCells(), getRowBox()->value(), getColBox()->value());

    nonZeroDialog = new QDialog;                        //istanzia nonZeroDialog
    nonZeroDialog->setAttribute(Qt::WA_DeleteOnClose);  //delete on close
    nonZeroDialog->setWindowTitle("nonZeroRow");        //titolo finestra
    nonZeroDialog->setWindowModality(Qt::ApplicationModal); //impedisce l'interazione con altre finestre
    nonZeroDialog->setMinimumSize(150,100);

    nonZeroSpinBox = new QSpinBox(nonZeroDialog);
    setSpinBoxLimits(nonZeroSpinBox, 0, getRowBox()->value()-1);

    QHBoxLayout* l = new QHBoxLayout;
    QVBoxLayout* dialogLayout = new QVBoxLayout;

    l->addWidget(new QLabel("Scegli la riga", nonZeroDialog));
    l->addWidget(nonZeroSpinBox);

    QPushButton* button = new QPushButton("Ok", nonZeroDialog);

    dialogLayout->addLayout(l);
    dialogLayout->addWidget(button);

    nonZeroDialog->setLayout(dialogLayout);
    nonZeroDialog->show();

    connect(button, SIGNAL(clicked()), this, SLOT(handleSparseMatrixObtainResult()));
    setOperationSelected(NON_ZERO_ROW);
}

void SparseMatrixKalk::handleNonZeroCol() {
    controller->buildMatrix(getCells(), getRowBox()->value(), getColBox()->value());

    nonZeroDialog = new QDialog;                        //istanzia nonZeroDialog
    nonZeroDialog->setAttribute(Qt::WA_DeleteOnClose);  //delete on close
    nonZeroDialog->setWindowTitle("nonZeroCol");        //titolo finestra
    nonZeroDialog->setWindowModality(Qt::ApplicationModal); //impedisce l'interazione con altre finestre
    nonZeroDialog->setMinimumSize(150,100);

    nonZeroSpinBox = new QSpinBox(nonZeroDialog);
    setSpinBoxLimits(nonZeroSpinBox, 0, getColBox()->value()-1);

    QHBoxLayout* l = new QHBoxLayout;
    QVBoxLayout* dialogLayout = new QVBoxLayout;

    l->addWidget(new QLabel("Scegli la colonna", nonZeroDialog));
    l->addWidget(nonZeroSpinBox);

    QPushButton* button = new QPushButton("Ok", nonZeroDialog);

    dialogLayout->addLayout(l);
    dialogLayout->addWidget(button);

    nonZeroDialog->setLayout(dialogLayout);
    nonZeroDialog->show();

    connect(button, SIGNAL(clicked()), this, SLOT(handleSparseMatrixObtainResult()));
    setOperationSelected(NON_ZERO_COL);
}

void SparseMatrixKalk::handleSparseMatrixObtainResult() {
    QVector<double> res;
    QWidget* result = new QWidget;
    result->setAttribute(Qt::WA_DeleteOnClose); //delete on close

    try {
        if (getOperationSelected() == NON_ZERO_ROW) {
            res = static_cast<SparseMatrixController*>(controller)->nonZeroRow(nonZeroSpinBox->value());

            result->setWindowTitle("Risultato nonZeroRow");
        }
        else if (getOperationSelected() == NON_ZERO_COL) {
            res = static_cast<SparseMatrixController*>(controller)->nonZeroCol(nonZeroSpinBox->value());

            result->setWindowTitle("Risultato nonZeroCol");
        }

        result->setMinimumSize(res.size() * 15, 50);
        QLabel* label = new QLabel("", result);
        label->setMargin(15);

        for (auto it = res.begin(); it != res.end(); it++) {
            label->setText(label->text() + "  " + QString::number(*it));
        }

        result->show();
        nonZeroDialog->close();
        getOperationsSet()->hide();

        //reset dell'interfaccia
        resetDimensionsGroupBox();
        getObtainResult()->hide();
        getSelectSecondMatrixLabel()->hide();
    }
    catch(KalkException& e) {
        exceptionHandling(e);
        result->close();
    }
}
