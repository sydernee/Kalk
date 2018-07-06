#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(unsigned int a, unsigned int b) :
    Matrix(a, b, 0), dirtyBit(false), sparsity(-1) {}
    
SparseMatrix::SparseMatrix(const SparseMatrix& mat) :
    Matrix(mat), dirtyBit(-1), sparsity(-1) {}

SparseMatrix::SparseMatrix(unsigned int a, unsigned int b, std::initializer_list<double> l) :
	Matrix(a, b, l), dirtyBit(false), sparsity(-1) {}

SparseMatrix::SparseMatrix(unsigned int a, unsigned int b, QVector<std::initializer_list<double>> l) :
    Matrix(a, b, l), dirtyBit(false), sparsity(-1) {}

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& mat) {
    if (this != &mat) {
        sparsity = mat.getSparsity();
        Matrix::operator=(mat);
    }
    return *this;
}

void SparseMatrix::clear() {
    fill(0);
}

double SparseMatrix::getSparsity() const {
    if (!dirtyBit && sparsity != -1)
        return sparsity;

    dirtyBit = false;
    double cumulator = 0;
    for (unsigned int i = 0; i < rowCount(); i++)
        for (unsigned int j = 0; j < colCount(); j++)
            if (get(i,j) == 0)
                cumulator++;
    sparsity = cumulator / static_cast<double>(rowCount() * colCount());
    return sparsity;
}

void SparseMatrix::set(unsigned int _row, unsigned int _col, double value) {
    if (get(_row, _col) != value)
        dirtyBit = true;
    Matrix::set(_row, _col, value);
}

double& SparseMatrix::getReference(unsigned int _row, unsigned int _col) {
    dirtyBit = true;
    return Matrix::getReference(_row, _col);
}

bool SparseMatrix::isDense() const {
    if (getSparsity() <= 0.5)
        return true;
    return false;
}

QVector<double> SparseMatrix::nonZeroRow(unsigned int i) const {
    if (i >= rowCount())
        throw IndexOutOfBoundsException("SparseMatrix::nonZeroRow(): Out of bounds parameter index.");

    QVector<double> res;
    for (unsigned int j = 0; j < colCount(); j++) {
        if (get(i,j) != 0)
            res.append(get(i,j));
    }
    return res;
}

QVector<double> SparseMatrix::nonZeroCol(unsigned int j) const {
    if (j >= colCount())
        throw IndexOutOfBoundsException("SparseMatrix::nonZeroCol(): Out of bounds parameter index.");

    QVector<double> res;
    for (unsigned int i = 0; i < rowCount(); i++) {
        if (get(i,j) != 0)
            res.append(get(i,j));
    }
    return res;
}

//operations overriding

void SparseMatrix::swapRows(unsigned int row, unsigned int col) {
    dirtyBit = true;
    Matrix::swapRows(row, col);
}

void SparseMatrix::swapCols(unsigned int row, unsigned int col) {
    dirtyBit = true;
    Matrix::swapCols(row, col);
}

void SparseMatrix::substituteRow(unsigned int row, unsigned int col, double value) {
    dirtyBit = true;
    Matrix::substituteRow(row, col, value);
}

//somma
SparseMatrix operator +(const SparseMatrix& mat1, const SparseMatrix& mat2) {
    if (mat1.rowCount() != mat2.rowCount() || mat1.colCount() != mat2.colCount())
        throw InvalidMatrixIndexes("SparseMatrix::operator+(): Matrixes must have the same dimensions.");

    SparseMatrix res(mat1.rowCount(), mat1.colCount());
    for (unsigned int i = 0; i < mat1.rowCount(); i++)
        for (unsigned int j = 0; j < mat1.colCount(); j++)
            res.set(i,j, mat1.get(i,j) + mat2.get(i,j));
    return res;
}

//differenza
SparseMatrix operator -(const SparseMatrix& mat1, const SparseMatrix& mat2) {
    if (mat1.rowCount() != mat2.rowCount() || mat1.colCount() != mat2.colCount())
        throw InvalidMatrixIndexes("SparseMatrix::operator-(): Matrixes must have the same dimensions.");

    SparseMatrix res(mat1.rowCount(), mat1.colCount());
    for (unsigned int i = 0; i < mat1.rowCount(); i++)
        for (unsigned int j = 0; j < mat1.colCount(); j++)
            res.set(i,j, mat1.get(i,j) - mat2.get(i,j));
    return res;
}

//Prodotto scalare
SparseMatrix operator *(const SparseMatrix& mat1, const SparseMatrix& mat2) {
    if (mat1.colCount() != mat2.rowCount())
        throw InvalidMatrixIndexes("SparseMatrix::operator*(): mat1.colCount() is not equal to mat2.rowCount().");

    SparseMatrix res(mat1.rowCount(), mat2.colCount());
    for (unsigned int i = 0; i < mat1.rowCount(); i++)
        for (unsigned int j = 0; j < mat2.colCount(); j++) {
            double sum = 0; //accumulatore
            for (unsigned int k = 0; k < mat1.colCount(); k++)
                sum += mat1.get(i,k) * mat2.get(k, j);
            res.set(i,j, sum);
    }
    return res;
}

//prodotto per uno scalare
SparseMatrix SparseMatrix::operator *(double value) const {
    SparseMatrix res(rowCount(), colCount());
    for (unsigned int i = 0; i < rowCount(); i++)
        for (unsigned int j = 0; j < colCount(); j++)
            res.set(i,j, get(i,j) * value);

    return res;
}
