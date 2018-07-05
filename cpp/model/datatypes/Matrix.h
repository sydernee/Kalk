#ifndef MATRIX_H
#define MATRIX_H

#include "../DataType.h"
#include <QVector>
#include <iostream>
#include <initializer_list>

#include "../../exceptions/IndexOutOfBoundsException.h"
#include "../../exceptions/InvalidMatrixIndexes.h"
#include "../../exceptions/ZeroMultiplierException.h"

class Matrix : public DataType {

private:
    unsigned int row, col;
    QVector<double> matrix; //1 dimensione, visto in 2 dimensioni in fase di implementazione

    //classe proxy per poter utilizzare l'operatore [][]
    class Row {
        friend class Matrix;

    private:
        Row(Matrix&, unsigned int); //costruttore privato, non è di interesse dell'utente istanziare oggetti Row
        Matrix& parent;
        unsigned int row;

    public:
        double& operator[](unsigned int);
    };

    //versione costante di Row
    class CRow {
        friend class Matrix;

    private:
        CRow(const Matrix&, unsigned int); //costruttore privato, non è di interesse dell'utente istanziare oggetti Row
        const Matrix& parent;
        unsigned int row;

    public:
        const double& operator[](unsigned int) const;
    };
    
    const double& getReference(unsigned int _row, unsigned int _col) const; //restituisce un riferimento costante alla cella [_row][_col]

protected:
    virtual double& getReference(unsigned int _row, unsigned int _col); //restituisce un riferimento alla cella [_row][_col]

public:
    Matrix(unsigned int numRows, unsigned int numCols);
    Matrix(unsigned int numRows, unsigned int numCols, double value); //costruttore che inizializza tutti i campi al valore passato come parametro
    Matrix(unsigned int numRows, unsigned int numCols, std::initializer_list<double> list); //permette una costruzione e.g. Matrix(2,3, {1,2,1,...,2})
    Matrix(unsigned int numRows, unsigned int numCols, QVector<std::initializer_list<double>> list); //permette una costruzione e.g. Matrix(2,3, {1,2,1}, {2,2,3}})

    virtual void fill(double value, double range = 0); //assegna ad ogni cella value+i*range, i in [0,n[

    Matrix(const Matrix& mat);            //costruttore di copia
    Matrix& operator=(const Matrix& mat); //assegnazione profonda

    virtual unsigned int rowCount() const; //matrix length
    virtual unsigned int colCount() const; //matrix height

    Matrix operator *(double) const; //prodotto per uno scalare
    virtual Matrix* transposed() const; //trasposta della matrice di invocazione
    
    //operatori booleani
    virtual bool operator==(const Matrix& mat) const; //uguaglianza tra due matrici
    virtual bool operator!=(const Matrix& mat) const; //disuguaglianza tra due matrici

    virtual double get(unsigned int _row, unsigned int _col) const; //restituisce il valore della cella [_row][_col]
    virtual void set(unsigned int _row, unsigned int _col, double value); //imposta la cella [_row][_col] a value

    Row operator[](unsigned int);
   CRow operator[](unsigned int) const;
   
   //3 operazioni elementari
   virtual void swapRows(unsigned int rowA, unsigned int rowB); //scambia le righe rowA e rowB
   virtual void swapCols(unsigned int colA, unsigned int colB); //scambia le colonne colA e colB

   //somma alla riga destRow la riga sourceRow moltiplicata per value (!= 0)
   virtual void substituteRow(unsigned int destRow, unsigned int sourceRow, double value);
};

std::ostream& operator<<(std::ostream& out, const Matrix& mat); //output operator overload

Matrix operator +(const Matrix& mat1, const Matrix& mat2); //somma tra matrici
Matrix operator -(const Matrix& mat1, const Matrix& mat2); //differenza tra matrici
Matrix operator *(const Matrix& mat1, const Matrix& mat2); //prodotto scalare tra matrici

#endif // MATRIX_H
