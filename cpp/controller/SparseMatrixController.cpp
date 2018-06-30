#include "SparseMatrixController.h"
#include "../model/datatypes/SparseMatrix.h"
#include "../view/SparseMatrixKalk.h"

SparseMatrixController::SparseMatrixController(MatrixCreator* _view, Matrix* _mat1, Matrix* _mat2)
    : MatrixController(_view, _mat1, _mat2)
{
    if (!qobject_cast<SparseMatrixKalk*>(_view)
            || !dynamic_cast<SparseMatrix*>(_mat1)
            || !dynamic_cast<SparseMatrix*>(_mat2))
    {
        //TODO throw Exception();
    }
}

SparseMatrixController::~SparseMatrixController() {}


void SparseMatrixController::buildMatrix1(QVector<KeypadInput*> cells, unsigned int rows, unsigned int cols) {
    if (matrix1 != nullptr) {
        delete matrix1;
    }
    matrix1 = new SparseMatrix(rows, cols); //alloca una SquareMatrix se le dimensioni sono uguali

    if (!cells.isEmpty()) //se cells non è vuoto, imposta il valore delle celle di matrix1
        for (unsigned int i = 0; i < rows; i++)
            for (unsigned int j = 0; j < cols; j++)
                matrix1->set(i,j,cells[i*cols+j]->text().toDouble());
}

void SparseMatrixController::buildMatrix1(unsigned int rows, unsigned int cols) {
    if (matrix1 != nullptr)
        delete matrix1;

        matrix1 = new SparseMatrix(rows, cols); //alloca una SquareMatrix se le dimensioni sono uguali
}

void SparseMatrixController::buildMatrix2(QVector<KeypadInput*> cells, unsigned int rows, unsigned int cols) {
    if (matrix2 != nullptr) {
        delete matrix2;
    }
    matrix2 = new SparseMatrix(rows, cols);

    if (!cells.isEmpty()) //se cells non è vuoto, imposta il valore delle celle di matrix2
        for (unsigned int i = 0; i < rows; i++)
            for (unsigned int j = 0; j < cols; j++)
                matrix2->set(i,j,cells[i*cols+j]->text().toDouble());
}

void SparseMatrixController::buildMatrix2(unsigned int rows, unsigned int cols) {
    if (matrix2 != nullptr)
        delete matrix2;

        matrix2 = new SparseMatrix(rows, cols);
}

//SETTERS

void SparseMatrixController::setMatrix1(const Matrix& mat) {
    if (matrix1 != nullptr)
        delete matrix1;
    const Matrix* ptr = &mat;
    if (!dynamic_cast<const SparseMatrix*>(ptr)) {
        //TODO throw Exception;
    }
    matrix1 = new SparseMatrix(static_cast<const SparseMatrix&>(mat));
}

void SparseMatrixController::setMatrix2(const Matrix& mat) {
    if (matrix2 != nullptr)
        delete matrix2;
    const Matrix* ptr = &mat;
    if (!dynamic_cast<const SparseMatrix*>(ptr)) {
        //TODO throw Exception;
    }
    matrix2 = new SparseMatrix(static_cast<const SparseMatrix&>(mat));
}

double SparseMatrixController::getSparsity() const {
    return static_cast<SparseMatrix*>(matrix1)->getSparsity();
}

bool SparseMatrixController::isDense() const {
    return static_cast<SparseMatrix*>(matrix1)->isDense();
}

bool SparseMatrixController::isSymmetric() const {
    return static_cast<SparseMatrix*>(matrix1)->isSymmetric();
}
