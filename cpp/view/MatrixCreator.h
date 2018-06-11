#ifndef MATRIXCREATOR_H
#define MATRIXCREATOR_H

#include <QWidget>
#include <QBoxLayout>

class Matrix;
class QLabel;
class QSpinBox;
class QHBoxLayout;
class QGroupBox;
class QPushButton;

class MatrixCreator : public QWidget
{
    Q_OBJECT
private:
    Matrix* matrix; //matrice ottenuta dopo la costruzione
    QGroupBox* dimensionsGroupBox;
    QGroupBox* matrixBuilder;
    QLabel* selectDimensionsLabel; //label per la selezione delle dimensione
    QSpinBox* rowBox; //box per row
    QSpinBox* colBox; //box per col
    QPushButton* selectDimensions; //bottone per accettare la selezione delle dimensioni

public:
    explicit MatrixCreator(QWidget *parent = nullptr);

    //costruisce i pulsanti per le dimensioni e restituisce il layout
    virtual void buildDimensionsGroupBox();

    //set box per le dimensioni
    //0,2,3 parametri (min,max,default)
    void setRowBox(unsigned int, unsigned int, unsigned int = 2);
    void setRowBox();
    void setColBox(unsigned int, unsigned int, unsigned int = 2);
    void setColBox();

signals:

public slots:
    virtual void handleSelectDimensions(); //virtual?
};

#endif // MATRIXCREATOR_H
