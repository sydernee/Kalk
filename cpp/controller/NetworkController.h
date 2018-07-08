#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include "../model/datatypes/Network.h"
#include "../model/datatypes/User.h"
#include "../view/NetworkManager.h"

#include <QString>
#include <QStringList>
#include <QDebug>
#include <QSharedPointer>
#include <QList>
#include <QVector>
#include <QSet>

class NetworkManager;
//()
class NetworkController {
private:
    QList<QSharedPointer<Network>> netlist; //model
    QList<QSharedPointer<User>> gUsers; //model
    NetworkManager* view;

public:
    NetworkController(NetworkManager*); 
    virtual ~NetworkController();

    virtual bool existUsername(QString) const;    
    virtual bool createGlobalUser(QString,QString,QString); //ritorna false se esiste un utente con lo stesso username
    
    virtual QVector<QString> getUserData(int); //ritorna i dati di un user data la sua pos nel model
    //virtual QVector<QString> getUserData(QString); TODO //ritorna i dati di un user dato il suo username
    
    virtual void setUserData(int, QString, QString); //modifica i dati di un user data la sua pos nel model
    //void setUserData(int, QString, QString); TODO //modifica i dati di un user dato il suo username, name e surname
    
    virtual void deleteUser(int); //data la posizione di un utente all'interno del model, lo elimina

    virtual bool existNet(QString netname) const; //ritorna false se esiste una rete con lo stesso nome     
    virtual bool createNet(QString);//ritorna false se esiste una rete con lo stesso nome
    
    virtual QString getNetName(int) const;//data la posizione di una rete nel model, ritorna il suo nome
    
    virtual bool renameNet(int,QString);//data la posizione di una rete nel model, cambia il nome della rete 
    //con il valore passato sse non è già in uso. Ritorna l'esito della modifica
    
    virtual void deleteNet(int); //data la posizione di una rete all'interno del model, la elimina
    
    virtual bool addUserToNetwork(int,int); //data la posizione di una rete e di un user all'interno del model, aggiunge l'utente alla rete. 
                                    // ritorna false sse user già presente nella rete
                                    
    virtual QStringList getNetworkUsers(int); //data la posizione di una rete all'interno del model, ritorna i suoi utenti
    
    virtual void removeUserFromNetwork(int,QString); //data la posizione di una rete all'interno del model e la username di un utente, rimuove l'utente
    
    
    virtual QStringList calculateUnion(int, int);
    virtual QStringList calculateIntersection(int, int);
    virtual QStringList calculateRelativeComplement(int, int);
    virtual QStringList calculateSymmetricDifference(int, int);
    
    
};

//()
#endif //NETWORKCONTROLLER_H
