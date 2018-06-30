#ifndef SPARSEMATRIXKALK_H
#define SPARSEMATRIXKALK_H

#include "MatrixCreator.h"


class SparseMatrixKalk : public MatrixCreator {
    Q_OBJECT
private:
    void insertSparseOperations();
public:
    explicit SparseMatrixKalk(MatrixController*, QWidget* parent = nullptr);
    ~SparseMatrixKalk();

public slots:
    virtual void handleGetSparsity();
    virtual void handleIsDense();
    virtual void handleIsSymmetric();
};

#endif // SPARSEMATRIXKALK_H
