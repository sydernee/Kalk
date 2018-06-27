#ifndef MATRIXCONTROLLER_H
#define MATRIXCONTROLLER_H

#include <QVector>
//#include <QObject>

class Matrix;
class MatrixCreator;
class KeypadInput;

class MatrixController //: public QObject
{
    //Q_OBJECT //worth it?

private:
    Matrix* matrix1;
    Matrix* matrix2;
    MatrixCreator* view;
public:
    MatrixController(MatrixCreator* = nullptr, Matrix* = nullptr, Matrix* = nullptr);
    ~MatrixController();

    void buildMatrix1(QVector<KeypadInput*>, unsigned int, unsigned int);  //costruisce matrix1
    void buildMatrix1(unsigned int, unsigned int); //costruisce matrix1 con celle e valori di default
    void setMatrix1(const Matrix&);
    Matrix& getMatrix1() const;

    void buildMatrix2(QVector<KeypadInput*>, unsigned int, unsigned int); //costruisce matrix2
    void buildMatrix2(unsigned int, unsigned int); //costruisce matrix2 con celle e valori di default
    void setMatrix2(const Matrix&);
    Matrix& getMatrix2() const;

    static void displayMatrix(const Matrix& mat);

    //operations

    static Matrix sum(const Matrix&, const Matrix&);
    Matrix sum() const;

    static Matrix subtract(const Matrix&, const Matrix&);
    Matrix subtract() const;

    //static
    Matrix scalarMultiply() const;
};

#endif // MATRIXCONTROLLER_H
