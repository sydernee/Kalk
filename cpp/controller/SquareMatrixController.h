#ifndef SQUAREMATRIXCONTROLLER_H
#define SQUAREMATRIXCONTROLLER_H

#include "MatrixController.h"

class SquareMatrixKalk;
class SquareMatrix;

class SquareMatrixController : public MatrixController {
public:
    SquareMatrixController(SquareMatrixKalk* = nullptr, SquareMatrix* = nullptr, SquareMatrix* = nullptr);
    virtual ~SquareMatrixController();

//    Matrix& getMatrix1() const;
//    Matrix& getMatrix2() const;
    void buildMatrix1(QVector<KeypadInput*>, unsigned int, unsigned int);
    void buildMatrix1(unsigned int, unsigned int);
    void setMatrix1(const Matrix&);

    void buildMatrix2(QVector<KeypadInput*>, unsigned int, unsigned int);
    void buildMatrix2(unsigned int, unsigned int);
    void setMatrix2(const Matrix&);

    //operations

    double determinant() const;
    SquareMatrix getMinor(unsigned int, unsigned int) const;
    bool isSupTriangular() const;
    bool isInfTriangular() const;
    bool isDiagonal() const;
};

#endif // SQUAREMATRIXCONTROLLER_H
