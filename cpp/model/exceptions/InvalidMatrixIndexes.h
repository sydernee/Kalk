#ifndef INVALIDMATRIXINDEXES_H
#define INVALIDMATRIXINDEXES_H

#include <QException>

class InvalidMatrixIndexes : public QException {
private:
    QString message;
public:
    InvalidMatrixIndexes(const QString& what = "");
    void raise() const;
    InvalidMatrixIndexes* clone() const;
    QString getMessage() const;
};

#endif // INVALIDMATRIXINDEXES_H
