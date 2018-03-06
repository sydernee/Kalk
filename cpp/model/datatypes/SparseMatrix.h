#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "Matrix.h"

class SparseMatrix : public Matrix {
private:
    mutable bool dirtyBit;
    mutable double sparsity; //-1 in fase di costruzione per migliorare l'efficienza,
                     // assegnato solo in caso venga richiesto
 
	//getReference() protected?
    virtual double& getReference(unsigned int, unsigned int); //override, cambia il dirty bit
    
public:
    SparseMatrix(unsigned int, unsigned int);
    SparseMatrix(const SparseMatrix&);
    SparseMatrix(unsigned int, unsigned int, std::initializer_list<double>);

    void clear(); //setta a zero tutte le celle della matrice
    double getSparsity() const; //restituisce la sparsità della matrice
    bool isSymmetric() const;
    bool isDense() const;
};

#endif // SPARSEMATRIX_H
