#include "Network.h"

Network::Network(QString n) : name(n),userlist() {qDebug() << "Creata la rete " << n;}

Network::Network(QSet<QSharedPointer<User>> ul, QString n) : name(n), userlist(ul.toList()) {qDebug() << "Creata la rete " << n;}

QString Network::getName() {return name;}

void Network::setName(QString n) {
    qDebug() << "Rinomino la rete " << name << "con il nome " << n;
    name = n;
}

unsigned int Network::size() const {
    return userlist.size();
}


void Network::addUser(QSharedPointer<User> u) {
    if (!isUserOfTheNetwork(u)) {
       userlist.append(u);
       qDebug() << "Aggiunto " << u->getUsername() << "alla rete " << getName();
    }
}

bool Network::isUserOfTheNetwork(QSharedPointer<User> u) const {
    return userlist.contains(u);
}

QSet<QSharedPointer<User>> Network::getUsers() const {
    return userlist.toSet();
}


void Network::removeUser(QSharedPointer<User> u) {
    userlist.removeAll(u); 
    // ora rimuovo following/follower
    auto it = following.begin();
    while ( it!=following.end()) {
        if ((it->first == u) || (it->second == u)) {
            it = following.erase(it);
        } else {
            ++it;
        }
    } 
}

void Network::removeUser(const QString u) {
    bool found = false;
    
    for (auto it = userlist.begin(); it != userlist.end() && found == false; ++it) {
        if ((*it)->getUsername() == u) {
            removeUser(*it);
            found = true;
        }
    }
}

void Network::addFollower(QSharedPointer<User> follower, QSharedPointer<User> followed) {
    if (isUserOfTheNetwork(follower) && isUserOfTheNetwork(followed)) {
        following.append(qMakePair(follower,followed));
        qDebug() << "Ora " << follower->getUsername() << " segue " << followed->getUsername();
    }
}

void Network::removeFollower(QSharedPointer<User> follower, QSharedPointer<User> followed) {
    bool found = false;
    auto it = following.begin();
    while (it!=following.end() && !found) {
        if ((it->first == follower) && (it->second == followed)) {
            it = following.erase(it);
            found = true;
            qDebug() << follower->getUsername() << " non segue più " << followed->getUsername();
        } else {
            ++it;
        }
    } 
}

bool Network::isFollowerOf(QSharedPointer<User> follower, QSharedPointer<User> followed) const {
    return following.contains(qMakePair(follower,followed)); 
}

QSet<QSharedPointer<User>> Network::getFollower(QSharedPointer<User> u) const{
       
    QSet<QSharedPointer<User>> res;
    
    for (auto it = following.cbegin(); it!=following.cend(); ++it) {
        if ((it->second == u) && !res.contains(it->first)) {
            res.insert(it->first);
        }
    }
    
    return res;
}

QSet<QSharedPointer<User>> Network::getFollowed(QSharedPointer<User> u) const {//get user followed by user `u`
        
    QSet<QSharedPointer<User>> res;
    
    for (auto it = following.cbegin(); it!=following.cend(); ++it) {
        if ((it->first == u) && !res.contains(it->second)) {
            res.insert(it->second);
        }
    }
    
    return res;
}

QSet<QSharedPointer<User>> Network::getUnion(const Network& net) const {
    return userlist.toSet() + net.userlist.toSet();
}

QSet<QSharedPointer<User>> Network::getIntersection(const Network& net) const {
    return userlist.toSet() & net.userlist.toSet();
}

//relative complement of this userlist set in net userlist set 
QSet<QSharedPointer<User>> Network::getRelativeComplement(const Network& net) const {
        return net.userlist.toSet() - userlist.toSet();
}

QSet<QSharedPointer<User>> Network::getSymmetricDifference(const Network& net) const {
    return getUnion(net) - getIntersection(net); 
}

Network::~Network() {
    qDebug() << "Eliminata la rete " << getName();
}
