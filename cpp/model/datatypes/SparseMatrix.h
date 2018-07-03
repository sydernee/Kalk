#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "Matrix.h"
#include <QVector>

class SparseMatrix : public Matrix {
private:
    mutable bool dirtyBit;      //usato per ricordare se è necessario modificare sparsity
    mutable double sparsity;    //-1 in fase di costruzione per migliorare l'efficienza,
                                // assegnato solo in caso venga richiesto
public:
    SparseMatrix(unsigned int, unsigned int);
    SparseMatrix(const SparseMatrix&);
    SparseMatrix(unsigned int, unsigned int, std::initializer_list<double>);
    SparseMatrix(unsigned int, unsigned int, std::vector<std::initializer_list<double>>);

    virtual void set(unsigned int, unsigned int, double);
    void clear(); //setta a zero tutte le celle della matrice
    double getSparsity() const; //restituisce la sparsità della matrice
    bool isSymmetric() const;
    bool isDense() const;

    QVector<double> nonZeroRow(unsigned int) const;
    QVector<double> nonZeroCol(unsigned int) const;
};

#endif // SPARSEMATRIX_H
