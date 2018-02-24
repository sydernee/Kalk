#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "matrix.h"

class SquareMatrix : public Matrix {
public:
    SquareMatrix(unsigned int);
    SquareMatrix(unsigned int, double);
    SquareMatrix(const SquareMatrix&);
    double det() const; //calcola e restituisce il determinante
    bool supTriangular() const;
    bool infTriangular() const;
    bool isDiagonal() const;

    SquareMatrix diagonalMatrix(unsigned int);

    static SquareMatrix identityMatrix(unsigned int);
};

#endif // SQUAREMATRIX_H
