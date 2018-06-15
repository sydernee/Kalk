#include "MatrixController.h"
#include "../model/datatypes/Matrix.h"
#include "../view/MatrixCreator.h"

MatrixController::MatrixController(MatrixCreator* _view, Matrix* _model)
    : view(_view),
      matrix(_model) //copia di puntatori
{}

Matrix MatrixController::sum(const Matrix& m1, const Matrix& m2) {
    return m1 + m2;
}
