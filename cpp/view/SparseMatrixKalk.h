#ifndef SPARSEMATRIXKALK_H
#define SPARSEMATRIXKALK_H

#include "MatrixCreator.h"


class SparseMatrixKalk : public MatrixCreator {
    Q_OBJECT
private:
    QDialog* nonZeroDialog;
    QSpinBox* nonZeroSpinBox;

    void insertSparseOperations();
public:
    explicit SparseMatrixKalk(MatrixController*, QWidget* parent = nullptr);
    ~SparseMatrixKalk();

public slots:
    virtual void handleGetSparsity();
    virtual void handleIsDense();
    virtual void handleNonZeroRow();
    virtual void handleNonZeroCol();
    void handleSparseMatrixObtainResult();
};

#endif // SPARSEMATRIXKALK_H
