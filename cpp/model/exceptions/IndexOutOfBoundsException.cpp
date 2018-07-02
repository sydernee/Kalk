#include "IndexOutOfBoundsException.h"

IndexOutOfBoundsException::IndexOutOfBoundsException(const QString& what)
    : message(what) {}

QString IndexOutOfBoundsException::getMessage() const {
    return message;
}

void IndexOutOfBoundsException::raise() const {
    throw *this;
}

IndexOutOfBoundsException* IndexOutOfBoundsException::clone() const {
    return new IndexOutOfBoundsException(*this);
}
