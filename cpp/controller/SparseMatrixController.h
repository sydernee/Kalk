#ifndef SPARSEMATRIXCONTROLLER_H
#define SPARSEMATRIXCONTROLLER_H

#include "MatrixController.h"

class SparseMatrixController : public MatrixController {
public:
    SparseMatrixController(Matrix* = nullptr, Matrix* = nullptr);

    //matrix2 if whichMatrix=2, matrix2 else
    void buildMatrix(const QVector<KeypadInput*>&, unsigned int, unsigned int, int whichMatrix = 1) override;
    void buildMatrix(unsigned int, unsigned int, int whichMatrix = 1) override;
    void setMatrix(const Matrix&, int whichMatrix = 1) override;

    //sparse operations
    virtual double getSparsity() const;
    virtual bool isDense() const;
    virtual QVector<double> nonZeroRow(unsigned int) const;
    virtual QVector<double> nonZeroCol(unsigned int) const;
};

#endif // SPARSEMATRIXCONTROLLER_H
