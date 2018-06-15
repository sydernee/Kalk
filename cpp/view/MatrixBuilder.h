#ifndef MATRIXBUILDER_H
#define MATRIXBUILDER_H

#include <QWidget>
#include <QComboBox>
#include <QStringListModel>
#include <QPushButton>
#include <QStackedWidget>


//Classe che gestisce il widget di creazione di una matrice
class MatrixBuilder : public QWidget
{
    Q_OBJECT
private:
    QStackedWidget* stackedWidget;
    QVector<QWidget*> pages;
    QStringListModel* matrixListModel;  //lista per matrixSelectionBox
    QComboBox* matrixSelectionBox;      //selezione a tendina della matrice
    QPushButton* matrixSelection;       //pulsante di selezione
    QPushButton* backButton;            //pulsante per tornare indietro

    void buildMatrixSelectionBox(); //costruisce il GroupBox per la selezione del tipo di matrice

public:
    explicit MatrixBuilder(QWidget *parent = nullptr);
    ~MatrixBuilder();

signals:

private slots:
    void handleMatrixSelection();
    void handleBackButton();
};

#endif // MATRIXBUILDER_H
