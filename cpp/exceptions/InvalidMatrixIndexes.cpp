#include "InvalidMatrixIndexes.h"

InvalidMatrixIndexes::InvalidMatrixIndexes(const QString& what)
    : KalkException(what) {}

InvalidMatrixIndexes* InvalidMatrixIndexes::clone() const {
    return new InvalidMatrixIndexes(*this);
}

void InvalidMatrixIndexes::raise() const {
    throw *this;
}

