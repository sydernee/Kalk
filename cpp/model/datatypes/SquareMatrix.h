#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "Matrix.h"

class SquareMatrix : public Matrix {
public:
    SquareMatrix(unsigned int);
    SquareMatrix(unsigned int, double);
    SquareMatrix(const SquareMatrix&);
    SquareMatrix(unsigned int, std::initializer_list<double>);
    SquareMatrix getMinor(unsigned int, unsigned int) const;
    SquareMatrix* transposed() const; //trasposta della matrice di invocazione
    double determinant() const; //calcola e restituisce il determinante
    bool supTriangular() const;
    bool infTriangular() const;
    bool isDiagonal() const;

    static SquareMatrix identityMatrix(unsigned int);
    static SquareMatrix zeroMatrix(unsigned int);
};

#endif // SQUAREMATRIX_H
