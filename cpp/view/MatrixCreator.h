#ifndef MATRIXCREATOR_H
#define MATRIXCREATOR_H

#include <QWidget>
#include <QBoxLayout>

class Matrix;
class KeypadInput;
class QLabel;
class QSpinBox;
class QHBoxLayout;
class QGroupBox;
class QPushButton;
//class NonScalarMulDialog;
class Dialog;
class MatrixController; //controller




class MatrixCreator : public QWidget
{
    Q_OBJECT
public:
    enum Operation {
        SUM,
        SUBTRACTION,
        SCALAR_MULTIPLICATION,
        NON_SCALAR_MULTIPLICATION
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

    QDialog* nonScalarMulDialog;    //QDialog per ottenere l'input per la moltiplicazione non scalare
    KeypadInput* nonScalarMulInput; //QLineEdit che contiene il double da moltiplicare alla Matrice con la moltiplicazione non scalare


    MatrixController* controller;   //controller Matrix - MatrixCreator
    QVector<KeypadInput*> cells;    //vettore che contiene le celle di matrixBuilder

    MatrixCreator::Operation operationSelected;
public:
    explicit MatrixCreator(QWidget *parent = nullptr);
    ~MatrixCreator();

    //costruisce i pulsanti per le dimensioni e restituisce il layout
    virtual void buildDimensionsGroupBox();

    //costruisce il set di pulsanti per le operazioni
    virtual void buildOperationsSet();

    //set dei QSpinBox per le dimensioni
    //0,2,3 parametri (min,max,default)
    void setRowBox(unsigned int, unsigned int, unsigned int = 2);
    void setRowBox();
    void setColBox(unsigned int, unsigned int, unsigned int = 2);
    void setColBox();

    void setOperationSelected(MatrixCreator::Operation);
    MatrixCreator::Operation getOperationSelected() const;

    void clearCells(); //delete cells[i] per ogni i in 0..n-1 e svuota cells
    void resetCells(); //cells[i]->setText("") per ogni i in 0..n-1

    //resetta dimensionsGroupBox
    virtual void resetDimensionsGroupBox();

    //resetta e inizializza matrixBuilder
    void initializeMatrixBuilder();

signals:
//    void nonScalarMulSignal(double);
//    void buildMatrixSignal(const Matrix&);

public slots:
    virtual void handleSelectDimensions(); //virtual?
    virtual void handleSelectSecondMatrixDimensions();

//    void handleBuildMatrixButton();
    void handleObtainResult();

    //operations slots
    void sumClicked();
    void subtractionClicked();
    void scalarMultiplicationClicked();
    void nonScalarMultiplicationClicked();
    void transposedClicked();
    void swapRowsClicked();
    void swapColsClicked();
    void substituteRowClicked();
};

#endif // MATRIXCREATOR_H
