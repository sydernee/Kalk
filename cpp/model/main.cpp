#include "DataType.h"
#include "datatypes/Matrix.h"
#include "datatypes/SquareMatrix.h"
#include <iostream>

int main(){
    
    // 2x2
    SquareMatrix* m1 = new SquareMatrix(2,{2,-3,1,3});
    std::cout << *m1;
    std::cout << "Determinante: ";
    std::cout << m1->determinant() << std::endl; 
    
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
    std::cout << m2->determinant() << std::endl; 
    
    SquareMatrix r2ridotta = m2->getMinor(0,1);
    std::cout << r2ridotta;
    
    /// 5x5
    SquareMatrix* m3 = new SquareMatrix(5,{0,0,0,1,2,1,3,2,-1,0,4,3,2,1,5,1,-1,2,1,3,0,2,3,-1,4});
    std::cout << *m3;
    std::cout << "Determinante: ";
    std::cout << m3->determinant() << std::endl; 
    
    // trasposta di m3
    std::cout << "Test SquareMatrix trasposta: " << std::endl;
    std::cout << "Originale:" << std::endl << *m3;
    SquareMatrix* m3t = m3->transposed();
    std::cout << "Trasposta:" << std::endl << *m3t;
    
    // trasposta di m3
    std::cout << "Test Matrix trasposta: " << std::endl;
    Matrix* m4 = new Matrix(5,5,{0,0,0,1,2,1,3,2,-1,0,4,3,2,1,5,1,-1,2,1,3,0,2,3,-1,4});
    std::cout << "Originale:" << std::endl << *m4;
    Matrix* m4t = m4->transposed();
    std::cout << "Trasposta:" << std::endl << *m4t;    
    
<<<<<<< HEAD
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
    std::cout << "Scambio prima con il doppio della terza" << std::endl << mswap;
=======
    //matrice identità
    std::cout << "Test Matrice identità: " << std::endl;
    SquareMatrix m5 = SquareMatrix::identityMatrix(5);
    std::cout << "Originale:" << std::endl << m5;

    //matrice di zeri
    std::cout << "Test Matrice di zeri: " << std::endl;
    SquareMatrix m6 = SquareMatrix::zeroMatrix(5);
    std::cout << "Originale:" << std::endl << m6;

>>>>>>> eab6f84f4557ced9b59a16a5b6e78fe5833fdc51
    return 0;
}

