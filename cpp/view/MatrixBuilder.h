#ifndef MATRIXBUILDER_H
#define MATRIXBUILDER_H

#include <QWidget>
#include <QComboBox>
#include <QStringListModel>
#include <QPushButton>
#include <QStackedWidget>
#include "MatrixKalk.h"


//Classe che gestisce il widget di creazione di una matrice
class MatrixBuilder : public QWidget
{
    Q_OBJECT
private:
    QStackedWidget* stackedWidget;      //contiene uno Stack di QWidget switchabili
    QVector<QWidget*> pages;            //QWidgets "paralleli"
    QStringListModel* matrixListModel;  //lista per matrixSelectionBox
    QComboBox* matrixSelectionBox;      //selezione a tendina della matrice
    QPushButton* matrixSelection;       //pulsante di selezione
    QPushButton* backButton;            //pulsante per tornare indietro

    MatrixController* controller;

    //costanti per le dimensioni della finestra
    const int hWindowSize = 200;
    const int wWindowSize = 300;
    const int hCreatorWindowSize = 300;
    const int wCreatorWindowSize = 500;

    void buildMatrixSelectionBox();     //costruisce il GroupBox per la selezione del tipo di matrice

public:
    explicit MatrixBuilder(QWidget *parent = nullptr);
    ~MatrixBuilder();

signals:
    void matrixBuilderCloseSignal();

private slots:
    void handleMatrixSelection();
    void handleBackButton();
    void connectMatrixKalk();
};

#endif // MATRIXBUILDER_H
