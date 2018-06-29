#ifndef MATRIXCREATOR_H
#define MATRIXCREATOR_H

#include "../controller/MatrixController.h"
#include "../view/KeypadInput.h"
#include "../model/datatypes/Matrix.h"

#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QWidget>
#include <QDialog>
#include <QGroupBox>
#include <QPushButton>
#include <cfloat>

class MatrixCreator : public QWidget
{
    Q_OBJECT
public:
    enum Operation {
        SUM,
        SUBTRACTION,
        SCALAR_MULTIPLICATION,
        NON_SCALAR_MULTIPLICATION,
        SWAP_ROWS,
        SWAP_COLS,
        SUBSTITUTE_ROW,
        DETERMINANT,
        GET_MINOR
    };

private:

    //set di operazioni
    QGroupBox* dimensionsGroupBox;  //QGroupBox per il box della selezione delle dimensioni
    QGroupBox* matrixBuilder;       //QGroupBox per la costruzione della matrice
    QGroupBox* operationsSet;       //QGroupBox per il set di operazioni

    QLabel* selectDimensionsLabel;  //label per la selezione delle dimensione
    QLabel* selectSecondMatrixLabel;//label per l'istanziazione della seconda matrice
    QSpinBox* rowBox;               //box per row
    QSpinBox* colBox;               //box per col
    QPushButton* selectDimensions;  //pulsante per accettare la selezione delle dimensioni
    QPushButton* selectSecondMatrixDimensions; //pulsante per la selezione della seconda matrice
    QPushButton* obtainResult;      //pulsante per =

    //nonScalarMultiplication fields
    QDialog* nonScalarMulDialog;    //QDialog per ottenere l'input per la moltiplicazione non scalare
    KeypadInput* nonScalarMulInput; //QLineEdit che contiene il double da moltiplicare alla Matrice con la moltiplicazione non scalare

    //swapRows/Cols fields
    QDialog* swapDialog;            //QDialog per l'input delle operazioni di swap
    QSpinBox* swapFieldA;           //field A delle operazioni di swap
    QSpinBox* swapFieldB;           //field B delle operazioni di swap

    //substituteRow fields
    QDialog* substituteRowDialog; //QDialog per substituteRow
    QSpinBox* subRowA;
    QSpinBox* subRowB;
    KeypadInput* subRowDouble;

    QVector<KeypadInput*> cells;    //vettore che contiene le celle di matrixBuilder

    Operation operationSelected;

protected:
    MatrixController* controller;   //controller Matrix - MatrixCreator

public:
    explicit MatrixCreator(MatrixController*, QWidget *parent = nullptr);
    ~MatrixCreator();

    //costruisce i pulsanti per le dimensioni e restituisce il layout
    void buildDimensionsGroupBox();

    //costruisce il set di pulsanti per le operazioni
    void buildOperationsSet();



    void clearCells(); //delete cells[i] per ogni i in 0..n-1 e svuota cells
    void resetCells(); //cells[i]->setText("") per ogni i in 0..n-1

    //resetta dimensionsGroupBox
    virtual void resetDimensionsGroupBox();

    //resetta e inizializza matrixBuilder
    void initializeMatrixBuilder();

    //set dei QSpinBox per le dimensioni
    //0,2,3 parametri (min,max,default)
    void setRowBox(unsigned int, unsigned int, unsigned int = 2);
    void setRowBox();
    void setColBox(unsigned int, unsigned int, unsigned int = 2);
    void setColBox();
    static void setSpinBoxLimits(QSpinBox*, unsigned int, unsigned int, unsigned int = 0);

protected:
    //setters
    void setDimensionsGroupBox(QGroupBox*);
    void setSelectDimensions(QPushButton*);
    void setSelectSecondMatrixDimensions(QPushButton*);
    void setSelectDimenionsLabel(QLabel*);
    void setObtainResult(QPushButton*);
    void setRowBox(QSpinBox*);
    void setColBox(QSpinBox*);
    void setMatrixBuilder(QGroupBox*);
    void setOperationsSet(QGroupBox*);
    void setOperationSelected(MatrixCreator::Operation);

    //getters
    QGroupBox* getDimensionsGroupBox() const;
    QPushButton* getSelectDimensions() const;
    QPushButton* getSelectSecondMatrixDimensions() const;
    QLabel* getSelectDimensionsLabel() const;
    QLabel* getSelectSecondMatrixLabel() const;
    QPushButton* getObtainResult() const;
    QSpinBox* getRowBox() const;
    QSpinBox* getColBox() const;
    QGroupBox* getMatrixBuilder() const;
    QGroupBox* getOperationsSet() const;
    QVector<KeypadInput*> getCells() const;
    Operation getOperationSelected() const;

signals:
//    void nonScalarMulSignal(double);
//    void buildMatrixSignal(const Matrix&);

public slots:
    virtual void handleSelectDimensions(); //virtual?
    virtual void handleSelectSecondMatrixDimensions();

//    void handleBuildMatrixButton();
    void handleObtainResult();

    //operations slots
    virtual void sumClicked();
    virtual void subtractionClicked();
    virtual void scalarMultiplicationClicked();
    virtual void nonScalarMultiplicationClicked();
    virtual void transposedClicked();
    virtual void swapRowsClicked();
    virtual void swapColsClicked();
    virtual void substituteRowClicked();
};

#endif // MATRIXCREATOR_H
