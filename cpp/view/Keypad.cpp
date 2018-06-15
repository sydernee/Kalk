#include "Keypad.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QKeyEvent>

Keypad::Keypad(QWidget *parent)
    : QWidget(parent),
      dotButton(new QPushButton(".", this)),
      assignmentButton(new QPushButton("=", this)),
      inputText("")
{
    //istanzia i pulsanti e gli shortcut da tastiera
    for (int i = 0; i < 10; i++) {
        numericButtons.push_back(new QPushButton(QString::number(i), this));
        connect(numericButtons[i], SIGNAL(clicked()), this, SLOT(buttonClicked()));
        numericButtons[i]->setShortcut(QString::number(i));

        //tab order
        if (i > 1)
            setTabOrder(numericButtons[i-1], numericButtons[i]);
    }
    setTabOrder(numericButtons[9], numericButtons[0]);
    setTabOrder(numericButtons[0], dotButton);
    setTabOrder(dotButton, assignmentButton);

    dotButton->setShortcut(tr("."));
    connect(dotButton, SIGNAL(clicked()), this, SLOT(dotClicked()));

    assignmentButton->setShortcut(tr("="));

    //connect(backspace, SIGNAL(), this, SLOT(backspaceClicked()));

    //keypadInput
    keypadInput = new KeypadInput("", nullptr, this);
    //keypadInput->setStyleSheet("background-color: #000; color: green;");

    //crea il layout
    createLayout();
}

void Keypad::createLayout() {
    //layout principale
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(keypadInput);

    //layout tastierino numerico
    QGridLayout* gridLayout = new QGridLayout;
    gridLayout->addWidget(numericButtons[1],0,0);
    gridLayout->addWidget(numericButtons[2],0,1);
    gridLayout->addWidget(numericButtons[3],0,2);
    gridLayout->addWidget(numericButtons[4],1,0);
    gridLayout->addWidget(numericButtons[5],1,1);
    gridLayout->addWidget(numericButtons[6],1,2);
    gridLayout->addWidget(numericButtons[7],2,0);
    gridLayout->addWidget(numericButtons[8],2,1);
    gridLayout->addWidget(numericButtons[9],2,2);
    gridLayout->addWidget(numericButtons[0],3,0);
    gridLayout->addWidget(dotButton,3,1);
    gridLayout->addWidget(assignmentButton,3,2);

    gridLayout->setSpacing(0);

    mainLayout->addLayout(gridLayout);
    setLayout(mainLayout);
}

QString Keypad::getInputText() const {
    return inputText;
}

void Keypad::setInputText(const QString& text) {
        inputText = text;
        keypadInput->setText(inputText);
}

//appende stringa text a inputText
void Keypad::appendInputText(const QString& text) {
    //impedisce di appendere il dot se già presente
    if (text != "." || !inputText.contains(".")) {
        setInputText(inputText + text);
    }
}

//SLOTS

void Keypad::buttonClicked() {
    //riconosce il pulsante premuto
    QPushButton* button = (QPushButton*)sender();
    appendInputText(button->text());
    keypadInput->setFocus();
    emit digitClicked(button->text()[0].digitValue());
}

void Keypad::dotClicked() {
    appendInputText(".");
    keypadInput->setFocus();
    emit digitClicked('.');

}

void Keypad::backspaceClicked() {
    if (!inputText.isEmpty()) {
        if (inputText.size() == 1)
            setInputText("");
        else {
            inputText.remove(inputText.size()-1, inputText.size()-1);
            setInputText(inputText);
        }
    }
}
