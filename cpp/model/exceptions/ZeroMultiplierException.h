#ifndef ZEROMULTIPLIEREXCEPTION_H
#define ZEROMULTIPLIEREXCEPTION_H

#include<QException>

class ZeroMultiplierException : public QException {
private:
    QString message;
public:
    ZeroMultiplierException(const QString& what = "");
    void raise() const;
    ZeroMultiplierException* clone() const;
    QString getMessage() const;
};

#endif // ZEROMULTIPLIEREXCEPTION_H
