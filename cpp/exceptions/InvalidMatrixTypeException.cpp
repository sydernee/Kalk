#include "InvalidMatrixTypeException.h"

InvalidMatrixTypeException::InvalidMatrixTypeException(const QString& msg)
    : KalkException(msg) {}

void InvalidMatrixTypeException::raise() const {
    throw *this;
}

InvalidMatrixTypeException* InvalidMatrixTypeException::clone() const {
    return new InvalidMatrixTypeException(*this);
}
