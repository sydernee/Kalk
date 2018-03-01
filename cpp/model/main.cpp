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
    
    return 0;
}

