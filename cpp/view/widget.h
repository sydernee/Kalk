#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT
private:
    QVector<QPushButton*> NumericButtons;
    QPushButton* dotButton;
    QPushButton* assignmentButton;

    QPushButton* createMatrix;

    void buildNumButtons(int x, int y, int w, int h); //costruisce il tastierino numerico

private slots:
    void handleNumButtons();
    void handleDotButton();
    void handleAssignmentButton();
    void handleCreateMatrixButton();

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
