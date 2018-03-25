#ifndef USER_H
#define USER_H

#include <QMap>
#include <QString>


class User 
private:
   QString userName;
   QMap<QString,User*> following;
public:
   User(QString);
   
   virtual operator==(const User&) const; //due utenti sono uguali se hanno lo stesso username

   QString getUserName() const;
   void changeUserName(QString); // eccezione se lo username già è presente
};

#endif // USER_H

