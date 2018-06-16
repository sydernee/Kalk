#ifndef MATRIXCONTROLLER_H
#define MATRIXCONTROLLER_H

#include <initializer_list>

class Matrix;
class MatrixCreator;

class MatrixController
{
private:
    Matrix* matrix;
    MatrixCreator* view;
public:
    MatrixController(MatrixCreator* = nullptr, Matrix* = nullptr);
    ~MatrixController();

    void buildMatrix(unsigned int, unsigned int, std::initializer_list<double>);
    void buildMatrix(unsigned int, unsigned int);
    Matrix& getMatrix() const;

    static Matrix sum(const Matrix&, const Matrix&);
};

#endif // MATRIXCONTROLLER_H
