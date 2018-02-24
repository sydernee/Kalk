#include "Number.h"
#include <limits>

//-----------|
//COSTRUTTORI|
//-----------|

Number::Number() :
    value(nullptr) {}

Number::Number(double v) : value(new double(v)) {}

Number::Number(const QString& strin) :
    value(new double(strin.toDouble())) {}

//-------|
//MEMORIA|
//-------|

Number::Number(const Number& num) :
    value(new double(num.getValue())) {}

Number& Number::operator =(const Number& num) {
    if (this != &num) {
        delete value;
        value = new double(num.getValue());
    }
    return *this;
}

Number::~Number() {
    delete value;
}

//---------|
//CONFRONTI|
//---------|

double Number::getValue() const {
    return *value;
}

bool Number::operator<(const Number& num) const {
    return getValue() < num.getValue();
}

bool Number::operator<=(const Number& num) const {
    return getValue() <= num.getValue();
}

bool Number::operator==(const Number& num) const {
    return getValue() == num.getValue();
}

bool Number::operator!=(const Number& num) const {
    return getValue() != num.getValue();
}

bool Number::operator>(const Number& num) const {
    return getValue() > num.getValue();
}

bool Number::operator>=(const Number& num) const {
    return getValue() >= num.getValue();
}

//-----------|
//CONVERSIONI|
//-----------|

Number::operator float() const {
    return static_cast<float>(getValue());
}

Number::operator int() const {
    return static_cast<int>(getValue());
}

Number::operator QString() const {
    QLocale locale;
    QString str = locale.toString(getValue());

    return str;
}

QString Number::toString() const {
    QLocale locale;
    QString str = locale.toString(getValue());

    return str;
}

//-------------------|
//PROPRIETA' STATICHE|
//-------------------|

const double Number::MAX_VALUE = std::numeric_limits<double>::max();

const double Number::MIN_VALUE = std::numeric_limits<double>::min();

const short int Number::SIZE = sizeof(double);

const double Number::POSITIVE_INFINITY = std::numeric_limits<double>::infinity();

const double Number::NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();

const double Number::NaN = std::numeric_limits<double>::quiet_NaN();

//----------------------|
//SPECIAL NUMBERS CHECKS|
//----------------------|

bool Number::isNaN() const {
    if (getValue() == NaN)
        return true;
    return false;
}

bool Number::isNaN(const Number& num) {
    if (num.getValue() == NaN)
        return true;
    return false;
}

bool Number::isPositiveInfinity() const {
    if (getValue() == POSITIVE_INFINITY)
        return true;
    return false;
}

bool Number::isPositiveInfinity(const Number& num) {
    if (num.getValue() == POSITIVE_INFINITY)
        return true;
    return false;
}

bool Number::isNegativeInfinity() const {
    if (getValue() == NEGATIVE_INFINITY)
        return true;
    return false;
}

bool Number::isNegativeInfinity(const Number& num) {
    if (num.getValue() == NEGATIVE_INFINITY)
        return true;
    return false;
}

//----------|
//OPERAZIONI|
//----------|

Number operator+(const Number& v1, const Number& v2) {
    return Number(v1.getValue() + v2.getValue());
}

Number operator-(const Number& v1, const Number& v2) {
    return Number(v1.getValue() - v2.getValue());
}

Number operator*(const Number& v1, const Number& v2) {
    return Number(v1.getValue() * v2.getValue());
}

Number operator/(const Number& v1, const Number& v2) {
    return Number(v1.getValue() / v2.getValue());
}

//------|
//OUTPUT|
//------|

QTextStream& operator<<(QTextStream& out, const Number& num) {
    return out << num.getValue();
}
