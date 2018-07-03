#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "Matrix.h"

class SquareMatrix : public Matrix {
public:
    SquareMatrix(unsigned int);
    SquareMatrix(unsigned int, double);
    SquareMatrix(const SquareMatrix&);
    SquareMatrix(const Matrix&);
    SquareMatrix(unsigned int, std::initializer_list<double>);
    SquareMatrix(unsigned int, std::vector<std::initializer_list<double>>);
    SquareMatrix getMinor(unsigned int, unsigned int) const;
    SquareMatrix* transposed() const; //trasposta della matrice di invocazione
    double determinant() const; //calcola e restituisce il determinante
    bool supTriangular() const;
    bool infTriangular() const;
    bool isDiagonal() const;
    bool isSymmetric() const;

    SquareMatrix operator*(double) const;

    static SquareMatrix identityMatrix(unsigned int);
    static SquareMatrix zeroMatrix(unsigned int);
};

SquareMatrix operator+(const SquareMatrix&, const SquareMatrix&);
SquareMatrix operator-(const SquareMatrix&, const SquareMatrix&);
SquareMatrix operator*(const SquareMatrix&, const SquareMatrix&);

#endif // SQUAREMATRIX_H
