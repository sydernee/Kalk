#include "InvalidLayoutException.h"

InvalidLayoutException::InvalidLayoutException(const QString &what)
    : KalkException(what) {}

void InvalidLayoutException::raise() const {
    throw *this;
}

InvalidLayoutException *InvalidLayoutException::clone() const {
    return new InvalidLayoutException(*this);
}
