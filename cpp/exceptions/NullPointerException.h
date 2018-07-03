#ifndef NULLPOINTEREXCEPTION_H
#define NULLPOINTEREXCEPTION_H

#include "KalkException.h"

class NullPointerException : public KalkException {
public:
    NullPointerException(const QString& what = "");
    void raise() const;
    NullPointerException* clone() const;
};

#endif // NULLPOINTEREXCEPTION_H
