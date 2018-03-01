#ifndef MATRIX_H
#define MATRIX_H

#include "../DataType.h"
#include <vector>
#include <iostream>
#include <initializer_list>
//#include <iterator>

class Matrix : public DataType {

private:
    unsigned int row, col;
    std::vector<double> matrix; //1 dimensione, visto in 2 dimensioni in fase di implementazione

    class Row { //classe proxy per poter utilizzare l'operatore [][]
        friend class Matrix;

    private:
        Row(Matrix&, unsigned int); //costruttore privato, non è di interesse dell'utente istanziare oggetti Row
        Matrix& parent;
        unsigned int row;

    public:
        double& operator[](unsigned int);
    };

    class CRow { //versione costante di Row
        friend class Matrix;

    private:
        CRow(const Matrix&, unsigned int); //costruttore privato, non è di interesse dell'utente istanziare oggetti Row
        const Matrix& parent;
        unsigned int row;

    public:
        const double& operator[](unsigned int) const;
    };
    
    double& getReference(unsigned int, unsigned int);
    const double& getReference(unsigned int _row, unsigned int _col) const;
    
public:
    Matrix(unsigned int, unsigned int);
    Matrix(unsigned int, unsigned int, double); //costruttore che inizializza tutti i campi al valore passato come parametro
    Matrix(unsigned int, unsigned int, std::initializer_list<double>);

    void fill(double, double = 0); 

    virtual ~Matrix();
    Matrix(const Matrix&); 
    Matrix& operator=(const Matrix&); 

    unsigned int getRow() const; //matrix length
    unsigned int getCol() const; //matrix height

    Matrix operator *(double) const; //prodotto per uno scalare
    Matrix* transposed() const; //trasposta della matrice di invocazione
    
    //operatori booleani
    bool operator==(const Matrix&) const;
    bool operator!=(const Matrix&) const;

    virtual double get(unsigned int, unsigned int) const;
    virtual void set(unsigned int, unsigned int, double);

    Row operator[](unsigned int);
   CRow operator[](unsigned int) const;
};

std::ostream& operator<<(std::ostream&, const Matrix&); //output operator overload

Matrix operator +(const Matrix&, const Matrix&); //somma tra matrici
Matrix operator -(const Matrix&, const Matrix&); //differenza tra matrici
Matrix operator *(const Matrix&, const Matrix&); //prodotto scalare tra matrici

#endif // MATRIX_Hs
