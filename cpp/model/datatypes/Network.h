#ifndef NETWORK_H
#define NETWORK_H

#include "../DataType.h"
#include <QDebug>
#include <QSet>
#include <QPair>
#include <QList>
#include <QString>
#include "User.h"


class Network : public DataType {
private:
    QString name; //network name (e.g. Twitter, Instagram, LinQuedin)
    QList<const User*> userlist;
    QList<QPair<const User*,const User*> > following; //first follows second
public:
    Network(QString n);
    QString getName();
    void addUser(User*);
    void removeUser(User*);
    void removeUser(const QString); 
    int calculateDistance(const User&, const User&) const;
    void addFollower(const User&,const User&);
    void removeFollower(const User&,const User&);
    bool isFollowerOf(const User&,const User&) const;
    QSet<const User*> getFollower(const User&) const;
    QSet<const User*> getFollowed(const User&) const;
};

#endif // NETWORK_H

