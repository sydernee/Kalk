package dataTypes;

import kalkException.*;
import java.util.AbstractMap;
import java.util.List;
import java.util.LinkedList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

public class Network extends DataType {
	
    private String name; //network name (e.g. Twitter, Instagram, LinQuedin)
    private List<User> userlist; // per mantenere l'ordine di inserimento, uso List e non Set
    private List<AbstractMap.SimpleEntry<User, User>> following; //first follows second

    //ctor
    public Network(String s) {
    	this(new HashSet<User>(),s);
    }
    public Network(Set<User> userlist) {
    	this(userlist,"");
    }
    public Network(Set<User> userlist, String name) {
        this.userlist = new LinkedList<User>(userlist);
        this.name = name;
        this.following = new LinkedList<AbstractMap.SimpleEntry<User, User>>(); 
    }
    
    public String getName() {return name;}
    
    public void setName(String name) {this.name=name;}
    
    public int size() {return userlist.size();}

    public void addUser(User u) {userlist.add(u);}
    
    public void printUsers() {
    	Iterator<User> it = userlist.listIterator();
    	while (it.hasNext()) {
    		User element = it.next();
    		System.out.println(element);
    	}
    }
    
    public boolean isUserOfTheNetwork(User u) {return userlist.contains(u);}
    
    public Set<User> getUsers() {return new HashSet<User>(userlist);}
    
    public void removeUser(User u) {
    	userlist.remove(u);
    	
    	Iterator<AbstractMap.SimpleEntry<User, User>> it = following.listIterator();
    	while (it.hasNext()) {
    		AbstractMap.SimpleEntry<User, User> element = it.next();
    		if (element.getKey() == u || element.getValue() == u)
    			it.remove();
    	}
    }
    
    public void removeUser(String s) {
    	boolean found = false;
    	
    	Iterator<User> it = userlist.listIterator();
    	while (it.hasNext() && !found) {
    		User element = it.next();
    		if (element.getUsername() == s) {
    			it.remove();
    			found = true;
    		}
    	}
    }
    
    public void addFollower(User follower, User followed) {
    	if (isUserOfTheNetwork(follower) && isUserOfTheNetwork(followed))
    		this.following.add(new AbstractMap.SimpleEntry<User, User>(follower,followed));
    }
    
    public void removeFollower(User follower, User followed) {
    	boolean found = false;
    	
    	Iterator<AbstractMap.SimpleEntry<User, User>> it = following.listIterator();
    	while(it.hasNext() && !found) {
    		AbstractMap.SimpleEntry<User, User> element = it.next();
    		if (element.getKey() == follower && element.getValue() == followed) {
    			it.remove();
    			found = true;
    		}
    	}
    }
    
    public boolean isFollowerOf(User follower, User followed) {
    	Iterator<AbstractMap.SimpleEntry<User, User>> it = this.following.listIterator();
    	while (it.hasNext()) {
    		AbstractMap.SimpleEntry<User, User> element = it.next();
    		if (element.getKey() == follower && element.getValue() == followed)
    			return true;
    	}
    	return false;
    }
    
    public Set<User> getFollower(User u) {
    	Set<User> res = new HashSet<User>();
    	Iterator<AbstractMap.SimpleEntry<User, User>> it = this.following.listIterator();
    	while (it.hasNext()) {
    		AbstractMap.SimpleEntry<User, User> element = it.next();
    		if (element.getValue() == u && !res.contains(element.getKey())) {
    			res.add(element.getKey());
    		}
    	}
    	return res;
    }
    
    public Set<User> getFollowed(User u) {
    	Set<User> res = new HashSet<User>();
    	Iterator<AbstractMap.SimpleEntry<User, User>> it = this.following.listIterator();
    	while (it.hasNext()) {
    		AbstractMap.SimpleEntry<User, User> element = it.next();
    		if (element.getKey() == u && !res.contains(element.getValue())) {
    			res.add(element.getValue());
    		}
    	}
    	return res;
    }

    // SET OPERATIONS
    Set<User> getUnion(Network network) {
    	Set<User> res = new HashSet<User>();
    	res.addAll(this.userlist);
    	res.addAll(network.userlist);
    	return res;
    }
    
    Set<User> getIntersection(Network network) {
    	//mantiene in userlist solo gli elementi in comune tra i due insiemi
    	Set<User> res = new HashSet<User>(this.userlist);
    	res.retainAll(network.userlist); 
    	return res;
    }
    
    Set<User> getRelativeComplement(Network network) { //B - A
    	Set<User> res = new HashSet<User>(network.userlist);
    	res.removeAll(this.userlist);
    	return res;
    }
    
    Set<User> getSymmetricDifference(Network network) {
    	Set<User> res = new HashSet<User>(this.userlist);
	    res.addAll(network.userlist);
	    Set<User> tmp = new HashSet<User>(this.userlist);
	    tmp.retainAll(network.userlist);
	    res.removeAll(tmp);
	    return res;
    }
}
