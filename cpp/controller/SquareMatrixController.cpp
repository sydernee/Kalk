#include "SquareMatrixController.h"
#include "../model/datatypes/SquareMatrix.h"

SquareMatrixController::SquareMatrixController(SquareMatrixKalk* _view, SquareMatrix* _mat1, SquareMatrix* _mat2)
    : MatrixController((MatrixCreator*)_view, (Matrix*)_mat1, (Matrix*)_mat2)
{}

//getters
/*SquareMatrix& getMatrix1() const {
    return static_cast<SquareMatrix&>(MatrixController::getMatrix1());
}

SquareMatrix& getMatrix2() const {
    return static_cast<SquareMatrix&>(MatrixController::getMatrix2());
}
*/
//operations

SquareMatrix SquareMatrixController::determinant() const {
    return static_cast<SquareMatrix&>(getMatrix1()).determinant();
}
