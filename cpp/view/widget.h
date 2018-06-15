#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QPushButton;
class Keypad;
class QGroupBox;

class Widget : public QWidget
{
    Q_OBJECT
private:
/*    QGroupBox* keypad;
    QVector<QPushButton*> NumericButtons;
    QPushButton* dotButton;
    QPushButton* assignmentButton;
*/
    Keypad* keypad;
    QPushButton* createMatrix;

    void buildKeypad(); //costruisce il tastierino numerico

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
