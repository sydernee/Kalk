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


    //network
    Network* facebook = new Network("facebook");
    qDebug() << facebook->getName();
    
    // creo gli utenti della rete
    User* massimo = new User("massimo");
    User* andrea = new User("andrea");
    User* michele = new User("michele");
    User* nicola = new User("nicola");
    
    // gli aggiungo alla rete
    facebook->addUser(massimo);
    facebook->addUser(andrea);
    facebook->addUser(michele);
    facebook->addUser(nicola);
    facebook->addUser(nicola); //tento doppia aggiunta
    
    //aggiungo le amicizie 
    facebook->addFollower(*andrea,*michele); // andrea follower di michele
    facebook->addFollower(*massimo,*michele);
    facebook->addFollower(*michele,*nicola);
    facebook->addFollower(*michele,*andrea);
    
    // stampo i follower di michele
     QSet<const User*> fr = facebook->getFollower(*michele);
    
    foreach (const User* follower, fr) {
        qDebug() << follower->getUsername();
    }
    
    // stampo le persone seguite da michele
    QSet<const User*> fd = facebook->getFollowed(*michele);
    
    foreach (const User* followed, fd) {
        qDebug() << followed->getUsername();
    } 
     
    // controllo se è follower
    qDebug() << facebook->isFollowerOf(*nicola,*michele); // false
    qDebug() << facebook->isFollowerOf(*michele,*nicola); // true
    
    // No duplicati, stampa 2
    QSet<User*> si;
    si.insert(massimo);
    si.insert(massimo);
    si.insert(andrea);
    qDebug() << si.count();
    foreach (const User* u, si) {
        qDebug() << u->getUsername();
    }
    
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
