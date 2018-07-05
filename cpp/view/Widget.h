#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QPushButton;
class Keypad;

class Widget : public QWidget
{
    Q_OBJECT
private:
    QPushButton* createMatrixKalk;

private slots:
    void handleNumButtons();
    void handleDotButton();
    void handleAssignmentButton();
    void handleCreateMatrixKalkButton();
    void showWidget();

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
