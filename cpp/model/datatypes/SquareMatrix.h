#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "Matrix.h"

class SquareMatrix : public Matrix {
public:
    SquareMatrix(unsigned int dimension);
    SquareMatrix(unsigned int dimension, double value);
    SquareMatrix(unsigned int dimension, std::initializer_list<double> list);
    SquareMatrix(unsigned int dimension, QVector<std::initializer_list<double>> list);

    SquareMatrix(const SquareMatrix& mat); //costruttore di copia profondo
    SquareMatrix& operator=(const SquareMatrix& mat); //assegnazione profonda

    /*restituisce una SquareMatrix con dimension=dimension-1 a cui sono state eliminate
     la riga _row e la riga _col */
    virtual SquareMatrix getMinor(unsigned int _row, unsigned int _col) const;

    SquareMatrix* transposed() const override; //trasposta della matrice di invocazione
    virtual double determinant() const; //calcola e restituisce il determinante
    virtual bool supTriangular() const; //è triangolare superiore?
    virtual bool infTriangular() const; //è triangolare inferiore?
    virtual bool isDiagonal() const;    //è matrice diagonale?
    virtual bool isSymmetric() const;   //è simmetrica?

    SquareMatrix operator*(double value) const; //prodotto non scalare

    static SquareMatrix identityMatrix(unsigned int dim); //restituisce una matrice identità di dimension = dim
    static SquareMatrix zeroMatrix(unsigned int dim);
};

SquareMatrix operator+(const SquareMatrix& mat1, const SquareMatrix& mat2);
SquareMatrix operator-(const SquareMatrix& mat1, const SquareMatrix& mat2);
SquareMatrix operator*(const SquareMatrix& mat1, const SquareMatrix& mat2);

#endif // SQUAREMATRIX_H
