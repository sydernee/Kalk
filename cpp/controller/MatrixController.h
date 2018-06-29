#ifndef MATRIXCONTROLLER_H
#define MATRIXCONTROLLER_H

#include <QVector>
//#include <QObject>

class Matrix;
class MatrixCreator;
class KeypadInput;
class SquareMatrix;

class MatrixController //: public QObject
{
    //Q_OBJECT //worth it?

private:
    Matrix* matrix1;
    Matrix* matrix2;
    MatrixCreator* view;
public:
    MatrixController(MatrixCreator* = nullptr, Matrix* = nullptr, Matrix* = nullptr);
    virtual ~MatrixController();

    void buildMatrix1(QVector<KeypadInput*>, unsigned int, unsigned int);  //costruisce matrix1
    void buildMatrix1(unsigned int, unsigned int); //costruisce matrix1 con celle e valori di default
    void setMatrix1(const Matrix&);
    virtual Matrix& getMatrix1() const;

    void buildMatrix2(QVector<KeypadInput*>, unsigned int, unsigned int); //costruisce matrix2
    void buildMatrix2(unsigned int, unsigned int);  //costruisce matrix2 con celle e valori di default
    void setMatrix2(const Matrix&);
    virtual Matrix& getMatrix2() const;

    static void displayMatrix(const Matrix& mat);   //genera l'output in una nuova finestra del parametro

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

    double determinant() const;
    SquareMatrix getMinor(unsigned int, unsigned int) const;
};

#endif // MATRIXCONTROLLER_H
