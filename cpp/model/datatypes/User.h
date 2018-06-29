#ifndef USER_H
#define USER_H

#include <QList>
#include <QString>


class User {
private:
   QString username;
public:
   User(QString);
   
   virtual bool operator==(const User&) const; //due utenti sono uguali se hanno lo stesso username

   QString getUsername() const;
   void changeUsername(QString); // eccezione se lo username già è presente
};

#endif // USER_H

