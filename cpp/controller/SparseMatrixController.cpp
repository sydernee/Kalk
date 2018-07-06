#include "SparseMatrixController.h"
#include "../model/datatypes/SparseMatrix.h"
#include "../view/SparseMatrixKalk.h"

SparseMatrixController::SparseMatrixController(Matrix* _mat1, Matrix* _mat2)
    : MatrixController(_mat1, _mat2)
{
    if ((_mat1 != nullptr && !dynamic_cast<SparseMatrix*>(_mat1))
            || (_mat2 != nullptr && !dynamic_cast<SparseMatrix*>(_mat2)))
    {
        throw InvalidMatrixTypeException("SparseMatrixController::SparseMatrixController(): Invalid matrix type.");
    }
}

void SparseMatrixController::buildMatrix(const QVector<KeypadInput*>& cells, unsigned int rows, unsigned int cols, int whichMatrix) {

    if (getMatrix(whichMatrix) != nullptr)
        delete getMatrix(whichMatrix);

    getMatrix(whichMatrix) = new SparseMatrix(rows, cols); //alloca una SquareMatrix se le dimensioni sono uguali

    if (!cells.isEmpty()) //se cells non è vuoto, imposta il valore delle celle di matrix1
        for (unsigned int i = 0; i < rows; i++)
            for (unsigned int j = 0; j < cols; j++)
                (getMatrix(whichMatrix))->set(i,j,cells[i*cols+j]->text().toDouble());
}

void SparseMatrixController::buildMatrix(unsigned int rows, unsigned int cols, int whichMatrix) {
    if (getMatrix(whichMatrix) != nullptr)
        delete getMatrix(whichMatrix);

    getMatrix(whichMatrix) = new SparseMatrix(rows, cols); //alloca una SquareMatrix se le dimensioni sono uguali
}

//SETTERS

void SparseMatrixController::setMatrix(const Matrix& mat, int whichMatrix) {
    if (getMatrix(whichMatrix) != nullptr)
        delete getMatrix(whichMatrix);

    const Matrix* ptr = &mat;
    if (!dynamic_cast<const SparseMatrix*>(ptr)) {
        throw InvalidMatrixTypeException("SparseMatrix::setMatrix1(): Parameter mat is not a SparseMatrix.");
    }
    getMatrix(whichMatrix) = new SparseMatrix(static_cast<const SparseMatrix&>(mat));
}

double SparseMatrixController::getSparsity() const {
    if (getMatrix() == nullptr)
        throw NullPointerException("SparseMatrixController::getSparsity(): Attempted to dereference a nullpointer.");

    return static_cast<SparseMatrix*>(getMatrix())->getSparsity();
}

bool SparseMatrixController::isDense() const {
    if (getMatrix() == nullptr)
        throw NullPointerException("SparseMatrixController::isDense(): Attempted to dereference a nullpointer.");

    return static_cast<SparseMatrix*>(getMatrix())->isDense();
}

QVector<double> SparseMatrixController::nonZeroRow(unsigned int i) const {
    if (getMatrix() == nullptr)
        throw NullPointerException("SparseMatrixController::nonZeroRow(): Attempted to dereference a nullpointer.");

    return static_cast<SparseMatrix*>(getMatrix())->nonZeroRow(i);
}


QVector<double> SparseMatrixController::nonZeroCol(unsigned int i) const {
    if (getMatrix() == nullptr)
        throw NullPointerException("SparseMatrixController::nonZeroCol(): Attempted to dereference a nullpointer.");

    return static_cast<SparseMatrix*>(getMatrix())->nonZeroCol(i);
}
