#include "MatrixController.h"
#include "../model/datatypes/Matrix.h"
#include "../view/MatrixCreator.h"

MatrixController::MatrixController(MatrixCreator* _view, Matrix* _model)
    : view(_view),
      matrix(_model) //copia di puntatori
{}

MatrixController::~MatrixController() {
    //delete Matrix;
}

Matrix MatrixController::sum(const Matrix& m1, const Matrix& m2) {
    return m1 + m2;
}

void MatrixController::buildMatrix(unsigned int rows, unsigned int cols, std::initializer_list<double> list) {
    if (matrix != nullptr)
        delete matrix;
    matrix = new Matrix(rows, cols, list);
}

void MatrixController::buildMatrix(unsigned int rows, unsigned int cols) {
    if (matrix != nullptr)
        delete matrix;
    matrix = new Matrix(rows, cols);
}

Matrix& MatrixController::getMatrix() const {
    return *matrix;
}
