#ifndef SQUAREMATRIXCONTROLLER_H
#define SQUAREMATRIXCONTROLLER_H

#include "MatrixController.h"

class SquareMatrixKalk;
class SquareMatrix;

class SquareMatrixController : public MatrixController {
public:
    SquareMatrixController(Matrix* = nullptr, Matrix* = nullptr);

    //matrix2 if whichMatrix=2, matrix2 else
    void buildMatrix(const QVector<KeypadInput*>&, unsigned int, unsigned int, int whichMatrix = 1) override;
    void buildMatrix(unsigned int, unsigned int, int whichMatrix = 1) override;
    void setMatrix(const Matrix&, int whichMatrix = 1) override;

    //operations

    virtual double determinant() const;
    SquareMatrix getMinor(unsigned int, unsigned int) const;
    virtual bool isSupTriangular() const;
    virtual bool isInfTriangular() const;
    virtual bool isDiagonal() const;
    virtual bool isSymmetric() const;
};

#endif // SQUAREMATRIXCONTROLLER_H
