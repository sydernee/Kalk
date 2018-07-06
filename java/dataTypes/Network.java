package dataTypes;

import kalkException.*;
import java.util.AbstractMap;

public class Network extends DataType {
private:
    String name; //network name (e.g. Twitter, Instagram, LinQuedin)
    List<User> userlist; // per mantenere l'ordine di inserimento, uso List e non Set
    List<AbstractMap.SimpleEntry<User, User>> following; //first follows second
public:
    //ctor
    Network(String s) {this(new HashSet<>(),"");}
    Network(Set<User> userlist) {this(userlist,"");}
    Network(Set<User> userlist, String name) {
        this.userlist = userlist;
        this.name = name;
        this.following = new LinkedList<>(); 
    }
    
    String getName() {return name;}
    void setName(String name) {this.name=name;}
    int size() {return userlist.size();}

    void addUser(User u) {userlist.add(u);}
    bool isUserOfTheNetwork(User);
    Set<User> getUsers();
    void removeUser(User);
    void removeUser(String); 
    void addFollower(User, User);
    void removeFollower(User, User);
    bool isFollowerOf(User, User);
    Set<User> getFollower(User);
    Set<User> getFollowed(User);

    // SET OPERATIONS
    Set<User> getUnion(Network);
    Set<User> getIntersection(Network);
    Set<User> getRelativeComplement(Network);  // B - A  
    Set<User> getSymmetricDifference(Network);
    public static void main(String[] args) {}
}
