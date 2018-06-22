#ifndef MATRIXCONTROLLER_H
#define MATRIXCONTROLLER_H

#include <QVector>

class Matrix;
class MatrixCreator;
class KeypadInput;

class MatrixController
{
private:
    Matrix* matrix;
    MatrixCreator* view;
public:
    MatrixController(MatrixCreator* = nullptr, Matrix* = nullptr);
    ~MatrixController();

    void buildMatrix(QVector<KeypadInput*>, unsigned int, unsigned int);
    void buildMatrix(unsigned int, unsigned int);
    Matrix& getMatrix() const;

    static Matrix sum(const Matrix&, const Matrix&);
};

#endif // MATRIXCONTROLLER_H
