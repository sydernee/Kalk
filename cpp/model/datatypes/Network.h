#ifndef NETWORK_H
#define NETWORK_H

#include "../DataType.h"
#include <QDebug>
#include <QSet>
#include <QPair>
#include <QList>
#include <QString>
#include <QSharedPointer>
#include "User.h"


class Network : public DataType {
private:
    QString name; //network name (e.g. Twitter, Instagram, LinQuedin)
    QList<QSharedPointer<User>> userlist; // per mantenere l'ordine di inserimento, uso QList e non QSet
    QList<QPair<QSharedPointer<User>, QSharedPointer<User>>> following; //first follows second
public:
    Network(QString n);
    Network(QSet<QSharedPointer<User>>, QString="");
    QString getName();
    void setName(QString);
    unsigned int size() const;

    virtual void addUser(QSharedPointer<User>);
    virtual bool isUserOfTheNetwork(QSharedPointer<User>) const;
    virtual QSet<QSharedPointer<User>> getUsers() const;
    virtual void removeUser(QSharedPointer<User>);
    virtual void removeUser(const QString); 
    virtual void addFollower(QSharedPointer<User>, QSharedPointer<User>);
    virtual void removeFollower(QSharedPointer<User>, QSharedPointer<User>);
    virtual bool isFollowerOf(QSharedPointer<User>, QSharedPointer<User>) const;
    virtual QSet<QSharedPointer<User>> getFollower(QSharedPointer<User>) const;
    virtual QSet<QSharedPointer<User>> getFollowed(QSharedPointer<User>) const;

    // SET OPERATIONS
    virtual QSet<QSharedPointer<User>> getUnion(const Network&) const;
    virtual QSet<QSharedPointer<User>> getIntersection(const Network&) const;
    virtual QSet<QSharedPointer<User>> getRelativeComplement(const Network&) const;  // B - A  
    virtual QSet<QSharedPointer<User>> getSymmetricDifference(const Network&) const;
    
    virtual ~Network();
};

#endif // NETWORK_H

