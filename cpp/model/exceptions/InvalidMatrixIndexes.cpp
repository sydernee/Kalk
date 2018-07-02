#include "InvalidMatrixIndexes.h"

InvalidMatrixIndexes::InvalidMatrixIndexes(const QString& what)
    : message(what) {}

QString InvalidMatrixIndexes::getMessage() const {
    return message;
}

InvalidMatrixIndexes* InvalidMatrixIndexes::clone() const {
    return new InvalidMatrixIndexes(*this);
}

void InvalidMatrixIndexes::raise() const {
    throw *this;
}

