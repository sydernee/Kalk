#ifndef MATRIXCONTROLLER_H
#define MATRIXCONTROLLER_H

class Matrix;
class MatrixCreator;

class MatrixController
{
private:
    Matrix* matrix;
    MatrixCreator* view;
public:
    MatrixController(MatrixCreator* = nullptr, Matrix* = nullptr);
    static Matrix sum(const Matrix&, const Matrix&);
};

#endif // MATRIXCONTROLLER_H
