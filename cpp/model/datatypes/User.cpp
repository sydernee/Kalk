#include "User.h"

User::User(QString name): username(name) {}

bool User::operator==(const User& other) const { return getUsername() == other.getUsername(); }

QString User::getUsername() const {return username;}

void User::changeUsername(QString name) { username = name; }

User::~User(){ qDebug() << getUsername() << " destroyed";}
