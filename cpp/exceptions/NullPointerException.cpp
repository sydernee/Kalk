#include "NullPointerException.h"

NullPointerException::NullPointerException(const QString& what)
    : KalkException(what) {}

void NullPointerException::raise() const {
    throw *this;
}

NullPointerException *NullPointerException::clone() const {
    return new NullPointerException(*this);
}
