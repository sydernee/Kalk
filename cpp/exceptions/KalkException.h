#ifndef KALKEXCEPTION_H
#define KALKEXCEPTION_H

#include <QException>

class KalkException : public QException {
private:
    QString message;
public:
    KalkException(const QString& = "");
    virtual QString getMessage() const;
    virtual ~KalkException() = 0;
};

#endif // KALKEXCEPTION_H
