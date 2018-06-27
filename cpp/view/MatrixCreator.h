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
class MatrixController; //controller


enum Operation {
    SUM,
    SUBTRACTION,
    SCALAR_MULTIPLICATION,
    NON_SCALAR_MULTIPLICATION
};

class MatrixCreator : public QWidget
{
    Q_OBJECT
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
    QPushButton* obtainResult;      //pulsante per =

    MatrixController* controller;   //controller Matrix - MatrixCreator
    QVector<KeypadInput*> cells;    //vettore che contiene le celle di matrixBuilder

    Operation operationSelected;
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

    void setOperationSelected(Operation);
    Operation getOperationSelected() const;

    void clearCells(); //delete cells[i] per ogni i in 0..n-1 e svuota cells
    void resetCells(); //cells[i]->setText("") per ogni i in 0..n-1

    //resetta dimensionsGroupBox
    virtual void resetDimensionsGroupBox();
signals:
    void buildMatrixSignal(const Matrix&);

public slots:
    virtual void handleSelectDimensions(); //virtual?

private slots:
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
