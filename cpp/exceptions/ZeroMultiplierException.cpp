#include "ZeroMultiplierException.h"

ZeroMultiplierException::ZeroMultiplierException(const QString& what)
    : KalkException(what) {}

ZeroMultiplierException* ZeroMultiplierException::clone() const {
    return new ZeroMultiplierException(*this);
}

void ZeroMultiplierException::raise() const {
    throw *this;
}
