#include "KalkException.h"

KalkException::KalkException(const QString& msg)
    : message(msg) {}

QString KalkException::getMessage() const {
    return message;
}

KalkException::~KalkException() {}
