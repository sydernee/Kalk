#include "ZeroMultiplierException.h"

ZeroMultiplierException::ZeroMultiplierException(const QString& what)
    : message(what) {}

QString ZeroMultiplierException::getMessage() const {
    return message;
}

ZeroMultiplierException* ZeroMultiplierException::clone() const {
    return new ZeroMultiplierException(*this);
}

void ZeroMultiplierException::raise() const {
    throw *this;
}

