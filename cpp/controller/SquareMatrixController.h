#ifndef SQUAREMATRIXCONTROLLER_H
#define SQUAREMATRIXCONTROLLER_H

#include "MatrixController.h"

class SquareMatrixKalk;
class SquareMatrix;

class SquareMatrixController : public MatrixController {
public:
    SquareMatrixController(/*MatrixKalk* = nullptr, */Matrix* = nullptr, Matrix* = nullptr);

    void buildMatrix(const QVector<KeypadInput*>&, unsigned int, unsigned int, int whichMatrix = 1) override;
    void buildMatrix(unsigned int, unsigned int, int whichMatrix = 1) override;
    void setMatrix(const Matrix&, int whichMatrix = 1) override;

//    void buildMatrix2(QVector<KeypadInput*>, unsigned int, unsigned int);
//    void buildMatrix2(unsigned int, unsigned int);
//    void setMatrix2(const Matrix&);

    //operations

    virtual double determinant() const;
    SquareMatrix getMinor(unsigned int, unsigned int) const;
    virtual bool isSupTriangular() const;
    virtual bool isInfTriangular() const;
    virtual bool isDiagonal() const;
    virtual bool isSymmetric() const;
};

#endif // SQUAREMATRIXCONTROLLER_H
