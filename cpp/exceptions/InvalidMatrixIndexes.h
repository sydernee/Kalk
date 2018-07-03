#ifndef INVALIDMATRIXINDEXES_H
#define INVALIDMATRIXINDEXES_H

#include "KalkException.h"

class InvalidMatrixIndexes : public KalkException {
public:
    InvalidMatrixIndexes(const QString& what = "");
    void raise() const;
    InvalidMatrixIndexes* clone() const;
};

#endif // INVALIDMATRIXINDEXES_H
