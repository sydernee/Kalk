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

    void insertSquareOperations();
public:
    enum Operation {
        DETERMINANT
    };

    explicit SquareMatrixKalk(MatrixController*, QWidget *parent = nullptr);
    ~SquareMatrixKalk();

//    virtual void buildDimensionsGroupBox();
//    virtual void buildOperationsSet();

//    virtual void resetDimensionsGroupBox();
signals:

public slots:
    virtual void handleSelectDimensions();
    virtual void handleSelectSecondMatrixDimensions();

    //operations slots
    virtual void scalarMultiplicationClicked();
    virtual void handleDeterminant();
    virtual void handleGetMinor();
    void handleSquareMatrixObtainResult();
};

#endif // SQUAREMATRIXKALK_H
