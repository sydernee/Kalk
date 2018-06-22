#include "MatrixController.h"
#include "../model/datatypes/Matrix.h"
#include "../view/MatrixCreator.h"
#include "../view/KeypadInput.h"

MatrixController::MatrixController(MatrixCreator* _view, Matrix* _model)
    : matrix(_model), //copia di puntatori
      view(_view)
{}

MatrixController::~MatrixController() {
    //delete Matrix;
}

Matrix MatrixController::sum(const Matrix& m1, const Matrix& m2) {
    return m1 + m2;
}

void MatrixController::buildMatrix(QVector<KeypadInput*> cells, unsigned int rows, unsigned int cols) {
    if (matrix != nullptr)
        delete matrix;

    matrix = new Matrix(rows, cols);
    for (unsigned int i = 0; i < rows; i++)
        for (unsigned int j = 0; j < cols; j++)
            matrix->set(i,j,cells[i*j+j]->text().toDouble());
}

void MatrixController::buildMatrix(unsigned int rows, unsigned int cols) {
    if (matrix != nullptr)
        delete matrix;
    matrix = new Matrix(rows, cols);
}

Matrix& MatrixController::getMatrix() const {
    return *matrix;
}
