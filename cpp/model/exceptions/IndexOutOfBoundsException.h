#ifndef INDEXOUTOFBOUNDSEXCEPTION_H
#define INDEXOUTOFBOUNDSEXCEPTION_H

#include <QException>

class IndexOutOfBoundsException : public QException {
private:
    QString message;

public:
    IndexOutOfBoundsException(const QString& what = "");
    void raise() const;
    IndexOutOfBoundsException* clone() const;

    QString getMessage() const;
};

#endif // INDEXOUTOFBOUNDSEXCEPTION_H
