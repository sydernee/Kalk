#include "Network.h"

Network::Network(QString n) : name(n),userlist() {}

QString Network::getName() {return name;}


void Network::addUser(User* u) { //meh
    if (!userlist.contains(u)) {
       userlist.append(u);
    }
}

void Network::removeUser(User* u) {
    userlist.removeAll(u);
}

void Network::removeUser(const QString u) {
    bool found = false;
    for (auto it = userlist.begin(); it != userlist.end() && found == false; ++it) {
        if ((*it)->getUsername() == u) {
            userlist.erase(it); //devo deallocare?
            found = false;
        }
    }
    
}

//[static]
//QList<T> QList::fromSet(const QSet<T> &set)
//Returns a QList object with the data contained in set. The order of the elements in the QList is undefined.
int Network::calculateDistance(const User& u1, const User& u2) const { //TODO
 //empty
    
    return 0;
} 

// ritorna -1 se non è stato non trovato


void Network::addFollower(const User& follower,const User& followed) {
    following.append(qMakePair(&follower,&followed));
}

bool Network::isFollowerOf(const User& follower,const User& followed) const{
    return following.contains(qMakePair(&follower,&followed));
}



QSet <const User*> Network::getFollower(const User& u) const{
    QSet<const User*> res;
    
    for (auto it = following.cbegin(); it!=following.cend(); ++it) {
        if ((it->second == &u) && !res.contains(it->first)) {
            res.insert(it->first);
        }
    }
    
    return res;
}

QSet<const User*> Network::getFollowed(const User& u) const{ //get user followed by user `u`
    QSet<const User*> res;
    
    for (auto it = following.cbegin(); it!=following.cend(); ++it) {
        if ((it->first == &u) && !res.contains(it->second)) {
            res.insert(it->second);
        }
    }
    
    return res;
}




