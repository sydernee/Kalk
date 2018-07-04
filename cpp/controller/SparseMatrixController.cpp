#include "SparseMatrixController.h"
#include "../model/datatypes/SparseMatrix.h"
#include "../view/SparseMatrixKalk.h"

SparseMatrixController::SparseMatrixController(MatrixKalk* _view, Matrix* _mat1, Matrix* _mat2)
    : MatrixController(_view, _mat1, _mat2)
{
    if ((_view != nullptr && !qobject_cast<SparseMatrixKalk*>(_view))
            || (_mat1 != nullptr && !dynamic_cast<SparseMatrix*>(_mat1))
            || (_mat2 != nullptr && !dynamic_cast<SparseMatrix*>(_mat2)))
    {
        throw InvalidMatrixTypeException("SparseMatrixController::SparseMatrixController(): Invalid matrix type.");
    }
}

void SparseMatrixController::buildMatrix1(QVector<KeypadInput*> cells, unsigned int rows, unsigned int cols) {
    if (getMatrix1() != nullptr) {
        delete getMatrix1();
    }
    getMatrix1() = new SparseMatrix(rows, cols); //alloca una SquareMatrix se le dimensioni sono uguali

    if (!cells.isEmpty()) //se cells non è vuoto, imposta il valore delle celle di matrix1
        for (unsigned int i = 0; i < rows; i++)
            for (unsigned int j = 0; j < cols; j++)
                getMatrix1()->set(i,j,cells[i*cols+j]->text().toDouble());
}

void SparseMatrixController::buildMatrix1(unsigned int rows, unsigned int cols) {
    if (getMatrix1() != nullptr)
        delete getMatrix1();

    getMatrix1() = new SparseMatrix(rows, cols); //alloca una SquareMatrix se le dimensioni sono uguali
}

void SparseMatrixController::buildMatrix2(QVector<KeypadInput*> cells, unsigned int rows, unsigned int cols) {
    if (getMatrix2() != nullptr) {
        delete getMatrix2();
    }
    getMatrix2() = new SparseMatrix(rows, cols);

    if (!cells.isEmpty()) //se cells non è vuoto, imposta il valore delle celle di matrix2
        for (unsigned int i = 0; i < rows; i++)
            for (unsigned int j = 0; j < cols; j++)
                getMatrix2()->set(i,j,cells[i*cols+j]->text().toDouble());
}

void SparseMatrixController::buildMatrix2(unsigned int rows, unsigned int cols) {
    if (getMatrix2() != nullptr)
        delete getMatrix2();

    getMatrix2() = new SparseMatrix(rows, cols);
}

//SETTERS

void SparseMatrixController::setMatrix1(const Matrix& mat) {
    if (getMatrix1() != nullptr)
        delete getMatrix1();

    const Matrix* ptr = &mat;
    if (!dynamic_cast<const SparseMatrix*>(ptr)) {
        throw InvalidMatrixTypeException("SparseMatrix::setMatrix1(): Parameter mat is not a SparseMatrix.");
    }
    getMatrix1() = new SparseMatrix(static_cast<const SparseMatrix&>(mat));
}

void SparseMatrixController::setMatrix2(const Matrix& mat) {
    if (getMatrix2() != nullptr)
        delete getMatrix2();

    const Matrix* ptr = &mat;
    if (!dynamic_cast<const SparseMatrix*>(ptr)) {
        throw InvalidMatrixTypeException("SparseMatrix::setMatrix2(): Parameter mat is not a SparseMatrix.");
    }
    getMatrix2() = new SparseMatrix(static_cast<const SparseMatrix&>(mat));
}

double SparseMatrixController::getSparsity() const {
    if (getMatrix1() == nullptr)
        throw NullPointerException("SparseMatrixController::getSparsity(): Attempted to dereference a nullpointer.");

    return static_cast<SparseMatrix*>(getMatrix1())->getSparsity();
}

bool SparseMatrixController::isDense() const {
    if (getMatrix1() == nullptr)
        throw NullPointerException("SparseMatrixController::isDense(): Attempted to dereference a nullpointer.");

    return static_cast<SparseMatrix*>(getMatrix1())->isDense();
}

QVector<double> SparseMatrixController::nonZeroRow(unsigned int i) const {
    if (getMatrix1() == nullptr)
        throw NullPointerException("SparseMatrixController::nonZeroRow(): Attempted to dereference a nullpointer.");

    return static_cast<SparseMatrix*>(getMatrix1())->nonZeroRow(i);
}


QVector<double> SparseMatrixController::nonZeroCol(unsigned int i) const {
    if (getMatrix1() == nullptr)
        throw NullPointerException("SparseMatrixController::nonZeroCol(): Attempted to dereference a nullpointer.");

    return static_cast<SparseMatrix*>(getMatrix1())->nonZeroCol(i);
}
