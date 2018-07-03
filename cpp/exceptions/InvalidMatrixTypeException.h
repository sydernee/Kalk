#ifndef INVALIDMATRIXTYPEEXCEPTION_H
#define INVALIDMATRIXTYPEEXCEPTION_H

#include "KalkException.h"

class InvalidMatrixTypeException : public KalkException {
public:
    InvalidMatrixTypeException(const QString& what="");
    void raise() const;
    InvalidMatrixTypeException* clone() const;
};

#endif // INVALIDMATRIXTYPEEXCEPTION_H
