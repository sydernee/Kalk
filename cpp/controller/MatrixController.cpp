#include <QWidget>
#include <QLabel>

#include "MatrixController.h"
#include "../model/datatypes/Matrix.h"
#include "../view/MatrixCreator.h"
#include "../view/KeypadInput.h"

MatrixController::MatrixController(MatrixCreator* _view, Matrix* _matrix1, Matrix* _matrix2)
    : matrix1(_matrix1), //copia di puntatori
      matrix2(_matrix2),
      view(_view)
{}

MatrixController::~MatrixController() {
    //delete matrix;
}

void MatrixController::buildMatrix1(QVector<KeypadInput*> cells, unsigned int rows, unsigned int cols) {
    //PRE: cells[n] viene visto come cells[rows][cols] e sono le corrette dimensioni della matrice che si vuole costruire
    if (matrix1 != nullptr) {
        delete matrix1;
    }

    matrix1 = new Matrix(rows, cols); //alloca matrix1 nello heap
    if (!cells.isEmpty()) //se cells non è vuoto, imposta il valore delle celle di matrix1
        for (unsigned int i = 0; i < rows; i++)
            for (unsigned int j = 0; j < cols; j++)
                matrix1->set(i,j,cells[i*cols+j]->text().toDouble());
}

void MatrixController::buildMatrix1(unsigned int rows, unsigned int cols) {
    if (matrix1 != nullptr)
        delete matrix1;
    matrix1 = new Matrix(rows, cols);
}

void MatrixController::buildMatrix2(QVector<KeypadInput*> cells, unsigned int rows, unsigned int cols) {
    //PRE: cells[n] viene visto come cells[rows][cols] e sono le corrette dimensioni della matrice che si vuole costruire
    if (matrix2 != nullptr) {
        delete matrix2;
    }
    matrix2 = new Matrix(rows, cols); //alloca matrix1 nello heap
    if (!cells.isEmpty()) //se cells non è vuoto, imposta il valore delle celle di matrix2
        for (unsigned int i = 0; i < rows; i++)
            for (unsigned int j = 0; j < cols; j++)
                matrix2->set(i,j,cells[i*cols+j]->text().toDouble());
}

void MatrixController::buildMatrix2(unsigned int rows, unsigned int cols) {
    if (matrix2 != nullptr)
        delete matrix2;
    matrix2 = new Matrix(rows, cols);
}

//SETTERS

void MatrixController::setMatrix1(const Matrix& mat) {
    delete matrix1;
    matrix1 = new Matrix(mat);
}

void MatrixController::setMatrix2(const Matrix& mat) {
    delete matrix2;
    matrix2 = new Matrix(mat);
}

//GETTERS

Matrix& MatrixController::getMatrix1() const {
    return *matrix1;
}

Matrix& MatrixController::getMatrix2() const {
    return *matrix2;
}

//output

void MatrixController::displayMatrix(const Matrix& mat) {
    unsigned int rows = mat.rowCount();
    unsigned int cols = mat.colCount();

    QGridLayout* resultLayout = new QGridLayout;
    QVector<QLabel*> matrixOutput;
    QWidget* result = new QWidget;

    for (unsigned int i = 0; i < rows; i++)
        for (unsigned int j = 0; j < cols; j++) {
            matrixOutput.append(new QLabel(QString::number(mat[i][j]), result));
            resultLayout->addWidget(matrixOutput.last(),i,j);
        }

    result->setLayout(resultLayout);
    result->show();
}

Matrix MatrixController::sum() const {
    return (*matrix1) + (*matrix2);
}

Matrix MatrixController::sum(const Matrix& m1, const Matrix& m2) {
    return m1 + m2;
}
