#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "Matrix.h"
#include <QVector>

class SparseMatrix : public Matrix {
private:
    mutable bool dirtyBit;      //usato per ricordare se è necessario modificare sparsity
    mutable double sparsity;    //-1 in fase di costruzione per migliorare l'efficienza,
                                // assegnato solo in caso venga richiesto
protected:
    double& getReference(unsigned int row, unsigned int col) override;

public:
    SparseMatrix(unsigned int numRows, unsigned int numCols);
    SparseMatrix(unsigned int numRows, unsigned int numCols, std::initializer_list<double> list);
    SparseMatrix(unsigned int numRows, unsigned int numCols, QVector<std::initializer_list<double>> list);

    SparseMatrix(const SparseMatrix& mat);            //costruttore di copia
    SparseMatrix& operator=(const SparseMatrix& mat); //overload operatore di assegnazione

    //setta a zero tutte le celle della matrice
    void clear(); //chiama fill() che è virtuale, non c'è bisogno del virtual

    void set(unsigned int row, unsigned int col, double value) override;
    virtual double getSparsity() const; //restituisce la sparsità della matrice
    virtual bool isDense() const;       //la matrice è densa (50+% celle != 0)?

    SparseMatrix operator*(double) const; //moltiplicazione non scalare

    //restituisce un QVector con tutti gli elementi diversi da zero nella riga i
    virtual QVector<double> nonZeroRow(unsigned int i) const;

    //restituisce un QVector con tutti gli elementi diversi da zero nella colonna i
    virtual QVector<double> nonZeroCol(unsigned int i) const;

    void swapRows(unsigned int rowA,unsigned int rowB) override;
    void swapCols(unsigned int colA, unsigned int colB) override;
    void substituteRow(unsigned int destRow, unsigned int sourceRow, double value) override;
};

SparseMatrix operator+(const SparseMatrix& mat1, const SparseMatrix& mat2);
SparseMatrix operator-(const SparseMatrix& mat1, const SparseMatrix& mat2);
SparseMatrix operator*(const SparseMatrix& mat1, const SparseMatrix& mat2);

#endif // SPARSEMATRIX_H
