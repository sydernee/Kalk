#ifndef NETWORK_H
#define NETWORK_H

#include <QMap>
#include <QList>
#include <QString>


class Network : public DataType {
private:
    QMap<User*> userlist;
public:

    void addUser(const User&);
    void removeUser(const User&);
    int calculateDistance(const User&, const User&, int) const;
    void addFollower(const User&,const User&);
    void removeFollower(const User&,const User&);
    bool isFollowerOf(const User&,const User&) const;
    QList getFollower(const User&) const;
    QList getFollowed(const User&) const;
};

#endif // NETWORK_H

