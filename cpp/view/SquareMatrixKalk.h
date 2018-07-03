#ifndef SQUAREMATRIXKALK_H
#define SQUAREMATRIXKALK_H

#include "MatrixKalk.h"

class SquareMatrixKalk : public MatrixKalk
{
    Q_OBJECT
private:
    QDialog* minorDialog;
    QSpinBox* minorX;
    QSpinBox* minorY;

    void insertSquareOperations(); //aggiunge le operazioni di SquareMatrix a operationsSet

public:
    explicit SquareMatrixKalk(MatrixController*, QWidget *parent = nullptr);

signals:

public slots:
    virtual void handleSelectDimensions();
    virtual void handleSelectSecondMatrixDimensions();

    //operations slots
    virtual void scalarMultiplicationClicked();
    virtual void handleDeterminant();
    virtual void handleGetMinor();
    virtual void handleIsSymmetric();
    virtual void handleSupTriangular();
    virtual void handleInfTriangular();
    virtual void handleIsDiagonal();
    void handleSquareMatrixObtainResult();
};

#endif // SQUAREMATRIXKALK_H
