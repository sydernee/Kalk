#ifndef SQUAREMATRIXKALK_H
#define SQUAREMATRIXKALK_H

#include "MatrixCreator.h"

class SquareMatrixKalk : public MatrixCreator
{
    Q_OBJECT
private:
    QDialog* getMinorDialog;
    QSpinBox* getMinorX;
    QSpinBox* getMinorY;

    void insertSquareOperations(); //aggiunge le operazioni di SquareMatrix a operationsSet

public:
    explicit SquareMatrixKalk(MatrixController*, QWidget *parent = nullptr);
    ~SquareMatrixKalk();
//    virtual void resetDimensionsGroupBox();

signals:

public slots:
    virtual void handleSelectDimensions();
    virtual void handleSelectSecondMatrixDimensions();

    //operations slots
    virtual void scalarMultiplicationClicked();
    virtual void handleDeterminant();
    virtual void handleGetMinor();
    virtual void handleSupTriangular();
    virtual void handleInfTriangular();
    virtual void handleIsDiagonal();
    void handleSquareMatrixObtainResult();
};

#endif // SQUAREMATRIXKALK_H
