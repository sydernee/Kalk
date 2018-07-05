#ifndef SPARSEMATRIXCONTROLLER_H
#define SPARSEMATRIXCONTROLLER_H

#include "MatrixController.h"

class SparseMatrixController : public MatrixController {
public:
    SparseMatrixController(/*MatrixKalk* = nullptr, */Matrix* = nullptr, Matrix* = nullptr);

    void buildMatrix(const QVector<KeypadInput*>&, unsigned int, unsigned int, int whichMatrix = 1) override;
    void buildMatrix(unsigned int, unsigned int, int whichMatrix = 1) override;
    void setMatrix(const Matrix&, int whichMatrix = 1) override;

//    void buildMatrix2(QVector<KeypadInput*>, unsigned int, unsigned int);
//    void buildMatrix2(unsigned int, unsigned int);
//    void setMatrix2(const Matrix&);

    //sparse operations
    virtual double getSparsity() const;
    virtual bool isDense() const;
    virtual QVector<double> nonZeroRow(unsigned int) const;
    virtual QVector<double> nonZeroCol(unsigned int) const;
};

#endif // SPARSEMATRIXCONTROLLER_H
