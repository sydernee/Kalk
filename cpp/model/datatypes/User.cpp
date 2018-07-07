#include "User.h"

User::User(QString uname, QString n, QString s): username(uname), name(n), surname(s) {}
   
QString User::getUsername() const {return username;}
QString User::getName() const {return name;}
QString User::getSurname() const {return surname;}
   
void User::setName(QString n) {name=n;}
void User::setSurname(QString s) {surname=s;}

User::~User(){ qDebug() << getUsername() << " destroyed";}
