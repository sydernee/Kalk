#include <QWidget>
#include <QLabel>

#include "MatrixController.h"
#include "../model/datatypes/Matrix.h"
#include "../model/datatypes/SquareMatrix.h"
#include "../view/MatrixCreator.h"
#include "../view/KeypadInput.h"


#include <QGridLayout>

MatrixController::MatrixController(MatrixCreator* _view, Matrix* _matrix1, Matrix* _matrix2)
    : matrix1(_matrix1), //copia di puntatori
      matrix2(_matrix2),
      view(_view)
{}

MatrixController::~MatrixController() {
    delete matrix1;
    delete matrix2;
}

void MatrixController::buildMatrix1(QVector<KeypadInput*> cells, unsigned int rows, unsigned int cols) {
    //PRE: cells[n] viene visto come cells[rows][cols] e sono le corrette dimensioni della matrice che si vuole costruire
    if (matrix1 != nullptr) {
        delete matrix1;
    }
    if (rows == cols)
        matrix1 = new SquareMatrix(rows, cols); //alloca una SquareMatrix se le dimensioni sono uguali
    else
        matrix1 = new Matrix(rows, cols); //alloca matrix1 nello heap

    if (!cells.isEmpty()) //se cells non è vuoto, imposta il valore delle celle di matrix1
        for (unsigned int i = 0; i < rows; i++)
            for (unsigned int j = 0; j < cols; j++)
                matrix1->set(i,j,cells[i*cols+j]->text().toDouble());
}

void MatrixController::buildMatrix1(unsigned int rows, unsigned int cols) {
    if (matrix1 != nullptr)
        delete matrix1;

    if (rows == cols)
        matrix1 = new SquareMatrix(rows, cols); //alloca una SquareMatrix se le dimensioni sono uguali
    else
        matrix1 = new Matrix(rows, cols); //alloca matrix1 nello heap
}

void MatrixController::buildMatrix2(QVector<KeypadInput*> cells, unsigned int rows, unsigned int cols) {
    //PRE: cells[n] viene visto come cells[rows][cols] e sono le corrette dimensioni della matrice che si vuole costruire
    if (matrix2 != nullptr)
        delete matrix2;

    if (rows == cols)
        matrix2 = new SquareMatrix(rows, cols); //alloca una SquareMatrix se le dimensioni sono uguali
    else
        matrix2 = new Matrix(rows, cols); //alloca matrix1 nello heap

    if (!cells.isEmpty()) //se cells non è vuoto, imposta il valore delle celle di matrix2
        for (unsigned int i = 0; i < rows; i++)
            for (unsigned int j = 0; j < cols; j++)
                matrix2->set(i,j,cells[i*cols+j]->text().toDouble());
}

void MatrixController::buildMatrix2(unsigned int rows, unsigned int cols) {
    if (matrix2 != nullptr)
        delete matrix2;
    if (rows == cols)
        matrix2 = new SquareMatrix(rows, cols); //alloca una SquareMatrix se le dimensioni sono uguali
    else
        matrix2 = new Matrix(rows, cols); //alloca matrix1 nello heap;
}

//SETTERS

void MatrixController::setMatrix1(const Matrix& mat) {
    delete matrix1;
    const Matrix* ptr = &mat;
    if (dynamic_cast<const SquareMatrix*>(ptr))
        matrix1 = new SquareMatrix(static_cast<const SquareMatrix&>(mat));
    else
        matrix1 = new Matrix(mat);
}

void MatrixController::setMatrix2(const Matrix& mat) {
    delete matrix2;
    const Matrix* ptr = &mat;
    if (dynamic_cast<const SquareMatrix*>(ptr))
        matrix2= new SquareMatrix(static_cast<const SquareMatrix&>(mat));
    else
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

    QGridLayout* resultLayout = new QGridLayout; //output su layout a griglia per la matrice
    QVector<QLabel*> matrixOutput;
    QWidget* result = new QWidget;
    result->setMinimumSize(50,50);

    for (unsigned int i = 0; i < rows; i++)
        for (unsigned int j = 0; j < cols; j++) {
            matrixOutput.append(new QLabel(QString::number(mat[i][j]), result));
            resultLayout->addWidget(matrixOutput.last(),i,j);
        }

    result->setLayout(resultLayout);
    result->show();
}

//operations

Matrix MatrixController::sum() const {
    // PRE: matrix1 e matrix2 != nullptr
    //try
    return (*matrix1) + (*matrix2);
}

Matrix MatrixController::sum(const Matrix& m1, const Matrix& m2) {
    return m1 + m2;
}

Matrix MatrixController::subtract() const {
    // PRE: matrix1 e matrix2 != nullptr
    return (*matrix1) - (*matrix2);
}

Matrix MatrixController::subtract(const Matrix& m1, const Matrix& m2) {
    return m1 - m2;
}

Matrix MatrixController::scalarMultiply() const {
    // PRE: matrix1 e matrix2 != nullptr
    return (*matrix1) * (*matrix2);
}

Matrix MatrixController::nonScalarMultiply(double value) const {
    // PRE: matrix1 != nullptr
    return (*matrix1) * value;
}


Matrix MatrixController::transposed() const {
    // PRE: matrix1 != nullptr
    Matrix* mat = matrix1->transposed();
    Matrix res(*mat);
    delete mat;
    return res;
}

Matrix MatrixController::swapRows(unsigned int rowA, unsigned int rowB) {
    // PRE: matrix1 != nullptr
    matrix1->swapRows(rowA, rowB);
    return *matrix1;
}

Matrix MatrixController::swapCols(unsigned int colA, unsigned int colB) {
    // PRE: matrix1 != nullptr
    matrix1->swapCols(colA, colB);
    return *matrix1;
}

Matrix MatrixController::substituteRow(unsigned int destRow, unsigned int sourceRow, double factor) {
    //PRE; matrix1 != nullptr
    matrix1->substituteRow(destRow, sourceRow, factor);
    return *matrix1;
}

double MatrixController::determinant() const {
    if (!dynamic_cast<SquareMatrix*>(matrix1)) {
        //TODO throw
    }
    return static_cast<SquareMatrix*>(matrix1)->determinant();
}

SquareMatrix MatrixController::getMinor(unsigned int x, unsigned int y) const {
    if (!dynamic_cast<SquareMatrix*>(matrix1)) {
        //TODO throw
    }
    return static_cast<SquareMatrix*>(matrix1)->getMinor(x, y);
}
