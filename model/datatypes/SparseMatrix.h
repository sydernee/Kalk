#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "Matrix.h"

class SparseMatrix : public Matrix {
private:
    bool dirtyBit;
    double sparsity; //-1 in fase di costruzione per migliorare l'efficienza,
                     // assegnato solo in caso venga richiesto

public:
    SparseMatrix(unsigned int, unsigned int);

    void clear(); //setta a zero tutte le celle della matrice
    double getSparsity(); //restituisce la sparsità della matrice
    bool isSymmetric() const;
    bool isDense();
    virtual double& get(unsigned int, unsigned int); //override, cambia il dirty bit
};

#endif // SPARSEMATRIX_H
