#include "Matrix.h"

Matrix::Matrix(unsigned int a, unsigned int b) :
    row(a), col(b), matrix(row * col) {}

Matrix::Matrix(unsigned int a, unsigned int b, double val) :
    row(a), col(b), matrix(row * col, val) {}

//  se la lista di inizializzazione è troppo grande, i dati extra vengono ignorati
//  se troppo piccola, i restanti dati rimangono inizializzati a 0    
Matrix::Matrix(unsigned int a, unsigned int b, std::initializer_list<double> l) :
    row(a), col(b), matrix(row * col, 0) {
    unsigned int tableSize = a*b;
    unsigned int numEle = (tableSize > l.size()) ? l.size() : tableSize;
    
    copy(l.begin(), std::next(l.begin(),numEle), matrix.begin());
}

Matrix::~Matrix() {}

Matrix::Matrix(const Matrix& mat) :
    row(mat.getRow()), col(mat.getCol()), matrix(mat.matrix) {}

Matrix& Matrix::operator =(const Matrix& mat) {
    if (this != &mat) {
        col = mat.col;
        row = mat.row;
        matrix = mat.matrix;

    }
    return *this;
}

//getter methods

unsigned int Matrix::getRow() const {
    return row;
}

unsigned int Matrix::getCol() const {
    return col;
}

//OPERATORI

//somma
Matrix operator +(const Matrix& mat1, const Matrix& mat2) { //THROW
    if (mat1.getRow() != mat2.getRow() || mat1.getCol() != mat2.getCol()) {
        //throw MatrixException();
    }

    Matrix res(mat1.getRow(), mat1.getCol());
    for (unsigned int i = 0; i < mat1.getRow(); i++)
        for (unsigned int j = 0; j < mat1.getCol(); j++)
            res.set(i,j, mat1.get(i,j) + mat2.get(i,j));
    return res;
}

//differenza
Matrix operator -(const Matrix& mat1, const Matrix& mat2) { //THROW
    if (mat1.getRow() != mat2.getRow() || mat1.getCol() != mat2.getCol()) {
        //throw MatrixException();
    }

    Matrix res(mat1.getRow(), mat1.getCol());
    for (unsigned int i = 0; i < mat1.getRow(); i++)
        for (unsigned int j = 0; j < mat1.getCol(); j++)
            res.set(i,j, mat1.get(i,j) - mat2.get(i,j));
    return res;
}

//prodotto per uno scalare
Matrix Matrix::operator *(double value) const {
    Matrix res(row, col);
    for (unsigned int i = 0; i < row; i++)
        for (unsigned int j = 0; j < col; j++)
            res.set(i,j, get(i,j) * value);

    return res;
}

//Prodotto scalare
Matrix operator *(const Matrix& mat1, const Matrix& mat2) { //THROW
    if (mat1.getCol() != mat2.getRow()) {
        //throw MatrixException();
     }

    Matrix res(mat1.getRow(), mat2.getCol());
    for (unsigned int i = 0; i < mat1.getRow(); i++)
        for (unsigned int j = 0; j < mat2.getCol(); j++) {
            double sum = 0; //accumulatore
            for (unsigned int k = 0; k < mat1.getCol(); k++)
                sum += mat1.get(i,k) * mat2.get(k, j);
            res.set(i,j, sum);
    }
    return res;
}

//trasposta
Matrix* Matrix::transposed() const {
    Matrix* res = new Matrix(col, row);
    for (unsigned int i = 0; i < col; i++)
        for (unsigned int j = 0; j < row; j++)
            res->set(i,j, get(j,i));
    return res;
}


//operatori booleani di confronto

bool Matrix::operator ==(const Matrix& mat) const {
    if (getRow() != mat.getRow() || getCol() != mat.getCol())
        return false;

    for (unsigned int i = 0; i < getRow(); i++)
        for (unsigned int j = 0; j < getCol(); j++)
            if (get(i,j) != mat.get(i,j))
                return false;
    return true;
}

bool Matrix::operator !=(const Matrix& mat) const {
    return !(*this == mat);
}

//metodi setter/getter (più efficenti di usare l'operatore di subscripting [][])

double Matrix::get(unsigned int _row, unsigned int _col) const {
    return matrix[_row * col + _col];
}

void Matrix::set(unsigned int _row, unsigned int _col, double val) {
    matrix[_row * col + _col] = val;
}

double& Matrix::getReference(unsigned int _row, unsigned int _col) {
    return matrix[_row * col + _col];
}

const double& Matrix::getReference(unsigned int _row, unsigned int _col) const {
    return matrix[_row * col + _col];
}

//output operator overload
std::ostream& operator<<(std::ostream& out, const Matrix& mat) {
    for (unsigned int i = 0; i < mat.getRow(); i++)
        for (unsigned int j = 0; j < mat.getCol(); j++) {
            out << mat.get(i,j) << " ";
            if (j == (mat.getCol() - 1))
                out << "\n";
        }
    return out;
}

//class Row

Matrix::Row::Row(Matrix& _parent, unsigned int _row) :
    parent(_parent), row(_row) {}

double& Matrix::Row::operator [](unsigned int _col) {
    return parent.getReference(row, _col);
}

//class CRow

Matrix::CRow::CRow(const Matrix& _parent, unsigned int _row) :
    parent(_parent), row(_row) {}

const double& Matrix::CRow::operator [](unsigned int _col) const {
    return parent.getReference(row, _col);
}


//Row e CRow, operator [][]
Matrix::Row Matrix::operator [](unsigned int _row) {
    return Row(*this, _row);
}

Matrix::CRow Matrix::operator [](unsigned int _row) const {
    return CRow(*this, _row);
}

//3 operazioni elementari
void Matrix::swapRows(unsigned int rowA, unsigned int rowB) {
    if (rowA == rowB) { return; } //non ho nulla da scambiare
    for (unsigned int c = 0; c < getCol(); ++c) {
        double aux = get(rowA,c);
        set(rowA,c, get(rowB,c));
        set(rowB,c, aux);
    }
}

void Matrix::swapCols(unsigned int colA, unsigned int colB) {
    if (colA == colB) { return; } //non ho nulla da scambiare
    for (unsigned int r = 0; r < getRow(); ++r) {
        double aux = get(r,colA);
        set(r,colA, get(r,colB));
        set(r,colB, aux);
    }    
}

void Matrix::substituteRow(unsigned int destRow, unsigned int sourceRow, double factor) {
    //if (factor == 0) // eccezione TODO
    if (sourceRow == destRow && factor==1) { return; } //non ho nulla da scambiare
    for (unsigned int c = 0; c < getCol(); ++c) {
        set(destRow,c, get(sourceRow,c) * factor);
    }
}
