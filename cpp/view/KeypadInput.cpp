#include "KeypadInput.h"
#include <cfloat>
#include <QKeyEvent>

KeypadInput::KeypadInput(const QString& text, QDoubleValidator* validator, QWidget* parent)
    : QLineEdit(text, parent),
      inputValidator(validator)
{

    if (validator == nullptr)
        inputValidator = new QDoubleValidator(DBL_MIN, DBL_MAX, 50, this);
    setValidator(inputValidator);
    setFocus();
}

//impedisce l'inserimento di due punti di virgola
void KeypadInput::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Period:
            if (!text().contains('.'))
                QLineEdit::keyPressEvent(event);
            break;
        default:
            QLineEdit::keyPressEvent(event);
            break;

    }
}
