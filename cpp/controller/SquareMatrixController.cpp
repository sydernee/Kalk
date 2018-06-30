#include "SquareMatrixController.h"
#include "../model/datatypes/SquareMatrix.h"

SquareMatrixController::SquareMatrixController(SquareMatrixKalk* _view, SquareMatrix* _mat1, SquareMatrix* _mat2)
    : MatrixController((MatrixCreator*)_view, (Matrix*)_mat1, (Matrix*)_mat2)
{}

SquareMatrixController::~SquareMatrixController() {}

/*
SquareMatrixController::SquareMatrixController(MatrixCreator* _view, Matrix* _mat1, Matrix* _mat2)
    : MatrixController(_view, _mat1, _mat2)
{
    if (!qobject_cast<SquareMatrixKalk*>(_view)
            || !dynamic_cast<SquareMatrix*>(_mat1)
            || !dynamic_cast<SquareMatrix*>(_mat2))
        throw Exception();
}*/

void SquareMatrixController::buildMatrix1(QVector<KeypadInput*> cells, unsigned int rows, unsigned int cols) {
    //    if (rows != cols)
            //TODO throw Exception;
        MatrixController::buildMatrix1(cells,rows,cols);
}

void SquareMatrixController::buildMatrix1(unsigned int rows, unsigned int cols) {
//    if (rows != cols)
        //TODO throw Exception;
    MatrixController::buildMatrix1(rows,cols);
}

void SquareMatrixController::buildMatrix2(QVector<KeypadInput*> cells, unsigned int rows, unsigned int cols) {
    //    if (rows != cols)
            //TODO throw Exception;
        MatrixController::buildMatrix2(cells,rows,cols);
}

void SquareMatrixController::buildMatrix2(unsigned int rows, unsigned int cols) {
    //    if (rows != cols)
            //TODO throw Exception;
        MatrixController::buildMatrix2(rows,cols);
}

//SETTERS

void SquareMatrixController::setMatrix1(const Matrix& mat) {
    //    if (mat.rowCount() != mat.colCount()) //oppure (!dynamic_cast<const SquareMatrix&>(mat))
            //TODO throw Exception;
        MatrixController::setMatrix1(mat);
}

void SquareMatrixController::setMatrix2(const Matrix& mat) {
    //    if (mat.rowCount() != mat.colCount()) //oppure (!dynamic_cast<const SquareMatrix&>(mat))
            //TODO throw Exception;
        MatrixController::setMatrix2(mat);
}

//operations

double SquareMatrixController::determinant() const {
    //matrix1 ha TD SquareMatrix*
    return static_cast<SquareMatrix&>(getMatrix1()).determinant();
}

SquareMatrix SquareMatrixController::getMinor(unsigned int x, unsigned int y) const {
    //matrix1 ha TD SquareMatrix*
    return static_cast<SquareMatrix&>(getMatrix1()).getMinor(x, y);
}

bool SquareMatrixController::isSupTriangular() const {
    return static_cast<SquareMatrix&>(getMatrix1()).supTriangular();
}

bool SquareMatrixController::isInfTriangular() const {
    return static_cast<SquareMatrix&>(getMatrix1()).infTriangular();
}

bool SquareMatrixController::isDiagonal() const {
    return static_cast<SquareMatrix&>(getMatrix1()).isDiagonal();
}
