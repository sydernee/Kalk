#ifndef MATRIXCONTROLLER_H
#define MATRIXCONTROLLER_H

#include <QVector>

#include "../exceptions/InvalidMatrixTypeException.h"
#include "../exceptions/NullPointerException.h"
#include "../exceptions/IndexOutOfBoundsException.h"

#include "../model/datatypes/Matrix.h"
#include "../model/datatypes/SquareMatrix.h"
#include "../view/KeypadInput.h"


class MatrixController
{
private:
    Matrix* matrix1;
    Matrix* matrix2;

public:
    MatrixController(Matrix* = nullptr, Matrix* = nullptr);
    virtual ~MatrixController();

    //matrix2 if whichMatrix=2, matrix2 else
    virtual void buildMatrix(const QVector<KeypadInput*>&, unsigned int, unsigned int, int whichMatrix = 1);  //costruisce matrix1
    virtual void buildMatrix(unsigned int, unsigned int, int whichMatrix = 1); //costruisce matrix1 con celle e valori di default
    virtual void setMatrix(const Matrix&, int whichMatrix = 1);
    virtual Matrix*& getMatrix(int whichMatrix = 1);
    virtual Matrix* getMatrix(int whichMatrix = 1) const;

    static void displayMatrix(const Matrix& mat, const QString& = "");   //genera l'output in una nuova finestra del parametro

    //operations

    static Matrix sum(const Matrix&, const Matrix&);    //somma statica tra due matrici passate come parametri
    Matrix sum() const;                                 //somma tra matrix1 e matrix2

    static Matrix subtract(const Matrix&, const Matrix&);
    Matrix subtract() const;

    //static
    Matrix scalarMultiply() const;

    Matrix nonScalarMultiply(double) const;

    Matrix transposed() const;
    Matrix swapRows(unsigned int, unsigned int);
    Matrix swapCols(unsigned int, unsigned int);
    Matrix substituteRow(unsigned int, unsigned int, double);
};

#endif // MATRIXCONTROLLER_H
