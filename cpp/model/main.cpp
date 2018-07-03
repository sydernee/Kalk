#include "DataType.h"
#include "datatypes/Matrix.h"
#include "datatypes/SquareMatrix.h"
#include "datatypes/SparseMatrix.h"
#include "datatypes/Network.h"
#include "datatypes/User.h"
#include <iostream>

int main(){
    
    // 2x2
    SquareMatrix* m1 = new SquareMatrix(2,{2,-3,1,3});
    std::cout << *m1;
    std::cout << "Determinante: ";
    std::cout << m1->determinant() << std::endl << std::endl; 
    
    /*
      m2:
        0 2 -3
        0 1 3
        2 0 -1
    */
    // 3x3
    SquareMatrix* m2 = new SquareMatrix(3,{0,2,-3,0,1,3,2,0,-1});
    std::cout << *m2;
    std::cout << "Determinante: ";
    std::cout << m2->determinant() << std::endl << std::endl; 
    
    SquareMatrix r2ridotta = m2->getMinor(0,1);
    std::cout << r2ridotta;
    
    /// 5x5
    SquareMatrix* m3 = new SquareMatrix(5,{0,0,0,1,2,1,3,2,-1,0,4,3,2,1,5,1,-1,2,1,3,0,2,3,-1,4});
    std::cout << *m3;
    std::cout << "Determinante: ";
    std::cout << m3->determinant() << std::endl << std::endl; 
    
    // trasposta di m3
    std::cout << "Test SquareMatrix trasposta: " << std::endl;
    std::cout << "Originale:" << std::endl << *m3;
    SquareMatrix* m3t = m3->transposed();
    std::cout << "Trasposta:" << std::endl << *m3t << std::endl;
    
    // trasposta di m3
    std::cout << "Test Matrix trasposta: " << std::endl;
    Matrix* m4 = new Matrix(5,5,{0,0,0,1,2,1,3,2,-1,0,4,3,2,1,5,1,-1,2,1,3,0,2,3,-1,4});
    std::cout << "Originale:" << std::endl << *m4;
    Matrix* m4t = m4->transposed();
    std::cout << "Trasposta:" << std::endl << *m4t << std::endl;    
    
    // 3 operazioni elementari
    SquareMatrix m5r = *m3;
    std::cout << "Originale:" << std::endl << m5r;
    m5r.swapRows(0,2);
    std::cout << "Scambio prima e terza riga:" << std::endl << m5r;
    SquareMatrix m5c = *m3;
    std::cout << "Originale:" << std::endl << m5c;
    m5r.swapCols(0,2);
    std::cout << "Scambio prima e terza colonna:" << std::endl << m5c;
    SquareMatrix mswap = *m3; 
    mswap.substituteRow(0,2,0.5);
    std::cout << "Scambio prima con il doppio della terza" << std::endl << mswap << std::endl;
    
    //matrice identità
    std::cout << "Test Matrice identità: " << std::endl;
    SquareMatrix m5 = SquareMatrix::identityMatrix(5);
    std::cout << "Originale:" << std::endl << m5 << std::endl;

    //matrice di zeri
    std::cout << "Test Matrice di zeri: " << std::endl;
    SquareMatrix m6 = SquareMatrix::zeroMatrix(5);
    std::cout << "Originale:" << std::endl << m6 << std::endl;

    //matrice sparsa
    std::cout << "Test Matrice sparsa: " << std::endl;
    SparseMatrix* m7 = new SparseMatrix(4, 4, {0,0,1,0,0,2,0,0,0,0,3,2,0,0,0,4});
    std::cout << *m7;
    std::cout << "Sparsità: " << m7->getSparsity() << std::endl;
    std::cout << "La matrice è densa? ";
    if (m7->isDense())
    	std::cout << "True" << std::endl;
    else 
    	std::cout << "False" << std::endl << std::endl;
    
    //std::vector<std::initializer_list<double>>
    Matrix* m8 = new Matrix(3, 4, {{1,3}, {1,4,2,5,6}, {3,0,-1,2}});
    std::cout << *m8;
    
    std::cout << std::endl;


    //network facebook
    Network* facebook = new Network("facebook");
    qDebug() << facebook->getName();
    
    // creo gli utenti della rete Facebook
    QSharedPointer<User> massimo = QSharedPointer<User>(new User("massimo"));
    QSharedPointer<User> andrea = QSharedPointer<User>(new User("andrea"));
    QSharedPointer<User> michele = QSharedPointer<User>(new User("michele"));
    QSharedPointer<User> nicola = QSharedPointer<User>(new User("nicola"));
    QSharedPointer<User> ettore = QSharedPointer<User>(new User("ettore"));
    QSharedPointer<User> achille = QSharedPointer<User>(new User("achille"));
    
    // gli aggiungo alla rete
    facebook->addUser(massimo);
    facebook->addUser(andrea);
    facebook->addUser(michele);
    facebook->addUser(nicola);
    facebook->addUser(nicola); //tento doppia aggiunta
    facebook->addUser(ettore);
    facebook->addUser(achille);
	 
    qDebug() << "Stampo il numero di utenti di facebook";
    qDebug() << facebook->size();
    
    // stampo tutti i nominativi degli utenti di facebook 
    QSet<QSharedPointer<User>> ulist = facebook->getUsers();
    qDebug() << "Utenti di Facebook";
    foreach (QSharedPointer<User> usr, ulist) {
        qDebug() << usr->getUsername();
    }
    qDebug() << "FINE";

    //aggiungo le amicizie 
    facebook->addFollower(andrea,michele); // andrea follower di michele
    facebook->addFollower(andrea,nicola);    
    facebook->addFollower(massimo,michele);
    facebook->addFollower(michele,nicola);
    facebook->addFollower(michele,andrea);
    facebook->addFollower(ettore,achille);
    facebook->addFollower(andrea,ettore);
    facebook->addFollower(ettore,michele);

    //elimino Ettore e Achille dalla rete    
    facebook->removeUser(ettore);
    facebook->removeUser("achille");
  
    // stampo i follower di michele
    QSet<QSharedPointer<User>> fr = facebook->getFollower(michele);
	qDebug() << "Follower di Michele in Facebook";
    foreach (QSharedPointer<User> follower, fr) {
        qDebug() << follower->getUsername();
    }
	qDebug() << "FINE";

    //rimuovo nicola dalle persone seguite da andrea
    qDebug() << "rimuovo nicola dalle persone seguite da andrea";
    facebook->removeFollower(andrea,nicola);
 
    // stampo le persone seguite da andrea   
	qDebug() << "Followed da Andrea in Facebook";
    QSet<QSharedPointer<User>> fd = facebook->getFollowed(andrea);
    
    foreach (QSharedPointer<User> followed, fd) {
        qDebug() << followed->getUsername();
    } 
	qDebug() << "FINE";
     
    // controllo se è follower
    qDebug() << facebook->isFollowerOf(nicola,michele); // false
    qDebug() << facebook->isFollowerOf(michele,nicola); // true
    
    // No duplicati, stampa 2 (che sono massimo e andrea)
    QSet<QSharedPointer<User>> si;
    si.insert(massimo);
    si.insert(massimo);
    si.insert(andrea);
    qDebug() << si.count();
    foreach (QSharedPointer<User> u, si) {
        qDebug() << u->getUsername();
    }

    // istanzio la rete twitter
    Network* twitter = new Network("twitter");
    qDebug() << twitter->getName();    

    // creo gli utenti della rete Twitter
    QSharedPointer<User> orazio = QSharedPointer<User>(new User("Ser Orazio"));
    QSharedPointer<User> pomponio = QSharedPointer<User>(new User("Re Pomponio Mela"));    
    QSharedPointer<User> andy = andrea;
    
    // gli aggiungo alla rete
    twitter->addUser(orazio);
    twitter->addUser(pomponio);
    twitter->addUser(andy);
    twitter->addUser(michele);    

    //aggiungo le amicizie 
    twitter->addFollower(andrea,michele); // andrea follower di michele
    twitter->addFollower(andrea,nicola);    
    twitter->addFollower(massimo,michele);

    // stampo i follower di michele
    QSet<QSharedPointer<User>> tmf = twitter->getFollower(michele);
	qDebug() << "Follower di Michele in Twitter";
    foreach (QSharedPointer<User> follower, tmf) {
        qDebug() << follower->getUsername();
    }
	qDebug() << "FINE";    

    //unisco facebook e twitter
    QSet<QSharedPointer<User>> facetwitter = facebook->getUnion(*twitter);
    
    // stampo tutti i nominativi degli utenti di facebook 
    QSet<QSharedPointer<User>> faceunionlist = facebook->getUsers();
    qDebug() << "Utenti di Facebook";
    foreach (QSharedPointer<User> usr, faceunionlist) {
        qDebug() << usr->getUsername();
    }
    qDebug() << "FINE";
    // stampo tutti i nominativi degli utenti di facebook 
    QSet<QSharedPointer<User>> twitterunionlist = twitter->getUsers();
    qDebug() << "Utenti di Twitter";
    foreach (QSharedPointer<User> usr, twitterunionlist) {
        qDebug() << usr->getUsername();
    }
    qDebug() << "FINE";
    // stampo tutti i nominativi degli utenti di facebook 
    qDebug() << "Utenti di Facebook uniti agli utenti di Twitter";
    foreach (QSharedPointer<User> usr, facetwitter) {
        qDebug() << usr->getUsername();
    }
    qDebug() << "FINE";

    //unisco facebook e twitter
    QSet<QSharedPointer<User>> facetwitterIntersection = facebook->getIntersection(*twitter);
    // stampo tutti i nominativi degli utenti di facebook 
    qDebug() << "Intersezione tra gli utenti di Facebook e gli utenti di Twitter";
    foreach (QSharedPointer<User> usr, facetwitterIntersection) {
        qDebug() << usr->getUsername();
    }
    qDebug() << "FINE";


    //unisco facebook e twitter
    QSet<QSharedPointer<User>> facetwitterRelativeComplement = facebook->getRelativeComplement(*twitter);
    // stampo tutti i nominativi degli utenti di facebook 
    qDebug() << "Complemento relativo di Facebook in Twitter";
    foreach (QSharedPointer<User> usr, facetwitterRelativeComplement) {
        qDebug() << usr->getUsername();
    }
    qDebug() << "FINE";

    //unisco facebook e twitter
    QSet<QSharedPointer<User>> facetwitterdiffsym = facebook->getSymmetricDifference(*twitter);
    // stampo tutti i nominativi degli utenti di facebook 
    qDebug() << "Differenza simmetrica tra gli utenti di Facebook e gli utenti di Twitter";
    foreach (QSharedPointer<User> usr, facetwitterdiffsym) {
        qDebug() << usr->getUsername();
    }
    qDebug() << "FINE";
    
    Network* telegram = new Network(facebook->getUnion(*twitter));
    telegram->setName("Telegram");
    // stampo tutti i nominativi degli utenti di facebook     
    qDebug() << "Elenco utenti di " << telegram->getName();
    QSet<QSharedPointer<User>> telegramusers = telegram->getUsers();
    foreach (QSharedPointer<User> usr, telegramusers) {
        qDebug() << usr->getUsername();
    }
    qDebug() << "FINE";
    /**/
    //elimino le reti
    delete facebook;
    delete twitter;
    delete telegram;


    // yep, non va bene modificare il QSet nel loop
    QSet<QString> set;
    set << "January";
    
    bool first = true;
    QSet<QString>::iterator i;
    for (i = set.begin(); i != set.end(); ++i) {
       if (first) {
          set << "March";
          set << "April";
          set << "June";
          set << "July";
          set << "August";
          set << "September";
          set << "October";
          set << "November";//*/
           first = false;
       }
      
       qDebug() << *i;
    }
    return 0;
}
