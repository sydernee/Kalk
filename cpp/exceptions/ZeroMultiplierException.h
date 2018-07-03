#ifndef ZEROMULTIPLIEREXCEPTION_H
#define ZEROMULTIPLIEREXCEPTION_H

#include "KalkException.h"

class ZeroMultiplierException : public KalkException {

public:
    ZeroMultiplierException(const QString& what = "");
    void raise() const;
    ZeroMultiplierException* clone() const;
};

#endif // ZEROMULTIPLIEREXCEPTION_H
