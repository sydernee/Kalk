#ifndef USER_H
#define USER_H

#include <QList>
#include <QString>
#include <QDebug>


class User {
private:
   QString username;
   QString name;
   QString surname;
public:
   User(QString,QString="",QString="");
   
   virtual QString getUsername() const;
   virtual QString getName() const;
   virtual QString getSurname() const;
   
   virtual void setName(QString);
   virtual void setSurname(QString);
   
   virtual ~User();
};

#endif // USER_H
