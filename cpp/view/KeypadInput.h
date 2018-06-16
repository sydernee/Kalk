#ifndef KEYPADINPUT_H
#define KEYPADINPUT_H

#include <QLineEdit>
#include <QDoubleValidator>

//Ridefinizione di QLineEdit per l'input della classe Keypad
class KeypadInput : public QLineEdit {
private:
    QDoubleValidator* inputValidator;

public:
    KeypadInput(QWidget* parent = nullptr, const QString& = "", QDoubleValidator* = nullptr);
    void keyPressEvent(QKeyEvent* event); //override per la gestione di Qt::Key_Period
};

#endif // KEYPADINPUT_H
