#include "squarematrix.h"

SquareMatrix::SquareMatrix(unsigned int n) :
    Matrix(n, n) {}

SquareMatrix::SquareMatrix(unsigned int n, double val) :
    Matrix(n, n, val) {}

SquareMatrix::SquareMatrix(const SquareMatrix& mat) :
    Matrix(mat) {}

bool SquareMatrix::isDiagonal() const {
    for (unsigned int i = 0; i < getRow(); i++)
        for (unsigned int j = 0; j < getCol(); i++)
            if (i != j && get(i,j) != 0)
                return false;
    return true;
}

SquareMatrix SquareMatrix::identityMatrix(unsigned int n) {
    SquareMatrix res(n, 0);
    for (unsigned int i = 0; i < n; i++)
        res.get(i,i) = 1;
    return res;
}

double SquareMatrix::det() const {
    if (getCol() == 2)
        return get(0,0) * get(1,1) - get(0,1) * get(1,0);

    if (getCol() == 3) { //Sarrus rule
        return get(0,0) * get(1,1) * get(2,2) +
                get(0,1) * get(1,2) * get(2,0) +
                get(0,2) * get(1,0) * get(2,1) -
                get(0,2) * get(1,1) * get(2,0) -
                get(0,1) * get(1,0) * get(2,2) -
                get(0,0) * get(1,2) * get(2,1);
    }
    return 0; //n x n?
}

bool SquareMatrix::infTriangular() const {
    for (unsigned int i = 0; i < getRow(); i++)
        for (unsigned int j = 0; j < getCol(); j++)
            if ((i == j && get(i,i) != 1) || (i < j && get(i,j) != 0))
                return false;
    return true;
}

bool SquareMatrix::supTriangular() const {
    for (unsigned int i = 0; i < getRow(); i++)
        for (unsigned int j = 0; j < getCol(); j++)
            if ((i == j && get(i,i) != 1) || (i > j && get(i,j) != 0))
                return false;
    return true;
}
