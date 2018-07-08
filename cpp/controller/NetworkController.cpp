//()
#include "NetworkController.h"

//ctor
NetworkController::NetworkController(NetworkManager* v)
    : view(v)
{
    // empty
}


//dtor
NetworkController::~NetworkController() {

}

bool NetworkController::existUsername(QString username) const {
    bool found = false;
    for (auto it = gUsers.cbegin(); it!=gUsers.cend() && !found; ++it) {
        if ((*it)->getUsername() == username)
            return true;
    }
    return false;
}

bool NetworkController::createGlobalUser(QString username,QString name,QString surname) {
    if (existUsername(username)) {return false;}
    
    qDebug() << "Aggiungo " << username << "agli utenti";
    gUsers.append(QSharedPointer<User>(new User(username,name,surname)));
    return true;
}

QVector<QString> NetworkController::getUserData(int pos) {
    qDebug() << "Carico i dati di " << gUsers[pos]->getUsername();    
    QVector<QString> res;
    res.push_back(gUsers[pos]->getUsername());
    res.push_back(gUsers[pos]->getName());
    res.push_back(gUsers[pos]->getSurname());        
    
    return res;
}

void NetworkController::setUserData(int pos, QString name, QString surname) { //modifica i dati di un user data la sua pos nel model
    qDebug() << "Modifico i dati di " << gUsers[pos]->getUsername();    
    gUsers[pos]->setName(name);
    gUsers[pos]->setSurname(surname);
}

void NetworkController::deleteUser(int pos) {
    //elimino user da tutte le reti in cui è presente
    for (auto it = netlist.cbegin(); it!=netlist.cend(); ++it) {
        (*it)->removeUser(gUsers[pos]);
    }
    
    //rimuovo l'utente
    gUsers.removeAt(pos);
    
}

bool NetworkController::existNet(QString netname) const {
    bool found = false;
    for (auto it = netlist.cbegin(); it!=netlist.cend() && !found; ++it) {
        if ((*it)->getName() == netname)
            return true;
    }
    return false;
}


bool NetworkController::createNet(QString netname) {
    if (existNet(netname)) {return false;}
    
    netlist.append(QSharedPointer<Network>(new Network(netname)));
    return true;
}

QString NetworkController::getNetName(int pos) const {
    qDebug() << "Carico il nome della rete " << pos << ": " << netlist[pos]->getName(); 
    return netlist[pos]->getName();   
}

bool NetworkController::renameNet(int pos, QString netname) {
    if (existNet(netname)) {return false;}
    
    netlist[pos]->setName(netname);
    return true;
}

void NetworkController::deleteNet(int pos) {
    netlist.removeAt(pos);
}

bool NetworkController::addUserToNetwork(int posNet, int posUser){
    if (netlist[posNet]->isUserOfTheNetwork(gUsers[posUser])) {return false;}
    
    netlist[posNet]->addUser(gUsers[posUser]); 
    return true;
}

QStringList NetworkController::getNetworkUsers(int pos) {
    QStringList res;
    
    QSet<QSharedPointer<User>>  users = netlist[pos]->getUsers();
    
    for (auto it = users.begin(); it != users.end(); ++it) {
        res << (*it)->getUsername();
    }
    
    return res;
}


void NetworkController::removeUserFromNetwork(int posNet,QString username) {
    netlist[posNet]->removeUser(username);
}

QStringList NetworkController::calculateUnion(int posNetA, int posNetB) const {
    QSet<QSharedPointer<User>> userset = netlist[posNetA]->getUnion(*(netlist[posNetB]));

    QStringList res;
    
    foreach (auto usr, userset) {
        res << usr->getUsername();
    }

    return res;
}

QStringList NetworkController::calculateIntersection(int posNetA, int posNetB) const {
    QSet<QSharedPointer<User>> userset = netlist[posNetA]->getIntersection(*(netlist[posNetB]));
    QStringList res;
    
    foreach (auto usr, userset) {
        res << usr->getUsername();
    }

    return res;
}

QStringList NetworkController::calculateRelativeComplement(int posNetA, int posNetB) const {
    QSet<QSharedPointer<User>> userset = netlist[posNetA]->getRelativeComplement(*(netlist[posNetB]));

    QStringList res;
    
    foreach (auto usr, userset) {
        res << usr->getUsername();
    }

    return res;
}

QStringList NetworkController::calculateSymmetricDifference(int posNetA, int posNetB) const {
    QSet<QSharedPointer<User>> userset = netlist[posNetA]->getSymmetricDifference(*(netlist[posNetB]));

    QStringList res;
    
    foreach (auto usr, userset) {
        res << usr->getUsername();
    }

    return res;
}

QSharedPointer<User> NetworkController::getUserSmartPtrByUsername(QString username) const {
    bool found = false;
    QSharedPointer<User> res;
    for (auto it = gUsers.cbegin(); it != gUsers.cend() && !found; ++it) {
        if ((*it)->getUsername() == username) {
            found = true;
            res = *it;
        }
    }
    return res;
}

void NetworkController::addFollower(QString followerName, QString followedName, int netPos) {
    netlist[netPos]->addFollower(getUserSmartPtrByUsername(followerName), getUserSmartPtrByUsername(followedName));
}

QStringList NetworkController::getFollower(int netPos, QString username) const {
    QSet<QSharedPointer<User>> userset = netlist[netPos]->getFollower(getUserSmartPtrByUsername(username));
    
    QStringList res;
    
    qDebug() << "stampo follower";
    
    foreach (auto usr, userset) {
        qDebug() << username << " segue " << usr->getUsername();
        res << usr->getUsername();
    }

    return res;
}

QStringList NetworkController::getFollowed(int netPos, QString username) const {
    QSet<QSharedPointer<User>> userset = netlist[netPos]->getFollowed(getUserSmartPtrByUsername(username));
    
        qDebug() << "stampo followed";
    QStringList res;
    
    foreach (auto usr, userset) {
        qDebug() << username << " è seguito da " << usr->getUsername();
        res << usr->getUsername();
    }

    return res;
}

void NetworkController::removeFollowed(QString followerName,QString  followedName, int netPos) {
    netlist[netPos]->removeFollower(getUserSmartPtrByUsername(followerName), getUserSmartPtrByUsername(followedName));
}
//()
