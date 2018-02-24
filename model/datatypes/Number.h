#ifndef NUMBER_H
#define NUMBER_H

#include "../DataType.h"
#include <QString>
#include <QTextStream>
#include <QLocale>

class Number : public DataType {
private:
    double* value;

public:
    Number();
    Number(double);
    Number(const QString&);
    double getValue() const;

    ~Number();
    Number(const Number&);
    Number& operator=(const Number&);

    static const double MAX_VALUE;
    static const double MIN_VALUE;
    static const short int SIZE;
    static const double POSITIVE_INFINITY;
    static const double NEGATIVE_INFINITY;
    static const double NaN;

    //compare between two Number Objects
    bool operator<(const Number&) const;
    bool operator<=(const Number&) const;
    bool operator==(const Number&) const;
    bool operator!=(const Number&) const;
    bool operator>(const Number&) const;
    bool operator>=(const Number&) const;

    bool isNaN() const;
    static bool isNaN(const Number&);

    bool isPositiveInfinity() const;
    static bool isPositiveInfinity(const Number&);

    bool isNegativeInfinity() const;
    static bool isNegativeInfinity(const Number&);

    operator float() const; //conversione a float
    operator int() const; //conversione a int
    QString toString() const; //conversione esplicita a QString
    operator QString() const; //conversione implicita a QString
};

QTextStream& operator<<(QTextStream&, const Number&);

Number operator+(const Number&, const Number&);
Number operator-(const Number&, const Number&);
Number operator*(const Number&, const Number&);
Number operator/(const Number&, const Number&);


#endif // NUMBER_H
