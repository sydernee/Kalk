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
    QStringListModel* matrixListModel;
    QComboBox* matrixSelectionBox;
    QPushButton* matrixSelection;

    void buildMatrixSelectionBox();

public:
    explicit MatrixBuilder(QWidget *parent = nullptr);
    ~MatrixBuilder();

signals:

private slots:
    void handleMatrixSelection();
};

#endif // MATRIXBUILDER_H
