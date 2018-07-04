#include "SquareMatrixController.h"
#include "../view/SquareMatrixKalk.h"

SquareMatrixController::SquareMatrixController(MatrixKalk* _view, Matrix* _mat1, Matrix* _mat2)
    : MatrixController(_view, _mat1, _mat2)
{
    if ((_view != nullptr && !qobject_cast<SquareMatrixKalk*>(_view))
            || (_mat1 != nullptr && !dynamic_cast<SquareMatrix*>(_mat1))
            || (_mat2 != nullptr && !dynamic_cast<SquareMatrix*>(_mat2)))
    {
        throw InvalidMatrixTypeException("SquareMatrixController::SquareMatrixController(): Invalid Matrix type");
    }
}

void SquareMatrixController::buildMatrix1(QVector<KeypadInput*> cells, unsigned int rows, unsigned int cols) {
    if (rows != cols)
        throw InvalidMatrixIndexes("SquareMatrixController::buildMatrix1(): rows != cols.");

    MatrixController::buildMatrix1(cells,rows,cols);
}

void SquareMatrixController::buildMatrix1(unsigned int rows, unsigned int cols) {
    if (rows != cols)
        throw InvalidMatrixIndexes("SquareMatrixController::buildMatrix1(): rows != cols.");

    MatrixController::buildMatrix1(rows,cols);
}

void SquareMatrixController::buildMatrix2(QVector<KeypadInput*> cells, unsigned int rows, unsigned int cols) {
    if (rows != cols)
        throw InvalidMatrixIndexes("SquareMatrixController::buildMatrix2(): rows != cols.");

    MatrixController::buildMatrix2(cells,rows,cols);
}

void SquareMatrixController::buildMatrix2(unsigned int rows, unsigned int cols) {
    if (rows != cols)
        throw InvalidMatrixIndexes("SquareMatrixController::buildMatrix2(): rows != cols.");

    MatrixController::buildMatrix2(rows,cols);
}

//SETTERS

void SquareMatrixController::setMatrix1(const Matrix& mat) {
    if (mat.rowCount() != mat.colCount())
        throw InvalidMatrixTypeException("SquareMatrixController::setMatrix1(): Parameter mat is not a SquareMatrix.");

    MatrixController::setMatrix1(mat);
}

void SquareMatrixController::setMatrix2(const Matrix& mat) {
    if (mat.rowCount() != mat.colCount())
        throw InvalidMatrixTypeException("SquareMatrixController::setMatrix2(): Parameter mat is not a SquareMatrix.");

    MatrixController::setMatrix2(mat);
}

//operations

double SquareMatrixController::determinant() const {
    //matrix1 ha sicuramente TD SquareMatrix*
    if (getMatrix1() == nullptr)
        throw NullPointerException("SquareMatrixController::determinant(): Attempted to dereference a null pointer.");

    return static_cast<SquareMatrix*>(getMatrix1())->determinant();
}

SquareMatrix SquareMatrixController::getMinor(unsigned int x, unsigned int y) const {
    //matrix1 ha sicuramente TD SquareMatrix*
    if (getMatrix1() == nullptr)
        throw NullPointerException("SquareMatrixController::determinant(): Attempted to dereference a null pointer.");

    return static_cast<SquareMatrix*>(getMatrix1())->getMinor(x, y); //throws
}

bool SquareMatrixController::isSupTriangular() const {
    if (getMatrix1() == nullptr)
        throw NullPointerException("SquareMatrixController::determinant(): Attempted to dereference a null pointer.");

    return static_cast<SquareMatrix*>(getMatrix1())->supTriangular();
}

bool SquareMatrixController::isInfTriangular() const {
    if (getMatrix1() == nullptr)
        throw NullPointerException("SquareMatrixController::determinant(): Attempted to dereference a null pointer.");

    return static_cast<SquareMatrix*>(getMatrix1())->infTriangular();
}

bool SquareMatrixController::isDiagonal() const {
    if (getMatrix1() == nullptr)
        throw NullPointerException("SquareMatrixController::determinant(): Attempted to dereference a null pointer.");

    return static_cast<SquareMatrix*>(getMatrix1())->isDiagonal();
}

bool SquareMatrixController::isSymmetric() const {
    if (getMatrix1() == nullptr)
        throw NullPointerException("SquareMatrixController::determinant(): Attempted to dereference a null pointer.");

    return static_cast<SquareMatrix*>(getMatrix1())->isSymmetric();
}
