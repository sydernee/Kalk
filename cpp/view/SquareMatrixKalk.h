#ifndef SQUAREMATRIXKALK_H
#define SQUAREMATRIXKALK_H

#include "MatrixKalk.h"

class SquareMatrixKalk : public MatrixKalk
{
    Q_OBJECT
private:
    QDialog* minorDialog;       //QDialog per getMinor()
    QSpinBox* minorX;           //campo row di getMinor()
    QSpinBox* minorY;           //campo col di getMinor()

    void insertSquareOperations();          //aggiunge le operazioni di SquareMatrix a operationsSet
    void buildZeroIdentityMatrixButtons();  //costruisce i pulsanti per Zero e identity matrix

public:
    explicit SquareMatrixKalk(MatrixController*, QWidget *parent = nullptr);

signals:

public slots:
    void handleSelectDimensions() override;
    void handleSelectSecondMatrixDimensions() override;

    //operations slots
    void scalarMultiplicationClicked() override;
    virtual void handleDeterminant();
    virtual void handleGetMinor();
    virtual void handleIsSymmetric();
    virtual void handleSupTriangular();
    virtual void handleInfTriangular();
    virtual void handleIsDiagonal();
    virtual void handleIdentityMatrix();
    virtual void handleZeroMatrix();

    void handleSquareMatrixObtainResult();
};

#endif // SQUAREMATRIXKALK_H
