#ifndef INDEXOUTOFBOUNDSEXCEPTION_H
#define INDEXOUTOFBOUNDSEXCEPTION_H

#include "KalkException.h"

class IndexOutOfBoundsException : public KalkException {
public:
    IndexOutOfBoundsException(const QString& what = "");
    void raise() const;
    IndexOutOfBoundsException* clone() const;
};

#endif // INDEXOUTOFBOUNDSEXCEPTION_H
