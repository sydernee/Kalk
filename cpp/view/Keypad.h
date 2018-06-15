#ifndef KEYPAD_H
#define KEYPAD_H

#include <QWidget>
#include "KeypadInput.h"

class QPushButton;
class QLabel;

//Classe che genera un QWidget tastierino numerico
class Keypad : public QWidget
{
    Q_OBJECT
private:
    QVector<QPushButton*> numericButtons; // {0,1,..,9}
    QPushButton* dotButton; // .
    QPushButton* assignmentButton; // =
    QString inputText;  //stringa di input inserita
    KeypadInput* keypadInput; //output dell'input
    //QKeyEvent* backspace;  //cancella l'ultimo digit

    void createLayout(); //crea il layout del tastierino numerico
public:
    explicit Keypad(QWidget *parent = nullptr);
    void setInputText(const QString&);      //set per inputText
    void appendInputText(const QString&);   //append di una stringa a inputText
    QString getInputText() const;           //get per inputText

signals:
    void digitClicked(int);
    void digitClicked(const QChar&);

private slots:
    void buttonClicked();
    void dotClicked();
    void backspaceClicked();
};

#endif // KEYPAD_H
