#ifndef INVALIDLAYOUTEXCEPTION_H
#define INVALIDLAYOUTEXCEPTION_H

#include "KalkException.h"

class InvalidLayoutException : public KalkException {
public:
    InvalidLayoutException(const QString& what="");
    void raise() const;
    InvalidLayoutException* clone() const;
};

#endif // INVALIDLAYOUTEXCEPTION_H
