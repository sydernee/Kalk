#include "SquareMatrix.h"

SquareMatrix::SquareMatrix(unsigned int n) :
    Matrix(n, n) {}

SquareMatrix::SquareMatrix(unsigned int n, double val) :
    Matrix(n, n, val) {}

SquareMatrix::SquareMatrix(const SquareMatrix& mat) :
    Matrix(mat) {}

SquareMatrix::SquareMatrix(unsigned int n, std::initializer_list<double> l) :
    Matrix(n, n, l) {}

SquareMatrix::SquareMatrix(unsigned int n, std::vector<std::initializer_list<double>> l) :
    Matrix(n, n, l) {}

bool SquareMatrix::isDiagonal() const {
    for (unsigned int i = 0; i < getRow(); i++)
        for (unsigned int j = 0; j < getCol(); i++)
            if (i != j && get(i,j) != 0)
                return false;
    return true;
}

SquareMatrix SquareMatrix::getMinor(unsigned int x, unsigned int y) const {
    unsigned int N = getCol();
    SquareMatrix res = SquareMatrix(N-1);
    
    unsigned int i,j,resX,resY; //i riga, j colonna di  matrix; 
    i = j = resX = resY = 0;
    while (i < N) {
        if (j == N) {j = 0; ++i; resY = 0; ++resX; continue;}
        if (i == x) { ++i; continue; }
        if (j == y) { ++j; continue; }
        
        res.set(resX, resY, get(i,j));
        
        ++resY; ++j;
    }
    return res;
}

SquareMatrix* SquareMatrix::transposed() const {
    return static_cast<SquareMatrix*>(Matrix::transposed());
}


double SquareMatrix::determinant() const {  
    unsigned int N = getCol();

    if (N == 1)
        return get(0,0);
    if (N == 2)
        return get(0,0) * get(1,1) - get(0,1) * get(1,0);
    if (getCol() == 3) { 
        return get(0,0) * get(1,1) * get(2,2) +
                get(0,1) * get(1,2) * get(2,0) +
                get(0,2) * get(1,0) * get(2,1) -
                get(0,2) * get(1,1) * get(2,0) -
                get(0,1) * get(1,0) * get(2,2) -
                get(0,0) * get(1,2) * get(2,1);
    }     
    
    double res = 0;
    for (unsigned int i = 0; i < N; ++i) {
    	if (get(0,i) != 0) {
    		res += get(0,i) * ((i % 2 == 0) ? 1 : -1) * getMinor(0,i).determinant();
        }
    }
	    
    return res;
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

// Matrice identità
SquareMatrix SquareMatrix::identityMatrix(unsigned int n) {
    SquareMatrix res(n, 0);
    for (unsigned int i = 0; i < n; i++)
        res.set(i,i, 1);
    return res;
}

// Matrice di zeri
SquareMatrix SquareMatrix::zeroMatrix(unsigned int n) {
    return SquareMatrix(n, 0);
}
