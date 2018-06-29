#ifndef SQUAREMATRIXCONTROLLER_H
#define SQUAREMATRIXCONTROLLER_H

#include "MatrixController.h"

class SquareMatrixKalk;
class SquareMatrix;

class SquareMatrixController : public MatrixController {
public:
    SquareMatrixController(SquareMatrixKalk* = nullptr, SquareMatrix* = nullptr, SquareMatrix* = nullptr);
//    virtual ~MatrixController();

//    SquareMatrix& getMatrix1() const;
//    SquareMatrix& getMatrix2() const;

    //operations

    SquareMatrix determinant() const;
    SquareMatrix getMinor(unsigned int, unsigned int) const;
};

#endif // SQUAREMATRIXCONTROLLER_H
