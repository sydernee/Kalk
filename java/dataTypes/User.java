package dataTypes;

//import kalkException.*;

public class User {
	//fields
    private final String username;
    private String name;
    private String surname;
   
    // ctors
    User(final String username) {this(username, "", "");}
    User(String username, final String name, final String surname) {
        this.username = username;
        this.name = name;
        this.surname = surname;
    }
    
    String getUsername() {return username;}
    String getName() {return name;}
    String getSurname() {return surname;}
    
    @Override
    public String toString() {
		return username;
    }
   
    void setName(final String n) {name=n;}
    void setSurname(final String s) {surname=s;}
}


