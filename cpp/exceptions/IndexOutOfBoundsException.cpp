#include "IndexOutOfBoundsException.h"

IndexOutOfBoundsException::IndexOutOfBoundsException(const QString& what)
    : KalkException(what) {}

void IndexOutOfBoundsException::raise() const {
    throw *this;
}

IndexOutOfBoundsException* IndexOutOfBoundsException::clone() const {
    return new IndexOutOfBoundsException(*this);
}
