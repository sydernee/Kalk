#ifndef NETWORK_H
#define NETWORK_H

#include <QList>
#include <QString>


class Network : public DataType {
private:
    QMap<User*> userlist;
public:
    class User {
        //friend class Network; //attualmente non necessario, da valutare
    private:
       QString userName;
       QMap<QString,User*> following;
    public:
       User(QString);
       User(QString,QVector<User*>);
       
       virtual operator==(const User&) const; //due utenti sono uguali se hanno lo stesso username

       QString getUserName() const;
       void changeUserName(QString); // eccezione se lo username già è presente
       void follow(const User&);
       bool isFriendOf(const User&) const;
       int calculateDistance(const User&, int) const; // ritorna -1 se non è stato non trovato
    };

    void addUser(QString); // eccezione se lo username già è presente
    void removeUser(QString); //eccezione se l'utente non esiste ?
    
    
};


#endif // NETWORK_H

